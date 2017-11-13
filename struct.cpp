#include "struct.hpp"

family::family()
{
    oldest = nullptr;
    currentPerson = nullptr;
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
                            other.oldest->born_date, other.oldest->dead_date,other.oldest->isMale);
        copyTree(other.oldest, oldest);
    }
    string currentName = other.getCurrentName();
    currentPerson = findName(currentName, oldest);
}

bool family::addPerson(bool isCompeer, string name_, string wife_name_,
    string born, string dead,bool isMale_,person* ptr)
{
    auto root = ptr;
    if (ptr == nullptr && isCompeer&& oldest ==nullptr)
    {
        cout << "Init the oldest:";
        oldest = new person(name_, wife_name_, born, dead,isMale_);
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
        guy->compeer = new person(name_, wife_name_, born, dead,isMale_);
        cout << guy->compeer->name << endl;
    }
    else if (root != nullptr && !isCompeer)
    {
        cout << "Add junior:";
        if (root->junior == nullptr)
        {
            root->junior = new person(name_, wife_name_, born, dead,isMale_);
            cout << root->junior->name << endl;
        }
        else
        {
            auto guy = root->junior;
            while (guy->compeer != nullptr)
            {
                guy = guy->compeer;
            }
            guy->compeer = new person(name_, wife_name_, born, dead,isMale_);
            cout << guy->compeer->name << endl;
        }
    }
}

void family::print()
{
    if(oldest == NULL) {
        cout << "Empty!" << endl;
        return;
    }
    traverse(oldest);
}
void family::printCompeer()
{
    if(oldest == NULL) {
        cout << "Empty!" << endl;
        return;
    }
    traverseCompeer(oldest);
}
void family::printAllJunior()
{
    if(oldest == NULL) {
        cout << "Empty!" << endl;
        return;
    }
    traverseCompeer(oldest->junior);
}
void family::printByName(string name_)
{
    auto ptr = findName(name_, oldest);
    if(ptr == NULL)
        return;
    cout << "Name:" << ptr->name << " Wife:" << ptr->wife_name << endl;
}
void family::printParentByName(string name_)
{
    auto ptr = findParent(findName(name_, oldest), oldest);
    if(ptr == NULL)
        return;
    cout << "Name:" << ptr->name << " Wife:" << ptr->wife_name << endl;
}
void family::printGenerationNumByName(string name)
{
    cout << findGenerationNum(findName(name, oldest), oldest, 1) << endl;
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
void family::traverseCompeer(person *ptr)
{
    if (ptr != nullptr)
    {
        cout << "Name:" << ptr->name << " Wife:" << ptr->wife_name << endl;
        traverseCompeer(ptr->compeer);
    }
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

void family::copyTree(const person *Source_Root, person *&Target_Root)
{
    if (Source_Root->junior != nullptr)
    {
        person *l = new person(Source_Root->junior->name, Source_Root->junior->wife_name,
                               Source_Root->junior->born_date, Source_Root->junior->dead_date,Source_Root->junior->isMale);
        copyTree(Source_Root->junior, l); //copy the left;
        Target_Root->junior = l;
    }
    if (Source_Root->compeer != nullptr)
    {
        person *r = new person(Source_Root->compeer->name, Source_Root->compeer->wife_name,
                               Source_Root->compeer->born_date, Source_Root->compeer->dead_date,Source_Root->compeer->isMale);
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
int family::findGenerationNum(person *guy, person *ptr, int gen)
{
    if (ptr != nullptr) //preorder
    {
        if (ptr == guy)
            return gen;
        auto jun = findGenerationNum(guy, ptr->junior, gen + 1);
        auto com = findGenerationNum(guy, ptr->compeer, gen);
        return jun > com ? jun : com;
    }
}
void family::changePerson(person* ptr,string name_, string wife_name_,
    Date born, Date dead,bool isMale_)
{
    if(ptr!=nullptr)
    {
        ptr->name=name_;
        ptr->wife_name=wife_name_;
        ptr->born_date=born;
        ptr->dead_date=dead;
        ptr->isMale=isMale_;
    }
}
void family::changePerson(person*ptr ,person* source)
{
    if(ptr!=nullptr&&source!=nullptr)
    {
        ptr->name=source->name;
        ptr->wife_name=source->wife_name;
        ptr->born_date=source->born_date;
        ptr->dead_date=source->dead_date;
        ptr->isMale=source->isMale;
    }
}

string family::getCurrentName()
{
    if(currentPerson == NULL)
        return "";
    else
        return currentPerson->name;
}
bool family::changeCurrentPerson(string name)
{
    if(findName(name) == NULL)
        return false;
    currentPerson = findName(name);
    return true;
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
