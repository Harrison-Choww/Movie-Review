#include "WordEntry.h"

/* WordEntry contructor
* input: the string text (word) and the intial score the
*         word should be assigned to
*  note that numAppearances should be set to 1 here
*/

WordEntry::WordEntry(const string& text, int score)
	: word(text), code(score) {

}

/*getWord
* this accessor function is needed
* particularly in the HashTable code to get the word to be
* used for the hash value
* simple accessor function
*/
const string& WordEntry::getWord() {
	return word;
}

/* getAverage
*  returns the average score of the word
*  based on totalScore and numAppearances
*  note that typecasting -- turning one of the integers
*  to a double will be necessary to avoid integer division
*/
int WordEntry::getCode() {
	return code;
}
