#include "struct.hpp"

familyTree::familyTree()
{
    oldest = nullptr;
    currentPerson = nullptr;
}
familyTree::~familyTree()
{
    clear(oldest);
}
familyTree::familyTree(const familyTree &other)
{
    if (other.oldest == nullptr)
        oldest = nullptr;
    else
    {
        oldest = new Person(other.oldest->name, other.oldest->partnerName,
                            other.oldest->born_date, other.oldest->dead_date, other.oldest->isMale);
        copyTree(other.oldest, oldest);
        currentPerson = findName(other.getCurrentName(), oldest);
    }
}

bool familyTree::addPerson(bool isCompeer, string name_, string partnerName_,
                           string born, string dead, bool isMale_, Person *ptr)
{
    auto root = ptr;
    if (ptr == nullptr && isCompeer && oldest == nullptr)
    {
        //cout << "Init the oldest:";
        oldest = new Person(name_, partnerName_, born, dead, isMale_);
        currentPerson = oldest;
        //cout << oldest->name << endl;
    }
    else if (root != nullptr && isCompeer)
    {
        //cout << "Add compeer:";
        auto guy = root;
        while (guy->compeer != nullptr)
        {
            guy = guy->compeer;
        }
        guy->compeer = new Person(name_, partnerName_, born, dead, isMale_);
        //cout << guy->compeer->name << endl;
    }
    else if (root != nullptr && !isCompeer)
    {
        //cout << "Add junior:";
        if (root->junior == nullptr)
        {
            root->junior = new Person(name_, partnerName_, born, dead, isMale_);
            //cout << root->junior->name << endl;
        }
        else
        {
            auto guy = root->junior;
            while (guy->compeer != nullptr)
            {
                guy = guy->compeer;
            }
            guy->compeer = new Person(name_, partnerName_, born, dead, isMale_);
            //cout << guy->compeer->name << endl;
        }
    }
}
bool familyTree::addCompeer(string name, string partnerName, string born, string dead, bool isMale)
{
    addPerson(true, name, partnerName, born, dead, isMale, currentPerson);
}
bool familyTree::addJunior(string name, string partnerName, string born, string dead, bool isMale)
{
    addPerson(false, name, partnerName, born, dead, isMale, currentPerson);
}
void familyTree::print()
{
    if (oldest == NULL)
    {
        //cout << "Empty!" << endl;
        return;
    }
    traverse(oldest);
}
void familyTree::printCompeer()
{
    if (oldest == NULL)
    {
        //cout << "Empty!" << endl;
        return;
    }
    traverseCompeer(oldest);
}
void familyTree::printAllJunior()
{
    if (oldest == NULL)
    {
        //cout << "Empty!" << endl;
        return;
    }
    traverseCompeer(oldest->junior);
}
void familyTree::printByName(string name_)
{
    auto ptr = findName(name_, oldest);
    if (ptr == NULL)
        return;
    //cout << "Name:" << ptr->name << " Wife:" << ptr->partnerName << endl;
}
void familyTree::printParentByName(string name_)
{
    auto ptr = findParent(findName(name_, oldest), oldest);
    if (ptr == NULL)
        return;
    //cout << "Name:" << ptr->name << " Wife:" << ptr->partnerName << endl;
}
void familyTree::printGenerationNumByName(string name)
{
    //cout << findGenerationNum(findName(name, oldest), oldest, 1) << endl;
}

void familyTree::traverse(Person *ptr)
{
    while (1)
    {
        //cout << "Name:" << ptr->name << " Wife:" << ptr->partnerName << endl;
        if (ptr->junior != nullptr)
            traverse(ptr->junior);
        if (ptr->compeer != nullptr)
            ptr = ptr->compeer;
        else
            break;
    }
}
void familyTree::traverseCompeer(Person *ptr)
{
    if (ptr != nullptr)
    {
        //cout << "Name:" << ptr->name << " Wife:" << ptr->partnerName << endl;
        traverseCompeer(ptr->compeer);
    }
}

void familyTree::clear(Person *ptr)
{
    if (ptr != nullptr)
    {
        clear(ptr->compeer);
        clear(ptr->junior);
        delete ptr;
    }
}

void familyTree::copyTree(const Person *Source_Root, Person *&Target_Root)
{
    if (Source_Root->junior != nullptr)
    {
        Person *l = new Person(Source_Root->junior->name, Source_Root->junior->partnerName,
                               Source_Root->junior->born_date, Source_Root->junior->dead_date, Source_Root->junior->isMale);
        copyTree(Source_Root->junior, l); //copy the left;
        Target_Root->junior = l;
    }
    if (Source_Root->compeer != nullptr)
    {
        Person *r = new Person(Source_Root->compeer->name, Source_Root->compeer->partnerName,
                               Source_Root->compeer->born_date, Source_Root->compeer->dead_date, Source_Root->compeer->isMale);
        copyTree(Source_Root->compeer, r); //copy the right;
        Target_Root->compeer = r;
    }
}

Person *familyTree::findName(string name_, Person *ptr)
{
    if (ptr != nullptr) //preorder
    {
        if (ptr->name == name_ || ptr->partnerName == name_)
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
Person *familyTree::findParent(Person *son, Person *ptr)
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
Person *familyTree::findPreCompeer(Person *guy)
{
    auto tmp = findBigCompeer(guy, oldest, oldest);
    if (tmp == guy)
        return nullptr;
    while (tmp->compeer != nullptr)
    {
        if (tmp->compeer == guy)
            return tmp;
        tmp = tmp->compeer;
    }
    return nullptr;
}

Person *familyTree::findBigCompeer(Person *guy, Person *ptr, Person *big)
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
Person *familyTree::findJunior(Person *ptr)
{
    if (ptr->junior != nullptr) //preorder
    {
        return ptr->junior;
    }
    else
        return nullptr;
}
int familyTree::findGenerationNum(Person *guy, Person *ptr, int gen)
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
void familyTree::changePerson(Person *ptr, string name_, string partnerName_,
                              Date born, Date dead, bool isMale_)
{
    if (ptr != nullptr)
    {
        ptr->name = name_;
        ptr->partnerName = partnerName_;
        ptr->born_date = born;
        ptr->dead_date = dead;
        ptr->isMale = isMale_;
    }
}
void familyTree::changePerson(Person *ptr, Person *source)
{
    if (ptr != nullptr && source != nullptr)
    {
        ptr->name = source->name;
        ptr->partnerName = source->partnerName;
        ptr->born_date = source->born_date;
        ptr->dead_date = source->dead_date;
        ptr->isMale = source->isMale;
    }
}

string familyTree::getCurrentName() const
{
    if (currentPerson == nullptr)
        return "";
    else
        return currentPerson->name;
}
bool familyTree::changeCurrentPerson(string name)
{
    auto ptr = findName(name, oldest);
    if (ptr == nullptr)
        return false;
    currentPerson = ptr;
    return true;
}

bool familyTree::moveCurrentPerson(int pos)
{
    switch (pos)
    {
    case 8:
    {
        auto ptr = findParent(findBigCompeer(findName(currentPerson->name, oldest), oldest, oldest), oldest);
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
        auto ptr = findPreCompeer(currentPerson);
        if (ptr != nullptr)
        {
            currentPerson = ptr;
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

void familyTree::test_z()
{
    auto ptr = oldest;
    while (1)
    {
        char cmd;
        //cout << "test>";
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
                //cout << "compeer null" << endl;
                if (ptr->junior == nullptr)
                    //cout << "junior null" << endl;
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
            auto tmp = findPreCompeer(findName(n, oldest));
            if (tmp != nullptr)
            //cout<<tmp->name<<endl;
        }
        case 'x':
        {
            ofstream XML("users.xml");
            toXML(oldest);
            XML.close();
        }
        }
    }
}
//a a a1 1 a b b1 0 a c c1 0 a d d1 0

bool familyTree::toXML(person *ptr)
{
    XML<<"<gen "<<findGenerationNum(ptr,oldest,0)<<">"<<endl;
    while (1)
    {
        XML << "<Name>" << ptr->name << "</name>" << endl;
        XML << "<partner>" << ptr->partnerName << "</partner>" << endl;
        if (ptr->junior != nullptr)
            toXML(ptr->junior);
        if (ptr->compeer != nullptr)
            ptr = ptr->compeer;
        else
            break;
    }
    XML<<"</gen "<<findGenerationNum(ptr,oldest,0)<<">"<<endl;
}