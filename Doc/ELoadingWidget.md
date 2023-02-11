# ELoadingWidget

该控件是一个加载（刷新）对话框。用于在加载数据时限制用户的输入。

Header:`#include <ELoadingWidget>`

Inherits :`QLineEdit`

## 描述

![image-20230209010722092](images/ELoadingWidget.png)

在需要加载窗口时，创建`ELoadingWidget`对象，此时会在窗口顶端弹出加载窗口。此窗口会屏蔽用户输入操作，但是不会阻塞后续代码的执行。例如:

```cpp
do{
  //此处弹出对话框，期间不影响后续代码执行，但是不响应界面操作
  ELoadingWidget w(this);//("111111111111111",10 * 1000,this);
  //可以重新指定加载图标
  //w.setFileName("C:\\Users\\zl\\Desktop\\loading2.gif");
  
  if(...)
  {
    dosomething;
    break;
  }
  
  if(....)
  {
    doelasething;
    break;
  }
  
    if(....)
  {
    doelasething;
    break;
  }
  
  dothing;

}while (false);

//加载框在跳出循环时不必手动隐藏或者释放，加载窗口自动关闭
```

##  公有函数

###### ELoadingWidget(const QString &text ,qint32 delayMillisecond ,QWidget *parent = nullptr)

指定加载窗口的显示文本（text,在加载图标下显示），图标延时时间（delayMillisecond,毫秒，定时若干时间后图片加载显示）以及指定父对象。

加载窗口会铺满整个窗口，限定用户的输入点击操作。

###### ELoadingWidget(QWidget *parent = nullptr)

指定父对象，如果没有指定父对象，那么加载图标会铺满整个桌面。

加载窗口会铺满整个窗口，限定用户的输入点击操作。

###### void setText(const QString &text)

设置加载图标下的显示文本。

###### void setFileName(const QString &fileName)

可以设置加载的图标。