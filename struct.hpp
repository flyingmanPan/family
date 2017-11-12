/*——————————————————————————————————————————————




Generate by ZZ





*/
#include <iostream>
#include <string>
#include "Date.hpp"
using namespace std;

struct person
{
    string name;
    string wife_name;
    bool isMale;
    Date born_date;
    Date dead_date;
    person *compeer;
    person *junior;

    person()
    {
        name = "NULL";
        wife_name = "NULL";
        compeer = nullptr;
        junior = nullptr;
        isMale = true;
    }
    person(string name_, string wife_name_, string born, string dead)
    {
        name = name_;
        if (wife_name_ != "NULL" && wife_name_.size())
            wife_name = wife_name_;
        if (born.size())
            born_date = Date(born);
        if (dead.size())
            dead_date = Date(dead);
        compeer = nullptr;
        junior = nullptr;
        isMale = true;
    }
    person(string name_, string wife_name_, Date born, Date dead)
    {
        name = name_;
        if (wife_name_ != "NULL" && wife_name_.size())
            wife_name = wife_name_;
        born_date = born;
        dead_date = dead;
        compeer = nullptr;
        junior = nullptr;
        isMale = true;
    }
};

class family
{
  private:
    person *oldest;

    void clear(person *);
    //Clear all tree;

    void copyTree(const person *source, person *&target);
    //Copy the tree from source node to target node.

  public:
    family();
    ~family();
    family(const family &);

    bool add_person(bool isCompeer, string name_, string wife_name,
                    string born, string dead);
    //1:Judge which side to place,compeer or junior;
    //2:3:...
    //4:5:Date form string:e.g. 1989-06-04/20:00

    void printCompeer();
    //traverse all compeer from the oldest node, and print

    void printAllJunior();
    //traverse all compeer from the oldest's junior node, and print

    void printByName(string);
    //Print a person's info by name;

    void printParentByName(string);
    //Print a person's parent info by name;

    void test_z();
    //for z to test

    //--------Find func------------

    person *findName(string, person *);
    //include all name, such as name & wife name.
    //person* findParent(string);
    person *findParent(person *, person *);
    void findCompeer(person *);
    //traverse all compeer from the node.

    void findAllJunior(person *);
    //NULL

    //-----------------------------

    //------traverse func--------
    void traverse(person *);
};

family::family()
{
    oldest = nullptr;
}
family::~family()
{
    clear(oldest);
}
family::family(const family &other)
{
    if (other.oldest == nullptr)
        oldest = nullptr;
    else
    {
        oldest = new person(other.oldest->name, other.oldest->wife_name,
                            other.oldest->born_date, other.oldest->dead_date);
        copyTree(other.oldest, oldest);
    }
}
bool family::add_person(bool isCompeer, string name_, string wife_name_, string born, string dead)
{
    auto root = oldest;
    if (oldest == nullptr && isCompeer)
    {
        cout << "Init the oldest:";
        oldest = new person(name_, wife_name_, born, dead);
        cout << oldest->name << endl;
    }
    else if (root != nullptr && isCompeer)
    {
        cout << "Add compeer:";
        auto guy = root;
        while (guy->compeer != nullptr)
        {
            guy = guy->compeer;
        }
        guy->compeer = new person(name_, wife_name_, born, dead);
        cout << guy->compeer->name << endl;
    }
    else if (root != nullptr && !isCompeer)
    {
        cout << "Add junior:";
        if (root->junior == nullptr)
        {
            root->junior = new person(name_, wife_name_, born, dead);
            cout << root->junior->name << endl;
        }
        else
        {
            auto guy = root->junior;
            while (guy->compeer != nullptr)
            {
                guy = guy->compeer;
            }
            guy->compeer = new person(name_, wife_name_, born, dead);
            cout << guy->compeer->name << endl;
        }
    }
}
void family::printCompeer()
{
    findCompeer(oldest);
}
void family::printAllJunior()
{
    findCompeer(oldest->junior);
}
void family::printByName(string name_)
{
    auto ptr = findName(name_, oldest);
    cout << "Name:" << ptr->name << " Wife:" << ptr->wife_name << endl;
}
void family::printParentByName(string name_)
{
    auto ptr = findParent(findName(name_, oldest), oldest);
    cout << "Name:" << ptr->name << " Wife:" << ptr->wife_name << endl;
}
void family::findCompeer(person *ptr)
{
    if (ptr != nullptr)
    {
        cout << "Name:" << ptr->name << " Wife:" << ptr->wife_name << endl;
        findCompeer(ptr->compeer);
    }
}
void family::findAllJunior(person *ptr)
{
    /*
    if (ptr != nullptr)
    {
        cout << "Name:" << ptr->name << " Wife:" << ptr->wife_name << endl;
        findCompeer(ptr->compeer);
    }
    */
}

void family::clear(person *ptr)
{
    if (ptr != nullptr)
    {
        clear(ptr->compeer);
        clear(ptr->junior);
        delete ptr;
    }
}

void family::test_z()
{
    auto ptr = oldest;
    while (1)
    {
        char cmd;
        cout << "test>";
        cin >> cmd;
        switch (cmd)
        {
        case 'e':
            return;
        case 'j':
        {
            ptr = ptr->junior;
            break;
        }
        case 'c':
        {
            ptr = ptr->compeer;
            break;
        }
        case 'l':
        {
            if (ptr->compeer == nullptr)
                cout << "compeer null" << endl;
            if (ptr->junior == nullptr)
                cout << "junior null" << endl;
            break;
        }
        case 'r':
        {
            clear(oldest);
            break;
        }
        case 't':
        {
            traverse(oldest);
            break;
        }
        }
    }
}
void family::copyTree(const person *Source_Root, person *&Target_Root)
{
    if (Source_Root->junior != nullptr)
    {
        person *l = new person(Source_Root->junior->name, Source_Root->junior->wife_name,
                               Source_Root->junior->born_date, Source_Root->junior->dead_date);
        copyTree(Source_Root->junior, l); //copy the left;
        Target_Root->junior = l;
    }
    if (Source_Root->compeer != nullptr)
    {
        person *r = new person(Source_Root->compeer->name, Source_Root->compeer->wife_name,
                               Source_Root->compeer->born_date, Source_Root->compeer->dead_date);
        copyTree(Source_Root->compeer, r); //copy the right;
        Target_Root->compeer = r;
    }
}

person *family::findName(string name_, person *ptr)
{
    if (ptr != nullptr) //preorder
    {
        if (ptr->name == name_ || ptr->wife_name == name_)
            return ptr;
        auto jun_ptr = findName(name_, ptr->junior);
        auto com_ptr = findName(name_, ptr->compeer);
        if (jun_ptr != nullptr)
            return jun_ptr;
        if (com_ptr != nullptr)
            return com_ptr;
        return nullptr;
    }
}
void family::traverse(person *ptr)
{
    while (1)
    {
        cout << "Name:" << ptr->name << " Wife:" << ptr->wife_name << endl;
        if (ptr->junior != nullptr)
            traverse(ptr->junior);
        if (ptr->compeer != nullptr)
            ptr = ptr->compeer;
        else
            break;
    }
}
person *family::findParent(person *son,person *ptr)
{
    if (ptr->junior != nullptr) //preorder
    {
        if (ptr->junior == son)
            return ptr;
        auto jun_ptr = findParent(son,ptr->junior);
        auto com_ptr = findParent(son,ptr->compeer);
        if (jun_ptr != nullptr)
            return jun_ptr;
        if (com_ptr != nullptr)
            return com_ptr;
        return nullptr;
    }
}