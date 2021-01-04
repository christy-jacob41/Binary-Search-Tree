/*
 * word.h
 *
 *  Created on: Apr 15, 2019
 *      Author: Christy Jacob
 */

#ifndef WORD_H_
#define WORD_H_

#include <cctype>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

class word
{

private:
	// vector holding strings and string variable to hold the actual words and their key
	std::vector<std::string> realWords;
	std::string wordKey;

public:
	// default constructor
	word();
	// constructor
	word(std::string newWord);
	// overriding the ==, <, and > operators
	bool operator==(word otherWord) const;
	bool operator<(word otherWord) const;
	bool operator>(word otherWord) const;
	// getter for the actual word vector and word key
	std::vector<std::string> getWords() const
	{
		return realWords;
	}
	std::string getWordKey() const
	{
		return wordKey;
	}
	// adds a word to the vector of actual words
	void addWord(word otherWord)
	{
		realWords.push_back(otherWord.getWords().at(0));
	}
};

// overriding the << operator
std::ostream& operator<<(std::ostream &out, const word &outputWord);

#endif /* WORD_H_ */
