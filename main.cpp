#include <iostream>
#include "struct.hpp"
using namespace std;

family obj;
void print_ui();
void add_oldest();

int main(void) {
    cout << "# family_tree #" << endl << endl
    	 << "[add the oldest people to build the family_tree]" << endl;
    add_oldest();
    while(1) {
    	print_ui();
	}
    return 0;
}

void print_ui() {
	system("cls");
    cout << "# family_tree #" << endl << endl;
    obj.print();
    cout << endl << "[ptr -> ]"
}

void add_oldest() {
	string name, male_str, born, dead, partner;
	bool male_temp;
	cout << "[name]" << endl;
	cin >> name;
	cout << "[gender 0:male 1:female]";
	cin >> male_str;
	cout << "[born_date format:2000-01-25]"
	cin >> born;
	cout << "[dead_date format:2000-01-25 (input 0 if alive)]"
	cin >> dead;
	cout << "[partner_name (input 0 if single)]"
	cin >> partner;
	if(male_str == "1")
		male_temp = false;
	else
		male_temp = true;
	if(partner == "0")
		partner = "";
	obj.addCompeer("", name, partner, born, dead, male_temp);
	return;
}

