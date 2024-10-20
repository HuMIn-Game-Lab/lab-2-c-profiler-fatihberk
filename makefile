CXX = clang++
CXXFLAGS = -g -std=c++17

SOURCES = main.cpp Profiler.cpp ProfilerOutput.cpp ProfiledSection.cpp TimeUtils.cpp tinyxml2.cpp

TARGET = output

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)
