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
	void readFile(string path);
	void writeFile(float* buffer, SF_INFO sfInfo, string outName);
	float* getBuffer();
	unsigned long getBufferSize();

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
