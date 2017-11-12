#include "struct.hpp"
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
    traverseCompeer(oldest);
}
void family::printAllJunior()
{
    traverseCompeer(oldest->junior);
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

void family::traverseCompeer(person *ptr)
{
    if (ptr != nullptr)
    {
        cout << "Name:" << ptr->name << " Wife:" << ptr->wife_name << endl;
        traverseCompeer(ptr->compeer);
    }
}
void family::printGenerationNumByName(string name)
{
    cout<<findGenerationNum(findName(name,oldest),oldest,1)<<endl;
}
void family::traverseJunior(person *ptr)
{
    /*
    if (ptr != nullptr)
    {
        cout << "Name:" << ptr->name << " Wife:" << ptr->wife_name << endl;
        traverseCompeer(ptr->compeer);
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
person *family::findParent(person *son, person *ptr)
{
    if (ptr->junior != nullptr) //preorder
    {
        if (ptr->junior == son)
            return ptr;
        auto jun_ptr = findParent(son, ptr->junior);
        auto com_ptr = findParent(son, ptr->compeer);
        if (jun_ptr != nullptr)
            return jun_ptr;
        if (com_ptr != nullptr)
            return com_ptr;
        return nullptr;
    }
}
person *family::findJunior(person *ptr)
{
    if (ptr->junior != nullptr) //preorder
    {
        return ptr->junior;
    }
    else
        return nullptr;
}
void family::deleteOnefamily(person *ptr)
{
    ;
}
int family::findGenerationNum(person *guy,person* ptr,int gen)
{
    if (ptr != nullptr) //preorder
    {
        if (ptr==guy)
            return gen;
        auto jun = findGenerationNum(guy, ptr->junior,gen+1);
        auto com = findGenerationNum(guy, ptr->compeer,gen);
        return jun>com?jun:com;
    }
}