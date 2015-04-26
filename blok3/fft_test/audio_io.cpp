#include "audio_io.h"

audioIO::audioIO() {
	inFile = NULL;
	outFile = NULL;
	buffer = NULL;
	path = NULL;
}

audioIO::~audioIO() {
	if (buffer) {
		delete[] buffer;
	}
}

void audioIO::readFile(string path) {
	this->path = path.c_str();
	inFile = sf_open(path.c_str(), SFM_READ, &sfInfo);

	if(inFile == NULL) {
		throw -1;
	}
	sampleRate = sfInfo.samplerate;
	channels = sfInfo.channels;
	numFrames = sfInfo.frames;

	buffer = new float[numFrames*channels];
	sf_readf_float(inFile, buffer, numFrames);
}

void audioIO::writeFile() {
	string outName = path;
	unsigned find_ext = outName.find_last_of(".");
	string extension = outName.substr(find_ext);

	outName = outName.substr(0,find_ext);
	outName = outName + "2" + extension;

	outFile = sf_open(outName.c_str(), SFM_WRITE, &sfInfo);

	if(outFile == NULL) {
		throw -2;
	}
	sf_writef_float(outFile, buffer, numFrames);

	sf_close(inFile);
	sf_close(outFile);
}
