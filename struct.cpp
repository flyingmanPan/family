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
                            other.oldest->born_date, other.oldest->dead_date, other.oldest->isMale);
        copyTree(other.oldest, oldest);
        currentPerson = findName(other.getCurrentName(), oldest);
    }
}

bool family::addPerson(bool isCompeer, string name_, string wife_name_,
                       string born, string dead, bool isMale_, person *ptr)
{
    auto root = ptr;
    if (ptr == nullptr && isCompeer && oldest == nullptr)
    {
        cout << "Init the oldest:";
        oldest = new person(name_, wife_name_, born, dead, isMale_);
        currentPerson = oldest;
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
        guy->compeer = new person(name_, wife_name_, born, dead, isMale_);
        cout << guy->compeer->name << endl;
    }
    else if (root != nullptr && !isCompeer)
    {
        cout << "Add junior:";
        if (root->junior == nullptr)
        {
            root->junior = new person(name_, wife_name_, born, dead, isMale_);
            cout << root->junior->name << endl;
        }
        else
        {
            auto guy = root->junior;
            while (guy->compeer != nullptr)
            {
                guy = guy->compeer;
            }
            guy->compeer = new person(name_, wife_name_, born, dead, isMale_);
            cout << guy->compeer->name << endl;
        }
    }
}
bool family::addCompeer(string name, string wife_name, string born, string dead, bool isMale)
{
    addPerson(true, name, wife_name, born, dead, isMale, currentPerson);
}
bool family::addJunior(string name, string wife_name, string born, string dead, bool isMale)
{
    addPerson(false, name, wife_name, born, dead, isMale, currentPerson);
}
void family::print()
{
    if (oldest == NULL)
    {
        cout << "Empty!" << endl;
        return;
    }
    traverse(oldest);
}
void family::printCompeer()
{
    if (oldest == NULL)
    {
        cout << "Empty!" << endl;
        return;
    }
    traverseCompeer(oldest);
}
void family::printAllJunior()
{
    if (oldest == NULL)
    {
        cout << "Empty!" << endl;
        return;
    }
    traverseCompeer(oldest->junior);
}
void family::printByName(string name_)
{
    auto ptr = findName(name_, oldest);
    if (ptr == NULL)
        return;
    cout << "Name:" << ptr->name << " Wife:" << ptr->wife_name << endl;
}
void family::printParentByName(string name_)
{
    auto ptr = findParent(findName(name_, oldest), oldest);
    if (ptr == NULL)
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
                               Source_Root->junior->born_date, Source_Root->junior->dead_date, Source_Root->junior->isMale);
        copyTree(Source_Root->junior, l); //copy the left;
        Target_Root->junior = l;
    }
    if (Source_Root->compeer != nullptr)
    {
        person *r = new person(Source_Root->compeer->name, Source_Root->compeer->wife_name,
                               Source_Root->compeer->born_date, Source_Root->compeer->dead_date, Source_Root->compeer->isMale);
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
    return nullptr;
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
    return nullptr;
}
person *family::findPreCompeer(person *guy)
{
    auto tmp=findBigCompeer(guy, oldest, oldest);
    if(tmp==guy)
        return nullptr;
    while(tmp->compeer!=nullptr)
    {
        if(tmp->compeer==guy)
            return tmp;
        tmp=tmp->compeer;
    }
    return nullptr;
}

person *family::findBigCompeer(person *guy, person *ptr, person *big)
{
    if (ptr != nullptr) //preorder
    {
        if (ptr == guy)
            return big;
        auto jun_ptr = findBigCompeer(guy, ptr->junior, ptr->junior);
        auto com_ptr = findBigCompeer(guy, ptr->compeer, big);
        if (jun_ptr != nullptr)
            return jun_ptr;
        if (com_ptr != nullptr)
            return com_ptr;
        return nullptr;
    }
    return nullptr;
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
void family::changePerson(person *ptr, string name_, string wife_name_,
                          Date born, Date dead, bool isMale_)
{
    if (ptr != nullptr)
    {
        ptr->name = name_;
        ptr->wife_name = wife_name_;
        ptr->born_date = born;
        ptr->dead_date = dead;
        ptr->isMale = isMale_;
    }
}
void family::changePerson(person *ptr, person *source)
{
    if (ptr != nullptr && source != nullptr)
    {
        ptr->name = source->name;
        ptr->wife_name = source->wife_name;
        ptr->born_date = source->born_date;
        ptr->dead_date = source->dead_date;
        ptr->isMale = source->isMale;
    }
}

string family::getCurrentName() const
{
    if (currentPerson == nullptr)
        return "";
    else
        return currentPerson->name;
}
bool family::changeCurrentPerson(string name)
{
    auto ptr = findName(name, oldest);
    if (ptr == nullptr)
        return false;
    currentPerson = ptr;
    return true;
}

bool family::moveCurrentPerson(int pos)
{
    switch (pos)
    {
    case 8:
    {
        auto ptr = findParent(findBigCompeer(findName(currentPerson->name, oldest),oldest,oldest), oldest);
        if (ptr != nullptr)
        {
            currentPerson = ptr;
            return true;
        }
        return false;
    }
    case 2:
    {
        if (currentPerson->junior != nullptr)
        {
            currentPerson = currentPerson->junior;
            return true;
        }
        return false;
    }
    case 4:
    {
        auto ptr=findPreCompeer(currentPerson);
        if(ptr!=nullptr)
        {
            currentPerson=ptr;
            return true;
        }
        return false;
    }
    case 6:
    {
        if (currentPerson->compeer != nullptr)
        {
            currentPerson = currentPerson->compeer;
            return true;
        }
        return false;
    }
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
        case 'f':
        {
            string n;
            cin >> n;
            auto tmp=findPreCompeer(findName(n, oldest));
            if(tmp!=nullptr)
                cout<<tmp->name<<endl;
        }
        }
    }
}
//a a a1 1 a b b1 0 a c c1 0 a d d1 0