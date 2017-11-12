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

    
    

    void printCompeer();
    //traverse all compeer from the oldest node, and print

    void printAllJunior();
    //traverse all compeer from the oldest's junior node, and print

    void printByName(string name);
    //Print a person's info by name;

    void printParentByName(string name);
    //Print a person's parent info by name;
    
    void printGenerationNumByName(string name);
    //Print generation number by name
    void test_z();
    //for z to test
    //--------Change Func----------
    bool add_person(bool isCompeer, string name_, string wife_name,
        string born, string dead);
        //1:Judge which side to place,compeer or junior;
        //2:3:...
        //4:5:Date form string:e.g. 1989-06-04/20:00

    
    //--------Find func------------

    person *findName(string, person *);
    //include all name, such as name & wife name.
    //person* findParent(string);
    person *findJunior(person *);
    //Who's?
    person *findParent(person *, person *);
    //find parent using findName. The second one is where to find, downside is the same.
    int findGenerationNum(person *guy,person* ptr,int gen);
    //Who? Root 0
    //-----------------------------


    //------traverse func--------
    void traverse(person *);
    //traverse all tree

    void traverseCompeer(person *);
    //traverse all compeer from the node.

    void traverseJunior(person *);
    //NULL
    //----------------------------


    //-------Delete func--------
    //--------WARNING----------
    void deleteOnefamily(person *);
    //NULL
    //-----------------------
};