#ifndef _SNDFile_H_
#define _SNDFile_H_

#include <iostream>
#include <sndfile.h>
#include <string>

using std::string;

class SNDFile {
public:
	SNDFile();
	~SNDFile();
	int readFile(string path);
	int writeFile(float* buffer, SF_INFO sfInfo, string outName);
	float* getBuffer();
	unsigned long getBufferSize();
	int getSampleRate();

private:
	SF_INFO sfInfo;
	SNDFILE* inFile;
	SNDFILE* outFile;
	const char* path;

	float* buffer;
	unsigned long N;
	int sampleRate;
	int channels;
};

#endif
