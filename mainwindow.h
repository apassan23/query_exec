#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlQueryModel>
#include <QSqlError>
#include <QThread>
#include <QCloseEvent>
#include "databasehandler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    bool openDB(QString serverName,QString databaseName);
    void closeEvent(QCloseEvent *event);
    ~MainWindow();

signals:
    void execClicked(QSqlQueryModel*,QString);

private slots:
    void on_connectButton_clicked();
    void on_execButton_clicked();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QSqlQueryModel *sqlModel;
    DatabaseHandler *handler;
    QThread *connectionThread;
};

#endif // MAINWINDOW_H
