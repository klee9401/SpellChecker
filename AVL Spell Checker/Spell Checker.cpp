#include "avl.h"

#include <ctime>
#include "windows.h"
#include "psapi.h"
#include <vector>

int main()
{
	clock_t startTime;
	startTime = clock();

	Tree* DTree = NULL;

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

		//comparing and printing error
		std::cout << "The below word(s) are spelt wronyly\n";

		//insert dictionary
		while (!in_stream.eof())
		{
			in_stream >> fword;
			DTree = insert(DTree, toUpper(fword));
		}

		int errorCount = 0;

		//read test file and save words to vector
		while (!instream.eof())
		{
			instream >> testword;

			bool find = false;

			find = DTree->search(toUpper(testword));


			if (!find)
			{
				//std::cout << "Find ERROR\n";
				errorCount += 1;
				std::cout << errorCount << ". " << testword << std::endl;
			}
		}

		if (errorCount == 0)
		{
			std::cout << "The sentence is perfectly spelt. Congrats." << std::endl;
		}		
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

	std::cout << "\n\nTotal height: " << DTree->height << std::endl;

	std::cin.get();
	std::cin.get();
}