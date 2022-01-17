//
// Created by Asus on 1/10/2022.
//
#include <iostream>
#include <vector>
#include "Trie.h"

Trie * Trie::getNode()
{
	Trie *pNode = new Trie;
	pNode->wordEnd = false;
	for (auto & i : pNode->children)
		i = nullptr;
	return pNode;
}

//insert each character as a node
//a word is marked by its end node having
//isEndWord flag set to true
void Trie::insert(Trie *root, const string &key) {
	//crawler pointer for traversing the trie
	Trie *trieCrawler = root;
	//for each character in the string
	//if the index at that particular character is null
	//then we create a new node
	for (char c : key)
	{
		int index = CHAR_TO_INDEX(c);
		//if null then create new node
		if (!trieCrawler->children[index])
			trieCrawler->children[index] = getNode();
		//always traverse deeper whatever happens
		trieCrawler = trieCrawler->children[index];
	}
	//set wordEnd flag as true to mark
	//that a word has been inserted
	trieCrawler->wordEnd = true;
}

//checks whether or not a particular string
//is a word stored in the trie
bool Trie::search(Trie *root, const string &key) {
	//crawler pointer
	Trie *trieCrawler = root;
	//searching starts from level 0 which is root
	//and all the way down until we find the word
	for (int level = 0; level < key.length(); level++)
	{
		int index = CHAR_TO_INDEX(key[level]);
		//if at any point, we encounter a null node
		//at the index we traverse, we return false
		if (!trieCrawler->children[index])
			return false;
		//traverse deeper
		trieCrawler = trieCrawler->children[index];
	}
	//if at the end of the traversal
	//the crawler pointer is not null and has the wordEnd
	//flag set to true, we return true
	return (trieCrawler != nullptr && trieCrawler->wordEnd);
}

//checks whether or not a node is the last node
//meaning it has no children
bool Trie::isLastNode(Trie *root) {
	//simple check for each child node
	//if any is not null then return false
	for (auto & i : root->children)
		if (i) return false;
	//return true if all child is null
	return true;
}

//recursive part that explores all options
//from a particular node
void Trie::SuggestRecursive(Trie *root, string currPrefix) {
	//if we reach the end of a word
	//we print the word
	if (root->wordEnd)
		cout << currPrefix << endl;
	//if node is the last node,
	//backtrack to the previous call stack
	if (isLastNode(root)) return;
	//for each node that is not null
	//we append the 'character' (converted from the index)
	//to the suggestion string and recurse deeper
	//after the recursive call is done, we pop one letter back
	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (root->children[i])
		{
			currPrefix.push_back((char)('a' + i));
			SuggestRecursive(root->children[i], currPrefix);
			currPrefix.pop_back();
		}
	}
}

//the main function that supports the autocorrect feature
//lets you print the suggestions for what words are available
pair<int, vector<string>> Trie::printSuggestions(Trie* root, vector<string> suggestions, const string& query){
	//crawler pointer, set to root
	Trie* trieCrawler = root;
	//perform standard search algorithm
	for (int level = 0; level < query.length(); level++)
	{
		//predefined MACRO for converting character to integer index
		int index = CHAR_TO_INDEX(query[level]);
		if (!trieCrawler->children[index])
			return 0;
		trieCrawler = trieCrawler->children[index];
	}
	//wordEnd flag and isLastNode boolean value is stored
	//isLastNode signifies that it is the last node (has no more children)
	bool isLast = isLastNode(trieCrawler);
	//if prefix is the last node and is the end of a word
	if (trieCrawler->wordEnd && isLast)
	{
		//then we print the query
		cout << query << endl;
		//return -1 to indicate there is only one exact match
		return -1;
	}
	//if prefix is not the last match and still have children
	if (!isLast)
	{
		//we call the recursive function to print
		//all of the strings that are available in the trie
		//from this node that represents  the last node of the prefix
		SuggestRecursive(trieCrawler, query);
		return 1;
	}
}


