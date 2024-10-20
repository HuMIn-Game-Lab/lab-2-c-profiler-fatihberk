#include "Profiler.h"
#include "ProfilerOutput.h"  // Ensure this include is present
#include "TimeUtils.h"
#include <iostream>
#include <stdexcept>

// Singleton instance of the Profiler
Profiler& Profiler::getInstance() {
    static Profiler instance;
    return instance;
}

// Start profiling a section
void Profiler::startSection(const char* sectionName, const char* fileName, const char* funcName, int lineNum) {
    if (sections.find(sectionName) == sections.end()) {
        sections[sectionName] = ProfiledSection(sectionName, fileName, funcName, lineNum);
    }
    sectionStack.push(sectionName);
    sections[sectionName].start();
}

// End profiling a section
void Profiler::endSection(const char* sectionName) {
    if (sectionStack.empty() || sectionStack.top() != sectionName) {
        throw std::runtime_error("Profiler error: Mismatched start/end section calls");
    }
    sections[sectionName].end();
    sectionStack.pop();
}

// Output profiler data to a file in the given format (CSV, JSON, XML)
void Profiler::outputToFile(const std::string& format) {
    if (format == "CSV") {
        ProfilerOutput::writeToCSV(sections, "profiler_output.csv");  // Static call
    } else if (format == "JSON") {
        ProfilerOutput::writeToJSON(sections, "profiler_output.json");  // Static call
    } else if (format == "XML") {
        ProfilerOutput::writeToXML(sections, "profiler_output.xml");  // Static call
    } else {
        throw std::runtime_error("Unsupported output format");
    }
}
