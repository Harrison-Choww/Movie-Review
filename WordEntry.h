#ifndef WORDENTRY_H
#define WORDENTRY_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class WordEntry {

private:
	string word;
	int code;
public:
	WordEntry(const string&, int);
	const string& getWord();
	int getCode();
};
#endif

