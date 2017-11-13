/*——————————————————————————————————————————————




Generate by ZZ





*/
#include <iostream>
#include <string>
#include "Date.hpp"

using namespace std;
//-------------------------
//-------------------------
#define test
//-------------------
struct Person
{
    string name;
    string partnerName;
    bool isMale;
    Date born_date;
    Date dead_date;
    Person *compeer;
    Person *junior;

    Person()
    {
        name = "NULL";
        partnerName = "NULL";
        compeer = nullptr;
        junior = nullptr;
        isMale = true;
    }
    Person(string name_, string partnerName_, string born, string dead, bool isMale_)
    {
        name = name_;
        if (partnerName_ != "NULL" && partnerName_.size())
            partnerName = partnerName_;
        if (born.size())
            born_date = Date(born);
        if (dead.size())
            dead_date = Date(dead);
        compeer = nullptr;
        junior = nullptr;
        isMale = isMale_;
    }
    Person(string name_, string partnerName_, Date born, Date dead, bool isMale_)
    {
        name = name_;
        if (partnerName_ != "NULL" && partnerName_.size())
            partnerName = partnerName_;
        born_date = born;
        dead_date = dead;
        compeer = nullptr;
        junior = nullptr;
        isMale = isMale_;
    }
};

class familyTree
{
  private:
    Person *oldest;
    Person *currentPerson;

    void clear(Person *);
    //Clear all tree;

    void copyTree(const Person *source, Person *&target);
    //Copy the tree from source node to target node.
    //--------Change Func----------
    bool addPerson(bool isCompeer, string name_, string partnerName,
                   string born, string dead, bool isMale, Person *ptr);
    //1:Judge which side to place,compeer or junior;
    //2:3:...
    //4:5:Date form string:e.g. 1989-06-04/20:00
    //6:On who?

    void changePerson(Person *ptr, string name_, string partnerName,
                      Date born, Date dead, bool isMale);
    //1:Who
    //...
    void changePerson(Person *ptr, Person *source);

    //--------Find func------------
    Person *findName(string, Person *);
    //include all name, such as name & wife name.
    //Person* findParent(string);
    Person *findJunior(Person *);
    //Who's?
    Person *findParent(Person *, Person *);
    //find parent using findName. The second one is where to find, downside is the same.
    Person *findPreCompeer(Person *);
    //find the front of compeer using findName. The second one is where to find, downside is the same.
    Person *findBigCompeer(Person *, Person *, Person *);
    //find the first of compeer using findName.
    //The second one is where to find, downside is the same.
    //The third one is the BIG, send oldest when using.
    int findGenerationNum(Person *guy, Person *ptr, int gen);
    //Who? Root 0
    //-----------------------------

    //------traverse func--------
    void traverse(Person *ptr);
    //traverse all tree

    void traverseCompeer(Person *);
    //traverse all compeer from the node.

    //----------------------------

    //-------Delete func--------

  public:
    familyTree();
    ~familyTree();
    familyTree(const familyTree &);

    void print();
    //traverse all the familyTree, and print

    void printCompeer();
    //traverse all compeer from the oldest node, and print

    void printAllJunior();
    //traverse all compeer from the oldest's junior node, and print

    void printByName(string name);
    //Print a Person's info by name;

    void printParentByName(string name);
    //Print a Person's parent info by name;

    void printGenerationNumByName(string name);
    //Print generation number by name
    void test_z();
    //for z to test

    bool addCompeer(string name, string partnerName,
                    string born, string dead, bool isMale);
    //Add compeer at current Person;
    bool addJunior(string name, string partnerName,
                   string born, string dead, bool isMale);
    //Add junior at current Person;
    string getCurrentName() const;
    bool changeCurrentPerson(string name);
    bool moveCurrentPerson(int pos);
    // 7  8  9
    // 4  5  6
    // 1  2  3
    //8 up,2 down,4 left,6 right
    bool toXML(Person* person);
};
