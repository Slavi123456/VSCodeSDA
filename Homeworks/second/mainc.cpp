#include <forward_list>
#include <iostream>
#include "secondTask.cpp"
#include "firstTask.cpp"

int main()
{
    /*std::forward_list<int> ls = {1,2,3,4,5};

    for(int el: ls) std::cout << el << " ";
    std::cout << std::endl;

    std::forward_list<int>::iterator it = ls.begin();
    ls.insert_after(it, 6);
    for(int el: ls) std::cout << el << " ";
    std::cout << std::endl;
    std::forward_list<int> flist = {1, 2, 3, 4, 5};

    int value_to_delete = 3;

    auto prev = flist.before_begin(); // Start before the first element
    auto curr = flist.begin();        // Iterator to the first element

    while (curr != flist.end())
    {
        if (*curr == value_to_delete)
        {
            curr = flist.erase_after(prev); // `erase_after` returns the iterator after the erased element
        }
        else
        {
            prev = curr; // Advance `prev` only if no deletion
            ++curr;
        }
    }

    // Print the updated list
    for (int val : flist)
    {
        std::cout << val << " ";
    }

    return 0;
    */

    UnorderedSet<std::string> *set = new UnorderedSet<std::string>();
    std::cout << std::boolalpha << "Is set empty " << set->empty() << std::endl;
    set->insert("1q2w3e");
    set->insert("slavcho");
    set->insert("petrancho");
    set->print();
    set->insert("tuskancho");
    std::string str = "petrancho";
    set->remove(str);
    set->print();
    std::cout << (*set->find("1q2w3e")).first << std::endl;
    std::cout << std::boolalpha << "Is set empty " << set->empty() << std::endl;
    set->clear();
    set->print();

    //std::vector<std::vector<int>> graph = {
    //    {1, 2, 7}, // 0 -> 1, 0 -> 2
    //    {3},       // 1 -> 2
    //    {4},       // 2 -> 3
    //    {5},       // 3 -> 4
    //    {3, 6, 7}, // 4 -> {}
    //    {1},       // 5 -> 3
    //    {},        // 5 -> 3
    //    {},        // 5 -> 3
    //};
    //DfsTraversalCollection dfsGr(graph, 0);
    //// dfsGr.print();
    //std::cout << dfsGr;
    //// dfsGr.crossEdge();
    //// dfsGr.treeEdge();
    //// dfsGr.forwardEdge();
    //// dfsGr.backEdge();
//
    //DfsTraversalCollection dfsGr2(graph, 5);
    //dfsGr2.print();
    //std::cout << std::boolalpha << (dfsGr < dfsGr2) << std::endl;
}