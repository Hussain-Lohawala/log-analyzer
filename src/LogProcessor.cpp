//LogProcessor.cpp
#include "LogProcessor.h"
#include "SQLiteHandler.h"

#include<fstream>
#include <iostream>
#include <sstream>

LogProcessor::LogProcessor(const std::string& filePath) : logFilePath(filePath) {}

void LogProcessor::process() {
	std::ifstream infile(logFilePath);
	if (!infile.is_open()) {
		std::cerr << "Failed to open file: " << logFilePath << std::endl;
		return;
	}
	std::string line;
	while (std::getline(infile, line)) {
		parseLine(line);
	}
	infile.close();
}

void LogProcessor::parseLine(const std::string& line) {
	//find date inside [YYYY-MM-DD HH:MM:SS]
	size_t openBracket = line.find('[');
	size_t closedBracket = line.find(']');
	if (openBracket == std::string::npos || closedBracket == std::string::npos) return; 

	std::string datetime = line.substr(openBracket + 1, closedBracket - openBracket - 1); // "2025-07-20 10:15:45"
	std::string date = datetime.substr(0, 10); // Extract just the "2025-07-20"

	// Find log level after "] "
	size_t levelStart = line.find_first_not_of(" ", closedBracket + 1);
	size_t levelEnd = line.find(' ', levelStart);
	if (levelStart == std::string::npos) return;

	std::string level = line.substr(levelStart, levelEnd - levelStart);

	++dateLevelCounts[date][level];
}

void LogProcessor::printStats() const {
	std::cout << "\n=== Log Level Statistics by Date ===" << std::endl;
	for (const auto& dateEntry : dateLevelCounts) {
		std::cout << dateEntry.first << ":" << std::endl;
		for (const auto& levelEntry : dateEntry.second) {
			std::cout << " " << levelEntry.first << ": " << levelEntry.second << std::endl;
		}
	}
}

void LogProcessor::saveToDatabase(const std::string& dbPath) {
	SQLiteHandler db(dbPath);
	db.open();
	for( const auto& dateEntry : dateLevelCounts) {
		const std::string& date = dateEntry.first;
		for (const auto& levelEntry : dateEntry.second) {
			const std::string& level = levelEntry.first;
			int count = levelEntry.second;
			db.insertLogStat(date, level, count);
		}
	}
	db.close();
}