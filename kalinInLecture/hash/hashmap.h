#pragma once

#include <vector>

template <typename Key, typename Value>
class HashMap
{
public:
    HashMap(unsigned int (*_hf)(const Key &), unsigned int capacity = 255);
    HashMap(const HashMap<Key, Value> &other);
    ~HashMap();

    bool hasKey(const Key &k) const;

    void add(const Key &, const Value &);
    Value *get(const Key &) const;

private:
    struct row
    {
        Key key;
        Value value;
        row *next;
    };
    std::vector<row *> table;
    unsigned int (*hf)(const Key &);
};