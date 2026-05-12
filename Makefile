CXX      = g++
CXXFLAGS = -std=c++11 -Wall
TARGET   = 25880243
SRCS     = main.cpp utils.cpp customer.cpp book.cpp invoice.cpp warehouse.cpp statistics.cpp

ifeq ($(OS),Windows_NT)
	TARGET := 25880243.exe
endif

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f 25880243 25880243.exe

.PHONY: clean
