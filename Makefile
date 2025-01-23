CXX       := g++
CXX_FLAGS := -std=c++17 -ggdb

BIN     := bin
SRC     := src
INCLUDE := include
LIB       := lib

LIBRARIES := $(wildcard $(LIB)/*.cpp)
EXECUTABLE  := main


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp $(LIBRARIES)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@

clean:
	-rm $(BIN)/*
