# Makefile
TARGET=library
CXX=g++
CXXFLAGS=-std=c++11
OBJECTS=main.o library.o resource.o member.o space.o
$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $^
library.o: library.cpp
	$(CXX) $(CXXFLAGS) -c $^
resource.o: resource.cpp
	$(CXX) $(CXXFLAGS) -c $^
member.o: member.cpp
	$(CXX) $(CXXFLAGS) -c $^
space.o: space.cpp
	$(CXX) $(CXXFLAGS) -c $^
clean:
	rm $(OBJECTS) $(TARGET)