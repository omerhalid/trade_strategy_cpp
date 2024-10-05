#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //void on_analyzeButton_clicked(); // Handle button click
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    void populateStockList(); // Method to populate stock list
};

#endif // MAINWINDOW_H
