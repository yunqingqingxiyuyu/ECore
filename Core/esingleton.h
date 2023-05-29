#ifndef ESINGLETON_H
#define ESINGLETON_H

#include "core_global.h"
#include <QMutex>
#include <QMutexLocker>
#include <QDebug>

#define ES(T) (ESingleton<T>::getInstance())


/**
 * @brief The ESingleton class
 * 单例模式的模板类
 */

template<typename T>
class ESingleton
{
public:

    static T* getInstance();

private:
    class Internal{
    public:
        ~Internal(){
            ESingleton<T>::s_instance->deleteLater();
            ESingleton<T>::s_instance = nullptr;
        }
    };

private:
    static T* volatile s_instance;
};

static QMutex mutex;

template<typename T>
T* volatile  ESingleton<T>::s_instance = nullptr;

template<typename T>
T* ESingleton<T>::getInstance()
{
    s_instance;
    if(s_instance == nullptr)
    {
        QMutexLocker locker(&mutex);
        if(s_instance == nullptr)
        {
            static Internal internal;
            s_instance = new T();
        }
    }

    return s_instance;
}

#endif // ESINGLETON_H
