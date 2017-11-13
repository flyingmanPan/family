#include <iostream>
#include <conio.h>
#include "struct.hpp"
using namespace std;

familyTree obj;
void print_ui();
void add_person(char oper);
void change_current();
void change_information();
void write_to_xml();

int main(void) {
    cout << "# family_Tree #" << endl << endl
    	 << "# Add the oldest people to build the family_tree. #" << endl << endl;
    add_person('3');
    char oper = 0;
    while(1) {
    	print_ui();
        oper = getch();
        if(oper == '1') {
            change_current();
        }
        else if(oper == '2') {
            change_information();
        }
        else if(oper == '3') {
            add_person(oper);
        }
        else if(oper == '4') {
            add_person(oper);
        }
        else if(oper == '5') {
            write_to_xml();
        }
        else if(oper == '0') {
            break;
        }
	}
    return 0;
}

void print_ui() {
	system("cls");
    cout << "# family_tree #" << endl << endl
    	 << "# people on right subtree are compeer" << endl
    	 << "# left-to-right is elder-to-younger" << endl << endl
    	 << "# people on left subtree are children" << endl
    	 << "# right-to-left is elder-to-junior" << endl << endl;
    obj.asd_show();
    cout << "[current person -> " << obj.getCurrentName() << " ]"
         << endl << endl
         << "[press 1] change the current person" << endl
         << "[press 2] change information of the current person" << endl
         << "[press 3] add a brother or sister" << endl
         << "[press 4] add a son or daughter" << endl
         << "[press 5] write to XML" << endl
         << "[press 0] exit the program" << endl << endl;
    return;
}

void add_person(char oper) {
	string name, male_str, born, dead, partner;
	bool male_temp;
	cout << "[name]" << endl;
	cin >> name;
	cout << "[gender 0:male 1:female]" << endl;
	cin >> male_str;
	cout << "[born_date format:2000-01-25]" << endl;
	cin >> born;
	cout << "[dead_date format:2000-01-25 (input 0 if alive)]" << endl;
	cin >> dead;
	cout << "[partner_name (input 0 if single)]" << endl;
	cin >> partner;
	if(male_str == "1")
		male_temp = false;
	else
		male_temp = true;
	if(partner == "0")
		partner = "";

    if(oper == '3') {
        if(!obj.addCompeer(name, partner, born, dead, male_temp)) {
            cout << endl << "[fail] Person exist" << endl
                 << "[fail] Press any button..." << endl;
            getch();
        }
    }
    else if(oper == '4') {
        if(!obj.addJunior(name, partner, born, dead, male_temp)) {
            cout << endl << "[fail] Person exist" << endl
                 << "[fail] Press any button..." << endl;
            getch();
        }
    }
	return;
}

void change_current() {
    string name;
    cout << "[name]" << endl;
    cin >> name;
    if(!obj.changeCurrentPerson(name)) {
        cout << endl << "[fail] Unfound" << endl
             << "[fail] Press any button..." << endl;
        getch();
    }
    return;
}

void change_information() {
    string name, male_str, born, dead, partner;
	bool male_temp;
	cout << "[name]" << endl;
	cin >> name;
	cout << "[gender 0:male 1:female]" << endl;
	cin >> male_str;
	cout << "[born_date format:2000-01-25]" << endl;
	cin >> born;
	cout << "[dead_date format:2000-01-25 (input 0 if alive)]" << endl;
	cin >> dead;
	cout << "[partner_name (input 0 if single)]" << endl;
	cin >> partner;
	if(male_str == "1")
		male_temp = false;
	else
		male_temp = true;
	if(partner == "0")
		partner = "";
    if(!obj.changePerson(name, partner, born, dead, male_temp)) {
        cout << endl << "[fail] Person exist" << endl
             << "[fail] Press any button..." << endl;
        getch();
    }
    return;
}

void write_to_xml() {
    obj.writeToXML();
    cout << "[succeed] XML has been updated" << endl
         << "[succeed] Press any button..." << endl;
    getch();
    return;
}
