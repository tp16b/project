.PHONY: clean

INCLUDE=./include/
SRC=./src/

main: $(SRC)main.cpp $(SRC)allocator.cpp $(SRC)DefaultAllocator.cpp
	g++ -std=c++11 -g -o $@ $^ -I$(INCLUDE)

clean:
	rm -rf main
