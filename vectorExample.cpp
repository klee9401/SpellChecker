#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <locale>

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
	bool error = false;
	locale loc;

	ifstream dictionary("dictionary.txt");
	
	if (dictionary.fail()) {
		cerr << "Cannot open 'dictionary'" << endl;
		exit(-1);
	}
	
	dictionary >> s;

	do {
		dic.push_back(s);
	} while(dictionary >> s);
	
	// for (int k = 0; k < dic.size(); ++k) {
	// 	cout << dic[k] << endl;
	// }

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
	// textFile.get(ch);

	while (!textFile.eof()) {

		textFile >> wrd;

		//~ if (textFile.eof())
			//~ break;

		for (i = 0; i < wrd.length(); ++i) {
			toupper(wrd[i], loc);
		}

		if(!wordFound(wrd)) {

			error = true;

			if (current == lineNum) {
				cout << ", " << s;
			}
		
			else {
				cout << "On line " << lineNum << " : " << wrd << endl;
				current = lineNum;
			}
		}
		
		++lineNum;
	}
	
	if (!error) {
         cout << "NONE";
	}
    
   dictionary.close();
   textFile.close();
    
   return 0;
}