#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connectionThread = new QThread(this);
    handler = new DatabaseHandler();
    handler->setStatusBar(ui->statusBar);
    handler->moveToThread(connectionThread);


    sqlModel = new QSqlQueryModel(this);

    connect(connectionThread,SIGNAL(started()),handler,SLOT(connectDB()));

    connect(this,SIGNAL(execClicked(QSqlQueryModel*,QString)),handler,SLOT(execSql(QSqlQueryModel*,QString)));

}

void MainWindow::closeEvent(QCloseEvent *event){
    handler->close();
    if(connectionThread->isRunning()){
        connectionThread->quit();
    }
    event->accept();
}
MainWindow::~MainWindow()
{
    delete handler;
    delete connectionThread;
    delete sqlModel;
    delete ui;
}


void MainWindow::on_execButton_clicked()
{
    QString query = ui->lineEdit_3->text();
    emit execClicked(sqlModel,query);
    ui->tableView->setModel(sqlModel);
}

void MainWindow::on_connectButton_clicked()
{
    handler->setServerName(ui->lineEdit->text());
    handler->setDatabaseName(ui->lineEdit_2->text());
    connectionThread->start();
}


void MainWindow::on_pushButton_clicked()
{
    QString msg;
    int timeout = 2000;
    if(connectionThread->isRunning()){
        handler->close();
        connectionThread->quit();
        sqlModel->clear();
        msg = "Connection Closed.";
    }

    else {
        msg = "No Connection Opened.";
    }
    ui->statusBar->showMessage(msg,timeout);
}
