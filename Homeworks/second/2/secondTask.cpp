#include <iostream>
#include <vector>
#include <forward_list>
#include <string>
#include <functional>

template <typename T>
class UnorderedSet
{
    typedef std::pair<T, int> element;

    std::forward_list<element> data;
    std::vector<std::forward_list<std::forward_list<element>::iterator>> hashSet;
    const int maxSize = 256;

public:
    UnorderedSet<T>()
    {
        hashSet.resize(maxSize);
    }
    UnorderedSet<T>(const UnorderedSet &other) = delete;
    UnorderedSet<T>(UnorderedSet &&other) = delete;
    UnorderedSet<T> operator=(const UnorderedSet &other) = delete;
    UnorderedSet<T> operator=(UnorderedSet &&other) = delete;

    void print()
    {
        std::cout << "{ ";
        for (element &curr : data)
        {
            std::cout << curr.first << " ";
        }
        std::cout << "}" << std::endl;
    }
    void clear()
    {
        for (std::vector<std::forward_list<std::forward_list<element>::iterator>>::iterator it = hashSet.begin(); 
             it != hashSet.end(); ++it)
        {
            it->clear();
        }
        data.clear();
    }
    bool empty()
    {
        return data.empty();
    }

    
    int getHash(const T &el) const
    {
    }
    int getHashCode(const T &key) const
    {
        return getHash(key) % maxSize;
    }
    typename std::forward_list<element>::iterator find(const T &el)
    {
        for (typename std::forward_list<element>::iterator it = data.begin(); it != data.end(); ++it)
        {
            if (it->first == el)
                return it;
        }

        return data.end();
    }
    void insert(const T &newElement)
    {
        if (find(newElement) != data.end())
            return;

        int hash = getHashCode(newElement);
        std::forward_list<std::forward_list<element>::iterator> &currList = hashSet[hash];
        element el = std::make_pair(newElement, hash);

        typename std::forward_list<element>::iterator thisIt;
        if (!currList.empty())
        {
            thisIt = data.insert_after(currList.front(), el);
        }
        else
        {
            thisIt = data.insert_after(data.before_begin(), el);
        }

        currList.push_front(thisIt);
    }
    void remove(T &el)
    {
        typename std::forward_list<element>::iterator it = data.begin();
        typename std::forward_list<element>::iterator prev = data.before_begin();
        while (it != data.end())
        {
            if (it->first == el)
            {
                data.erase_after(prev);
                break;
            }
            ++it;
            ++prev;
        }
        if (it == data.end())
            return;

        int hash = getHashCode(el);
        typename std::forward_list<std::forward_list<element>::iterator>::iterator beg = hashSet[hash].begin();
        typename std::forward_list<std::forward_list<element>::iterator>::iterator pr = hashSet[hash].before_begin();
        while (beg != hashSet[hash].end() && (*beg) != prev)
        {
            ++beg;
            pr = beg;
        }
        if (beg != hashSet[hash].end())
            hashSet[hash].erase_after(pr);
    }

    class Iterator
    {
        friend class UnorderedSet;
        UnorderedSet &set;
        typename std::forward_list<element>::iterator it;

    public:
        Iterator(UnorderedSet &other, typename std::forward_list<element>::iterator &otherIt) : set(other), it(otherIt) {}
        T &operator*() { return it->first; }
        T *operator->() { return &it->first; }
        Iterator &operator++()
        {
            if (it != set.data.end())
            {
                it++;
            }
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator copy = *this;
            ++(*this);
            return copy;
        }
        // there is no -- for the iterator of forward_list
        bool operator==(const Iterator &rhs) const { return it == rhs.it; }
        bool operator!=(const Iterator &rhs) { return !(it == rhs.it); }
    };
    Iterator begin()
    {
        return Iterator(*this, data.begin());
    }
    Iterator end()
    {
        return Iterator(*this, data.end());
    }
    void remove(Iterator &it)
    {
        remove(*it);
    }
    void erase_if(std::function<bool(const T&)> pred)
    {
        typename std::forward_list<element>::iterator prev = data.before_begin();
        typename std::forward_list<element>::iterator it = data.begin();

        while (it != data.end()) {
            if (pred(it->first)) {
                it = data.erase_after(prev);
            } else {
                prev = it;
                ++it;
            }
        }
    }
};
