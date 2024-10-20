#ifndef PROFILER_H
#define PROFILER_H

#include <string>
#include <unordered_map>
#include <stack>
#include "ProfiledSection.h"

class Profiler {
public:
    static Profiler& getInstance(); // Singleton
    void startSection(const char* sectionName, const char* fileName, const char* funcName, int lineNum);
    void endSection(const char* sectionName);
    void outputToFile(const std::string& format);

private:
    std::unordered_map<std::string, ProfiledSection> sections;
    std::stack<std::string> sectionStack;
    Profiler() = default;  // Private constructor for Singleton
    void calculateStatistics();  // Add this if needed in the future
};

#endif