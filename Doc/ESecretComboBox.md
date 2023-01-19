# ESecretComboBox

密级控件，默认显示四级机密等级。

Header:`#include <ESecretComboBox>`

qmake:

```
INCLUDEPATH += $$PWD/../Core/
LIBS += -L$$PWD/../Core/EWidgets -lEWidgets
```

Inherits :`QComboBox`

### 描述

![image-20230119233825688](.\images\ESecretComboBox.png)

密级控件，默认显示四级机密等级。每个密级有密级值以及该密级值所对应的显示文本。默认情况下，对应关系为：

| 密级值 | 对应显示文本 |
| ------ | ------------ |
| 0      | 非密         |
| 1      | 秘密         |
| 2      | 机密         |
| 3      | 绝密         |

密级控件可以自定义添加下拉选项的密级数量，自定义显示文本，自定义不同密级的密级值。可以设置`setTopLevel()`来决定密级显示的最高等级。

下拉选项的显示顺序是根据密级值来升序显示的。

#### 如何设置自定义的密级下拉选项

例如需要在“非密”后面添加一个“内部”的密级，可以这样做:

```
		ESecretComboBox *editor = new ESecretComboBox;
    //清除原来的选项
    editor->clear();

    //自己创建一个一个表
    //密级值可以不连续，但是密级越高，值就应当越大;密级值与显示文本的对应关系由自己定义。
    QMap<int ,QString> levels{
        {0,"非密"},
        {1,"内部"},
        {2,"秘密"},
        {11,"机密"},
        {33,"绝密"}
    };

    editor->addItems(levels);
```

### 属性

###### m_levels:QMap<int ,QString>

密级值以及密级值所对应的显示文本。密级值最高可设置范围为0~255。超过此范围设置无效，不会显示到下拉选项中。默认情况下会添加一个默认的映射表如上表所示。

### 共有函数

###### ESecretComboBox(QWidget *parent = nullptr)

构造一个包含四个密级等级的下拉框。

######     int currentLevel() const;

返回当前选择的密级值,如果为空选项或者没有选择选项，则返回为-1。

###### int findLevel(int level) const

查找level密级值对应在下拉框的索引值，没有找到就返回-1。

###### int fromMaskString(const QString &mask) const

返回mask所对应的密级值,没有找到就返回-1。

一般情况下，可能会使用"jm"这样的字符串来替代“机密”这样文本。此处的"jm"即为`mask`，他返回`jm`所对应的密级值，如果`mask`没有在预设的映射表中存在，则密级值返回-1。

预设的映射表对应关系如下：

| MASK | 显示文本 | 默认对应的密级值 |
| ---- | -------- | ---------------- |
| fm   | 非密     | 0                |
| mm   | 秘密     | 1                |
| mj   | 机密     | 2                |
| jm   | 绝密     | 3                |

###### QString toString(int level) const

返回level密级值所对应的显示文本。例如默认情况下，mj值为0对应的文本为"非 密"。找不到返回""。

###### int toLevel(const QString &text) const

返回text对应密级的密级值，找不到返回-1。例如默认情况下，“非密”对应的密级值为0。

###### void setTopLevel(int topLevel)

设置mj的最高级别，超过此级别的mj选项不显示,允许设置0~255个密级，设置超过此范围的数按照边界值设定。

例如默认情况下有四个密级选项显示，如果将`topLevel()`设置为2，那么下拉框只会显示密级值小于等于2的所有选项，高于2的密级选项不显示。

###### int topLevel() const

返回允许显示的最高密级。默认值为255，表示显示所有的密级选项（密级值取值范围为0~255,因此可以全部选择显示）。

###### void addItem(int level,const QString &text)

添加密级选项。如果其中的密级值(level)已存在，那么将会由新的显示文本(text)替换。密级的显示顺序由密级值升序显示。

###### void addItems(const QMap<int ,QString> &items)

添加多个密级选项。如果其中的密级值已存在，那么将会由新的显示文本替换。密级的显示顺序由密级值升序显示。

###### void clear()

清空下拉选项。