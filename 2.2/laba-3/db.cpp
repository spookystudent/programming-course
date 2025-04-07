#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

class Table {
private:
    vector<string> tableHeader;
    vector<vector<string>> tableData;
    unordered_map<string, multimap<string, size_t>> indices;

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
            indices[column] = multimap<string, size_t>();

            multimap<string, size_t> &index = indices[column];
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
};


void conduct_experiment() {
    cout << "1" << endl;
}


int main() {
    DB db;
    cout << endl << endl;

    // Создание таблицы T_1
    vector<string> header_1 {"A", "B"};
    db.addTable("T_1", header_1);

    Table* t1 = db.getTable("T_1");


    int variety = 1000;
    int maxRows = 100000;
    string testValue = to_string(rand() % variety);


    for (int i = 0; i < maxRows; ++i) {
        string valueA = to_string(rand() % variety);
        string valueB = to_string(rand() % variety);
        t1->addRow({valueA, valueB});
    }


    auto start = high_resolution_clock::now();
    Table* result_1 = t1->select("A", testValue);

    auto end = high_resolution_clock::now();
    auto durationWithoutIndex = duration_cast<microseconds>(end - start).count();

    cout << "T1: " << durationWithoutIndex << " ms" << endl;

    t1->addIndex("B");

    start = high_resolution_clock::now();
    Table* result_2 = t1->select("B", testValue); 
    end = high_resolution_clock::now();
    auto durationWithIndex = duration_cast<microseconds>(end - start).count();
    cout << "T2: " << durationWithIndex << " ms" << endl;

    return 0;
}