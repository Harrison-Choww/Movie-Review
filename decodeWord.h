#ifndef DECODEWORD_H
#define DECODEWORD_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class DecodeWord {

private:
	int decodeCode;
	string decodeWord;
public:
	DecodeWord(const string&, int);
	const string& getDecodeWord();
	int getDecodeCode();
};
#endif
