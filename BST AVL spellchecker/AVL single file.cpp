#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

struct Tree
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

	void insert(std::string newword);
	bool search(std::string item);

};


// A utility function to get maximum of two integers 
int max(int a, int b);

// A utility function to get the height of the tree 
int height(Tree *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

// A utility function to get maximum of two integers 
int max(int a, int b)
{
	return (a > b) ? a : b;
}

/* Helper function that allocates a new node with the given key and
	NULL left and right pointers. */
struct Tree* newNode(std::string newword)
{
	struct Tree* T = new Tree("A", NULL, NULL);
	T->setWord(newword);
	T->setLeft(NULL);
	T->setRight(NULL);
	T->height = 1;  // new node is initially added at leaf 
	return T;
}

// A utility function to right rotate subtree rooted with y 
// See the diagram given above. 
struct Tree *rightRotate(Tree* T)
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

// A utility function to left rotate subtree rooted with x 
// See the diagram given above. 
struct Tree *leftRotate(Tree* T)
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

// Get Balance factor of node N 
int getBalance(Tree* T)
{
	if (T == NULL)
		return 0;
	return height(T->left()) - height(T->right());
}

// Recursive function to insert a key in the subtree rooted 
// with node and returns the new root of the subtree. 
Tree* insert(Tree* T, std::string newword)
{
	/* 1.  Perform the normal BST insertion */
	if (T == NULL)
		return(newNode(newword));

	if (newword < T->rootData())
		T->setLeft(insert(T->left(), newword));
	else if (newword > T->rootData())
		T->setRight(insert(T->right(), newword));
	else // Equal keys are not allowed in BST 
		return T;

	/* 2. Update height of this ancestor node */
	T->height = max(height(T->left()), height(T->right())) + 1;

	/* 3. Get the balance factor of this ancestor
		  node to check whether this node became
		  unbalanced */
	int balance = getBalance(T);

	// If this node becomes unbalanced, then 
	// there are 4 cases 

	// Left Left Case 
	if (balance > 1 && newword < T->left()->rootData())
		return rightRotate(T);

	// Right Right Case 
	if (balance < -1 && newword > T->right()->rootData())
		return leftRotate(T);

	// Left Right Case 
	if (balance > 1 && newword > T->left()->rootData())
	{
		T->setLeft(leftRotate(T->left()));
		return rightRotate(T);
	}

	// Right Left Case 
	if (balance < -1 && newword < T->right()->rootData())
	{
		T->setRight(rightRotate(T->right()));
	}

	/* return the (unchanged) node pointer */
	return T;
}

void preOrder(Tree* T);

//int& toUpper(int& word);

Tree::Tree(std::string newword, Tree* L, Tree* R)
	: word(newword)
{
	leftptr = L;
	rightptr = R;
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

/*int& toUpper(int& word)
{
	std::transform(word.begin(), word.end(), word.begin(), static_cast<int(*)(int)>(std::toupper));
	return word;
}*/

//With printing wrong words
//without suggestion and AVL balance tree.


int main()
{
	struct Tree *root = NULL;

	/* Constructing tree given in the above figure */
	root = insert(root, "A");
	root = insert(root, "B");
	root = insert(root, "C");


	preOrder(root);

	delete root;
	std::cin.get();
}
