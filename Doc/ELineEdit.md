# ELineEdit

扩展QLineEdit控件，默认显示查找按钮与清除按钮，默认对输入的文本前后空白字符清除。

Header:`#include <ELineEdit>`

qmake:

```
INCLUDEPATH += $$PWD/../Core/
LIBS += -L$$PWD/../Core/EWidgets -lEWidgets
```

Inherits :`QLineEdit`

### 描述

![image-20230119133723874](.\images\ELineEdit.png)

获取设置文本时，会自动把文本内容前后的空白字符清空。ElineEdit默认显示搜索按钮，当控件内有内容时，显示清除按钮。ELineEdit默认添加了一个`validator`,使本输入框在默认情况下只能输入数字字符以及下划线（如果要取消该设置，使用setValidator(nullptr)）。本控件默认情况下的输入长度为20（可以使用setMaxLength()来重新指定可输入长度）。

### 信号    

###### void searchPressed(const QString &text)

当查找按钮被点击或者回车键被按下时触发本信号。

###### void textChanged(const QString &text)

文本发生改变时触发本信号

###### void textEdited(const QString &text)

文本发生改变时触发本信号。

### 公有函数

###### ELineEdit(QWidget *parent = nullptr)

###### ELineEdit(const QString &contents, QWidget *parent = nullptr)

构造一个包含`text`文本内容的行编辑控件。该控件默认设置的文本内容会自动去除其前后的空白字符。

最长的文本长度为32767个字符。

###### void setDecoration(bool enabled = true)

设置是否修饰文本，当enabled为true,无论时`setText()`或是`text()`设置或返回的内容，其前后的空白字符会被清除。默认为`true`。

目前只针对`searchPressed()、textChanged()、textEdited()、setText()以及text()`这几个函数设置的文本会作处理（清除前后的空白字符）。

###### bool isDecoration() const

当前是否处于文本修饰状态。

###### void setClearButtonEnabled(bool enable)

设置清空按钮是否显示。默认显示。

###### bool isClearButtonEnabled() const

返回清空按钮是否处于显示状态。

###### void setSearchButtonEnabled(bool enable)

设置查询按钮是否显示。默认显示。

###### bool isSearchButtonEnabled() const

返回查询按钮是否处于显示状态。

