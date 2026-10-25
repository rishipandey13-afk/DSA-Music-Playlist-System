CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = playlist_system

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
