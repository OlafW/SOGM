#ifndef _audioIO_H_
#define _audioIO_H_

#include <iostream>
#include <sndfile.h>
#include <string>

using namespace std;

class audioIO {

public:
	audioIO();
	~audioIO();
	void readFile(string path);
	void writeFile();

private:
	SF_INFO sfInfo;
	SNDFILE* inFile;
	SNDFILE* outFile;
	const char* path;
	float* buffer;
	long int numFrames;
	int sampleRate;
	int channels;
};

#endif
