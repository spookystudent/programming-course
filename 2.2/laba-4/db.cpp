#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <filesystem>
#include <algorithm>

using namespace std;
using namespace std::chrono;


class Table {
private:
    vector<string> tableHeader;
    vector<vector<string>> tableData;
    unordered_map<string, unordered_multimap<string, size_t>> indices;

public:
    Table(const vector<string>& header) : tableHeader(header) {}

    void addRow(const vector<string>& row) {
        tableData.push_back(row);
        updateIndices(tableData.size() - 1);
    }

    void print() const {
        for (auto& column : tableHeader) {
            cout << column << "\t";
        }
        cout << endl;

        for (auto& row : tableData) {
            for (auto& cell : row) {
                cout << cell << "\t";
            }
            cout << endl;
        }
    }

    void addIndex(const string& column) {
        if (indices.find(column) == indices.end()) {
            indices[column] = unordered_multimap<string, size_t>();

            unordered_multimap<string, size_t> &index = indices[column];
            int column_index = getColumnIndex(column);

            for (size_t i = 0; i < tableData.size(); ++i) {
                index.insert({tableData[i][column_index], i});
            }
        }
    }

    Table* select(const string& column, const string& value) {
        vector<string> resultHeader = tableHeader;
        Table* resultTable = new Table(resultHeader);

        if (indices.find(column) != indices.end()) {
            // Поиск по индексу
            auto range = indices[column].equal_range(value);
            for (auto it = range.first; it != range.second; ++it) {
                resultTable->addRow(tableData[it->second]);
            }
        } else {
            int columnIndex = getColumnIndex(column);
            if (columnIndex == -1) return nullptr;

            for (auto& row : tableData) {
                if (row[columnIndex] == value) {
                    resultTable->addRow(row);
                }
            }
        }

        return resultTable;
    }

private:
    int getColumnIndex(const string& column) const {
        for (int i = 0; i < tableHeader.size(); i++) {
            if (tableHeader[i] == column) {
                return i;
            }
        }
        return -1;
    }

    void updateIndices(size_t rowIndex) {
        for (auto& index : indices) {
            const string& column = index.first;
            int columnIndex = getColumnIndex(column);
            if (columnIndex != -1) {
                index.second.insert({tableData[rowIndex][columnIndex], rowIndex});
            }
        }
    }
};

class DB {
private:
    map<string, Table*> tableList;

public:
    void addTable(const string& name, const vector<string>& header) {
        tableList[name] = new Table(header);
    }

    Table* getTable(const string& name) {
        if (tableList.find(name) != tableList.end()) {
            return tableList[name];
        } else {
            return nullptr;
        }
    }

    ~DB() {
        for (auto& table : tableList) {
            delete table.second;
        }
    }
};



void runTest(int variety, int maxRows, ofstream& outFile, int numTests = 5) {
    DB db;
    
    vector<string> header_1 {"A", "B"};
    db.addTable("T_1", header_1);
    Table* t1 = db.getTable("T_1");

    for (int i = 0; i < maxRows; ++i) {
        string valueA = to_string(rand() % variety);
        string valueB = to_string(rand() % variety);
        t1->addRow({valueA, valueB});
    }

    double totalWithoutIndex = 0;
    string testValue = to_string(rand() % variety);
    
    for (int i = 0; i < numTests; ++i) {
        auto start = high_resolution_clock::now();
        Table* result = t1->select("A", testValue);
        auto end = high_resolution_clock::now();
        totalWithoutIndex += duration_cast<microseconds>(end - start).count();
        delete result;
    }

    double totalWithIndex = 0;
    t1->addIndex("B");
    testValue = to_string(rand() % variety);
    
    for (int i = 0; i < numTests; ++i) {
        auto start = high_resolution_clock::now();
        Table* result = t1->select("B", testValue);
        auto end = high_resolution_clock::now();
        totalWithIndex += duration_cast<microseconds>(end - start).count();
        delete result;
    }

    outFile << variety << ','
            << maxRows << ','
            << totalWithoutIndex / numTests << ','
            << totalWithIndex / numTests << endl;
}

void runPythonScript(const string& pythonScript, const string& dataFile, bool useCommandLine) {
    if (useCommandLine) {
        ifstream inFile(dataFile);
        stringstream buffer;
        buffer << inFile.rdbuf();
        string data = buffer.str();
        
        std::replace(data.begin(), data.end(), '\n', ' ');
        
        string command = "python " + pythonScript + " " + data;
        system(command.c_str());
    } else {
        string command = "python " + pythonScript + " " + dataFile;
        system(command.c_str());
    }
}

vector<int> generate_steps(int maxRows) {
    vector<int> steps;
    

    int base_step = 1;
    if (maxRows > 100000) base_step = 10000;
    else if (maxRows > 10000) base_step = 1000;
    else if (maxRows > 1000) base_step = 100;
    else if (maxRows > 100) base_step = 10;
    

    for (int step = base_step; step <= maxRows; step += base_step) {
        steps.push_back(step);
        
        if (step >= 10 * base_step) base_step *= 10;
    }
    

    if (steps.empty() || steps.back() != maxRows) {
        steps.push_back(maxRows);
    }
    
    return steps;
}

int main(int argc, char* argv[]) {
    bool useCommandLine = false;
    if (argc > 1 && string(argv[1]) == "--command-line") {
        useCommandLine = true;
    }

    srand(time(nullptr));

    string filename = "data.txt";
    ofstream outFile(filename);
    
    if (!outFile.is_open()) {
        cerr << "Не удалось открыть файл для записи: " << filename << endl;
        return 1;
    }

    vector<int> varieties = {10, 100, 1000};
    
    int maxRows;
    cout << "Введите максимальное количество строк для тестирования: ";
    cin >> maxRows;


    vector<int> steps = generate_steps(maxRows);


    cout << "Будут протестированы следующие количества строк: ";
    for (int step : steps) {
        cout << step << " ";
    }
    cout << endl << endl;

    for (int variety : varieties) {
        cout << "Тестирование для variety = " << variety << endl;
        for (int rows : steps) {
            cout << "  Количество строк: " << rows << endl;
            runTest(variety, rows, outFile);
        }
        outFile << endl;
    }

    outFile.close();
    cout << "Тестирование завершено. Результаты сохранены в: " << filename << endl;
    cout << filesystem::absolute(filename) << endl;

    string pythonScript = "graphics.py";
    runPythonScript(pythonScript, filename, useCommandLine);

    return 0;
}