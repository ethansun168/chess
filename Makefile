# Makefile

CXX ?= g++

CXXFLAGS ?= --std=c++11 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment 

# Add sanitizer flags for identifying undefined behavior.  The flags are
# different on macOS (AKA Darwin) and Windows/WSL/Linux.
UNAME := $(shell uname -s)
ifeq "$(UNAME)" "Darwin"
	CXXFLAGS += -fsanitize=address -fsanitize=undefined
else
	CXXFLAGS += -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG
endif

main.exe: main.cpp Piece.cpp Player.cpp Board.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

.SUFFIXES:

.PHONY: clean

clean:
	rm -rvf *.out *.exe *.dSYM *.stackdump