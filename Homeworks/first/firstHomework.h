#pragma once
#include <string>
#include <iostream>

struct Tab
{
    std::string url;
    Tab *prev = nullptr;
    Tab *next = nullptr;
    int time = 0;
    int data = 0;

    Tab(std::string &str);
    Tab(std::string &&str);
    Tab(const Tab &other);
    Tab(const Tab &&other);
    // Tab &operator=(const Tab &other);
    // Tab &operator=(const Tab &&other);
};
class Browser
{
public:
    Browser();
    Browser(Tab *newfirst);
    Browser(const Browser &other);
    Browser(Browser &&other);
    Browser &operator=(const Browser &other);
    Browser &operator=(Browser &&other);
    ~Browser();

    //missing the sort function
    void print(); 
    void insert(std::string &newTabStr);
    void insert(std::string &&newTabStr);
    void go(std::string &newTabStr);
    void go(std::string &&newTabStr);
    void back();
    void forward();
    void remove();
    void readFunction(std::string &commant);
    void interface();

    Tab *getFirst() const;
    Tab *getCurrent() const;

private:
    // can be made by insert and remove function
    void free();
    void copyFrom(const Browser &other);
    void moveFrom(Browser &&other);

    Tab *first = nullptr;
    Tab *current = nullptr;
};