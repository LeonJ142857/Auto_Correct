//
// Created by Asus on 1/10/2022.
//
#include <iostream>
#include "Trie.h"

Trie * Trie::getNode()
{
	Trie *pNode = new Trie;
	pNode->isWordEnd = false;
	for (auto & i : pNode->children)
		i = nullptr;
	return pNode;
}

//insert each character as a node
//a word is marked by its end node having
//isEndWord flag set to true
void Trie::insert(Trie *root, const string &key) {
	Trie *pCrawl = root;
	for (char level : key)
	{
		int index = CHAR_TO_INDEX(level);
		if (!pCrawl->children[index])
			pCrawl->children[index] = getNode();
		pCrawl = pCrawl->children[index];
	}
	pCrawl->isWordEnd = true;
}

//checks whether or not a particular string
//is a word stored in the trie
bool Trie::search(Trie *root, const string &key) {
	int length = key.length();
	Trie *pCrawl = root;
	for (int level = 0; level < length; level++)
	{
		int index = CHAR_TO_INDEX(key[level]);
		if (!pCrawl->children[index])
			return false;
		pCrawl = pCrawl->children[index];
	}
	return (pCrawl != nullptr && pCrawl->isWordEnd);
}

//checks whether or not a node is the last node
//meaning it has no children
bool Trie::isLastNode(Trie *root) {
	for (auto & i : root->children)
		if (i) return false;
	return true;
}

//recursive part that explores all options
//from a particular node
void Trie::suggestionsRec(Trie *root, string currPrefix) {
	if (root->isWordEnd)
	{
		cout << currPrefix;
		cout << endl;
	}
	if (isLastNode(root)) return;
	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (root->children[i])
		{
			currPrefix.push_back(97 + i);
			suggestionsRec(root->children[i], currPrefix);
			currPrefix.pop_back();
		}
	}
}

//the main function that supports the autocorrect feature
//lets you print the suggestions for what words are available
int Trie::printAutoSuggestions(Trie* root, const string& query){
	Trie* pCrawl = root;
	int level;
	int n = query.length();
	for (level = 0; level < n; level++)
	{
		int index = CHAR_TO_INDEX(query[level]);
		if (!pCrawl->children[index])
			return 0;
		pCrawl = pCrawl->children[index];
	}
	bool isWord = pCrawl->isWordEnd;
	bool isLast = isLastNode(pCrawl);
	if (isWord && isLast)
	{
		cout << query << endl;
		return -1;
	}
	if (!isLast)
	{
		const string& prefix = query;
		suggestionsRec(pCrawl, prefix);
		return 1;
	}
}


