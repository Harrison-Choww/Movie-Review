#include "HashTable.h"
#include "Decoder.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>


struct tokenFreq
{
	string token;
	int freq;
};


void quicksort(vector<tokenFreq>& values, int left, int right);
int partition(vector<tokenFreq>& values, int left, int right);

using namespace std;

int main() {
	// declare a few needed variables for inputing the dat

	vector<tokenFreq> tokenFreqTable;

	string line;
	string message = " ";
	const string delim = " .,'!\"&-?";

	// open input file
	ifstream myfile("movieReviews.txt");
	if (myfile.fail()) {
		cout << "could not open file" << endl;
		exit(1);
	}

	//create hash table
	HashTable encoder(20071);
	int decodersize = 73;
	Decoder decoder(decodersize);

	while (!myfile.eof()) {
		getline(myfile, line);
		int len = line.size();
		int loc = 0;
		while (len > 0) {     // identify all individual strings
			bool inTable = false;
			string sub;
			loc = line.find_first_of(delim);
			if (loc > 0)
			{
				sub = line.substr(0, loc);
				line = line.substr(loc, line.size());
			}
			else
			{
				sub = line.substr(0, 1);
				line = line.substr(1, line.size());
			}
			len = line.size();

			//cout << "Proccessing: " << sub << " length: " << sub.size() << endl;
			for (unsigned int i = 0; i < tokenFreqTable.size(); i++)
			{
				if (tokenFreqTable.at(i).token == sub)
				{
					tokenFreqTable.at(i).freq++;
					inTable = true;
				}
			}
			if (!inTable)
			{
				tokenFreqTable.push_back({ sub, 1 });
			}
		}
	}
	myfile.close();

	//cout << "finish processing " << endl;

	/*for (unsigned int i = 0; i < tokenFreqTable.size(); i++)
	{
		cout << tokenFreqTable.at(i).token << " " << tokenFreqTable.at(i).freq << endl;
	}*/

	//cout << "Sorting Started: " << endl << endl;//

	quicksort(tokenFreqTable, 0, tokenFreqTable.size() - 1);

	cout << "Token Frequency Table: " << endl;
	cout << "---------------------- " << endl;

	for (unsigned int i = 0; i < tokenFreqTable.size(); i++)
	{
		cout << tokenFreqTable.at(i).token << " " << tokenFreqTable.at(i).freq << endl;
	}

	for (unsigned int i = 0; i < tokenFreqTable.size(); i++)
	{
		encoder.put(tokenFreqTable.at(i).token, i + 1);
	}

	for (unsigned int i = 0; i < tokenFreqTable.size(); i++)
	{
		decoder.put(tokenFreqTable.at(i).token, i + 1);
	}

	ifstream origfile("movieReviews.txt");
	if (origfile.fail()) {
		cout << "could not open file" << endl;
		exit(1);
	}

	ofstream encodefile("encoder.txt");
	if (encodefile.fail()) {
		cout << "could not open file" << endl;
		exit(1);
	}

	while (!origfile.eof()) {
		getline(origfile, line);
		int len = line.size();
		while (len > 0) {     // identify all individual strings
			bool inTable = false;
			string sub;
			int loc = 0;

			loc = line.find_first_of(delim);
			if (loc > 0)
			{
				sub = line.substr(0, loc);
				line = line.substr(loc, line.size());
			}
			else
			{
				sub = line.substr(0, 1);
				line = line.substr(1, line.size());
			}
			encodefile << encoder.getCode(sub) << " ";
			len = line.size();

			//cout << "Encode Proccessing: " << sub << endl;
		}
		encodefile << "\n";
	}
	origfile.close();
	encodefile.close();

	ifstream enfile("encoder.txt");
	if (enfile.fail()) {
		cout << "could not open file" << endl;
		exit(1);
	}

	ofstream defile("decoder.txt");
	if (defile.fail()) {
		cout << "could not open file" << endl;
		exit(1);
	}

	while (!enfile.eof()) {
		getline(enfile, line);
		int len = line.size();
		while (len > 0) {     // identify all individual strings
			string sub;
			len = line.find(" ");
			if (len > 0) {
				sub = line.substr(0, len);
				line = line.substr(len + 1, line.size());
				//cout << "defile sub: " << sub << endl;
				defile << decoder.getDecodeWord(stoi(sub));
			}
			else {
				defile << "\n";
			}
			//cout << "Decode Proccessing: " << sub << endl;

		}
	}
	origfile.close();
	defile.close();

	ofstream decodefile("decoderfile.txt");
	if (decodefile.fail()) {
		cout << "could not open file" << endl;
		exit(1);
	}

	cout << endl << "Token Mapping Table: " << endl;
	cout << "-------------------- " << endl;
	for (unsigned int i = 0; i < tokenFreqTable.size(); i++)
	{
		decodefile << i + 1 << " " << tokenFreqTable.at(i).token << endl;
		cout << i + 1 << " " << tokenFreqTable.at(i).token << endl;
	}
	return 0;
}

void quicksort(vector<tokenFreq>& values, int left, int right)
{
	if (left < right)
	{
		int pivotIndex = partition(values, left, right);
		quicksort(values, left, pivotIndex - 1);
		quicksort(values, pivotIndex, right);
	}
}

int partition(vector<tokenFreq>& values, int left, int right)
{
	int pivotIndex = left + (right - left) / 2;
	int pivotValue = values[pivotIndex].freq;
	int i = left, j = right;
	int temp;
	while (i <= j)
		//while (i>j)
	{
		while (values[i].freq > pivotValue)
		{
			i++;
		}
		while (values[j].freq < pivotValue)
		{
			j--;
		}
		if (i <= j)
			//if (i < j)
		{
			string temp1 = values[i].token;
			int temp2 = values[i].freq;
			values[i].token = values[j].token;
			values[i].freq = values[j].freq;
			values[j].token = temp1;
			values[j].freq = temp2;
			i++;
			j--;
		}
	}
	return i;
}
