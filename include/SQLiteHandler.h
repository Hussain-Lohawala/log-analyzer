//SQLiteHandler.h
#pragma once

#include <string>
#include <sqlite3.h>

class SQLiteHandler {
public:
	explicit SQLiteHandler(const std::string& dbFile);
	~SQLiteHandler();

	bool open();
	void close();
	void insertLogStat(const std::string& date, const std::string& level, int count);

private:
	std::string databaseFile;
	sqlite3* db;

	void createTableIfNotExists();
};