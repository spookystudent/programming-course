#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

class Table {
private:
    vector<string> tableHeader;
    vector<vector<string>> tableData;
    unordered_map<string, multimap<string, size_t>> indices; // Индексы для столбцов

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

int main() {
    DB db;

    // Создание таблицы T_1
    vector<string> header_1 {"A", "B", "C"};
    db.addTable("T_1", header_1);

    Table* t1 = db.getTable("T_1");
    t1->addRow({"A1", "B1", "C1"});
    t1->addRow({"A2", "B2", "C2"});
    t1->addRow({"A3", "B3", "C3"});
    t1->addRow({"A4", "B4", "C4"});
    t1->addRow({"A1", "B2", "C3"});

    // Поиск без индекса
    Table* result_1 = t1->select("A", "A1");
    result_1->print();

    // Создание таблицы T_2
    vector<string> header_2 {"D", "E", "F"};
    db.addTable("T_2", header_2);

    Table* t2 = db.getTable("T_2");
    t2->addRow({"D1", "E1", "F1"});
    t2->addRow({"D2", "E2", "F2"});
    t2->addRow({"D3", "E3", "F3"});
    t2->addRow({"D4", "E4", "F4"});
    t2->addRow({"D1", "E2", "F3"});

    // Построение индекса для столбца D
    t2->addIndex("D");

    // Поиск по индексу
    Table* result_2 = t2->select("D", "D1");
    result_2->print();

    // Добавление данных. Индекс должен обновиться
    t2->addRow({"D1", "E3", "F3"});

    // Поиск по индексу после добавления данных
    Table* result_3 = t2->select("D", "D1");
    result_3->print();

    return 0;
}