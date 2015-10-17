#include "sndfile_io.h"

SNDFile::SNDFile() {
	inFile = NULL;
	outFile = NULL;
	buffer = NULL;
	path = NULL;
}

SNDFile::~SNDFile() {
	if (buffer) delete[] buffer;
}

void SNDFile::readFile(string path) {
	this->path = path.c_str();
	inFile = sf_open(this->path, SFM_READ, &sfInfo);

	sampleRate = sfInfo.samplerate;
	channels = sfInfo.channels;
	N = sfInfo.frames;

	buffer = new float[N*channels];

	sf_readf_float(inFile, buffer, N);
	sf_close(inFile);
}

void SNDFile::writeFile(float* buffer, SF_INFO sfInfo, string outName) {
	outFile = sf_open(outName.c_str(), SFM_WRITE, &sfInfo);

	sf_writef_float(outFile, buffer, sfInfo.frames);
	sf_close(outFile);
}

float* SNDFile::getBuffer() {
	return buffer;
}

unsigned long SNDFile::getBufferSize() {
	return N*channels;
}
