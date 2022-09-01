PYTHON_DIR := /usr/local/Python-3.4.3
PYTHON_CFLAGS := $(shell $(PYTHON_DIR)/bin/python3-config --cflags)
PYTHON_LDFLAGS := $(shell $(PYTHON_DIR)/bin/python3-config --ldflags)

MKDIR   := mkdir -p
RMDIR   := rm -rf
CC := g++ -std=c++11
#CC      := /home/noncad/gnu/gcc/gcc-8.2.0/bin/g++
BIN     := ./bin
OBJ     := ./obj
INCLUDE := -I./include -I/usr/local/Python-3.4.3/include/python3.4m
SRC     := ./src
SRCS    := $(wildcard $(SRC)/*.cpp)
OBJS    := $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SRCS))
EXE     := $(BIN)/embedPython
# -std=c++2a
CFLAGS  := $(INCLUDE) -g
LDFLAGS := $(PYTHON_LDFLAGS) 

.PHONY: all run clean test

all: $(EXE)

$(EXE): $(OBJS) | $(BIN)
	$(CC) -o $@ $^ $(LDFLAGS)  

$(OBJ)/%.o: $(SRC)/%.cpp | $(OBJ)
	$(CC) -o $@ -c $< $(CFLAGS) 

$(BIN) $(OBJ):
	$(MKDIR) $@

run: $(EXE)
	$<

clean:
	$(RMDIR) $(OBJ) $(BIN)

test:
	PYTHONPATH=./test $(EXE)

