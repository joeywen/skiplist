#ifndef __COMPARATOR_H__
#define __COMPARATOR_H__
#include <iostream>
#include <functional>

template<class T>
class Comparator : public std::binary_function<T, T, bool> {
public:
    bool operator() (T t1, T t2) {
        return (t1 > t2);
    }
};

#endif //__COMPARATOR_H__
