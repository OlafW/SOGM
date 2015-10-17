#include "playablesong.h"

void PlayableSong::set_url(string url) {

  this->url = url;

}


void PlayableSong::play() {

  cout << "Now playing " << url << endl;

}
