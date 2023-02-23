#ifndef DECODER_H
#define DECODER_H

#include <string>
#include <list>
#include <iostream>
#include "WordEntry.h"

using namespace std;

class Decoder {

private:
	list<WordEntry>* decode;
	int size;

public:
	Decoder(int);
	//bool contains(const string&);
	string getDecodeWord(const int&);
	void put(const string&, int);

private:
	int decodeHash(const int&);
};

#endif
