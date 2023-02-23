#include "Decoder.h"
#include "WordEntry.h"

/* HashTable constructor
*  input s is the size of the array
*  set s to be size
*  initialize array of lists of WordEntry
*/
Decoder::Decoder(int s)
{
	decode = new list<WordEntry>[s];
	size = s;
}


/* computeHash
*  return an integer based on the input string
*  used for index into the array in hash table
*  be sure to use the size of the array to
*  ensure array index doesn't go out of bounds
*/
int Decoder::decodeHash(const int& code)
{
	return code % size;
}


/* put
*  input: string word and int score to be inserted
*  First, look to see if word already exists in hash table
*   if so, addNewAppearence with the score to the WordEntry
*   if not, create a new Entry and push it on the list at the
*   appropriate array index
*/
void Decoder::put(const string& s, int score)
{
	int idx = decodeHash(score);
	WordEntry temp(s, score);
	decode[idx].push_back(temp);
	return;
}

/* getAverage
*  input: string word
*  output: the result of a call to getAverage()
*          from the WordEntry
*  Must first find the WordEntry in the hash table
*  then return the average
*  If not found, return the value 2.0 (neutral result)
*/

string Decoder::getDecodeWord(const int& s)
{
	int idx = decodeHash(s);

	list<WordEntry>::iterator i;
	for (i = decode[idx].begin(); i != decode[idx].end(); i++)
	{
		if (i->getCode() == s)
		{
			return i->getWord();
		}
	}

	return "";
}


/* contains
* input: string word
* output: true if word is in the hash table
*         false if word is not in the hash table
*/
/*bool HashTable::contains(const string& s)
{
	int idx = decodeHash(s);

	list<WordEntry>::iterator i;
	for (i = hashTable[idx].begin(); i != hashTable[idx].end(); i++)
	{
		if (i->getWord() == s)
		{
			return true;
		}
	}
	return false;
}*/
