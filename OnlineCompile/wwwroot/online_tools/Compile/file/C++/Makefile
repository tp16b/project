.PHONY: clean

DICT=/home/tp/project/OnlineCompile/wwwroot/online_tools/Compile
SRC=$(DICT)/file/edit.cc
COMPILE=$(DICT)/file/compile

$(COMPILE):$(SRC)
	g++ -std=c++11 -g -o $@ $^  
clean:
	rm -rf $(COMPILE) 
