//
// Created by Asus on 1/10/2022.
//

#ifndef AUTO_CORRECT_TRIE_H
#define AUTO_CORRECT_TRIE_H

//#include<bits/stdc++.h>
#include <string>
using namespace std;

// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)

// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

// trie node
class Trie
{

private:
	bool wordEnd;

public:
	Trie *children[ALPHABET_SIZE]{};
	//Constructor of a Trie node
	Trie(){
		//set all child nodes as null
		for (auto & i : children)
			i = nullptr;
		//initial root node is not end of word
		//because we have not inserted anything yet
		wordEnd = false;
	};
	Trie * getNode();

	//insert each character as a node
	//a word is marked by its end node having
	//isEndWord flag set to true
	void insert(Trie *root, const string& key);

	//checks whether or not a particular string
	//is a word stored in the trie
	bool search(Trie *root, const string& key);

	//checks whether or not a node is the last node
	//meaning it has no children
	bool isLastNode(Trie* root);

	//recursive part that explores all options
	//from a particular node
	void SuggestRecursive(Trie* root, string currPrefix);

	//the main function that supports the autocorrect feature
	//lets you print the suggestions for what words are available
	pair<int, vector<int>> printSuggestions(Trie* root, const string& query);

};


#endif //AUTO_CORRECT_TRIE_H
