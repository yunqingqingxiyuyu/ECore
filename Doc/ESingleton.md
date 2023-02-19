# ESingleton

创建的一个单例模板类，该模板类指定的模板参数必须是`QObject`派生的类。

Header:`#include <ELineEdit>`

## 描述

创建的一个单例模板类，该模板类指定的模板参数必须是`QObject`派生的类。该模板类可以创建唯一的一个实例，其用法如下，例如要创建一个`EDateTimeEdit`的一个唯一对象:

```C++
auto edit = ESingleton<EDateTimeEdit>::getInstance();
qDebug() << "对象地址" << edit;
edit = ESingleton<EDateTimeEdit>::getInstance();
qDebug() << "对象地址" << edit;
```

其输出的地址为:

```cpp
对象地址 EDateTimeEdit(0x7f9060)
对象地址 EDateTimeEdit(0x7f9060)
```

一般来说，为了防止对象被释放以及保证对象的唯一性，应当将类的拷贝构造函数禁用，其构造函数与析构函数都应当被隐藏。此时为了让模板类能正常创建对象，应当在类中将模板类声明为友元类。

比如`Singleton`(该类派生自`QObject`)

```cpp
#include <QObject>

class Singleton : public QObject
{
  Q_OBJECT
    Singleton();
  ~Singleton()
  {
    qDebug() << QStringLiteral("释放Singleton对象，可以执行保存，清除等操作");
  }

  Singleton(const Singleton &) = delete ;
  Singleton& operator = (const Singleton &) = delete ;
  //声明为友元
  friend class ESingleton<Singleton>;
};
```

在`ESingleton`创建实例时，同时创建了一个`Internal`的内部类静态局部变量，该变量在程序运行结束时会释放，因此在`Internal`析构函数中添加了实例对象的释放操作，其目的是在程序结束时调用实例对象的析构函数（此时可以做一些保存等操作）。

```cpp
~Internal(){
  delete  ESingleton<T>::s_instance;
  ESingleton<T>::s_instance = nullptr;
}
```

