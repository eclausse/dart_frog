CXX = g++
MAKE = make

CXXFLAGS = -std=c++17 -lcpr -pthread -Wall
CXXDEBUGFLAGS = -g
CXXRELEASEFLAGS = -03

SRCDIR = src/
BINDIR = bin/

TARGET = $(BINDIR)prog
SRC = $(wildcard $(SRCDIR)*.cpp)

OBJ = $(subst $(SRCDIR), $(BINDIR), $(SRC:.cpp=.o))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(CXXDEBUGFLAGS)

$(BINDIR)%.o : $(SRCDIR)%.cpp
	$(CXX) -c $^ -o $@ $(CXXFLAGS) $(CXXDEBUGFLAGS)

run : 
	./$(TARGET)

.PHONY : clean 

clean : 
	$(RM) $(BINDIR)*.o