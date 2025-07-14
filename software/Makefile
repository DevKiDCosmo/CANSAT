CC=gcc
CXX=g++
CFLAGS=-Wall -O2
CXXFLAGS=-Wall -O2
LDFLAGS=-lbcm2835 -lm

SRC_C=$(wildcard src/*.c)
SRC_CPP=$(wildcard src/*.cpp)
OBJ=$(patsubst src/%.c,build/%.o,$(SRC_C)) $(patsubst src/%.cpp,build/%.o,$(SRC_CPP))
TARGET=build/main

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p build
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: src/%.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build