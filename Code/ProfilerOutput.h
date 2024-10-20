#ifndef PROFILER_OUTPUT_H
#define PROFILER_OUTPUT_H

#include <unordered_map>
#include <string>
#include "ProfiledSection.h"

class ProfilerOutput {
public:
    static void writeToCSV(const std::unordered_map<std::string, ProfiledSection>& sections, const std::string& filePath);
    static void writeToJSON(const std::unordered_map<std::string, ProfiledSection>& sections, const std::string& filePath);
    static void writeToXML(const std::unordered_map<std::string, ProfiledSection>& sections, const std::string& filePath);
};

#endif
