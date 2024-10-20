#ifndef PROFILED_SECTION_H
#define PROFILED_SECTION_H

#include <string>

class ProfiledSection {
public:
    ProfiledSection(const char* sectionName, const char* fileName, const char* funcName, int lineNum);
    
    void start();
    void end();
    void calculateStatistics();
    
    std::string getStatistics() const;
    
private:
    const char* sectionName;
    const char* fileName;
    const char* funcName;
    int lineNumber;
    
    int callCount;
    double totalTime;
    double minTime;
    double maxTime;
    double averageTime;
    
    double startTime;
};

#endif
