vectorExample.exe	: vectorExample.o
	g++ -O2 -std=c++11 -o vectorExample.exe vectorExample.o -l gdi32 -lpsapi -static-libgcc -static-libstdc++

vectorExample.o	: vectorExample.cpp
	g++ -O2 -std=c++11 -c -fpermissive -Wwrite-strings vectorExample.cpp