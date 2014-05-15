#ifndef SINGLETON_HPP
#define SINGLETON_HPP 1

#include <iostream>

 //! Classe template représentant le design pattern Singleton
template<class T> class Singleton {

  public:

    //! Retourne (en créant au besoin) une instance vers la classe «singletonisée»
    static T* getInstance() {
        if (instance) {
            std::cout<<"pas de création"<<std::endl;
            return instance;
        }
        std::cout<<"création"<<std::endl;
        instance = new T;
        return instance;
    }

    //! Supprime l’instance si créée
    static void freeInstance() {
        if (instance) {
            delete instance;
            instance = 0;
        }
    }


  private:
    Singleton();
    ~Singleton();
    Singleton(const Singleton&);
    Singleton operator=(const Singleton&);

    //! Instance de la classe à rendre singleton
    static T* instance;

};

template<class T> T* Singleton<T>::instance = 0;

#endif // SINGLETON_HPP
