#include <iostream>
#include "struct.hpp"
using namespace std;

void print_ui();

int main(void) {
    family obj;
    while(1) {
        print_ui(obj);

    }
    return 0;
}

void print_ui(family& obj) {
    cout << "# 家谱管理系统 #" << endl;
    obj.traverse()
}
/*-----------To Do List
XML
hihi

----------------------*/