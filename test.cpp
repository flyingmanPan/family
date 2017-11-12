/*——————————————————————————————————————————————




Generate by ZZ





*/
#include <iostream>
#include "struct.hpp"
#include"Date.hpp"
using namespace std;
int main()
{
    family oldest;
    while (1)
    {
        char cmd;
        cout<<">";
        cin >> cmd;
        switch (cmd)
        {
        case 'e':
            return 0;
        case 'a':
        {
            string name, wife_name, born, dead;
            cin >> name >> wife_name ;
            //cin>> born >> dead;
            int isCompeer = 0;
            cin >> isCompeer;
            oldest.add_person(isCompeer, name, wife_name, born, dead);
            break;
        }
        case 'c':
        {
            oldest.printCompeer();
            break;
        }
        case 'j':
        {
            oldest.printAllJunior();
            break;
        }
        case 't':
        {
            oldest.test();
            break;
        }
        
        }
    }
}