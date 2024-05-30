TARGETS = ./bin/jsonTest1
CXX = g++
CXXFLAGS = -std=c++11

all: $(TARGETS)

./bin/%: ./src/%.cpp
	$(CXX) -o $@ $< $(CXXFLAGS)

.PHONY: clean

clean:
	rm -rf ./bin/*