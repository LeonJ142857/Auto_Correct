//
// Created by Asus on 1/10/2022.
//
#include <iostream>
#include "Trie.h"

Trie * Trie::getNode()
{
	struct Trie *pNode = new Trie;
	pNode->isWordEnd = false;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = NULL;

	return pNode;
}
// If not present, inserts key into trie.  If the
// key is prefix of trie node, just marks leaf node
void Trie::insert(Trie *root, const string &key) {
	Trie *pCrawl = root;

	for (char level : key)
	{
		int index = CHAR_TO_INDEX(level);
		if (!pCrawl->children[index])
			pCrawl->children[index] = getNode();

		pCrawl = pCrawl->children[index];
	}

	// mark last node as leaf
	pCrawl->isWordEnd = true;
}

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

	return (pCrawl != NULL && pCrawl->isWordEnd);
}

// Returns 0 if current node has a child
// If all children are NULL, return 1.
bool Trie::isLastNode(Trie *root) {
	for (auto & i : root->children)
		if (i) return 0;
	return 1;
}
// Recursive function to print auto-suggestions for given
// node.
void Trie::suggestionsRec(Trie *root, string currPrefix) {
	// found a string in Trie with the given prefix
	if (root->isWordEnd)
	{
		cout << currPrefix;
		cout << endl;
	}

	// All children struct node pointers are NULL
	if (isLastNode(root))
		return;

	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (root->children[i])
		{
			// append current character to currPrefix string
			currPrefix.push_back(97 + i);

			// recur over the rest
			suggestionsRec(root->children[i], currPrefix);
			// remove last character
			currPrefix.pop_back();
		}
	}
}
// print suggestions for given query prefix.
int Trie::printAutoSuggestions(Trie* root, const string& query){
	struct Trie* pCrawl = root;

	// Check if prefix is present and find the
	// the node (of last level) with last character
	// of given string.
	int level;
	int n = query.length();
	for (level = 0; level < n; level++)
	{
		int index = CHAR_TO_INDEX(query[level]);

		// no string in the Trie has this prefix
		if (!pCrawl->children[index])
			return 0;

		pCrawl = pCrawl->children[index];
	}

	// If prefix is present as a word.
	bool isWord = pCrawl->isWordEnd;

	// If prefix is last node of tree (has no
	// children)
	bool isLast = isLastNode(pCrawl);

	// If prefix is present as a word, but
	// there is no subtree below the last
	// matching node.
	if (isWord && isLast)
	{
		cout << query << endl;
		return -1;
	}

	// If there are are nodes below last
	// matching character.
	if (!isLast)
	{
		const string& prefix = query;
		suggestionsRec(pCrawl, prefix);
		return 1;
	}
}


