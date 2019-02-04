spellChecker.exe	: spellChecker.o AVL.o
	g++ -O2 -std=c++11 -o spellChecker.exe spellChecker.o AVL.o -l gdi32 -lpsapi -static-libgcc -static-libstdc++
			
spellChecker.o	: spellChecker.cpp AVL.h
	g++ -O2 -std=c++11 -c -fpermissive -Wwrite-strings spellChecker.cpp
	
AVL.o : AVL.cpp AVL.h
	g++ -O2 -std=c++11 -c  -fpermissive -Wwrite-strings AVL.cpp

clean :
	rm *.o spellChecker.exe