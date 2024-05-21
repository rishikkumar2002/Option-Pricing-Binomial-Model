#pragma once

#include <string>

void capture_output(const std::string& cmd, const std::string& outputFile);
void capture_output(const std::string& cmd, const std::string& inputFile, const std::string& outputFile);