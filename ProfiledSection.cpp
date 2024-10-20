#include "ProfiledSection.h"
#include "TimeUtils.h"
#include <limits>
#include <iostream>

// Constructor initializes the section with metadata
ProfiledSection::ProfiledSection(const char* sectionName, const char* fileName, const char* funcName, int lineNum)
    : sectionName(sectionName), fileName(fileName), funcName(funcName), lineNumber(lineNum), callCount(0), 
      totalTime(0), minTime(std::numeric_limits<double>::max()), maxTime(0), averageTime(0), startTime(0) {}

// Start the timer for this section
void ProfiledSection::start() {
    startTime = TimeUtils::getCurrentTime();
}

// End the timer and calculate statistics for this section
void ProfiledSection::end() {
    double endTime = TimeUtils::getCurrentTime();
    double duration = endTime - startTime;

    // Update statistics
    callCount++;
    totalTime += duration;
    minTime = std::min(minTime, duration);
    maxTime = std::max(maxTime, duration);
    averageTime = totalTime / callCount;
}

// Calculate the statistics (already integrated into start/end)
void ProfiledSection::calculateStatistics() {
    averageTime = totalTime / callCount;
}

// Get a string representation of the statistics
std::string ProfiledSection::getStatistics() const {
    return "Section: " + std::string(sectionName) + "\n" +
           "Call count: " + std::to_string(callCount) + "\n" +
           "Total time: " + std::to_string(totalTime) + " s\n" +
           "Min time: " + std::to_string(minTime) + " s\n" +
           "Max time: " + std::to_string(maxTime) + " s\n" +
           "Average time: " + std::to_string(averageTime) + " s\n" +
           "File: " + std::string(fileName) + "\n" +
           "Function: " + std::string(funcName) + "\n" +
           "Line: " + std::to_string(lineNumber) + "\n";
}
