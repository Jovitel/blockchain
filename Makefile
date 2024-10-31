# Makefile

CXX = nmake
CXXFLAGS = /std:c++17 /W3
SOURCES = main.cpp block.cpp blockchain.cpp transaction.cpp user.cpp
TARGET = blockchain_simulation.exe

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	del $(TARGET)
