.PHONY: all clean


DICT=/home/tp/project/web/wwwroot/online_tools/Compile
COMPILE=$(DICT)/file/compile
LOADCODE=$(DICT)/loadcodefile 

all: $(LOADCODE) $(COMPILE)

$(LOADCODE): $(DICT)/getcode.cc
	g++ -std=c++11 -g -o $@ $^ -I../ 
$(COMPILE):$(DICT)/file/edit.cc
	g++ -std=c++11 -g -o $@ $^ 
clean:
	rm -rf $(LOADCODE) $(COMPILE) 
