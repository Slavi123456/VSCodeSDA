
#include <memory>

template <class T, class Allocator = std::allocator<T>>
class Vector
{
private:
    T *data = nullptr;
    size_t size = 0;
    size_t capacity = 0;

    Allocator alloc;

    void resize(size_t newSize);
    size_T calculateNewSize(size_t oldSize);

    void free();
    void copyFrom(const Vector &other);
    void moveFrom(Vector &&other);

public:
    Vector() = default;
    Vector(size_t initSize, const T &initValue);
    Vector(const Vector &other) { copyFrom(other); }
    Vector(Vector &&other) { moveFrom(std::move(other)); }
    Vector operator=(const Vector &other);
    Vector operator=(Vector &&other);
    ~Vector() { free(); }

    class Const_It;

    size_t size() const;
    size_t capacity() const;

    T *operator[](size_t index);
    const T *operator[](size_t index) const;

    bool push_back(const T &newValue);
    bool pop_back(const T &newValue);
    void clear();
    bool isEmpty();
    // void erase(const Const_It position);
    Const_It cbegin() const;
    Const_It cend() const;

    class Const_It
    {
    private:
        T *currPtr;

    public:
        Const_It(T *val) : currPtr(val) {}

        // in the const there is no ++ and -- because it will affect the iterator
        // Const_It operator++(int){}
        // Const_It& operator++(){}

        // Const_It operator--(int){}
        // Const_It& operator--(){}

        Const_It operator+(size_t off);
        Const_It operator-(size_t off);

        const T *operator->() const;
        const T &operator*() const;

        bool operator==(const Const_It &other) const;
        bool operator!=(const Const_It &other) const;
    }
};

template <class T, class Allocator>
void Vector<T, Allocator>::free() {}

template <class T, class Allocator>
void Vector<T, Allocator>::copyFrom(const Vector &other) {}

template <class T, class Allocator>
void Vector<T, Allocator>::moveFrom(Vector &&other) {}