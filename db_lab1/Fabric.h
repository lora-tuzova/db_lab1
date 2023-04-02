#pragma once
#include <iostream>
#include <fstream>
#include <istream>
#include <string>
using namespace std;

class Fabric { //master file
    public:
    int f_number;
    string f_name;
    string f_color;
    string f_material;
    double f_density;
    //int f_notes_count;
    //bool del_status;
    Fabric(int num, string name, string color, string mat, double dens) {
        this->f_number = num;
        this->f_name = name;
        this->f_color = color;
        this->f_material = mat;
        this->f_density = dens;
    }
    void AddToFile() {

        int dist;
        std::ofstream out("D:\\fabric.txt", std::ios::app);
        if (out.is_open())
        {
            out.seekp(0, ios_base::end);
            dist = out.tellp();
            out << this->f_number << "  " << this->f_name << "  " << this->f_color << "  " << this->f_material << "  " << this->f_density << endl;

        }
        out.close();

        std::ofstream ind("D:\\fabricInd.txt", std::ios::app);
        if (ind.is_open())
        {
            ind << this->f_number << "  " << dist << endl;
        }
    }
};