
CXX     := g++
CXXFLAGS:= -std=c++17 -Wall -Wextra -Iinclude

SRC_DIR := src
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:%.cpp=%.o)

all: admin reporter

admin: $(OBJS) main_admin.o
	$(CXX) $(CXXFLAGS) -o admin.exe $^

reporter: $(OBJS) main_reporter.o
	$(CXX) $(CXXFLAGS) -o reporter.exe $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o *.o admin.exe reporter.exe
