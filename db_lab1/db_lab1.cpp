#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <vector>
#include "Fabric.h"
#include "Catalog.h"
#include "Utils.h"
using namespace std;

extern vector<int> forDeletionM;
extern vector<Fabric> forEditingM;
extern vector<int> forDeletionS;
extern vector<CatalogNote> forEditingS;

int main()
{
    cout << "Commands:\n1 to add fabric,\n2 to add note,\n3 to get fabric,\n4 to get note,\n5 to delete fabric,\n6 to delete note,\n7 to print all fabrics,\n8 to print all notes,\n9 to edit fabric,\n10 to edit note,\n11 to count all fabrics,\n12 to count all notes,\n13 to count notes for a certain fabric\nEnter 0 to exit"<<endl;
    int a;
    cin >> a;
    while (a != 0) {
        switch (a) {
        case (1): {  //add fabric
            cout << "Enter the number, name, color, material and density of fabric:\n" <<"(color 1 corresponds to red, 2 - to green, 3 - to blue, 4 - to black, any other - to white)" << endl;
            int num, color;
            string name, s_color, mat;
            double dens;
            cin >> num >> name >> color >> mat >> dens;
            switch (color) {
            case 1: {s_color = "red"; break;}
            case 2: {s_color = "green"; break;}
            case 3: {s_color = "blue"; break;}
            case 4: {s_color = "black"; break;}
            default: {s_color = "white";}

            }
            Fabric f = Fabric(num, name, s_color, mat, dens);
            int check = checkExistenceM(num);
            if (check == 0)
                f.AddToFile();
            else
                cout << "This fabric is already on the list"<<endl;
            break;
        }
        case (2): {  //add note
            cout << "Enter number of note, number of corresponding fabric and an amount used (square meters):" << endl;
            int num, fnum;
            double amount;
            cin >> num >> fnum >> amount;
            CatalogNote cn = CatalogNote(num, fnum, amount);
            int check = checkExistenceM(fnum);
            if (check == 1) {
                check = checkExistenceS(num);
                if (check == 0)
                    cn.AddToFile();
                else
                    cout << "This note is already on the list"<<endl;
            }
            else
                cout << "This fabric is not on the list"<<endl;
            break;
        }
        case (3): {  //find fabric
            cout << "Enter the number" << endl;
            int num;
            cin >> num;
            string line = GetFabric(num);
            if (line.size() > 0)
                cout << line << endl;
            else
                cout << "This fabric is not on the list" << endl;
            break;
        }
        case (4): {  //find note
            cout << "Enter the number" << endl;
            int num;
            cin >> num;
            string line = GetNote(num);
            if (line.size() > 0)
                cout << line << endl;
            else
                cout << "This note is not on the list" << endl;
            break;
        }
        case (5): {  //delete fabric
            int num;
            string line;
            cout << "Enter the number" << endl;
            cin >> num;
            if (checkExistenceM) {
                forDeletionM.push_back(num);
                std::ifstream g("D:\\catalog.txt");
                string number = to_string(num) + "f";
                while (getline(g, line)) {
                    if (line.find(number) != std::string::npos) {
                        //push back note number for deletion
                        size_t pos = line.find_first_of(' ');
                        string part = line.substr(0, pos);
                        int n = stoi(part);
                        forDeletionS.push_back(n);
                    }
                }
                g.close();
            }
            else cout << "This fabric is not on the list" << endl;
            break;
        }
        case (6): {  //delete note
            int num;
            cout << "Enter the number" << endl;
            cin >> num;
            if (checkExistenceS) {
                string line = GetNote(num);
                size_t pos = line.find_first_of(' ');
                string part = line.substr(0, pos);
                int n = stoi(part);
                forDeletionS.push_back(n);
            }
            else
                cout<< "This note is not on the list" << endl;
            break;
        }
        case (7): {  //print all fabrics
            string line;
            ifstream myfile; //for reading records
            myfile.open("D:\\fabric.txt");
            while (getline(myfile, line))
                cout << line << endl;
            break;
        }
        case (8): {  //print all notes
            string line;
            ifstream myfile; //for reading records
            myfile.open("D:\\catalog.txt");
            while (getline(myfile, line))
                cout << line << endl;
            break;
        }
        case (9): {  //edit fabric
            int num;
            cout << "Enter the number" << endl;
            cin >> num;
            int check = checkExistenceM(num);
			if (check == 1) {
				cout << "Enter the name, color, material and density of this fabric:\n" << "(color 1 corresponds to red, 2 - to green, 3 - to blue, 4 - to black, any other - to white)" << endl;
				int color;
				string name, s_color, mat;
				double dens;
				cin >> name >> color >> mat >> dens;
				switch (color) {
				case 1: {s_color = "red"; break;}
				case 2: {s_color = "green"; break;}
				case 3: {s_color = "blue"; break;}
				case 4: {s_color = "black"; break;}
				default: {s_color = "white";}

				}
				Fabric f = Fabric(num, name, s_color, mat, dens);
				forEditingM.push_back(f);
			}
            else
                cout << "This fabric is not on the list"<<endl;
            break;
        }
        case (10): {  //edit note
            int num, fnum;
            double amount;
            cout << "Enter the number" << endl;
            cin >> num;
            cout << "fnum,am" << endl;
            cin >> num >> fnum >> amount;
            CatalogNote cn = CatalogNote(num, fnum, amount);
            int check = checkExistenceS(num);
            if (check == 1)
                forEditingS.push_back(cn);
            else
                cout << "This note is not on the list"<<endl;
            break;
        }
        case (11): {  //count fabrics
            string line;
            int count=0;
            ifstream myfile; //for reading records
            myfile.open("D:\\fabric.txt");
            while (getline(myfile, line))
                count++;
            cout << count << " fabrics total" << endl;
            break;
        }
        case (12): {  //count notes
            string line;
            int count=0;
            ifstream myfile; //for reading records
            myfile.open("D:\\catalog.txt");
            while (getline(myfile, line))
                count++;
            cout << count << " notes total" << endl;
            break;
        }
        case (13): {  //count notes for certain fabric
            int num,count=0;
            cout << "Enter number of fabric" << endl;
            cin >> num;
            int check = checkExistenceM(num);
            if (check == 1) {
                std::ifstream g("D:\\catalog.txt");
                string line;
                string number = to_string(num) + "f";
                while (getline(g, line)) {
                    if (line.find(number) != std::string::npos) {
                        cout << line << endl;
                        count++;
                    }
                }
                g.close();
                cout << count << endl;
            }
            else
                cout << "This fabric is not on the list"<<endl;
        }
        default: break;
        }
        cout << "Commands:\n1 to add fabric,\n2 to add note,\n3 to get fabric,\n4 to get note,\n5 to delete fabric,\n6 to delete note,\n7 to print all fabrics,\n8 to print all notes,\n9 to edit fabric,\n10 to edit note,\n11 to count all fabrics,\n12 to count all notes,\n13 to count notes for a certain fabric\nEnter 0 to exit" << endl;
        cin >> a;
    }
    checkDoubles();
    updM();
    updS();
 
    return 0;
}


