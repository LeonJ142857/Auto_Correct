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
	bool isWordEnd;

public:
	Trie *children[ALPHABET_SIZE]{};
	Trie(){
		for (auto & i : children)
			i = nullptr;
		isWordEnd = false;
	};
	Trie * getNode();
// If not present, inserts key into trie.  If the
// key is prefix of trie node, just marks leaf node
	void insert(Trie *root, const string& key);
// Returns true if key presents in trie, else false
	bool search(Trie *root, const string& key);
// Returns 0 if current node has a child
// If all children are NULL, return 1.
	bool isLastNode(Trie* root);
// Recursive function to print auto-suggestions for given
// node.
	void suggestionsRec(Trie* root, string currPrefix);

// print suggestions for given query prefix.
	int printAutoSuggestions(Trie* root, const string& query);

};


#endif //AUTO_CORRECT_TRIE_H
