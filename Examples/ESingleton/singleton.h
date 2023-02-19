#ifndef SINGLETON_H
#define SINGLETON_H

#include "ESingleton"

#include <QDebug>

class Singleton
{
    Singleton();
    ~Singleton()
    {
//        qDebug() << QStringLiteral("释放Singleton对象，可以执行保存，清除等操作");
    }

    //等效下面两行 Q_DISABLE_COPY(Singleton);
    Singleton(const Singleton &) = delete ;
    Singleton& operator = (const Singleton &) = delete ;
public:
    friend class ESingleton<Singleton>;
};

#endif // SINGLETON_H
