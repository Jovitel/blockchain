# Nustatymai
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
SOURCES = main.cpp block.cpp blockchain.cpp transaction.cpp user.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = blockchain_simulation

# Taisyklių
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean
