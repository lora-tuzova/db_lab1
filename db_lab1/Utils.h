#pragma once
#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <vector>
#include "Fabric.h"
#include "Catalog.h"
using namespace std;

vector<int> forDeletionM = {};
vector<Fabric> forEditingM = {};
vector<int> forDeletionS = {};
vector<CatalogNote> forEditingS = {};

void checkDoubles() {
	for (int i = 0; i < forDeletionM.size();i++) {
		for (int j = 0; j < forEditingM.size();j++) {
			if (forEditingM[j].f_number == forDeletionM[i]) forEditingM.erase(forEditingM.begin() + j);
		}
	}
	for (int i = 0; i < forDeletionS.size();i++) {
		for (int j = 0; j < forEditingS.size();j++) {
			if (forEditingS[j].c_number == forDeletionS[i]) forEditingS.erase(forEditingS.begin() + j);
		}
	}
}

int checkOccurenceM(int n) {
	for (int i = 0; i < forDeletionM.size();i++) {
		if (n == forDeletionM[i]) return 0;
	}
	for (int i = 0; i < forEditingM.size();i++) {
		if (n == forEditingM[i].f_number) return 1;
	}
	return -1;
}

int checkOccurenceS(int n) {
	for (int i = 0; i < forDeletionS.size();i++) {
		if (n == forDeletionS[i]) return 0;
	}
	for (int i = 0; i < forEditingS.size();i++) {
		if (n == forEditingS[i].c_number) return 1;
	}
	return -1;
}
//funcs return 0 to delete, 1 to update and -1 to miss

string GetFabric(int num) {
	std::ifstream g("D:\\fabricInd.txt");
	string line;
	string number = to_string(num) + "  ";
	while (1) {
		getline(g, line);
		if (line.find(number) != std::string::npos) {
			break;
		}
	}
	g.close();
	size_t found = line.find(" ");
	string addr = "";
	for (int i = found + 2;i < line.length();i++) {
		addr += line[i];
	}
	ifstream g2("D:\\fabric.txt");
	g2.seekg(stoi(addr), ios_base::beg);
	getline(g2, line);
	g2.close();
	return line;
}

string GetNote(int num) {
	std::ifstream g("D:\\catalog.txt");
	string line;
	string number = to_string(num) + "  ";
	while (1) {
		getline(g, line);
		if (line.find(number) != std::string::npos) {
			break;
		}
	}
	g.close();
	return line;
}

string findInVectorM(int num) {
	for (int i = 0;i < forEditingM.size();i++) {
		if (forEditingM[i].f_number == num) {
			string s = to_string(forEditingM[i].f_number) + "  " + forEditingM[i].f_name + "  " + forEditingM[i].f_color + "  " + forEditingM[i].f_material + "  " + to_string(forEditingM[i].f_density) /*+"  " + to_string(forEditingM[i].f_notes_count) + "  " + to_string(forEditingM[i].del_status)*/;
			return s;
		};
	}
}

string findInVectorS(int num) {
	for (int i = 0;i < forEditingS.size();i++) {
		if (forEditingS[i].c_number == num) {
			string s = to_string(forEditingS[i].c_number) + "  " + forEditingS[i].c_f_number + "  " + to_string(forEditingS[i].c_amount_used);
			return s;
		};
	}
}

int findInInd(int num, vector<string>ind) {
	int n, j = 0;
	string part;
	size_t pos;
	for (int i = 0;i < ind.size();i++) {
		pos = ind[i].find_first_of(' ');
		part = ind[i].substr(0, pos);
		n = stoi(part);
		if (n == num) return i;
	}
}

int checkExistenceM(int num) {
	string line;
	std::ifstream g("D:\\fabricInd.txt");
	string number = to_string(num) + "  ";
	while (getline(g, line)) {
		if (line.find(number) != std::string::npos) {
			return 1;
		}
	}
	g.close();
	return 0;
}

int checkExistenceS(int num) {
	string line;
	std::ifstream g("D:\\catalog.txt");
	string number = to_string(num) + "  ";
	while (getline(g, line)) {
		if (line.find(number) != std::string::npos) {
			return 1;
		}
	}
	g.close();
	return 0;
}

void updM() {
	ifstream myfile2; //for reading records
	myfile2.open("D:\\fabricInd.txt");

	string line;
	vector<string> ind = {};
	while (getline(myfile2, line))
	{
		if (line != "") {

			ind.push_back(line);
		}
	}
	myfile2.close(); //index table is in vector now

	int num, res, dist, position;
	ifstream myfile3; //for reading records
	myfile3.open("D:\\fabric.txt");
	ofstream temp;
	temp.open("D:\\temp.txt");
	string part_number;
	while (getline(myfile3, line))
	{
		position = line.find_first_of("  ");
		part_number = line.substr(0, position);
		num = stoi(part_number);
		res = checkOccurenceM(num);
		if (res != 0) {
			if (res == 1) {
				temp << findInVectorM(num) << endl;
				dist = temp.tellp();
				
				position = findInInd(num, ind);
				ind[position] = to_string(num) + "  " + to_string(dist);
			}
			else {
				temp << line << endl;
			}
		}
		else {
			position = findInInd(num, ind);
			ind.erase(ind.begin() + position);
			getline(myfile3, line);
		}
	}
	temp.close();
	myfile3.close();
	remove("D:\\fabric.txt");
	rename("D:\\temp.txt", "D:\\fabric.txt"); //master-file edited

	ofstream tempInd; //rewriting index table
	tempInd.open("D:\\tempInd.txt");
	for (int i = 0;i < ind.size();i++) {
		tempInd << ind[i] << endl;
	}
	tempInd.close();
	remove("D:\\fabricInd.txt");
	rename("D:\\tempInd.txt", "D:\\fabricInd.txt"); //ind table rewritten
}

void updS() {
	string line,part_number;
	int num, res, dist, position;
	ifstream myfile3; //for reading records
	myfile3.open("D:\\catalog.txt");
	ofstream temp;
	temp.open("D:\\temp.txt");
	while (getline(myfile3, line))
	{
		position = line.find_first_of("  ");
		part_number = line.substr(0, position);
		num = stoi(part_number);
		res = checkOccurenceS(num);
		if (res != 0) {
			if (res == 1) {
				temp << findInVectorS(num) << endl;
				dist = temp.tellp();
			}
			else {
				temp << line << endl;
			}
		}
	}
	temp.close();
	myfile3.close();
	remove("D:\\catalog.txt");
	rename("D:\\temp.txt", "D:\\catalog.txt"); //slave-file edited
}