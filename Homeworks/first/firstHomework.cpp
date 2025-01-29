#include "firstHomework.h"

Tab::Tab(std::string &str) : url(str) {}
Tab::Tab(std::string &&str) : url(std::move(str))
{
    prev = nullptr;
    next = nullptr;
    time = 0;
    data = 0;
}
Tab::Tab(const Tab &other)
{
    // ulr = other.url;
    next = other.next;
    prev = other.prev;
    time = other.time;
    data = other.data;
    url = other.url;
}
Tab::Tab(const Tab &&other) {}
// Tab &Tab::operator=(const Tab &other) {}
// Tab &Tab::operator=(const Tab &&other) {}

Browser::Browser()
{
    first = new Tab("about::blank");
    current = first;
}
Browser::Browser(Tab *newfirst)
{
    first = newfirst;
    current = first;
}
Browser::Browser(const Browser &other)
{
    copyFrom(other);
}
Browser::Browser(Browser &&other)
{
    moveFrom(std::move(other));
}
Browser &Browser::operator=(const Browser &other)
{
    if (&other != this)
    {
        free();
        copyFrom(other);
    }
    return *this;
}
Browser &Browser::operator=(Browser &&other)
{
    if (&other != this)
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}
Browser::~Browser()
{
    free();
}

Tab *Browser::getFirst() const
{
    return first;
}
Tab *Browser::getCurrent() const
{
    return current;
}

void Browser::print()
{
    Tab *headTab = first;
    if (!headTab)
        return;

    while (headTab)
    {
        if (headTab == current)
            std::cout << ">";
        std::cout << headTab->url << std::endl;
        headTab = headTab->next;
    }
}
void Browser::insert(std::string &newTabStr)
{
    Tab *dummy = new Tab(newTabStr);
    dummy->prev = current;
    dummy->next = current->next;

    current->next = dummy;
    current = current->next;
    if (!dummy->next)

        return;
    dummy->next->prev = dummy;
    // set the timestamp
}
void Browser::insert(std::string &&newTabStr)
{
    Tab *dummy = new Tab(newTabStr);
    dummy->prev = current;
    dummy->next = current->next;

    current->next = dummy;
    current = current->next;
    if (!dummy->next)
        return;
    dummy->next->prev = dummy;

    // set the timestamp
}
void Browser::go(std::string &newTabStr)
{
    current->url = newTabStr; // the string classes needs copy op =
    // change the timestamp
}
void Browser::go(std::string &&newTabStr)
{
    current->url = newTabStr; // the string classes needs move op =
    // change the timestamp
}
void Browser::back()
{
    if (current != first)
        current = current->prev;
    return;
}
void Browser::forward()
{
    if (!current->next)
        return;
    current = current->next;
}
void Browser::remove()
{
    Tab *toDelete = current;
    if (!toDelete->next)
    {
        current = current->prev;
        current->next = nullptr;
        delete toDelete;
        return;
    }
    else
    {
        current->prev->next = toDelete->next;
        current->next->prev = toDelete->prev;
        current = current->next;
        delete toDelete;
        return;
    }
}

bool isPrefix(std::string &wholeString, std::string &prefix)
{
    if (wholeString.empty())
        return false;

    int index = 0;
    while (wholeString[index] != '\0' && prefix[index] != '\0' && prefix[index] == wholeString[index])
    {
        index++;
    }
    if (index < prefix.size())
        return false;

    return true;
}
bool isPrefix(std::string &wholeString, std::string &&prefix)
{
    std::string pref = prefix;
    if (wholeString.empty())
        return false;

    int index = 0;
    while (wholeString[index] != '\0' && pref[index] != '\0' && pref[index] == wholeString[index])
    {
        index++;
    }
    if (index < pref.size())
        return false;

    return true;
}
std::string stringSubString(std::string &str, int begin)
{
    int strSize = str.size();

    int urlSize = strSize - begin;
    std::string url = "";

    for (int i = 0; i < urlSize; i++)
    {
        url.push_back(str[i + begin]);
    }
    return url;
}
void Browser::interface()
{
    std::string command;
    do
    {
        std::cout << "Type command" << std::endl;
        std::getline(std::cin, command);
        if (isPrefix(command, "$ EXIT"))
            break;
        readFunction(command);
    } while (true);
}
void Browser::readFunction(std::string &command)
{
    if (isPrefix(command, "$ GO "))
    {
        std::string str = stringSubString(command, 5);
        go(str);
    }
    else if (isPrefix(command, "$ INSERT "))
    {
        std::string str = stringSubString(command, 9);
        insert(str);
    }
    else if (isPrefix(command, "$ BACK "))
    {
        back();
        std::cout << "Current ptr is " << current->url << std::endl;
    }
    else if (isPrefix(command, "$ FORWARD "))
    {
        forward();
        std::cout << "Current ptr is " << current->url << std::endl;
    }
    else if (isPrefix(command, "$ REMOVE "))
        remove();
    else if (isPrefix(command, "$ PRINT "))
        print();
    else
        std::cout << "error" << std::endl;
    // throw "invalid command";
}

void Browser::free()

{
    if (!first || !first->next)
    {
        delete first;
        current = nullptr;
        first = nullptr;
        return;
    }

    Tab **curr = &(first->next);
    while ((*curr)->next)
    {
        delete (*curr)->prev;
        curr = &((*curr)->next);
    }
    delete (*curr);
    current = nullptr;
    first = nullptr;
    return;
}
void Browser::copyFrom(const Browser &other)

{
    Tab *otherFirst = other.first;
    if (!otherFirst || !otherFirst->next)
    {
        first = new Tab(*otherFirst);
        current = first;
        return;
    }

    Tab **currOther = &(otherFirst->next);
    first = new Tab(*(*currOther)->prev);
    Tab **currThis = &first;
    while ((*currOther))
    {
        Tab *nextTab = new Tab(*(*currOther));
        (*currThis)->next = nextTab;
        //(*currThis)->prev = ;
        nextTab->prev = (*currThis);
        currOther = &((*currOther)->next);
        currThis = &(*currThis)->next;
    }
}
void Browser::moveFrom(Browser &&other)
{
    first = other.first;
    current = other.current;
    other.first = nullptr;
    other.current = nullptr;
}
