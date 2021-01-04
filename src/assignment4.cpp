#include <cctype>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "binarySearchTree.h"
#include "word.h"

void duplicateItemFound(word& wordEntry, const word& insertingWord);
void wordFound(const word& wordEntry);

int main()
{
	// string holding filename
	std::string filename = "english_words.txt";
	// ifstream object to hold input file
	std::ifstream inputFile;
	// original wordcount is 0
	int wordCount = 0;
	// string variable to hold each word the user types
	std::string enteredWord = "";
	// creating binary search tree
	binarySearchTree<word> tree;

	// opening input file and processing if it worked
	inputFile.open(filename);
	if(inputFile)
	{
		// variable to hold each word in file to add to tree
		std::string tempWord = "";
		while(inputFile >> tempWord)
		{
			// adding each word to the binary tree while accounting for duplicates
			word* newWord = new word(tempWord);
			tree.insert(*newWord, duplicateItemFound);
			delete newWord;

		}
		// assigning word count
		wordCount = static_cast<int>(tree.size());

		// printing starting messages
		std::cout << "Test of find words\n" << std::endl;
		std::cout << "The dictionary has been built with " << wordCount <<" keys in the dictionary" << std::endl;

		// looping while user input isn't "quit-now"
		while(enteredWord!="quit-now")
		{
			tempWord ="";
			// taking in the word to find
			std::cout << "Word to unscramble (quit-now to stop): " << std::endl;
			std::cin >> enteredWord;
			// quit if word is quit-now
			if(enteredWord=="quit-now")
			{
				break;
			}

			// making lower case and sorting the entered word
			for(int i = 0; i < static_cast<int>(enteredWord.length());i++)
			{
				tempWord += static_cast<char>(tolower(enteredWord.at(i)));
			}
			std::cout << std::endl;
			std::sort(tempWord.begin(), tempWord.end());
			// creating word object containing word key of scrambled word
			word anotherWord(tempWord);
			// outputting entered word
			std::cout << "Scrambled word "<< enteredWord;
			// output message if word wasn't found
			if(!(tree.find(anotherWord, wordFound)))
			{
				std::cout << " was not found\n" << std::endl;
			}

		}
		// closing input file
		inputFile.close();

	}
	return 0;
}


void wordFound(const word& wordEntry)
{
	// vector containing the actual words corresponding to a word key
	std::vector<std::string> unscrambledWords = wordEntry.getWords();
	// output message depending on the number of words in the vector
	if(unscrambledWords.size()==1)
	{
		std::cout << " maps to word: " << unscrambledWords.at(0) << std::endl;
	}
	else
	{
		std::cout << " maps to words: ";
		// print out all the words with spaces in between if more than 1
		for(int i = 0; i < static_cast<int>(unscrambledWords.size()); i++)
		{
			std::cout << unscrambledWords.at(i) << " ";

		}
		// new line for formatting
		std::cout << std::endl;
	}
	// new line for formatting
	std::cout << std::endl;
}

void duplicateItemFound(word& wordEntry, const word& insertingWord)
{
	// if a word with the same key as another word is found, add that word to the word key's vector of actual words
	wordEntry.addWord(insertingWord);
}
