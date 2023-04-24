#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editrecord.h"
#include <QtSql>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QSqlQueryModel(this);
    sfModel = new QSortFilterProxyModel(this);

    loadData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadData()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("QtDatabase.sqlite");
    db.setUserName("user1");
    db.setHostName("host1");
    db.setPassword("pass1");
    if(!db.open()){
        QMessageBox::critical(0,"Ошибка",db.lastError().text(),QMessageBox::Ok);
        return;
    }

    QSqlQuery query;
    QString sql;

    sql = "select id, name, done from tasks";

    if(!query.exec(sql)){
        createTasksTable();
        query.exec(sql);
    }

    if(!query.first()){
        initData();
    }

    model->setQuery("select id, name, done from tasks");
    model->setHeaderData(0, Qt::Horizontal,"Код");
    model->setHeaderData(1, Qt::Horizontal,"Наименование");
    model->setHeaderData(2, Qt::Horizontal,"Выполнено");

    if(model->lastError().isValid()){
        qDebug() << model->lastError();
    }

    sfModel->setSourceModel(model);
    ui->view->setModel(sfModel);
}

void MainWindow::createTasksTable()
{
    QSqlQuery query;
    QString sql = "create table tasks (id integer primary key not null, name varchar(100), done integer);";

    if(!query.exec(sql)){
        QMessageBox::critical(0,"Ошибка","Не удалось создать таблицу tasks!",QMessageBox::Ok);
    }
}

void MainWindow::initData()
{
    QSqlQuery query;
    query.prepare("insert into tasks (id,name,done) values(:id,:name,:done);");

    query.bindValue(":id",1);
    query.bindValue(":name","Задача1");
    query.bindValue(":done","0");

    if(!query.exec())
    {
        QMessageBox::critical(0,"Ошибка","Не удалось добавить запись в таблицу tasks!",QMessageBox::Ok);
    }

    query.bindValue(":id",2);
    query.bindValue(":name","Задача2");
    query.bindValue(":done","0");

    if(!query.exec())
    {
        QMessageBox::critical(0,"Ошибка","Не удалось добавить запись в таблицу tasks!",QMessageBox::Ok);
    }
}

void MainWindow::addClicked()
{
    EditData data;

    if(showEditForm(&data))
    {
        QSqlQuery query;
        QString sql = QString("insert into tasks values(%1,'%2',%3);").arg(data.id).arg(data.name).arg(data.done);

        if(!query.exec(sql))
        {
            QMessageBox::critical(0,"Ошибка","Не удалось добавить запись в таблицу tasks!",QMessageBox::Ok);
            return;
        }
        loadData();
    }
}

void MainWindow::editClicked()
{
    QItemSelectionModel *selection = ui->view->selectionModel();
    EditData data;

    data.id = selection->selectedRows(0).value(0).data().toInt();
    data.name = selection->selectedRows(1).value(0).data().toString();
    data.done = selection->selectedRows(2).value(0).data().toBool();

    if(showEditForm(&data))
    {
        QSqlQuery query;
        QString sql = QString("update tasks set id=%1, name='%2', done=%3 where id=%1;").arg(data.id).arg(data.name).arg(data.done);

        if(!query.exec(sql))
        {
            QMessageBox::critical(0,"Ошибка","Не удалось обновить запись в таблице tasks!",QMessageBox::Ok);
            return;
        }
        loadData();
    }
}

void MainWindow::deleteClicked()
{
    QItemSelectionModel *selection = ui->view->selectionModel();

    qint32 id = selection->selectedRows(0).value(0).data().toInt();

    if(QMessageBox::question(0,"Подтверждение удаления","Вы действительно хотите удалить запись?",
                             QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        QSqlQuery query;
        QString sql = QString("delete from tasks where id=%1;").arg(id);

        if(!query.exec(sql))
        {
            QMessageBox::critical(0,"Ошибка","Не удалось добавить запись в таблицу tasks!",QMessageBox::Ok);
            return;
        }
        loadData();
    }
}
