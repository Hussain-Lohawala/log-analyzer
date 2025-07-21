//SQLiteHandler.cpp
#include "SQLiteHandler.h"
#include <iostream>

SQLiteHandler::SQLiteHandler(const std::string& dbFile) : databaseFile(dbFile), db(nullptr) {}
SQLiteHandler::~SQLiteHandler() {
	close();
}

bool SQLiteHandler::open() {
	if (sqlite3_open(databaseFile.c_str(), &db) == SQLITE_OK) {
		createTableIfNotExists();
		return true;
	}
	else {
		std::cerr << "Error opening DB: " << sqlite3_errmsg(db) << std::endl;
		return false;
	}
}

void SQLiteHandler::close() {
	if (db) {
		sqlite3_close(db);
		db = nullptr;
	}
}

void SQLiteHandler::createTableIfNotExists() {
	const char* createTableSQL = 
		"CREATE TABLE IF NOT EXISTS LogStats ("
		"Date TEXT, "
		"Level TEXT, "
		"Count INTEGER, "
		"PRIMARY KEY(Date, Level));";
	char* errMsg = nullptr;
	if (sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg) != SQLITE_OK) {
		std::cerr << "Create table error: " << errMsg << std::endl;
		sqlite3_free(errMsg);
	}
}

void SQLiteHandler::insertLogStat(const std::string& date, const std::string& level, int count) {
	std::string sql = "INSERT INTO LogStats (Date, Level, Count) VALUES (?, ?, ?) "
		"ON CONFLICT(Date, Level) DO UPDATE SET Count = excluded.Count;";
	sqlite3_stmt* stmt;
	if (sqlite3_prepare_v2(db,sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, date.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, level.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(stmt, 3, count);
		
		if (sqlite3_step(stmt) != SQLITE_DONE) {
			std::cerr << "Insert error: " << sqlite3_errmsg(db) << std::endl;
		}
		sqlite3_finalize(stmt);
	} else {
		std::cerr << "Prepare error: " << sqlite3_errmsg(db) << std::endl;
	}
}