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
	int height;
	Tree(std::string newword, Tree* L, Tree* R);
	~Tree() {}
	std::string rootData();
	Tree* left();
	Tree* right();

	void setWord(std::string W) { word = W; }
	void setLeft(Tree* L) { leftptr = L; }
	void setRight(Tree* R) { rightptr = R; }
	bool search(std::string item);

};

Tree* insert(Tree* T, std::string newword);

int diff(Tree* T);

Tree *rotateLeft(Tree* T);

Tree *rotateRight(Tree* T);

Tree* newNode(std::string newword);

int max(int a, int b);

int height(Tree *T);

void preOrder(Tree* T);

std::string& toUpper(std::string& word);
