//
// Created by a_mod on 06.01.2019.
//

#ifndef SIMSYSCOMPILER_STACK_H
#define SIMSYSCOMPILER_STACK_H


#include <vector>

namespace ACC {
    template <class T>
    class Stack {
    private:
        std::vector<T> internal;
    public:
        Stack() = default;

        void push(T element);
        T pop();
        T& peek(size_t offset = 0);
        size_t size();
        void destroy();

        T& at(size_t idx = 0);
        typename std::vector<T>::iterator begin();
        typename std::vector<T>::iterator end();
    };

    template<class T>
    void Stack<T>::push(T element) {
        internal.push_back(element);
    }

    template<class T>
    T Stack<T>::pop() {
        T thing = internal.at(internal.size() - 1);
        internal.pop_back();
        return thing;
    }

    template<class T>
    T &Stack<T>::peek(size_t offset)  {
        return internal.at(internal.size() - offset - 1);
    }

    template<class T>
    size_t Stack<T>::size() {
        return internal.size();
    }

    template<class T>
    T &Stack<T>::at(size_t idx) {
        return internal.at(idx);
    }

    template<class T>
    typename std::vector<T>::iterator Stack<T>::begin() {
        return internal.begin();
    }

    template<class T>
    typename std::vector<T>::iterator Stack<T>::end()  {
        return internal.end();
    }

    template<class T>
    void Stack<T>::destroy() {
        internal.clear();
    }

}

#endif //SIMSYSCOMPILER_STACK_H
