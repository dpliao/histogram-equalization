CXX = g++
CFLAGS = -shared -std=c++17 -O3 -Wall -fPIC $(shell python3 -m pybind11 --includes) $(shell python3-config --includes)

SRCDIR = src
SRC = wrapper.cpp $(SRCDIR)/pyFunc.h $(SRCDIR)/histEqSerial.h

OBJDIR = obj
OBJ = $(OBJDIR)/wrapper.o
EXE = myHist$(shell python3-config --extension-suffix)

all: dirs $(EXE)

dirs:
	mkdir -p $(OBJDIR)

$(EXE): $(OBJ)
	$(CXX) $(CFLAGS) $(SRC) -o $(EXE)

$(OBJ): $(SRC)
	$(CXX) $(CFLAGS) -c $(SRC) -o $(OBJ)

.PHONY: test clean

test: $(TARGET)
	python3 -m pytest

clean:
	rm -rf *.so __pycache__ .pytest_cache $(OBJDIR)