#include "avl.h"

#include <ctime>
#include "windows.h"
#include "psapi.h"
#include <vector>

int main()
{
	clock_t startTime;
	startTime = clock();

	Tree* DTree = new Tree("ABC", NULL, NULL);

	//for in_stream dictionary
	std::string fword;

	std::ifstream in_stream;

	//for instream test.txt
	std::string filename;
	std::string testword;
	std::vector<std::string> save;

	in_stream.open("dictionary.txt");

	if (in_stream.good())
	{
		//Ask for test file name
		std::ifstream instream;
		std::cout << "Please enter a file name: ";
		std::cin >> filename;
		instream.open(filename);

		//insert dictionary
		while (!in_stream.eof())
		{
			in_stream >> fword;
			DTree = insert(DTree, toUpper(fword));
		}

		//read test file and save words to vector
		while (!instream.eof())
		{
			instream >> testword;

			if (testword.size() > 0)
			{
				save.emplace_back(testword);
			}
		}

		//
		std::vector<std::string> errorList;
		std::string savedError;
		std::string word;
		bool find = false;
		bool error = false;

		int i = 0;

		//search for error
		for (int count = 0; count < save.size(); count++)
		{
			//save word for the error reporting list
			savedError = save[count];
			find = DTree->search(toUpper(save[count]));


			if (!find)
			{
				errorList.emplace_back(savedError);
				error = true;
				//std::cout << "Find ERROR\n";
			}
		}

		//printing result
		if (error)
		{
			std::cout << "The below word(s) are spelt wronyly\n";

			for (int errorCount = 0; errorCount < errorList.size(); errorCount++)
			{
				//n is for the order of numbering
				int n = errorCount + 1;
				std::cout << n << ". " << errorList[errorCount] << std::endl;
			}
		}
		else
		{
				std::cout << "The sentence is perfectly spelt. Congrats." << std::endl;
		}


		//inOrder(DTree);
		
	}
	else
	{
		std::cerr << "ERROR: Dictionary is not opened" << std::endl;
	}

	in_stream.close();

	float runTime;

	runTime = ((float)(clock() - startTime) / CLOCKS_PER_SEC);

	std::cout << "\nruntime: " << runTime << std::endl;


	PROCESS_MEMORY_COUNTERS_EX pmc;
	// GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
	GetProcessMemoryInfo(GetCurrentProcess(), reinterpret_cast<PPROCESS_MEMORY_COUNTERS>(&pmc), sizeof(pmc));
	SIZE_T memoryUsage = pmc.PrivateUsage; // WorkSetSize - physical memory

	std::cout << "memory used: " << memoryUsage << std::endl;

	std::cin.get();
	std::cin.get();
}