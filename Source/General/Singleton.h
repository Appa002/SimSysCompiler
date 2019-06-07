//
// Created by a_mod on 20.01.2019.
//

#ifndef SIMSYSCOMPILER_SINGLETON_H
#define SIMSYSCOMPILER_SINGLETON_H

namespace ACC{
    template <class T>
    class Singleton {
    private:
        static T* instance;
    public:
        static T* get(){
            if(instance == nullptr)
                instance = new T;
            return instance;
        }

        void del(){
            if(instance != nullptr)
                delete instance;
            instance = nullptr;
        }
    };
}

template <class T>
T* ACC::Singleton<T>::instance = nullptr;

#endif //SIMSYSCOMPILER_SINGLETON_H
