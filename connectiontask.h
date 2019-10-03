#ifndef CONNECTIONTASK_H
#define CONNECTIONTASK_H

#include <QObject>
#include <QStatusBar>
#include <QSqlDatabase>
#include <QSqlError>

class ConnectionTask : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionTask(QSqlDatabase *db,QStatusBar *statusBar,QObject *parent = nullptr);
    void setServerName(const QString &serverName);
    void setDatabaseName(const QString &databaseName);

signals:
    void finished();
public slots:
    void establishConnection();
private:
    QStatusBar *statusBar;
    QSqlDatabase *db;
    QString serverName;
    QString databaseName;
};

#endif // CONNECTIONTASK_H
