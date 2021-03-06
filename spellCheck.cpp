#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <ctime>
#include "windows.h"
#include "psapi.h"
#include "trie.h"

using namespace std;

char* strupr(char *s) {
    char *ss;
    
    for (ss = s; *s = toupper(*s); s++);
    
    return ss;
}

int main(int argc, char* argv[])  {

    char fileName[25], s[80], ch;
    int i, lineNum = 1, current;
    bool noError = true;

    clock_t startTime;
    startTime = clock();

    ifstream dictionary("dictionary.txt");
    
    if (dictionary.fail()) {
       cerr << "Cannot open 'dictionary'\n";
       exit(-1);
    }
    
    dictionary >> s;
    Trie trie(strupr(s));   // initialize root;
    
    while (dictionary >> s) // initialize trie;
        trie.insert(strupr(s));
    
    cout << "Dictionary:" << endl;
    // trie.printTrie();
    cout << endl;
    
    // cout << endl << endl << "****** BREADTH-FIRST TRAVERSAL ******" << endl;
    // trie.printBreadthFirstCaller();
    
    
    //show words to see if they are misspelled
    if (argc != 2) {
         cout << "Enter a file name: ";
         cin  >> fileName;
    }

    else strcpy(fileName,argv[1]);
    
    ifstream textFile(fileName);
    
    if (textFile.fail()) {
       cout << "Cannot open " << fileName << endl;
       exit(-1);
    }

    cout << "Mispelled words:" << endl << endl;
    textFile.get(ch);

    while (!textFile.eof()) {
        
        while (true) {

            if (!textFile.eof() && !isalpha(ch)) { // skip non-letters
                if (ch == '\n')
                    lineNum++;
                textFile.get(ch);
            }

            else break;
        }

        if (textFile.eof()) {      // spaces at the end of textFile;
            break;
        }
        
        for (i = 0; !textFile.eof() && isalpha(ch); i++) {
            s[i] = toupper(ch);
            textFile.get(ch);
        }

        s[i] = '\0';
        
        if (!trie.wordFound(s, lineNum)) {
            noError = false;
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
    

    PROCESS_MEMORY_COUNTERS_EX pmc;
    // GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    GetProcessMemoryInfo(GetCurrentProcess(), reinterpret_cast<PPROCESS_MEMORY_COUNTERS>(&pmc), sizeof(pmc));
    SIZE_T memoryUsage = pmc.PrivateUsage; // WorkSetSize - physical memory

    cout << "memory used: " << memoryUsage << endl;

    return 0;
}
