#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <chrono>
#include "Trie.h"

string random_string(size_t length)
{
	static const string alphabet = "abcdefghijklmnopqrstuvwxyz" ;
	static default_random_engine rng(time(nullptr)) ;
	static uniform_int_distribution<size_t> distribution( 0, alphabet.size() - 1 ) ;
	string str;
	while(str.size() < length) str += alphabet[distribution(rng)];
	return str ;
}

vector<string> random_strings(int STRING_LENGTH, int n){
	vector<string> random_strings;
	for(int i=1; i <= n; ++i)
		random_strings.push_back(random_string(STRING_LENGTH));
	return random_strings;
}

void time_count_insert_util(Trie* root, int n, int STRING_LENGTH){
	chrono::steady_clock sc;
	vector<string> strings = random_strings(STRING_LENGTH, n);
//	for(int i=0; i < n; ++i)
//		strings.push_back(random_string(STRING_LENGTH));
	auto begin = sc.now();
	for(auto& str : strings)
		root->insert(root, str);
	auto end = sc.now();
	auto time_loop = static_cast<chrono::duration<double>>(end - begin);
	cout << "for " << n << " inputs of strings length " << STRING_LENGTH;
	cout << " it takes " << time_loop.count() << " seconds" << endl;
}
void time_count_insert(Trie* root, int STRING_LENGTH){
	cout << "insertion time for string of length " << STRING_LENGTH << endl;
	time_count_insert_util(root, 10, STRING_LENGTH);
	time_count_insert_util(root, 100, STRING_LENGTH);
	time_count_insert_util(root, 1000, STRING_LENGTH);
	time_count_insert_util(root, 10000, STRING_LENGTH);
	time_count_insert_util(root, 100000, STRING_LENGTH);
}

void time_count_suggest_util(Trie* root, int n, int STRING_LENGTH, int m, int SUGGEST_LENGTH){
	chrono::steady_clock sc;
	vector<string> strings_insert = random_strings(STRING_LENGTH, n);
	vector<string> strings_suggest = random_strings(SUGGEST_LENGTH, m);

//	for(int i=0; i < n; ++i)
//		strings_insert.push_back(random_string(STRING_LENGTH));
	for(auto& str : strings_insert)
		root->insert(root, str);
	auto begin = sc.now();
	for(auto& str: strings_suggest)
		root->printSuggestions(root, str);
	auto end = sc.now();
	auto time_loop = static_cast<chrono::duration<double>>(end - begin);
	cout << "for " << n << " inputs of strings length " << STRING_LENGTH;
	cout << " and " << m << " suggestion strings of length " << SUGGEST_LENGTH;
	cout << " it takes " << time_loop.count() << " seconds" << endl;
}

void time_count_suggest_diffInput(Trie* root, int STRING_LENGTH, int m, int SUGGEST_LENGTH){
	cout << "suggestion time for string of length " << STRING_LENGTH << endl;
	time_count_suggest_util(root, 10, STRING_LENGTH, m, SUGGEST_LENGTH);
	time_count_suggest_util(root, 100, STRING_LENGTH, m, SUGGEST_LENGTH);
	time_count_suggest_util(root, 1000, STRING_LENGTH, m, SUGGEST_LENGTH);
	time_count_suggest_util(root, 10000, STRING_LENGTH, m, SUGGEST_LENGTH);
//	time_count_insert_util(root, 100, STRING_LENGTH, m, SUGGEST_LENGTH);
//	time_count_insert_util(root, 1000, STRING_LENGTH, m, SUGGEST_LENGTH);
//	time_count_insert_util(root, 10000, STRING_LENGTH);
//	time_count_insert_util(root, 100000, STRING_LENGTH)
}
void time_count_suggest_diffSuggest(Trie* root, int n, int STRING_LENGTH, int SUGGEST_LENGTH) {
	cout << "suggestion time for string of length " << STRING_LENGTH << endl;
	time_count_suggest_util(root, n, STRING_LENGTH, 2, SUGGEST_LENGTH);
	time_count_suggest_util(root, n, STRING_LENGTH, 3, SUGGEST_LENGTH);
	time_count_suggest_util(root, n, STRING_LENGTH, 5, SUGGEST_LENGTH);
	time_count_suggest_util(root, n, STRING_LENGTH, 8, SUGGEST_LENGTH);
}


int main() {
	Trie* root = new Trie(), *root2 = new Trie(), *root3 = new Trie();
	static const int STRING_LENGTH = 6, STRING_LENGTH2 = 20, STRING_LENGTH3 = 100,
	SUGGEST_LENGTH = 3, SUGGEST_LENGTH2 = 6, SUGGEST_LENGTH3 = 10;
//	time_count_insert(root, STRING_LENGTH);
//	time_count_insert(root2, STRING_LENGTH2);
//	time_count_insert(root3, STRING_LENGTH3);
//	time_count_suggest_util(root, 10, STRING_LENGTH, 10, SUGGEST_LENGTH);
//	time_count_suggest_util(root2, 100, STRING_LENGTH, 100, SUGGEST_LENGTH);
//	time_count_suggest_util(root3, 1000, STRING_LENGTH, 1000, SUGGEST_LENGTH);
	time_count_suggest_diffInput(root, STRING_LENGTH, 10, SUGGEST_LENGTH);
	time_count_suggest_diffInput(root, STRING_LENGTH, 100, SUGGEST_LENGTH);
	time_count_suggest_diffInput(root, STRING_LENGTH, 1000, SUGGEST_LENGTH);
	time_count_suggest_diffInput(root, STRING_LENGTH, 10000, SUGGEST_LENGTH);

//	cout << "insertion time for string of length " << STRING_LENGTH << endl;
//	time_count_insert_util(root, 10, STRING_LENGTH);
//	time_count_insert_util(root, 100, STRING_LENGTH);
//	time_count_insert_util(root, 1000, STRING_LENGTH);
//	time_count_insert_util(root, 10000, STRING_LENGTH);
//	time_count_insert_util(root, 100000, STRING_LENGTH);


//	chrono::steady_clock sc;   // create an object of `steady_clock` class
//	vector<string> strings, strings2, strings3, strings4;
//	for(int i = 0; i < 10; ++i)
//		strings.push_back(random_string(STRING_LENGTH));
//	for(int i = 0; i < 100; ++i)
//		strings2.push_back(random_string(STRING_LENGTH));
//	for(int i = 0; i < 1000; ++i)
//		strings3.push_back(random_string(STRING_LENGTH));
////	for(int i = 0; i < 10000; ++i)
////		strings4.push_back(random_string(STRING_LENGTH));
//	auto begin = sc.now();
//	for(auto& str : strings){
////		auto start = sc.now();     // start timer
//		root->insert(root, str);
////		auto end = sc.now();     // end timer
////		auto time_span = static_cast<chrono::duration<double>>(end - start);
////		cout << str << " " << time_span.count() << endl;
//	}
//	auto end = sc.now();
//	auto time_loop = static_cast<chrono::duration<double>>(end - begin);
//	cout << time_loop.count() << " seconds" << endl;
//	begin = sc.now();
//	for(auto& str: strings2)
//		root->insert(root, str);
//	end = sc.now();
//	time_loop = static_cast<chrono::duration<double>>(end - begin);
//	cout << time_loop.count() << " seconds" << endl;
//	begin = sc.now();
//	for(auto& str: strings3)
//		root->insert(root, str);
//	end = sc.now();
//	time_loop = static_cast<chrono::duration<double>>(end - begin);
//	cout << time_loop.count() << " seconds" << endl;

//	root->insert(root, "hello");
//	root->insert(root, "dog");
//	root->insert(root, "hell");
//	root->insert(root, "cat");
//	root->insert(root, "a");
//	root->insert(root, "hel");
//	root->insert(root, "help");
//	root->insert(root, "helps");
//	root->insert(root, "helping");

//	int comp = root->printSuggestions(root, "hel");
//	int option = 0;
//	while(option != 3){
//		cout << "Here's the options:\n1. Insert\n2. Suggest\n3. Quit" << endl;
//		cin >> option;
//		if(option == 1){
//			cout << "What word do you want to type?" << endl;
//			string word; cin >> word;
//			root->insert(root, word);
//		}
//		else if(option == 2){
//			cout << "Type a prefix to get suggestions:" << endl;
//			string word; cin >> word;
//			cout << "The suggestions are:\n";
//			int comp = root->printSuggestions(root, word);
//			if (comp == -1)
//				cout << "No other strings found with this prefix\n";
//			else if (comp == 0)
//				cout << "No string found with this prefix\n";
//		}
//	}

}
