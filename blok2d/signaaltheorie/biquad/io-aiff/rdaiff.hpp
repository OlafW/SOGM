/*
    RDAIFFPP version 0.14, may 18, 2015, a simple AIFF reading C++ class.
    Latest version at http://home.hku.nl/~pieter.suurmond/EDU/cpp/rdaiffpp/.

      To use the RDAIFF class, include this headerfile in your .cpp file 
      (as is done in example programs demo.cpp and test.cpp). Furthermore
      put sourcefile rdaiff.cpp in your compiler-project or your makefile.

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

#ifndef ostream
#include <ostream>  // Necessary for member function info(ostream&),
#endif              // in case client did not already include it.

class RDAIFF                                // API-class to read AIFF files.
{
  public:
    RDAIFF();                               // Default constructor.
    RDAIFF(const char* filename);           // Alternate opening-constructor.
    ~RDAIFF();                              // Destructor, may call close().

/* In case the default constructor is used (instead of the more elegant 
   opening-constructor), a subsequent call to function
*/
    void open(const char* filename);

/* is necessary to open an existing AIFF file for reading. 
   After successful return, the caller may forget 'filename' because a copy 
   of the name is stored inside the newly created RDAIFF object. It may be
   recalled with
*/
    const char* name();

/* At any moment between opening and closing of the file, AIFF header para-
   meters can be retrieved with the following member functions:
*/
    long long   frames();       // Total number of sampleframes in the file.
    double      samplerate();   // Perhaps 'framerate' would be a better name.
    short       channels();     // Number of channels (i.e. samples) per frame.
    short       bits();         // Number of bits per channel (i.e. sample).
    
    void   info(ostream& to); // Prints AIFF header info to for example 'cout',
                              // some file, or some other outputstream.

/* After having opened an AIFF file, audio-data may be read from it by 
   (repeatedly) calling (one of) the following functions:
*/
    void read(float*            audio, long frames);
    void read(double*           audio, long frames);
    
    void read(signed char*      audio, long frames);
    void read(signed short*     audio, long frames);
    void read(signed int*       audio, long frames);
    void read(signed long*      audio, long frames);
    void read(signed long long* audio, long frames);

/* All these funtions read the next 'frames' number of sampleframes from the
   open stream, without loss of information. Rather than losing only the
   smallest bit, RDAIFF prefers to throw an exception.

   In case of reading to floating point datatypes (float and double), samples
   are scaled to -1.0 (incl.) to +1.0 (excl.) without loss of information; we
   never multiply with dirty values like 0.9999. Only zero-bits are inserted 
   into the LSB during left-justification.

   No audiodata-rounding is ever performed in RDAIFF; the data is simply never
    touched. RDAIFF reads transparently.
   
   In case of reading-in to integer datatypes (signed char, short, int, long 
   and long long), samples are never upscaled, downscaled or clipped to fit the
   requested output datatype. Instead, data is kept right-justified and an
   error-message is generated if the user attempts to read into a too small 
   datatype.

   Bits resolution may range from 1 to 56 bits (inclusive). Unfortunately,
   64-bit files cannot be read. Non-integer multiples of 8 are allowed.
   However, according to the AIFF specifications, when for example a 25-bit 
   file is opened, the data is expected to be stored as right-justified 32-bit
   samples (the nearest higher-or-equal multiple of 8 bits).
   The following table shows which read-functions can be use for several bit
   resolutions (assuming that on your compiler/machine:
                numeric_limits<short>::digits >= 15; // without sign bit.
                numeric_limits<float>::digits >= 24; // mantissa without sign.
               numeric_limits<double>::digits >= 53; etc. Anyway, RDAIFF will
   check or correct for differences, throwing an error as soon as the risk of
   dataloss arises):
     Opened AIFF file:  8-bit: 16-bit: 24-bit:   32-bit: .... 56-bit:  64-bit: 

     read(char*,)       ok     ERROR   ERROR     ERROR        ERROR    ERROR
     read(short*,)      ok     ok      ERROR     ERROR        ERROR    ERROR
     read(long*,)       ok     ok      ok        ok           ERROR    ERROR
     read(long long*,)  ok     ok      ok        ok           ok       ERROR!!
      Output range:     -128   -32768  -8388608  -2147483648  -36028797018963968
                        +127   +32767  +8388607  +2147483647  +36028797018963967
     read(float*,)      ok     ok      ok        ERROR        ERROR    ERROR
     read(double*,)     ok     ok      ok        ok           ERROR    ERROR
      Output range:     always scaled from -1.0 inclusive up to +1.0 exclusive

   So, for example, after you've openened an 8-bit file, it doesn't matter what
   integer read-function you use: you'll always read sample-values ranging from
   -128 from +127.
   Whether read(int*,.) behaves like read(short*,.) or read(long*,.) may differ
   per computer, but most likely, reading ints is the same as reading longs.

   Samples are transferred to your array as they come from file: channel-
   interleaved. For example, for stereo this means:

        channel 0 (left)  sample-data   (frame #0)
        channel 1 (right) sample-data 
        channel 0 (left)  sample-data   (frame #1)
        channel 1 (right) sample-data 
        channel 0 (left)  sample-data   (frame #2)
                          etc.

   The total number of samples in the file is defined as:
    
        number of samples = number of sampleframes * number of channels

   Audio data can be re-read, without closing and re-opening, by calling
*/
    void rewind();

/* To retreive the number sampleframes available for subsequent reading, call
*/
    long long frames_togo();

/* Immediately after opening, frames_togo() equals frames(), but, whereas the 
   latter stays constant, frames_togo() will decrement during reading, reaching
   zero after having read the last sampleframe.

   To see whether the file is already or still open, call
*/
    int is_open();

/* It's a good habit to call close() explicitly as soon as you're done with
   the file, but when you don't do this (perhaps you forget), the destructor
   will call it for you.
*/
    void close();

  private:
    class RDAIFF_impl* impl;    // The implementation is kept away from the API.
};

