#pragma once
#include <iostream>
#include <fstream>
#include <istream>
#include <string>
using namespace std;

class CatalogNote { //slave file
    
public:
    string c_f_number;
    int c_number;
    double c_amount_used;
    CatalogNote(int num, int f_num, double amount) {
        this->c_number = num;
        this->c_f_number = to_string(f_num);
        this->c_f_number += "f";
        this->c_amount_used = amount;
    }
    void AddToFile() {

        std::ofstream out("D:\\catalog.txt", std::ios::app);
        if (out.is_open())
        {
            out << this->c_number << "  " << this->c_f_number << "  " << this->c_amount_used << endl;

        }
        out.close();
    }
};