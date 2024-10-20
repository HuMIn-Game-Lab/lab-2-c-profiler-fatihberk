#include "ProfilerOutput.h"
#include <fstream>
#include <iostream>
#include <json.hpp>  // For JSON Serialization
#include <tinyxml2.h>  // For XML serialization

using json = nlohmann::json;
using namespace tinyxml2;

// Write profiler data to a CSV file
void ProfilerOutput::writeToCSV(const std::unordered_map<std::string, ProfiledSection>& sections, const std::string& filePath) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open CSV file for writing." << std::endl;
        return;
    }

    // Write CSV header
    file << "Section,Call Count,Total Time,Min Time,Max Time,Average Time,File,Function,Line\n";

    // Write data for each section
    for (const auto& entry : sections) {
        const ProfiledSection& section = entry.second;
        file << section.sectionName << "," 
             << section.callCount << ","
             << section.totalTime << ","
             << section.minTime << ","
             << section.maxTime << ","
             << section.averageTime << ","
             << section.fileName << ","
             << section.funcName << ","
             << section.lineNumber << "\n";
    }
    file.close();
}

// Write profiler data to a JSON file
void ProfilerOutput::writeToJSON(const std::unordered_map<std::string, ProfiledSection>& sections, const std::string& filePath) {
    json outputJson;

    for (const auto& entry : sections) {
        const ProfiledSection& section = entry.second;
        outputJson[section.sectionName] = {
            {"Call Count", section.callCount},
            {"Total Time", section.totalTime},
            {"Min Time", section.minTime},
            {"Max Time", section.maxTime},
            {"Average Time", section.averageTime},
            {"File", section.fileName},
            {"Function", section.funcName},
            {"Line", section.lineNumber}
        };
    }

    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open JSON file for writing." << std::endl;
        return;
    }
    
    file << outputJson.dump(4); // Pretty print with 4 spaces of indentation
    file.close();
}

// Write profiler data to an XML file
void ProfilerOutput::writeToXML(const std::unordered_map<std::string, ProfiledSection>& sections, const std::string& filePath) {
    XMLDocument doc;

    XMLElement* root = doc.NewElement("ProfilerData");
    doc.InsertFirstChild(root);

    for (const auto& entry : sections) {
        const ProfiledSection& section = entry.second;

        XMLElement* sectionElement = doc.NewElement("Section");
        sectionElement->SetAttribute("Name", section.sectionName);

        XMLElement* callCountElement = doc.NewElement("CallCount");
        callCountElement->SetText(section.callCount);
        sectionElement->InsertEndChild(callCountElement);

        XMLElement* totalTimeElement = doc.NewElement("TotalTime");
        totalTimeElement->SetText(section.totalTime);
        sectionElement->InsertEndChild(totalTimeElement);

        XMLElement* minTimeElement = doc.NewElement("MinTime");
        minTimeElement->SetText(section.minTime);
        sectionElement->InsertEndChild(minTimeElement);

        XMLElement* maxTimeElement = doc.NewElement("MaxTime");
        maxTimeElement->SetText(section.maxTime);
        sectionElement->InsertEndChild(maxTimeElement);

        XMLElement* avgTimeElement = doc.NewElement("AverageTime");
        avgTimeElement->SetText(section.averageTime);
        sectionElement->InsertEndChild(avgTimeElement);

        XMLElement* fileElement = doc.NewElement("File");
        fileElement->SetText(section.fileName);
        sectionElement->InsertEndChild(fileElement);

        XMLElement* functionElement = doc.NewElement("Function");
        functionElement->SetText(section.funcName);
        sectionElement->InsertEndChild(functionElement);

        XMLElement* lineElement = doc.NewElement("Line");
        lineElement->SetText(section.lineNumber);
        sectionElement->InsertEndChild(lineElement);

        root->InsertEndChild(sectionElement);
    }

    XMLError eResult = doc.SaveFile(filePath.c_str());
    if (eResult != XML_SUCCESS) {
        std::cerr << "Error: Unable to save XML file." << std::endl;
    }
}
