//LogProcessor.h
#pragma once

#include <string>
#include <unordered_map>

class LogProcessor {
public:
	explicit LogProcessor(const std::string& filePath);

	void process();
	void printStats() const;
	void saveToDatabase(const std::string& dbPath);
private:
	std::string logFilePath;
	std::unordered_map<std::string, std::unordered_map<std::string, int>> dateLevelCounts;

	void parseLine(const std::string& line);
};
