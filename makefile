CC := g++
#CXXFLAGS := -std=c++17 -march=native -g -fopenmp
CXXFLAGS :=  -std=c++17 -march=native  -O3 -fopenmp
EXECUTABLES := main

SRC_DIR := src
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

HEADERS_DIR := headers
HEADERS := $(wildcard $(HEADERS_DIR)/*.h)


OBJS_DIR := bin
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJS_DIR)/%.o, $(SRCS))

all: $(EXECUTABLES)

$(EXECUTABLES): $(OBJS)
	$(CC) $(CXXFLAGS) -o $@ $^

$(OBJS_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $<
clean:
	rm -rf $(EXECUTABLES) $(OBJS)	
.PHONY: all clean
