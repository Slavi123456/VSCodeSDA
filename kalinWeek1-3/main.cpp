#include <iostream>
#include <string>
#include <vector>

////////////////////////////////////////////////////////////////////////
// Structs and Classes

template <class T>
struct BinTreeNode
{
    T _data;
    BinTreeNode *_left, *_right;

    BinTreeNode(const T &data) : _data(data), _left(nullptr), _right(nullptr) {}
    BinTreeNode(const T &data, BinTreeNode *left, BinTreeNode *right) : _data(data), _left(left), _right(right) {}

    //... помощни конструктори
};

//////////////////////////////////////////
// 19.1 - 19.7
// 19.11 - 19.16

template <class T>
class BTree
{
public:
    BTree(BinTreeNode<T> *root) : root(root) {}
    BTree() : root(nullptr) {}

    BTree<T> *getRoot() const { return root; }
    ~BTree() { free(root); }
    int searchCount(bool (*pred)(const T &))
    {
        return searchCountHelper(root, pred);
    }
    int height()
    {
        return heightHelper(root);
    }
    int countLeafs()
    {
        countLeafsHelper(root);
    }
    int countNodes()
    {
        countNodesHelper(root);
    }
    int countEvenNodes()
    {
        countEvenNodesHelper(root);
    }
    void printTree()
    {
        printTreeHelper(root);
    }
    int maxElement()
    {
        return maxElementHelper(root);
    }
    int elementByString(std::string &str)
    {
        return elementByStringHelper(root, str);
    }
    std::vector<T> listLeafs()
    {
        std::vector<T> listLeafs = listLeafsHelper(root);
        std::cout << "Vector of the leaf of the tree: ";
        std::cout << "vector  { ";
        for (T data : listLeafs)
        {
            std::cout << data << " ";
        }
        std::cout << "} " << std::endl;
        return listLeafs;
    }
    std::string findTrace(T el)
    {
        return findTraceHelper(root, el);
    }
    bool isOrdered()
    {
        if (!root)
            return true;
        return isOrderedHelper(root, root->_data);
    }

private:
    void free(BinTreeNode<T> *root)
    {
        if (!root)
            return;
        free(root->_right);
        free(root->_left);
        delete root;
    }
    int searchCountHelper(BinTreeNode<T> *root, bool (*pred)(const T &))
    {
        if (!root)
            return 0;

        if (pred(root->_data))
            return 1 + searchCountHelper(root->_left, pred) + searchCountHelper(root->_right, pred);
        else
            return searchCountHelper(root->_left, pred) + searchCountHelper(root->_right, pred);
    }
    int heightHelper(BinTreeNode<T> *root)
    {
        if (!root)
            return 0;
        int leftTreeHeight = heightHelper(root->_left);
        int rightTreeHeight = heightHelper(root->_right);
        return leftTreeHeight > rightTreeHeight ? leftTreeHeight + 1 : rightTreeHeight + 1;
    }
    int countLeafsHelper(BinTreeNode<T> *root)
    {
        if (!root)
            return 0;
        if (!root->_left && !root->_right)
            return 1;
        else
            return countLeafsHelper(root->_left) + countLeafsHelper(root->_right);
    }
    int countNodesHelper(BinTreeNode<T> *root)
    {
        if (!root)
            return 0;
        return 1 + countNodesHelper(root->_left) + countNodesHelper(root->_right);
    }
    int countEvenNodesHelper(BinTreeNode<T> *root)
    {
        if (!root)
            return 0;
        if ((root->_data & 1) == 0)
            return 1 + countEvenNodesHelper(root->_left) + countEvenNodesHelper(root->_right);
        else
            return countEvenNodesHelper(root->_left) + countEvenNodesHelper(root->_right);
    }
    void printTreeHelper(BinTreeNode<T> *root, int spacing = 0)

    {
        if (!root)
            return;
        printTreeHelper(root->_right, spacing + 3);
        std::string spaces(spacing, ' ');
        std::cout << spaces << root->_data << std::endl;
        printTreeHelper(root->_left, spacing + 3);
    }
    int maxElementHelper(BinTreeNode<T> *root)
    {
        if (!root)
            throw "The tree is empty?!?!??!";
        if (!root->_right && !root->_left)
            return root->_data;
        return maxElementHelper(root->_right);
    }
    int elementByStringHelper(BinTreeNode<T> *root, std::string &str)
    {
        if (!root)
            throw "no elements in empty tree";
        BinTreeNode<T> **current = &root;

        int strSize = str.size();
        int count = 0;
        while (*current && count < strSize)
        {
            if (str[count] == 'L')
                current = &((*current)->_left);
            if (str[count] == 'R')
                current = &((*current)->_right);
            count++;
        }

        if (!(*current))
            throw "the path goes to nullptr";

        return (*current)->_data;
    }
    std::vector<T> listLeafsHelper(BinTreeNode<T> *root)
    {
        std::vector<T> list;
        if (!root)
            return list;
        if (!root->_left && !root->_right)
            list.push_back(root->_data);
        std::vector<T> left = listLeafsHelper(root->_left);
        std::vector<T> right = listLeafsHelper(root->_right);
        for (size_t i = 0; i < left.size(); i++)
        {
            list.push_back(left[i]);
        }
        for (size_t i = 0; i < right.size(); i++)
        {
            list.push_back(right[i]);
        }
        return list;
    }
    std::string findTraceHelper(BinTreeNode<T> *root, T el)
    {
        std::string str = "";
        if (!root)
            return str;
        if (el < root->_data)
        {
            str.push_back('L');
            std::string left = findTraceHelper(root, el);
            str += left;
        }
        else
        {
            str.push_back('R');
            std::string right = findTraceHelper(root, el);
            str += right;
        }
    }
    bool isOrderedHelper(BinTreeNode<T> *root, T prevEl)
    {
        if (!root)
            return true;
        if (!root->_left && !root->_right)
            return true;
        else if (!root->_left)
        {
            if (root->_right->_data > prevEl)
            {
                return true && isOrderedHelper(root->_right, root->_right->_data);
            }
            else
                return false;
        }
        else if (!root->_right)
        {
            if (root->_left->_data <= prevEl)
            {
                return true && isOrderedHelper(root->_left, root->_left->_data);
            }
            else
                return false;
        }
        else
        {
            if (root->_right->_data > prevEl && root->_left->_data <= prevEl)
            {
                return true && isOrderedHelper(root->_right, root->_right->_data) && isOrderedHelper(root->_left, root->_left->_data);
            }
            else
                return false;
        }
    }
    BinTreeNode<T> *root;
};

////////////////////////////////////////////////////////////////////////
int main()
{
    // BinTreeNode<int> root = {7, nullptr, nullptr};
    BinTreeNode<int> *root = new BinTreeNode<int>(8, new BinTreeNode<int>(6, new BinTreeNode<int>(5, new BinTreeNode<int>(3, nullptr, nullptr), nullptr), new BinTreeNode<int>(7, nullptr, nullptr)), new BinTreeNode<int>(9, nullptr, nullptr));
    BTree<int> *bTree = new BTree<int>(root);
    bTree->printTree();
    std::cout << "Count of nodes of the tree is " << bTree->countNodes() << std::endl;
    std::cout << "Count of even nodes in the tree is " << bTree->countEvenNodes() << std::endl;
    std::cout << "Count of even nodes {with lambda function}  in the tree is " << bTree->searchCount([](const int &k)
                                                                                                     { return (k & 1) == 0; })
              << std::endl;
    std::cout << "Height of the tree " << bTree->height() << std::endl;
    std::cout << "Count leafs of the tree " << bTree->countLeafs() << std::endl;
    std::cout << "Max element of the tree " << bTree->maxElement() << std::endl;
    std::string newStr = "LLL";
    std::cout << "The element of the path is " << bTree->elementByString(newStr) << std::endl;
    bTree->listLeafs();
    std::cout << std::boolalpha << "Is the tree ordered " << bTree->isOrdered() << std::endl;
    // Still working on it
    // std::cout << "The trace of " << 3 << " of the path is " << bTree->findTrace(3) << std::endl;
    return 0;
}