#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

class Tree
{
private:
	std::string word;
	Tree* leftptr;
	Tree* rightptr;
public:
	Tree(std::string newword, Tree* L, Tree* R);
	~Tree() {}
	std::string rootData();
	Tree* left();
	Tree* right();
	void insert(std::string newword);
	bool search(std::string item);

};

void inOrder(Tree* T);

std::string& toUpper(std::string& word);
