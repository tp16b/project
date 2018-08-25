
DICT=/home/tp/project/OnlineCompile/wwwroot/online_tools/Compile
LOADCODE=$(DICT)/loadcodefile 
INCLUDE=$(DICT)/../
all: $(LOADCODE) $(COMPILE)

$(LOADCODE): $(DICT)/getcode.cc
	g++ -std=c++11 -g -o $@ $^ -I$(INCLUDE)

.PHONY: clean
clean:
	rm -rf $(LOADCODE) 
