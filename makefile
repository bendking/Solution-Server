all:
	g++ CacheManager/*.cpp CacheManager/*.h Searchable/*.cpp Searchable/*.h Searcher/*.cpp Searcher/*.h Server/*.cpp Server/*.h Solver/*.h Tester/*.cpp Tester/*.h main.cpp -std=c++14 -Wall -pthread
	
