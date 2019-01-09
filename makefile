spellCheck.exe	: spellCheck.o trie.o
	g++ -O2 -std=c++11 -o spellCheck.exe spellCheck.o trie.o -l gdi32 -static-libgcc -static-libstdc++
			
spellCheck.o	: spellCheck.cpp trie.h
	g++ -O2 -std=c++11 -c -fpermissive -Wwrite-strings spellCheck.cpp
	
trie.o : trie.cpp trie.h
	g++ -O2 -std=c++11 -c  -fpermissive -Wwrite-strings trie.cpp

clean :
	rm *.o spellCheck.exe