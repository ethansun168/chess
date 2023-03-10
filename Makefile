# Switches to a modern C++ compiler on CAEN
PATH := /usr/um/gcc-4.8.2/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/gcc-4.8.2/lib64
LD_RUN_PATH := /usr/um/gcc-4.8.2/lib64

CXX              = g++
CPP_FILES        = $(wildcard *.cpp)
COMPILED_OBJECTS = $(CPP_FILES:%.cpp=%.o)
EXECUTABLE       = main.exe
DIR 						 = $(wildcard *.d)

# Flags passed to the preprocessor. -MMD and -MP will cause the preprocessor
# to detect dependencies automatically.
CPPFLAGS = -MMD -MP
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

release: CXXFLAGS += -O3 -DNDEBUG
release: all

debug: CXXFLAGS += -g3 -DDEBUG
debug: clean all

all: $(COMPILED_OBJECTS)
	$(CXX) $(CXXFLAGS) $(COMPILED_OBJECTS) -o $(EXECUTABLE)
	@echo -e '\033[0;32m==========Successfully finished build==========\033[0m'

# The default rule for creating object files
%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $*.cpp

clean:
	rm -f $(COMPILED_OBJECTS) $(EXECUTABLE) $(DIR)

test: debug
# You add tests here

MY_FILES=$(wildcard Makefile *.h *.cpp test*.txt)
$(SUBMIT_FILE): $(MY_FILES)
	dos2unix $(MY_FILES)
	tar -vczf $(SUBMIT_FILE) $(MY_FILES)

# Imports the dependency files generated by the preprocessor.
-include *.d

# These targets do not create any files
.PHONY: all release debug clean submit test
# Disable built-in rules
.SUFFIXES: