\# 🔍 Log Analyzer – C++ Project



A high-performance log analysis tool written in modern C++.



This tool reads a `.log` file, parses its contents, analyzes severity-level statistics, and stores the results in an SQLite database.



---



\## 📁 Project Structure



LogAnalyzerVS/

├── LogAnalyzer.sln

└── LogAnalyzer/

├── main.cpp

├── src/

│ ├── LogProcessor.cpp

│ ├── SQLiteHandler.cpp

├── include/

│ ├── LogProcessor.h

│ ├── SQLiteHandler.h

│ └── MemoryPool.h

├── sqlite/

│ ├── sqlite3.h

│ ├── sqlite3.lib

│ └── sqlite3.dll

└── logs/

└── sample.log





---



\## ⚙️ Features



\- Parse structured log files (`\[timestamp] LEVEL - message`)

\- Count log entries by severity: INFO, WARN, ERROR

\- Save analytics to an SQLite database

\- Designed with OOP principles and modular C++ structure



---



\## 🚀 How to Build (Visual Studio)



1\. Open `LogAnalyzer.sln` in Visual Studio



2\. Add Include Paths:

&nbsp;  - Configuration Properties → C/C++ → General → Additional Include Directories:

&nbsp;    ```

&nbsp;    $(ProjectDir)\\include;$(ProjectDir)\\sqlite

&nbsp;    ```



3\. Add Library Path:

&nbsp;  - Configuration Properties → Linker → General → Additional Library Directories:

&nbsp;    ```

&nbsp;    $(ProjectDir)\\sqlite

&nbsp;    ```



4\. Link SQLite3:

&nbsp;  - Configuration Properties → Linker → Input → Additional Dependencies:

&nbsp;    ```

&nbsp;    $(CoreLibraryDependencies);sqlite3.lib;%(AdditionalDependencies)

&nbsp;    ```



5\. Copy `sqlite3.dll` to your output directory (e.g., `Debug/` or `Release/` folder)



---



\## 📄 Sample Log Format (logs/sample.log)



\[2025-07-20 10:15:01] INFO - Server started successfully.

\[2025-07-20 10:15:10] WARN - High memory usage detected.

\[2025-07-20 10:15:20] ERROR - Failed to connect to database.





---



\## 🧪 Output Example



INFO : 2

WARN : 1

ERROR : 2

Saved stats to log\_stats.db





---



\## 📚 Technologies Used



\- C++17

\- SQLite3

\- STL, OOP, RAII

\- Visual Studio (MSVC)



---



\## 👨‍💻 Author



\*\*Hussain\*\*  

C++ Developer | AI Enthusiast | System Engineer



---



\## 📝 License



This project is licensed under the MIT License.

## 🚀 Future Enhancements
- Integrate `MemoryPool` to optimize dynamic memory allocation for log entry parsing.



