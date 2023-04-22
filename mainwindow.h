#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSqlQueryModel *model;

    void loadData();
    void createTasksTable();
    void initData();
public slots:
    void addClicked();
    void editClicked();
    void deleteClicked();
};
#endif // MAINWINDOW_H
