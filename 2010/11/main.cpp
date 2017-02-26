template <typename T>
class Container
{
public:
    Container()
    {
    }

    virtual ~Container()
    {
    }

    class Iterator
    {
    public:
        virtual ~Iterator() {}

        virtual bool hasNext() const = 0;
        virtual T &next() = 0;
        virtual void insertBefore(const T &t) = 0;
        virtual void insertAfter(const T &t) = 0;
        virtual void remove() = 0;
        virtual void rewind() = 0;
    };

    class ConstIterator
    {
    public:
        virtual ~ConstIterator() {}

        virtual bool hasNext() const = 0;
        virtual const T &next() = 0;
        virtual void rewind() = 0;
    };
};

template <typename T>
class List
    : public Container<T>
{
public:
    List()
    {
    }

    virtual ~List()
    {
    }

    class Iterator
        : public Container<T>::Iterator
    {
    public:
        Iterator(const List<T> &list) {}
        virtual ~Iterator() {}

        virtual bool hasNext() const {}
        virtual T &next() {}
        virtual void insertBefore(const T &t) {}
        virtual void insertAfter(const T &t) {}
        virtual void remove() {}
        virtual void rewind() {}
    };

    class ConstIterator
        : public Container<T>::ConstIterator
    {
    public:
        ConstIterator(const List<T> &list) {}
        virtual ~ConstIterator() {}

        virtual bool hasNext() const {}
        virtual const T &next() {}
        virtual void rewind() {}
    };    
};

int main()
{
    List<int> b;
    List<int>::Iterator itb(b);
}
