/*
    WRAIFFPP 0.25 (may 18, 2015), a tiny audiofile writing utility in C++.
    Latest version at http://home.hku.nl/~pieter.suurmond/EDU/cpp/wraiffpp/.

    Include this file in your C++ source (as is done in example program
    write_aiff_files.cpp). Also add wraiff.cpp to your project or makefile.

    Thanks to Eduard Aylon, Maarten de Boer, Merlijn Blaauw, Peter Maas,
    Fokke de Jong, Niels Gorisse, Niels Bogaards and Hans Timmermans.

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
*/

#ifndef ostream
  #include <ostream>            // Needed for member function info(ostream&).
#endif                          // In case client did not already include.

class WRAIFF
{
  public:
    WRAIFF();                           // Default constructor.
    WRAIFF(const char* filename,        // An alternative open-constructor.
           double      samplerate,
           short       channels,
           short       bits);
    ~WRAIFF();                          // Destructor, it may call close().
/*

    When you use the default constructor instead of the (more elegant) open-
    constructor, you will need to call function
*/
    void open(const char* filename,   // Caller may free C-string after return.
              double      samplerate, // Number of samples per second (Hertz).
              short       channels,   // Number of channels (between 1 and 128).
              short       bits);      // Number of bits per channel (8, 16, 24).
/*
    before you can write data to the file. It tries to create a new (or over-
    write an existing) AIFF file with the filename and other parameters you
    specified. It throws an exception on failure: a const char* describing the
    error.


    After opening, you can write data to the file by (repeatedly) calling
*/
    void write(const float*        audio, long frames);
    void write(const double*       audio, long frames);

    void write(const signed char*  audio, long frames);
    void write(const signed short* audio, long frames);
    void write(const signed int*   audio, long frames);
    void write(const signed long*  audio, long frames);
/*
    where argument 'audio' is a pointer to an array of channel-interleaved
    floats, doubles, signed chars, shorts, ints or longs; and argument 'frames'
    is the number of sampleframes to write. Notice the number of sampleframes
    is defined as:
                    number of frames = number of samples / number of channels.
    
    When you supply a NULL pointer to 'audio', or when you specify 'frames' less
    than 0, write() will throw an (const char*) exception PRIOR to attempting
    to write (it then throws without even touching the file).

    But there are other cases, where write() may throw an exception AFTER having
    written the audio data (more or less succesfully).
    This may happen when the audiofile tends to grow enormously huge: it then 
    throws, but only ONCE: after more than 317520000 sampleframes were written.
    Of course, you may catch this (singly occuring) exception and just continue 
    writing.
    It may futhermore happen when your audio data goes out-of-range. Then
    WRAIFFPP will take care of clipping (preventing nasty sign-swaps).
    
    In case of floats and doubles, the lowest audio-value that can be written
    without being clipped is always -1.0. The highest value, however, depends
    on the number of bits resolution specified during opening:

         8 bits:  min = -1  max =     127/128     = +0.9921875
        16 bits:  min = -1  max =   32767/32768   = +0.999969482421875
        24 bits:  min = -1  max = 8388607/8388608 = +0.99999988079071044921875

    In case of writing signed chars, shorts or longs, the minimum and maximum 
    sample-values that you can write without clipping are:
    
         8 bits:  min = -128                  max = +127
        16 bits:  min = -32768                max = +32767
        24 bits:  min = -8388608              max = +8388607

    All simply a consequence of the 2's complement representation of signed
    integers.
    Function write() may furthermore throw an exception in case of low-level
    write-errors.


    At any time between opening and closing of the file, function
*/
    void info(ostream& to);    // Print file statistics (for example: to=cout).
/*  
    may be called to see how many sampleframes have been written, the filename,
    the number of channels, etcetera.

    To see whether the audiofile is still/already open, call
*/
    int is_open();
/*

    As soon as you're done, it is best to call function
*/
    void close();
/*
    explicitly because it might throw some exception. (Otherwise, the destructor
    will automatically call close() but C++ forbids a destructor to throw an
    exception!).
    Function close() updates the AIFF header (writes the total number of sample-
    frames written) and then closes the file.
*/

  private:
    class WRAIFF_impl* impl;      // Implementation is kept away from this API.
};
