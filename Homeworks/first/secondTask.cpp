#include <iostream>
#include <vector>

class BoolVector
{
public:
    class It
    {
    private:
        BoolVector *bv;
        unsigned index;

    public:
        It(BoolVector *bv, unsigned index) : bv(bv), index(index) {}

        bool operator*() const { return (*bv)[index]; }
        unsigned getIndex() const { return index; }

        It &operator++()
        {
            index++;
            return *this;
        }
        It operator++(int)
        {
            It temp = *this;
            ++(*this);
            return temp;
        }

        It &operator--()
        {
            index--;
            return *this;
        }
        It operator--(int)
        {
            It temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const It &other) const { return index == other.index; }
        bool operator!=(const It &other) const { return !(*this == other); }
    };
    class ConstIt
    {
    private:
        const BoolVector *bv;
        unsigned index;

    public:
        ConstIt(const BoolVector *bv, unsigned index) : bv(bv), index(index) {}

        bool operator*() const { return (*bv)[index]; }
        unsigned getIndex() const { return index; }

        ConstIt &operator++()
        {
            index++;
            return *this;
        }
        ConstIt operator++(int)
        {
            ConstIt temp = *this;
            ++(*this);
            return temp;
        }

        ConstIt &operator--()
        {
            index--;
            return *this;
        }
        ConstIt operator--(int)
        {
            ConstIt temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const ConstIt &other) const
        {
            return index == other.index;
        }
        bool operator!=(const ConstIt &other) const
        {
            return !(*this == other);
        }
    };
    class ReverseIt
    {
    private:
        BoolVector *boolVec;
        unsigned index;

    public:
        ReverseIt(BoolVector *newBoolVec, unsigned index) : boolVec(newBoolVec), index(index) {}

        bool operator*() const { return (*boolVec)[index]; }
        unsigned getIndex() const { return index; }

        ReverseIt &operator++()
        {
            index--;
            return *this;
        }
        ReverseIt operator++(int)
        {
            ReverseIt temp = *this;
            ++(*this);
            return temp;
        }
        ReverseIt &operator--()
        {
            index--;
            return *this;
        }
        ReverseIt operator--(int)
        {
            ReverseIt temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const ReverseIt &other) const { return index == other.index; }
        bool operator!=(const ReverseIt &other) const { return !(*this == other); }
    };

    BoolVector() = default;

    // unsigned getSize() const { return size; }

    bool &operator[](unsigned index)
    {
        if (index >= size)
            return;
        return getBitRef(index);
    }
    const bool &operator[](unsigned index) const
    {
        if (index >= size)
            return;
        return getBit(index);
    }

    void push_back(bool value)
    {
        if (size % BUCKET_SIZE == 0)
        {
            vec.push_back(0);
        }
        setBit(size, value);
        size++;
    }
    void pop_back()
    {
        if (size == 0)
            return;
        size--;
        if (size % BUCKET_SIZE == 0)
        {
            vec.pop_back();
        }
    }
    void pop_front()
    {
        if (size == 0)
            return;
        for (int i = 1; i < size; i++)
        {
            setBit(i - 1, getBit(i));
        }
        size--;
        if (size % BUCKET_SIZE == 0)
        {
            vec.pop_back();
        }
    }
    void print()
    {
        for (int y = 0; y < size; y++)
        {
            std::cout << "cell[" << y << "] = " << std::boolalpha << getBit(y) << std::endl;
        }
    }

    void insert(It &it, bool value)
    {
        int index = it.getIndex();
        if (index > size)
            return;
        push_back(false);
        for (int i = size - 1; i > index; i--)
        {
            setBit(i, getBit(i - 1));
        }
        setBit(index, value);
    }
    void remove(It &it)
    {
        int index = it.getIndex();
        if (index >= size)
            return;
        for (int i = index; i < size - 1; i++)
        {
            setBit(i, getBit(i + 1));
        }
        pop_back();
    }
    void insert(ConstIt &it, bool value)
    {
        int index = it.getIndex();
        if (index > size)
            return;
        push_back(false);
        for (int i = size - 1; i > index; i--)
        {
            setBit(i, getBit(i - 1));
        }
        setBit(index, value);
    }
    void remove(ConstIt &it)
    {
        int index = it.getIndex();
        if (index >= size)
            return;
        for (int i = index; i < size - 1; i++)
        {
            setBit(i, getBit(i + 1));
        }
        pop_back();
    }
    void insert(ReverseIt &it, bool value)
    {
        int index = it.getIndex();
        if (index > size)
            return;
        push_back(false);
        for (int i = size - 1; i > index; i--)
        {
            setBit(i, getBit(i - 1));
        }
        setBit(index, value);
    }
    void remove(ReverseIt &it)
    {
        int index = it.getIndex();
        if (index >= size)
            return;
        for (int i = index; i < size - 1; i++)
        {
            setBit(i, getBit(i + 1));
        }
        pop_back();
    }

    It begin() { return It(this, 0); }
    It end() { return It(this, size); }
    ReverseIt rbegin() { return ReverseIt(this, size - 1); }
    ReverseIt rend() { return ReverseIt(this, -1); }
    ConstIt cbegin() const { return ConstIt(this, 0); }
    ConstIt cend() const { return ConstIt(this, size); }

private:
    const uint8_t BUCKET_SIZE = 8;
    std::vector<uint8_t> vec;
    unsigned size = 0;

    bool getBit(unsigned index) const
    {
        unsigned bucketInd = index / BUCKET_SIZE;
        unsigned bitPos = index % BUCKET_SIZE;
        uint8_t mask = 1 << (BUCKET_SIZE - bitPos - 1);
        return (vec[bucketInd] & mask) == mask;
    }
    bool &getBitRef(unsigned index)
    {
        unsigned bucketInd = index / BUCKET_SIZE;
        unsigned bitPos = index % BUCKET_SIZE;
        uint8_t mask = 1 << (BUCKET_SIZE - bitPos - 1);
        bool res = (vec[bucketInd] & mask) == mask;
        return res;
    }
    void setBit(unsigned index, bool value)
    {
        unsigned bucketInd = index / BUCKET_SIZE;
        unsigned bitPos = index % BUCKET_SIZE;
        uint8_t mask = 1 << (BUCKET_SIZE - bitPos - 1);
        if (value)
            vec[bucketInd] |= mask;
        else
            vec[bucketInd] &= ~mask;
    }
};
