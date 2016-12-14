
#ifndef ITERATOR_H
#define ITERATOR_H


class Iterator{

    private:

    public:
    Iterator();
    ~Iterator();
    virtual bool hasNext() = 0;
   // virtual T next() = 0;

};

#endif // ITERATOR_H
