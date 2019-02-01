#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <locale>
#include "windows.h"
#include "psapi.h"

using namespace std;

vector<string> dic;

char* toUpper(char *s) {
	char *str;
	
	for (str = s; *s = toupper(*s); ++s);
	
	return str;
}

bool wordFound(string word) {
	for (int i = 0; i < dic.size(); ++i) {

		if (word.compare(dic[i]) == 0) {
			return true;
		}
	}
	return false;
}

int main (int argc, char* argv[]) {
	char fileName[20], s[80];
	string wrd;
	int i, lineNum = 1, current;
	bool noError = true;
	locale loc;
	clock_t startTime;

	ifstream dictionary("dictionary.txt");
	
	if (dictionary.fail()) {
		cerr << "Cannot open 'dictionary'" << endl;
		exit(-1);
	}
	
	dictionary >> s;

	do {
		dic.push_back(toUpper(s));
	} while(dictionary >> s);

	if (argc != 2) {
		//~ cout << "Enter a file name: ";
		//~ cin >> fileName;
		string f = "test.txt";
		strcpy(fileName, f.c_str());
	}

	else strcpy(fileName, argv[1]);

	ifstream textFile(fileName);

	if(textFile.fail()) {
		cout << "Cannot open " << fileName << endl;
		exit(-1);
	}

	cout << "Mispelled words:" << endl << endl;
	
	startTime = clock();

	while (!textFile.eof()) {

		textFile >> wrd;

		for (i = 0; i < wrd.length(); ++i) {
			wrd[i] = toupper(wrd[i], loc);
		}

		if(!wordFound(wrd)) {
			noError = false;
			cout << wrd << endl;
		}
	}
	
	if (noError) {
         cout << "NONE";
	}
    
   dictionary.close();
   textFile.close();
	
	float runTime;
	
	runTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	cout << "\nruntime: " << runTime << endl;
	
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
   SIZE_T physMemUsedByMe = pmc.WorkingSetSize;

   cout << "memory used: " << physMemUsedByMe << endl;

   return 0;
}