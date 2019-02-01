#include "bst.h"


Tree::Tree(std::string newword, Tree* L, Tree* R)
	: word(newword)
{
	leftptr = L;
	rightptr = R;
}

void Tree::insert(std::string newword)
{
	Tree* current = this;

	while (current != NULL)
	{
		if (newword > current->word)
		{
			if (current->rightptr == NULL)
			{
				current->rightptr = new Tree(newword, NULL, NULL);
				return;
			}
			else
			{
				current = current->rightptr;
			}
		}

		else if (newword < current->word)
		{
			if (current->leftptr == NULL)
			{
				current->leftptr = new Tree(newword, NULL, NULL);
				return;
			}
			else
			{
				current = current->leftptr;
			}
		}
		else if (newword == current->word)
		{
			//std::cout << "Target word " << newword << " exists in the dictionary.\n";
			return;
		}
	}
}

bool Tree::search(std::string item)
{
	Tree* current = this;

	while (current != NULL)
	{
		if (item > current->word)
		{
			if (current->rightptr == NULL)
			{
				return false;
			}
			else
			{
				current = current->rightptr;
			}
		}
		else if (item < current->word)
		{
			if (current->leftptr == NULL)
			{
				return false;
			}
			else
			{
				current = current->leftptr;
			}
		}
		else if (item == current-> word)
		{
			return true;
		}
	}
}

std::string Tree::rootData()
{
	return word;
}

Tree* Tree::left()
{
	return leftptr;
}

Tree* Tree::right()
{
	return rightptr;
}

void inOrder(Tree* T)
{
	if (T == NULL)
	{
		return;
	}
	
	inOrder(T->left());
	std::cout << T->rootData() << " ";
	inOrder(T->right());
}

std::string& toUpper(std::string& word)
{
	std::transform(word.begin(), word.end(), word.begin(), static_cast<int(*)(int)>(std::toupper));
	return word;
}