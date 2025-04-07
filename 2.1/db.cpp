// Online C++ compiler to run C++ program online
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;


class Table {
    private:
        vector<string> tableHeader;
        vector<vector<string>> tableData;
    public:
        Table(const vector<string>& header) : tableHeader(header) {}
        
        void addRow(const vector<string>& row) {
            tableData.push_back(row);
        }
        
        // Print all items in table data
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
        
        
        Table* select(const string& column, const string& value) {
            int columnIndex = -1;
            
            for (int i = 0; i < tableHeader.size(); i++) {
                if (tableHeader[i] == column) {
                    columnIndex = i;
                    break;
                }
            }
            
            
            if (columnIndex == -1) return nullptr;
            
            
            // Make a new table for returning data
            vector<string> resultHeader = tableHeader;
            Table* resultTable = new Table(resultHeader);
            
            for (auto& row : tableData) {
                if (row[columnIndex] == value) {
                    resultTable->addRow(row);
                }
            }
            
            return resultTable;
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
    //1
    vector<string> header_1 {"A", "B", "C"};
    db.addTable("T_1", header_1);
    
    Table* t1 = db.getTable("T_1");
    t1->addRow({"A1", "B1", "C1"});
    t1->addRow({"A2", "B2", "C2"});
    t1->addRow({"A3", "B3", "C3"});
    t1->addRow({"A4", "B4", "C4"});
    t1->addRow({"A1", "B2", "C3"});
    
    
    Table* result_1 = t1->select("A", "A1");
    result_1->print();
    
    //2
    vector<string> header_2 {"D", "E", "F"};
    db.addTable("T_2", header_2);
    
    Table* t2 = db.getTable("T_2");
    t2->addRow({"D1", "E1", "F1"});
    t2->addRow({"D2", "E2", "F2"});
    t2->addRow({"D3", "E3", "F3"});
    t2->addRow({"D4", "E4", "F4"});
    t2->addRow({"D1", "E2", "F3"});
    
    
    Table* result_2 = t2->select("D", "D1");
    result_2->print();
    
    
    // t2->print();

    return 0;
};
