CXX = clang++
CXXFLAGS = -g -std=c++17

SOURCES = Code/*.cpp

TARGET = output

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)
