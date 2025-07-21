// File: main.cpp
#include "LogProcessor.h"

int main() {
	LogProcessor processor("logs/sample.log");
	processor.process();
	processor.printStats();
	processor.saveToDatabase("log_stats.db");
	return 0;
}