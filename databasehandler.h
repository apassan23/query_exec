#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QStatusBar>

class DatabaseHandler : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseHandler(QObject *parent = nullptr);
    bool openDatabase();
    void setServerName(const QString &serverName);
    void setDatabaseName(const QString &databaseName);
    void exec(QSqlQueryModel *model,const QString &query);
    void setStatusBar(QStatusBar *statusBar = nullptr);
    bool isOpen();
    void close();

signals:

public slots:
    void connectDB();
    void disconnectDB();
    void execSql(QSqlQueryModel*,QString);

private:
    QSqlDatabase db;
    QString server;
    QString database;
    QStatusBar *statusBar;

};

#endif // DATABASEHANDLER_H
