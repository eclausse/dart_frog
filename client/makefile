CXX = g++
MAKE = make

CXXFLAGS = -std=c++17 -Wall

SRCDIR = src/
BINDIR = bin/

TARGET = $(BINDIR)prog
SRC = $(wildcard $(SRCDIR)*.cpp)

OBJ = $(subst $(SRCDIR), $(BINDIR), $(SRC:.cpp=.o))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

$(BINDIR)%.o : $(SRCDIR)%.cpp
	$(CXX) -c $^ -o $@ $(CXXFLAGS)

run : 
	./$(TARGET)

.PHONY : clean 

clean : 
	$(RM) $(BINDIR)*.o