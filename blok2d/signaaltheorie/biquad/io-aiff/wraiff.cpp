/*
    WRAIFFPP 0.25 (may 18, 2015), a tiny audiofile writing utility in C++.
    Latest version at http://home.hku.nl/~pieter.suurmond/EDU/cpp/wraiffpp/.

    Users of the WRAIFF utility, read the API specification in wraiff.hpp,
    since, as long as no errors occur, there is no need to look inside this 
    implementation file.

    Copyright (c) 2004, 2005, 2006, 2007, 2015 - Pieter Suurmond

    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files
    (the "Software"), to deal in the Software without restriction,
    including without limitation the rights to use, copy, modify, merge,
    publish, distribute, sublicense, and/or sell copies of the Software,
    and to permit persons to whom the Software is furnished to do so,
    subject to the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    Any person wishing to distribute modifications to the Software is
    requested to send the modifications to the original developer so that
    they can be incorporated into the canonical version.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
    ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
    CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

    KNOWN BUG: The destructor may call close(), which actually does a little
               more than only closing the file: it first tries to rewite the
               AIFF header to update the number of sampleframes written.
               When this fails, it throws an exception, and, in C++, it is
               forbidden for a destructor to throw!
*/

#include <cmath>                    // For IEEE exponents.
#include <string>                   // For copy of filename.
#include <fstream>                  // Necessary for ofstream.
#include <iostream>
using namespace std;

#include "wraiff.hpp"               // Read the WRAIFF specifications!

class WRAIFF_impl
{
  friend class WRAIFF;              // Necessary since most below is private.

  public:

    WRAIFF_impl()
    {
    }

    ~WRAIFF_impl()
    {
    if (this->f.is_open())
        {
        this->close();              // ALARM: close() may throw an exception!
        // Silently close file (try to rewrite AIFF header).
        // cerr << "WRAIFFPP closed '" << this->name << "' for you!\n";
        }
    }

  private:

    ofstream        f;          // Output file stream (class member).
    string          name;       // Internal copy of the filename (class member).
                                //                          Big endians on file:
    unsigned long   frames;     // Total number of frames    (at least 4 bytes).
    unsigned short  channels;   // Number of sound channels  (at least 2 bytes).
    unsigned short  bits;       // Number of bits resolution (at least 2 bytes).
    unsigned short  bytes;      // Derived.
    double          rate;       // Sampling rate in cycles per second.
    double          scale;      // For double to integer conversion.
    long            underflow;  // Values that may not be exceeded.
    long            overflow;
    unsigned long   clipped;    // Number of clipped samples (errors 2 and 3).
    static const                               // Not more than 2 hours at CD-
    unsigned long   max_frames = 317520000L;   // quality to protect harddisks.

 // Write 2 byte short, MSB first. Works ok on both big and little endians.
    void write_short_bin(unsigned short u0)
    {   
        this->f.put(u0 >> 8);
        this->f.put(u0);
    }

 // Writes a 4 byte unsigned long, MSB first, to file. Both this and the above
 // function are called by write_header() several times.
    void write_long_bin(unsigned long u0)
    {
        unsigned long u1 = u0 >> 8;
        unsigned long u2 = u1 >> 8;

        this->f.put(u2 >> 8);
        this->f.put(u2);
        this->f.put(u1);
        this->f.put(u0);
    }

    /*  C O N V E R T   T O   I E E E   E X T E N D E D
        Machine-independent I/O routines for IEEE floating-point numbers.
        NaN's and infinities are converted to HUGE_VAL or HUGE, which
        happens to be infinity on IEEE machines.  Unfortunately, it is
        impossible to preserve NaN's in a machine-independent way.
        Infinities are, however, preserved on IEEE machines.
        These routines have been tested on the following machines:
            Apple Macintosh, MPW 3.1 C compiler
            Apple Macintosh, THINK C compiler
            Silicon Graphics IRIS, MIPS compiler
            Cray X/MP and Y/MP
            Digital Equipment VAX
        Implemented by Malcolm Slaney and Ken Turkowski.
        Malcolm Slaney contributions during 1988-1990 include big- and little-
        endian file I/O, conversion to and from Motorola's extended 80-bit
        floating-point format, and conversions to and from IEEE single-
        precision floating-point format.
        In 1991, Ken Turkowski implemented the conversions to and from
        IEEE double-precision format, added more precision to the extended
        conversions, and accommodated conversions involving +/- infinity,
        NaN's, and denormalized numbers. 
    */
    void to_ieee_extd(double num, char *bytes)
    {
#ifndef HUGE_VAL
# define HUGE_VAL HUGE
#endif   /* HUGE_VAL */
#define FloatToUnsigned(f) ((unsigned long)(((long)(f-2147483648.0))+2147483647L)+1)

        int           sign, expon;
        double        fMant, fsMant;
        unsigned long hiMant, loMant;

        if (num < 0)
            {
            sign = 0x8000;
            num *= -1;
            }
        else
            {
            sign = 0;
            }
        if (num == 0)
            {
            expon = 0; hiMant = 0; loMant = 0;
            }
        else
            {
            fMant = frexp(num, &expon);
            if ((expon > 16384) || !(fMant < 1))
                {                                            // Infinity or NaN.
                expon = sign|0x7FFF; hiMant = 0; loMant = 0; // infinity.
                }
            else
                {                   /* Finite */
                expon += 16382;
                if (expon < 0)
                    {               /* denormalized */
                    fMant = ldexp(fMant, expon);
                    expon = 0;
                    }
                expon |= sign;
                fMant  = ldexp(fMant, 32);          
                fsMant = floor(fMant); 
                hiMant = FloatToUnsigned(fsMant);
                fMant  = ldexp(fMant - fsMant, 32); 
                fsMant = floor(fMant); 
                loMant = FloatToUnsigned(fsMant);
                }
            }
        bytes[0] = expon >> 8;
        bytes[1] = expon;
        bytes[2] = static_cast<char>(hiMant >> 24); // Explicit casts.
        bytes[3] = static_cast<char>(hiMant >> 16);
        bytes[4] = static_cast<char>(hiMant >> 8);
        bytes[5] = static_cast<char>(hiMant);
        bytes[6] = static_cast<char>(loMant >> 24);
        bytes[7] = static_cast<char>(loMant >> 16);
        bytes[8] = static_cast<char>(loMant >> 8);
        bytes[9] = static_cast<char>(loMant);
    }

 // Private method, only used within this file. Called by open() and close().
    void write_header() 
    {
        char          buf[10];
        unsigned long numBytes = this->frames * static_cast<unsigned long>
                                 (this->bytes * this->channels);
        this->f << "FORM";                       // Write IFF header.
        this->write_long_bin(8 + 18 +            // COMM hdr + COMM chunk +
                             8 + 12 + numBytes); // SSND hdr + SSND chunk + numBytes.
        this->f << "AIFF";                       // File type.
                                                 // COMM chunk ----------------------
        this->f << "COMM";                       // Describes encoding and #frames.
        this->write_long_bin(18L);               // COMM chunk size.
        this->write_short_bin(this->channels);   // Number of channels.
        this->write_long_bin(this->frames);      // Number of sampleframes.
        this->write_short_bin(this->bits);       // Sample width, in bits.
        this->to_ieee_extd(this->rate, buf);
        this->f.write(buf, 10);                  // Samplerate in cycles per second.
                                                 // SSND chunk ----------------------
        this->f << "SSND";
        this->write_long_bin(8 + numBytes);      // Chunk size.
        this->write_long_bin(0L);                // Offset.
        this->write_long_bin(0L);                // Block size.
    }

 // Called by WRAIFF::open(const char*, double, short, short) and by open-constructor
 // WRAIFF(const char*, double, short, short).
    void open(const char* filename, double samplerate, short channels, short bits)
    {
        if (!filename)                           // First check arguments.
            throw "No filename!\n";
        if (!*filename)
            throw "Empty filename!\n";
        if ((samplerate < 1.0) || (samplerate > 128000.0))
            throw "Samplerate out of range!\n";
        if ((channels < 1) || (channels > 128))
            throw "Too many or too less channels!\n";
        if ((bits & 7) || (bits < 8) || (bits > 64))
            throw "Wrong number of bits!\n";

        if (this->f.is_open())
            throw "An AIFF file is already open!\n";

        try {
            this->name = filename; // Try to store a copy of the filename so the
            }                      // caller is not forced to keep it in memory.
        catch (...)
            {
            throw "Not enough memory (to hold a copy of the filename)!\n";
            }

        this->f.open(filename, ios::binary);        // ios::out + ios::trunc are
        if (!(this->f.is_open() && this->f.good())) // default for ofstream.
            throw "Could not open AIFF file!\n";
        
        this->rate      = samplerate;
        this->channels  = channels;
        this->bits      = bits;
        this->bytes     = bits >> 3;                             // Redundant.
        this->scale     = pow(2.0, static_cast<double>(bits-1)); // 1 bit less for sign.
        this->overflow  = -1L + static_cast<long>(this->scale);
        this->underflow =  0L - static_cast<long>(this->scale);
        this->clipped   =  0L;
        this->frames    = this->max_frames; // Set to max size initially.

        this->write_header();     // Writes the above params to file.
        this->frames = 0L;
        if (!this->f.good())      // Will write again at closing.
            {
            this->f.close();      // this->name is a class-member (no need to cleanup).
            throw "Failed to write AIFF header!\n";
            }
    }

 // Should be called after open() to rewrite the header and close the open file.
    void close()
    {
        if (!this->f.is_open())
            throw "No AIFF file currently open!\n";
        if (!this->f.good())
            {
            this->f.close();
            throw "AIFF file gone bad. No header-rewrite!\n";
            }
        this->f.seekp(0);           // Rewind file.
        if (!this->f.good())
            {
            this->f.close();
            throw "Failed to rewind AIFF file!\n";
            }
        this->write_header();       // Rewrite header if rewind ok.
        if (!this->f.good())
            {
            this->f.close();
            throw "Failed to rewrite AIFF header!\n";
            }
        this->f.close();            // But always try to close.
        if (!this->f.good())
            throw "Failure during closing AIFF file!\n";
    }

 // Called by all write functions (inline hopefully speeds it up a bit).
    template <typename INPUT_TYPE>
    inline void test_args(const INPUT_TYPE* audio, long frames)
    {   
        if (!audio || (frames < 0L))
            throw "Wrong argument(s)!\n";
        if (!this->f.is_open())
            throw "No AIFF file currently open!\n";
    }
                          // MAYBE the word 'const' is wrong in these templates?
 // Code generator for writing floats and doubles.
    template <typename INPUT_TYPE>
    void write_fp(const INPUT_TYPE* audio, long frames)
    {
        test_args(audio, frames); // May throw.

        char            buff[8];
        unsigned long   clppd = this->clipped;
        unsigned long   frms = this->frames; // Help-var to throw only once.
        long            fr = frames;
        while (fr--)
            {
            short ch = this->channels;
            while (ch--)
                {
                long    a;          // Long should at least be 32 bit.
                short   b;          // Correct rounding of bipolar signals.
                                    // For example, 8 bits: +125.4 -> +125.
                if (*audio < 0.0)                        // +125.8 -> +126.
                    {
                    a = static_cast<long>((this->scale * (*audio++)) - 0.5);
                    if (a < this->underflow)             // -125.9 -> -126.
                        {                                // -125.2 -> -125.
                        a = this->underflow;             // Clip instead of
                        this->clipped++;                 // drastic sign-swap.
                        }                       // Count over- and underflows.
                    }
                else
                    {
                    a = static_cast<long>((this->scale * (*audio++)) + 0.5);
                    if (a > this->overflow)
                        {
                        a = this->overflow;
                        this->clipped++;
                        }
                    }
                for (b = 0; b < this->bytes; b++)  // LIFO buffer.
                    {
                    buff[b] = static_cast<char>(a & 0xFF);
                    a >>= 8;                // On little endians, these two
                    }                       // b-loops do the byte-swapping.
                while (b--)                 // On big endian processors, no-
                    {                       // thing effectively happens here.
                    this->f.put(buff[b]);
                    }
                }
            }
        this->frames += frames;                 // Increment frame-counter.
        if (this->f.bad())
            throw "AIFF file gone bad!\n";
        if (this->clipped && !clppd)            // Only report first clip.
            throw "Clipped!\n";
        if (this->frames > this->max_frames)    // Care for your harddisk.
            {
            if (frms <= this->max_frames)       // Don't repeat.
                throw "AIFF file growing huge!\n";
            }
    }

 // Code generator for writing signed chars, shorts, ints and longs.
    template <typename INPUT_TYPE> 
    void write_int(const INPUT_TYPE* audio, long frames)
    {
        test_args(audio, frames); // May throw.

        char            buff[8];
        unsigned long   clppd = this->clipped;
        unsigned long   frms = this->frames;
        long            fr = frames;
        while (fr--)
            {
            short ch = this->channels;
            while (ch--)
                {
                short b;
                long  a = static_cast<long>(*audio++);  // Long should at
                                                        // least be 32 bit.
                if (a < this->underflow)
                    {
                    a = this->underflow;                // Clip instead of
                    this->clipped++;                    // drastic sign-swap.
                    }
                else if (a > this->overflow)
                    {
                    a = this->overflow;             // Count over/underflows.
                    this->clipped++;
                    }
                for (b = 0; b < this->bytes; b++)  // LIFO buffer.
                    {
                    buff[b] = static_cast<char>(a & 0xFF);
                    a >>= 8;                // On little endians, these two
                    }                       // b-loops do the byte-swapping.
                while (b--)                 // On big endian processors, no-
                    {                       // thing effectively happens here.
                    this->f.put(buff[b]);
                    }
                }
            }
        this->frames += frames;                 // Increment frame-counter.
        if (this->f.bad())
            throw "AIFF file gone bad!\n";
        if (this->clipped && !clppd)            // Only report first clip.
            throw "Clipped!\n";
        if (this->frames > this->max_frames)    // Care for your harddisk.
            {
            if (frms <= this->max_frames)       // Don't repeat.
                throw "AIFF file growing huge!\n";
            }
    }

 // Print file statistics to cout, some textfile, or some stringstream.
    void info(ostream& to)
    {
        double             secs;
        static const char* line = "--------------------------------------\n";

        if (!to)
            throw "NULL argument!\n";
        if (!this->f.is_open()) // Values cannot be trusted (if never opened).
            throw "No AIFF file currently open!\n";
        to << line;
        //----------------------------------- OPEN FILE: -----------------
        to << "   AIFF file: " << this->name     << "\n";
        to << "    channels: " << this->channels << "\n";
        to << "      frames: " << this->frames   << "\n";
        to << "        bits: " << this->bits     << "\n";
        to << "  samplerate: " << this->rate     << " Hz\n";
        //----------------------------------- DERIVED INFO: --------------
        to << " bytes/frame: " << this->channels * this->bytes << "\n";
        to << "    filesize: " << 8 + 18 + 8 + 12 + (8) +
              (this->frames * this->bytes * this->channels) << " bytes\n";
        to << "    duration: ";
        secs = static_cast<double>(this->frames) / this->rate;
        if (secs >= 3600.0) to << secs/3600.0 << " hours\n";
        if (secs >= 60.0)   to << secs/60.0   << " minutes\n";
        else                to << secs        << " seconds\n";
        //----------------------------------- UNDERFLOWS+OVERFLOWS: ------
        if (this->clipped)
            {
            to << "     clipped: " << this->clipped << " sample";
            if (this->clipped > 1L) to << 's'; // Plural.
            to << "!\n";
            }
        to << line;
    }
};

WRAIFF::WRAIFF()                        // Constructor.
{
    this->impl = new WRAIFF_impl;
}

WRAIFF::WRAIFF(const char* filename,    // An alternative open-constructor.
               double      samplerate,
               short       channels,
               short       bits)
{
    this->impl = new WRAIFF_impl;
    this->impl->open(filename, samplerate, channels, bits);
}

WRAIFF::~WRAIFF()                       // Destructor.
{
    delete this->impl;                  // Call ~WRAIFF_impl().
}

// Open an AIFF file for writing.
void WRAIFF::open(const char* filename,
                  double      samplerate,
                  short       channels,
                  short       bits)
{
    this->impl->open(filename, samplerate, channels, bits);
}

// Functions for writing floating point data.
void WRAIFF::write(const double* audio, long frames)
{
    this->impl->write_fp(audio, frames);
}
void WRAIFF::write(const float* audio, long frames)
{
    this->impl->write_fp(audio, frames);
}

// Functions for writing signed integer data.
void WRAIFF::write(const signed long* audio, long frames)
{
    this->impl->write_int(audio, frames);
}
void WRAIFF::write(const signed int* audio, long frames)
{
    this->impl->write_int(audio, frames);
}
void WRAIFF::write(const signed short* audio, long frames)
{
    this->impl->write_int(audio, frames);
}
void WRAIFF::write(const signed char* audio, long frames)
{
    this->impl->write_int(audio, frames);
}

// Test whether file is (already/still) open.
int WRAIFF::is_open()
{
    return this->impl->f.is_open();
}

// Report file statistics (filename, samplerate, length, etcetera).
void WRAIFF::info(ostream& to)
{
    this->impl->info(to);
}

// Should be called after open() to rewrite the AIFF header and close the file.
void WRAIFF::close()
{
    this->impl->close();
}
