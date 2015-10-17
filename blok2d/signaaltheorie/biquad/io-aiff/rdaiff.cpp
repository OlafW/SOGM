/*
    RDAIFFPP version 0.14, may 18, 2015, a simple AIFF reading C++ class.
    Latest version at http://home.hku.nl/~pieter.suurmond/EDU/cpp/rdaiffpp/.

      Include this .cpp in your (IDE-)project or your (UNIX-)makefile.

    Copyright (c) 2004, 2005, 2009, 2015 - Pieter Suurmond

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
*/

#include <fstream>                  // For ifstream.
#include <iostream>                 // For ostream.
#include <cmath>                    // For IEEE exponents.
#include <limits>                   // For numeric_limits::digits.
#include <string>                   // To copy the filename.
#ifndef strncmp
  #include <cstring>                // For strncmp(), if necessary.
#endif
using namespace std;

#include "rdaiff.hpp"               // RDAIFF specifications.

class RDAIFF_impl
{
  friend class RDAIFF;              // Necessary since most below is private.

  public:

    RDAIFF_impl()
    {
    //----------- TYPE-CHECK: --------------------------------------------------
    int e = 0;                           // Prevent 'const-comparison' warning.
    if ((sizeof(short)     < 2) ||       // Better do this at compile-time only.
        (sizeof(long)      < 4) ||       // No (sign-ext-)problems when bigger.
        (sizeof(long long) < 8) ||
        (sizeof(float)     < 4) ||
        (sizeof(double)    < 8) || e)
        throw "RDAIFF: Datatype too small! Sorry, you cannot use RDAIFFPP.";
    //--------------------------------------------------------------------------
    }

    ~RDAIFF_impl()
    {
    if (this->f.is_open())      // Silently close if still open. Hope it never
        this->f.close();        // throws: destructors may not throw in C++!
    }

  private:

    ifstream        f;        // Input file stream (class member, auto-free).
    long            start;    // To store tellg(), just after the AIFF header.
                              // Type 'streampos' is not known on old C++-compi-
                              // lers (with CodeWarrior IDE 4.0, even '#include
                              // <istream>' doesn't help), so let's use long.
    string          name;     // Internal copy of the filename (class member).
    unsigned long   frames;   // Total number of frames    (at least 4 bytes).
    short           channels; // Number of sound channels  (at least 2 bytes).
    short           bits;     // Number of bits resolution (at least 2 bytes).
    short           bytes;    // Derived (minimum amount needed for storage).
    double          rate;     // Sampling rate in cycles per second.
    long long       scale;    // For integer to floating point conversion.
    long long       s_ext;    // For sign-extension independant on integer-size.
    unsigned long   frames_togo; // Decremented during reading.

 // Read a 2-byte big-endian into a short: MSB first. Independant on size of
 // short (except that it must be >= 2 bytes) and endianness of the CPU.
 // Negative results are checked by the caller (called only 2 times).
    short rd_big16_signed()
    {
        char    ubuf[2];
        short   result;
        
        this->f.read(ubuf, 2);
        // Casts for machines with default-signed chars:
        result  = static_cast<unsigned char>(ubuf[0]); result <<= 8;
        result |= static_cast<unsigned char>(ubuf[1]);
        return result;
    }

 // Read a 4-byte big-endian into a long: MSB first. Independant on size of
 // unsigned long (except that it must be >= 4 bytes) and endianness of the CPU.
    long rd_big32_unsigned()
    {
        char            buf[4];
        unsigned long   result;

        this->f.read(buf, 4);
        // Casts for machines with default-signed chars:
        result  = static_cast<unsigned char>(buf[0]); result <<= 8;
        result |= static_cast<unsigned char>(buf[1]); result <<= 8;
        result |= static_cast<unsigned char>(buf[2]); result <<= 8;
        result |= static_cast<unsigned char>(buf[3]);
        return result;
    }

   /*
      C O N V E R T   F R O M   I E E E   E X T E N D E D 
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
      Pieter changed minor things.
   */
#ifndef HUGE_VAL
  #define HUGE_VAL HUGE
#endif /*HUGE_VAL*/
#define UnsignedToFloat(u) (((double)((long)(u-2147483647L-1)))+2147483648.0)

    double ConvertFromIeeeExtended(const char *ten_bytes)
    {
        double        f;
        int           expon;
        unsigned long hiMant, loMant;

        expon  = ((ten_bytes[0] & 0x7F) << 8)
               |  (ten_bytes[1] & 0xFF);
        hiMant = (static_cast<unsigned long>(ten_bytes[2] & 0xFF) << 24)
               | (static_cast<unsigned long>(ten_bytes[3] & 0xFF) << 16)
               | (static_cast<unsigned long>(ten_bytes[4] & 0xFF) << 8)
               |  static_cast<unsigned long>(ten_bytes[5] & 0xFF);
        loMant = (static_cast<unsigned long>(ten_bytes[6] & 0xFF) << 24)
               | (static_cast<unsigned long>(ten_bytes[7] & 0xFF) << 16)
               | (static_cast<unsigned long>(ten_bytes[8] & 0xFF) << 8)
               |  static_cast<unsigned long>(ten_bytes[9] & 0xFF);
        if (!(expon || hiMant || loMant))
            f = 0;
        else
            {
            if (expon == 0x7FFF)
                f = HUGE_VAL; // Infinity or NaN.
            else
                {
                expon -= 16383;
                f  = ldexp(UnsignedToFloat(hiMant), expon -= 31);
                f += ldexp(UnsignedToFloat(loMant), expon -= 32);
                }
            }
        if (ten_bytes[0] & 0x80)
            f *= -1.0;
        return f;
    }

 // Called by open(const char*) and by opening-constructor RDAIFF(const char*).
    void open(const char* filename)
    {
        if (filename == NULL)                              // Check arguments.
            throw "RDAIFF: No filename (NULL pointer)!";
        try {
            this->name = filename; // Store copy of the filename (as soon as 
            }                      // possible) so caller may forget it
        catch (...)                // after opening.
            {
            throw "RDAIFF: Not enough memory to hold a copy of the filename!";
            }
        if (!*filename)
            throw "RDAIFF: Empty filename!";
        if (this->f.is_open())
            throw "RDAIFF: File already open!";
        this->f.open(filename, ios::binary);
        if (!(this->f.is_open() && this->f.good()))
            throw "RDAIFF: Could not open file!";

        char            buf[10]; // 4 bytes for most jobs, 10 for IEEE-reading.
        unsigned long   totalsize;
        short           COMMread = 0;   // Flags.
		short	        SSNDread = 0;

        //-------------------------------------------- Read FORM chunk:
        this->f.read(buf, 4);                       // Endian-safe read.
        if (this->f.fail() || this->f.eof())        // bad() also implies fail()
            throw "RDAIFF: Failed to read FORM chunk!";
        if (strncmp(buf, "FORM", 4))
            throw "RDAIFF: Header doesn't start with magic word FORM!";

        totalsize = rd_big32_unsigned();
        if (this->f.fail() || this->f.eof())
            throw "RDAIFF: Failed to read FORM size!";

        this->f.read(buf, 4);
        if (this->f.fail() || this->f.eof())
            throw "RDAIFF: Failed to read AIFF type!";
        if (strncmp(buf, "AIFF", 4))
            throw "RDAIFF: Header doesn't specify AIFF type!";
        //-------------------------------------------- Read COMM and SSND chunk:
        do  {
            unsigned long   chunksize;

			this->f.read(buf, 4);            // Read chunkID (COMM, SSND, etc.).
            if (this->f.fail() || this->f.eof())
                throw "RDAIFF: Failed to read chunkID!";
            chunksize = rd_big32_unsigned(); // Read size.
            if (this->f.fail() || this->f.eof())
                throw "RDAIFF: Failed to read chunksize!";
            if (!strncmp(buf, "COMM", 4)) //------------------------ COMM chunk:
                {
                if (COMMread)
                    throw "RDAIFF: Multiple COMM chunks!";
                COMMread = 1;
                if (chunksize < 18)
                    throw "RDAIFF: COMM chunk has bad size (too small)!";

                this->channels = rd_big16_signed();
                if (this->f.fail() || this->f.eof())
                    throw "RDAIFF: Failed to read number of channels!";
                if ((this->channels < 1) || (this->channels > 1000))
                    throw "RDAIFF: Invalid number of channels!";

                this->frames_togo = this->frames = rd_big32_unsigned();
                if (this->f.fail() || this->f.eof())
                    throw "RDAIFF: Failed to read number of sampleframes in\
 COMM chunk!";
                this->bits = rd_big16_signed();
                if (this->f.fail() || this->f.eof())
                    throw "RDAIFF: Failed to read number of bits resolution in\
 COMM chunk!";
                if ((this->bits < 1) || (this->bits > 56))
                    throw "RDAIFF: Invalid number of resolution bits!";
                this->bytes = this->bits >> 3;     // Redundant, handy later on.
                if (this->bits & 3)
                    this->bytes++;                 // Round up.
                // For sign-extension and integer to floating point conversion:
                this->s_ext = 1LL << (this->bytes << 3);
                this->scale = this->s_ext >> 1;

                long long mbytes = 8 + 18 + 8 + 12
                                 + (static_cast<long long>(this->frames) * 
                                    static_cast<long long>(this->bytes) *
                                    static_cast<long long>(this->channels));
                if (mbytes < 2147483648LL)         /* Only test files < 2 GB. */
                    {                  /* totalsize is unreliable above 4 GB. */
                    if (static_cast<long long>(totalsize) < mbytes)
                        throw "RDAIFF: Suspicious size in FORM chunk!";
                    }

                // Read 10-byte IEEE-float and store as double.
                this->f.read(buf, 10);
                if (this->f.fail() || this->f.eof())
                    throw "RDAIFF: Error reading samplerate!";
                this->rate = ConvertFromIeeeExtended(buf);
                if ((this->rate <= 0.0) || (this->rate > 1000000.0))
                    throw "RDAIFF: Samplerate out of range!";

				if (SSNDread)   // In case the SSND chunk preceeded SSND chunk,
				    {           // leave filestream position at start of data.
					if (!this->f.seekg(this->start))
						throw "RDAIFF: Failed to rewind!";
				    }
                else if (chunksize > 18) // Skip excessive COMM chunk bytes.
                    {
                    this->f.seekg(chunksize - 18, ios::cur);
                    if (this->f.fail())
                        throw "RDAIFF: Error while skipping extension-bytes in\
 COMM chunk!";
                    }
                }
            else if (!strncmp(buf, "SSND", 4)) //------------------- SSND chunk:
                {
                if (SSNDread)
                    throw "RDAIFF: Multiple SSND chunks!";
                SSNDread = 1;

                unsigned long offset    = rd_big32_unsigned(); // In bytes.
                unsigned long blocksize = rd_big32_unsigned();
                if (offset) // Skip offset.
                    {
                    this->f.seekg(offset, ios::cur);
                    if (this->f.fail())
                        throw "RDAIFF: Error while skipping offset in\
 SSND chunk!";
                    }
                // Remember where the data starts, for rewind() and in case
                // the COMM chunk is *after* SSND chunk	.
				this->start = this->f.tellg();         // Can tellg() throw?
				if (!COMMread)                         // Seek to next chunk.
                    {
                    unsigned long trail_pad = 0;
                    chunksize -= 8;         // Remaining bytes actually used
                    if (blocksize)          // (chunksize is without padding).
                        { // Block starts *after* offset.
                        trail_pad = chunksize % blocksize;
                        if (trail_pad)
                            trail_pad = blocksize - trail_pad;
                        }
				    this->f.seekg(this->start + chunksize + trail_pad);
                    }
                }
            else //-------------------------------------- Skip all other chunks:
                {
                this->f.seekg(chunksize, ios::cur);
                if (this->f.fail())
                    throw "RDAIFF: Error during skipping unknown chunk!";
                }
            } while (!(COMMread && SSNDread));
    }

    void info(ostream& to)
    {
        double             d;
        static const char* line = "-----------------------------------------\n";

        if (!this->f.is_open()) // Values cannot be trusted (if never opened).
            throw "RDAIFF: No file currently open!";
        to << line;
        //------------------------------------- ABOUT OPEN FILE: ---------------
        to << "    AIFF file: " << this->name     << "\n";
        to << "     channels: " << this->channels << "\n";
        to << "       frames: " << this->frames   << "\n";
        to << " bits/channel: " << this->bits     << "\n";
        to << "    framerate: " << this->rate     << "/second\n";
        //------------------------------------- DERIVED INFO: ------------------
        to << "  bytes/frame: " << this->channels * this->bytes << "\n";
        to << "     filesize: >"
           <<   8L+18L+8L+12L + (this->frames * this->bytes * this->channels)
           << " bytes\n";       // Minimum size, we don't know exact size yet.
        to << "     duration: ";
        d = static_cast<double>(this->frames) / this->rate;
        if      (d >= 3600.0) to << d / 3600.0 << " hours";
        else if (d >=   60.0) to << d /   60.0 << " minutes";
        else if (d >=    1.0) to << d          << " seconds";
        else                  to << d * 1000.0 << " milliseconds";
        to << endl << line;
    }

/* Generic code-generators for reading from file.
   But before reading, we always check whether the audio-data will fit the
   requested destination datatype.

   In <limits>: numeric_limits::digits (which is a static const int)
   stores the number of radix digits that the type can represent without change
   (which is the number of bits other than any sign bit for a predefined integer
   type, or the number of mantissa digits for a predefined floating-point type).
   For example: float=24; double=53; short=15 (thus without sign bit).
*/
#define TST(OUTTYPE) \
    if ((numeric_limits<OUTTYPE>::digits + 1) < (this->bytes << 3))\
        throw "RDAIFF: AIFF-data does not fit requested destination datatype!";

/* OLD macrodef (used up to version 0.09) for integer types only:
#define TST(OUTTYPE) \
    if (static_cast<short>(sizeof(OUTTYPE)) < this->bytes)\
        throw "RDAIFF: AIFF-data does not fit requested destination datatype!";
*/

#define RD(OUTTYPE,DIVIDER) \
    if (!this->f.is_open())             /* Check arguments and object-state. */\
        throw "RDAIFF: Cannot read from a closed file!";\
    if (audio == NULL)\
        throw "RDAIFF: NULL pointer supplied to read()!";\
    if (frames < 0L)\
        throw "RDAIFF: Cannot read negative amount of frames!";\
    if (static_cast<unsigned long>(frames) > this->frames_togo)\
        throw "RDAIFF: Requested to read more frames than available!";\
    while (frames--)                    /* Assure we never lose information. */\
        {\
        short ch = this->channels;   /* ->channels is at least 1 (for mono). */\
        do  {\
            char buf[sizeof(long long)];    /* Input buffer.  */\
            long long sample;               /* Output buffer. */\
                                            /* Endianness-unaware, but safe. */\
            this->f.read(buf, this->bytes);\
            if (this->f.fail() || this->f.eof())\
                throw "RDAIFF: Error reading audiosample!";\
            sample = static_cast<unsigned char>(buf[0]);    /* ->bytes >= 1. */\
            for (short b = 1; b < this->bytes; b++)\
                {                    /* Start with MSB, shift-in Lesser SBs. */\
                sample <<= 8;                                /* This cast is */\
                sample |= static_cast<unsigned char>(buf[b]);/* important!!! */\
                }                      /* Machine-independant sign-extension:*/\
            if (sample >= this->scale) /*  8-bit: scale=128;  s_ext=256.     */\
                sample -= this->s_ext; /* 24-bit: sc=8388608; s_ext=16777216.*/\
            *audio++ = static_cast<OUTTYPE>(sample) DIVIDER;\
            } while (--ch);\
        this->frames_togo--;  /* Inside the loop for robusteness (may throw).*/\
        }

 // Internal functions for reading-in signed integers:
 // Using an empty DIVIDER-argument keeps the data right-justified.
    void read(signed char*      audio,
              long              frames) { TST(signed char)  RD(signed char,)  }
    void read(signed short*     audio,
              long              frames) { TST(signed short) RD(signed short,) }
    void read(signed int*       audio,
              long              frames) { TST(signed int)   RD(signed int,)   }
    void read(signed long*      audio,
              long              frames) { TST(signed long)  RD(signed long,)  }
    void read(signed long long* audio,
              long              frames) { /*Always ok*/ RD(signed long long,) }

 // Internal functions for reading-in floating point numbers:
 // Using DIVIDER to scale between -1.0 (inclusive) and +1.0 (exclusive).
 // Notice we also pass the division-operator in the argument to the macro-def.
    void read(float*    audio,
              long      frames) { TST(float)  RD(float,  / float(this->scale)) }
    void read(double*   audio,
              long      frames) { TST(double) RD(double, / double(this->scale))}

 // When client wants to re-read without closing and re-opening.
    void rewind()
    {
        if (!this->f.is_open())
            throw "RDAIFF: Cannot rewind a closed file!";
        this->f.seekg(this->start);
        if (this->f.fail())    // Fail or bad.
            throw "RDAIFF: Failed to rewind!";
        this->frames_togo = this->frames;
    }
};

RDAIFF::RDAIFF()                        // The default constructor.
{
    this->impl = new RDAIFF_impl;
    this->impl->name = ""; // Initialise data-members to zero and empty strings?
}

RDAIFF::RDAIFF(const char* filename)    // An alternative open-constructor
{                                       // (more elegant to use).
    this->impl = new RDAIFF_impl;
    this->impl->open(filename);
}

RDAIFF::~RDAIFF()                       // The destructor.
{
    delete this->impl;                  // It calls ~RDAIFF_impl().
}

// Open the specified AIFF file for reading.
void RDAIFF::open(const char* filename)
{
    this->impl->open(filename);
}

// Test whether file is (already/still) open.
int RDAIFF::is_open()
{
    return this->impl->f.is_open();
}

// Report file statistics (filename, samplerate, length, etcetera).
void RDAIFF::info(ostream& to)
{
    this->impl->info(to); // Checks ->f.is_open() itself.
}

// Get-functions to retreive AIFF-parameters after opening.
double RDAIFF::samplerate()
{
    if (!this->impl->f.is_open())
        throw "RDAIFF: No samplerate, file closed!";
    return this->impl->rate;
}

short RDAIFF::channels()
{
    if (!this->impl->f.is_open())
        throw "RDAIFF: No number of channels, file closed!";
    return this->impl->channels;
}

short RDAIFF::bits()
{
    if (!this->impl->f.is_open())
        throw "RDAIFF: No number of bits, file closed!";
    return this->impl->bits;        // Number of bits per channel
}                                   // (i.e. bits per sample).

long long RDAIFF::frames()
{
    if (!this->impl->f.is_open())
        throw "RDAIFF: No number of frames, file closed!";
    return static_cast<long long>(this->impl->frames);
}// Total number of frames (constant).

long long RDAIFF::frames_togo()
{
    if (!this->impl->f.is_open())
        throw "RDAIFF: No number of frames to go, file closed!";
    return static_cast<long long>(this->impl->frames_togo); 
}// Number of frames left for reading (decrements during reading).

const char* RDAIFF::name()
{
    // Even when the file is closed!
    return this->impl->name.c_str(); 
}

// API functions for reading:
void RDAIFF::read(float* audio, long frames)
{
    return this->impl->read(audio, frames);
}

void RDAIFF::read(double* audio, long frames)
{
    return this->impl->read(audio, frames);
}

void RDAIFF::read(signed char* audio, long frames)
{
    return this->impl->read(audio, frames);
}

void RDAIFF::read(signed short* audio, long frames)
{
    return this->impl->read(audio, frames);
}

void RDAIFF::read(signed int* audio, long frames)
{
    return this->impl->read(audio, frames);
}

void RDAIFF::read(signed long* audio, long frames)
{
    return this->impl->read(audio, frames);
}

void RDAIFF::read(signed long long* audio, long frames)
{
    return this->impl->read(audio, frames);
}

// Rewind to the beginning of the SSND chunk audio data.
void RDAIFF::rewind()
{
    this->impl->rewind();
}

// May be called after open().
void RDAIFF::close()
{
    if (!this->impl->f.is_open())
        throw "RDAIFF: File already closed or never opened!";
    this->impl->f.close();
}

