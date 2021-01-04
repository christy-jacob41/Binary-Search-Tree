
#include "word.h"
// default constructor
word::word()
{
	realWords = {};
	wordKey = "";
}
// constructor
word::word(std::string newWord)
{
	// add the word after making it lower case
	realWords = {""};
	std::string tempWord = newWord;
	for(int i = 0; i < static_cast<int>(tempWord.length()); i++)
	{
		realWords.at(0) += (char)tolower(tempWord.at(i));
	}
	// change the key after sorting
	for(int i = 0; i < static_cast<int>(tempWord.length()); i++)
	{
		wordKey += realWords.at(0).at(i);
	}
	std::sort(wordKey.begin(), wordKey.end());
}
// overriding the ==, <, and > operators
bool word::operator==(word otherWord) const
{
	return this->getWordKey()==otherWord.getWordKey();
}
bool word::operator<(word otherWord) const
{
	return this->getWordKey()<otherWord.getWordKey();
}
bool word::operator>(word otherWord) const
{
	return this->getWordKey()>otherWord.getWordKey();
}
// overriding the << operator
std::ostream& operator<<(std::ostream &out, const word &outputWord)
{
	// holds word key
	std::string key = outputWord.getWordKey();
	// print for formatting
	out << "[" << key << ", {";
	// get the vector of words for the specified key
	std::vector<std::string> realWords = outputWord.getWords();
	// print out each word in the vector
	for(int i = 0; i < static_cast<int>(realWords.size());i++)
	{
		if(i==static_cast<int>((realWords.size()-1)))
			out << realWords.at(i);
		else
		{
			out << realWords.at(i) << ", ";
		}
	}
	// print for formatting
	out << "}]" << std::endl;
	// return ostream object
	return out;
}
