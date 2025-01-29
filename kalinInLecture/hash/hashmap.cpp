#include "hashmap.h"

template <typename Key, typename Value>
HashMap<Key, Value>::HashMap(unsigned int (*_hf)(const Key &), unsigned int capacity) : hf(_hf)
{
    table.assign(capacity, nullptr);
}
template <typename Key, typename Value>
HashMap<Key, Value>::~HashMap()
{
    int size = table.size();
    for (int i = 0; i < size; i++)
    {
        while (table[i])
        {
            row *toDelete = table[i];
            table[i] = table[i]->next;
            delete toDelete;
        }
    }
}

template <typename Key, typename Value>
HashMap<Key, Value>::HashMap(const HashMap<Key, Value> &other)
{
    int sizeOther = other.table.size();
    this->hf = other.hf;
    this->table.assign(capacity, nullptr);

    for (int i = 0; i < sizeOther; i++)
    {
        row *currRow = other.table[i];
        row *ourCurrRow = new row();
        ourCurrRow->key = currRow->key;
        ourCurrRow->value = currRow->value;

        row *ourCurrRowIt = ourCurrRow;
        while (currRow)
        {
            row *newRow = new row();
            newRow->key = currRow->key;
            newRow->value = currRow->value;

            ourCurrRowIt->next = newRow;
            ourCurrRowIt = ourCurrRowIt->next;
            currRow = currRow->next;
        }
        this->tablep[i] = ourCurrRow;
    }
}

template <typename Key, typename Value>
bool HashMap<Key, Value>::hasKey(const Key &key) const
{
    unsigned int hash = hf(key) % table.size();
    if (table[hash] == nullptr)
    {
        return false;
    }

    typename HashMap<Key, Value>::row *current = table[hash];
    while (current != nullptr && current->key != key)
    {
        current = current->next;
    }

    return current != nullptr;
}

template <typename Key, typename Value>
void HashMap<Key, Value>::add(const Key &key, const Value &val)
{
    unsigned int hashKey = hf(key) % table.size();

    row *newRow = new row();
    newRow->key = key;
    newRow->value = val;
    newRow->next = nullptr;

    if (table[hashKey]) //
    {
        row *curr = table[hashKey];
        while (curr->next && curr->key != key)
        {
            curr = curr->next;
        }
        if (curr->key != key)
        {
            curr->next = newRow;
            return;
        }
        delete newRow;
    }
    else
    {
        table[hashKey] = newRow;
    }
}

template <typename Key, typename Value>
Value *HashMap<Key, Value>::get(const Key &key) const
{
    unsigned int hashKey = hf(key) % table.size();

    if (table[hashKey])
    {
        row *curr = table[hashKey];
        while (curr && curr->key != key)
        {
            curr = curr->next;
        }
        return curr == nullptr ? throw "no item with that key" : curr->val;
    }
    else
    {
        throw "no item with that key";
    }
}