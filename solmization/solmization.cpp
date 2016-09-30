#include <iostream>
#include <fstream>
#include <string>

using std::string;

/*
    Implementation of solmization method of Guido d'Arezzo (c.q. 1026).
    Every vowel in a text correspond to notes in a scale.
    The vowel sequence 'a e i o u' is mapped to the pitches of the double octave (g3 - g5).

    Input: text to be put to music
    Ouput: notated music in lilyPond format
*/

const int numSequence = 3;
const int numVowels = 5;
const char vowels[numVowels] = {'a', 'e', 'i', 'o', 'u'};

const string vowelSequence[numSequence][numVowels] = {
    // a     e     i     o     u
    { "g,", "a,", "b,", "c,", "d,"},
    { "e",  "f",  "g",  "a",  "b" },
    { "c'", "d'", "e'", "f'" "g'" }
};

string solmization(string text) {
    string melody;

    // For every character in the text
    for (int n=0; n<text.length(); n++) {
        char c = text[n];

        // If character is vowel,
        // Choose a note based on random sequence and character
        for (int v=0; v<numVowels; v++) {
            if (c == vowels[v]) {
                int randomSeq = rand() % numSequence;
                melody += vowelSequence[randomSeq][v] + " ";
            }
        }
    }
    return melody;
}


int main() {
    string text = "Ut queant laxis resonare";
    string melody = solmization(text);

    // Write to lilyPond file
    std::ofstream lilyPondFile;
    lilyPondFile.open("solmization.ly");

    lilyPondFile << "\\version \"2.16.0\" \n\n";
    lilyPondFile << "{ \n";
    lilyPondFile << "\t" << melody << "\n";
    lilyPondFile << "} \n";
    lilyPondFile.close();

    return 0;
}
