#include "avl.h"

int height(Tree *T)
{
	if (T == NULL)
		return 0;
	return T->height;
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

Tree::Tree(std::string newword, Tree* L, Tree* R)
	: word(newword)
{
	leftptr = L;
	rightptr = R;
}

/* Helper function that allocates a new node with the given key and
	NULL left and right pointers. */
Tree* newNode(std::string newword)
{
	struct Tree* T = new Tree("A", NULL, NULL);
	T->setWord(newword);
	T->setLeft(NULL);
	T->setRight(NULL);
	T->height = 1;  // new node is initially added at leaf 
	return T;
}

Tree *rotateRight(Tree* T)
{
	Tree* newRoot = T->left();
	T->setLeft(newRoot->right());
	newRoot->setRight(T);

	// Update heights 
	T->height = max(height(T->left()), height(T->right())) + 1;
	newRoot->height = max(height(newRoot->left()), height(newRoot->right())) + 1;

	// Return new root 
	return newRoot;
}

Tree *rotateLeft(Tree* T)
{
	Tree* newRoot = T->right();
	T->setRight(newRoot->left());
	newRoot->setLeft(T);

	//  Update heights 
	T->height = max(height(T->left()), height(T->right())) + 1;
	newRoot->height = max(height(newRoot->left()), height(newRoot->right())) + 1;

	// Return new root 
	return newRoot;
}

// To see which side of the subtree is unbalanced
int diff(Tree* T)
{
	if (T == NULL)
		return 0;
	return height(T->left()) - height(T->right());
}

//Recursive func to insert and rearrange the tree until it is balanced
Tree* insert(Tree* T, std::string newword)
{
	//When T is NULL, end of normal insertion
	if (T == NULL)
		return(newNode(newword));

	//go to left and connect back with the root
	if (newword < T->rootData())
	{
		T->setLeft(insert(T->left(), newword));
	}
	//go to right and connect back with the root
	else if (newword > T->rootData())
	{
		T->setRight(insert(T->right(), newword));
	}
	// Key must be unique in BST
	else
		return T;

	//Update the height of the tree
	T->height = max(height(T->left()), height(T->right())) + 1;

	//Checking if the tree is unbalanced and which side of the subtree causes it
	int balance = diff(T);

	//Four cases of unbalanced tree: LL, RR (1 time rotation), LR, RL (2 time rotation)

	// Left Left Case 
	if (balance > 1 && newword < T->left()->rootData())
	{
		return rotateRight(T);
	}

	// Right Right Case 
	if (balance < -1 && newword > T->right()->rootData())
	{
		return rotateLeft(T);
	}

	// Left Right Case 
	if (balance > 1 && newword > T->left()->rootData())
	{
		T->setLeft(rotateLeft(T->left()));
		return rotateRight(T);
	}

	// Right Left Case 
	if (balance < -1 && newword < T->right()->rootData())
	{
		T->setRight(rotateRight(T->right()));
		return rotateLeft(T);
	}

	/* return the (unchanged) node pointer */
	return T;
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
		else if (item == current->word)
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

void preOrder(Tree* T)
{
	if (T == NULL)
	{
		return;
	}

	std::cout << T->rootData() << " ";
	preOrder(T->left());
	preOrder(T->right());
}

//FUNC to make all word to be uppercase for comparison
std::string& toUpper(std::string& word)
{
	std::transform(word.begin(), word.end(), word.begin(), static_cast<int(*)(int)>(std::toupper));
	return word;
}
