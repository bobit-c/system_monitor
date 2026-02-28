CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -O2

TARGET = system_monitor
SRCS = main.cpp system_monitor.cpp csv_logger.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

