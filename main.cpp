#include <iostream>
#include "Trie.h"


int main() {
	Trie* root = new Trie();
//	root->insert(root, "hello");
//	root->insert(root, "dog");
//	root->insert(root, "hell");
//	root->insert(root, "cat");
//	root->insert(root, "a");
//	root->insert(root, "hel");
//	root->insert(root, "help");
//	root->insert(root, "helps");
//	root->insert(root, "helping");

//	int comp = root->printAutoSuggestions(root, "hel");
	int option = 0;
	while(option != 3){
		cout << "Here's the options:\n1. Insert\n2. Suggest\n3. Quit" << endl;
		cin >> option;
		if(option == 1){
			cout << "What word do you want to type?" << endl;
			string word; cin >> word;
			root->insert(root, word);
		}
		else if(option == 2){
			cout << "Type a prefix to get suggestions:" << endl;
			string word; cin >> word;
			cout << "The suggestions are:\n";
			int comp = root->printAutoSuggestions(root, word);
			if (comp == -1)
				cout << "No other strings found with this prefix\n";
			else if (comp == 0)
				cout << "No string found with this prefix\n";
		}
	}

}
