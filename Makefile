CXX = g++
CFLAGS = -shared -std=c++17 -O3 -Wall -fPIC
PWD = $(shell pwd)

SRC = wrapper.cpp
TARGET = myHist

LIBS = -I/usr/include/python3.8 -I/usr/include/pybind11 -lpython3.8 -L/usr/include/mkl/intel64 -I/usr/include/mkl/ -lmkl_rt -lpthread -lm -ldl -lblas

$(TARGET):
	$(CXX) $(CFLAGS) `python3 -m pybind11 --includes` $(SRC) -o $(TARGET)`python3-config --extension-suffix` `python3-config --ldflags` $(LIBS)

.PHONY: test clean

test: $(TARGET)
	python3 -m pytest

clean:
	rm -rf *.so __pycache__ .pytest_cache