#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEventLoop>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ELoadingWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void noBlockingTest();
private:
    Ui::MainWindow *ui;
    ELoadingWidget *load;
    QWidget *w2;
    QEventLoop m_loop;
};
#endif // MAINWINDOW_H
