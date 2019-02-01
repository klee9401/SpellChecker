#include "bst.h"
//With printing wrong words
//without suggestion and AVL balance tree.


int main()
{
	Tree* DTree = new Tree("ABC", NULL, NULL);

	std::string fword;

	std::ifstream in_stream;
	in_stream.open("dictionary.txt");

	if (in_stream.good())
	{
		while (!in_stream.eof())
		{
			in_stream >> fword;
			

			DTree->insert(toUpper(fword));

		}
	}

	//User Interface: Enter sentence
	std::string txt;

	std::cout << "Please enter a sentence: ";
	std::getline(std::cin, txt);
	std::stringstream ss(txt);
	std::string errorList[10000];
	std::string typedWord;
	std::string word;
	bool find = false;
	bool error = false;

	int i = 0;

	//search for error
	while (ss >> word)
	{
		//search for the word in tree
		typedWord = word;
		find = DTree->search(toUpper(word));


		if (!find)
		{
			errorList[i] = typedWord;
			error = true;
			//std::cout << "Find ERROR\n";
			i++;
		}
	}

	//printing result
	if (error)
	{
		std::cout << "\nThe below word(s) are spelt wronyly\n";

		for (int j = 0; j < i; j++)
		{
			int q = j + 1;

			std::cout << q << ". " << errorList[j] << std::endl;
		}
	}
	else
	{
		std::cout << "The sentence is perfectly spelt. Congrats." << std::endl;
	}

	//inOrder(DTree);


	in_stream.close();


	std::cin.get();
}
