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
            char cmd2;
            cin >> cmd2;
            if(cmd2=='1')
                oldest.addCompeer(name, wife_name, born, dead,true);
            else
                oldest.addJunior(name, wife_name, born, dead,true);
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
            oldest.test_z();
            break;
        }
        case 'f':
        {
            string temp;
            cin>>temp;
            oldest.printByName(temp);
            break;
        }
        case 'p':
        {
            string temp;
            cin>>temp;
            oldest.printParentByName(temp);
            break;
        }
        case 'g':
        {
            string temp;
            cin>>temp;
            oldest.printGenerationNumByName(temp);
        }
        }
    }
}
//a a a1 1 a b b1 1 a c c1 0 a d d1 0