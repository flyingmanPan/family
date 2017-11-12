#include <iostream>
#include <string>
#include "Date.hpp"
using namespace std;

struct person
{
    string name;
    string wife_name;
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
    }
};

class family
{
  private:
    person *oldest;
    void clear(person *);
    void buildTree(const person *source, person *&target);

  public:
    family();
    ~family();
    family(const family &);
    bool add_person(bool isCompeer, string name_, string wife_name,
                    string born, string dead);
    void findCompeer(person *);
    void findAllJunior(person *);
    void printCompeer();
    void printAllJunior();
    void test();
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
        buildTree(other.oldest, oldest);
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
        person *preguy = nullptr;
        while (guy->compeer != nullptr)
        {
            preguy = guy;
            guy = guy->compeer;
        }
        guy = new person(name_, wife_name_, born, dead);
        if (preguy != nullptr)
        {
            preguy->compeer = guy;
            cout << preguy->name << endl;
        }
        cout << guy->name << endl;
    }
    else if (root != nullptr && !isCompeer)
    {
        cout << "Add junior:";
        if (root->junior == nullptr)
        {
            root->junior = new person(name_, wife_name_, born, dead);
        }
        else
        {
            auto guy = root->junior;
            person *preguy = nullptr;
            while (guy->compeer != nullptr)
            {
                preguy = guy;
                guy = guy->compeer;
            }
            guy = new person(name_, wife_name_, born, dead);
            preguy->compeer = guy;
            cout << guy->name << endl;
        }
    }
}
void family::printCompeer()
{
    findCompeer(oldest);
}
void family::printAllJunior()
{
    findAllJunior(oldest);
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
    if (ptr != nullptr)
    {
        cout << "Name:" << ptr->name << " Wife:" << ptr->wife_name << endl;
        findCompeer(ptr->compeer);
    }
}
void family::clear(person *ptr)
{
    while (ptr != nullptr)
    {
        clear(ptr->compeer);
        clear(ptr->junior);
        delete ptr;
    }
}
void family::test()
{

    if (oldest->compeer == nullptr)
        cout << "Compeer Is empty";
    if (oldest->junior == nullptr)
        cout << " junior Is empty";
    cout << oldest->name << "   " << oldest->wife_name << endl;
    cout << oldest->compeer->name << "   " << oldest->compeer->wife_name << endl;
}
void family::buildTree(const person *Source_Root, person *&Target_Root)
{
    if (Source_Root->junior != nullptr)
    {
        person *l = new person(Source_Root->junior->name, Source_Root->junior->wife_name,
                               Source_Root->junior->born_date, Source_Root->junior->dead_date);
        buildTree(Source_Root->junior, l); //copy the left;
        Target_Root->junior = l;
    }
    if (Source_Root->compeer != nullptr)
    {
        person *r = new person(Source_Root->compeer->name, Source_Root->compeer->wife_name,
                               Source_Root->compeer->born_date, Source_Root->compeer->dead_date);
        buildTree(Source_Root->compeer, r); //copy the right;
        Target_Root->compeer = r;
    }
}