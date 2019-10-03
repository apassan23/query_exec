#include "connectiontask.h"


ConnectionTask::ConnectionTask(QSqlDatabase *db,QStatusBar *statusBar,QObject *parent) : QObject(parent)
{
    this->statusBar = statusBar;
    this->db = db;
}

void ConnectionTask::establishConnection(){
    *db = QSqlDatabase::addDatabase("QODBC");
    QString connection = QString("DRIVER={SQL SERVER};SERVER=%1;DATABASE=%2;").arg(serverName).arg(databaseName);
    db->connectOptions();
    db->setDatabaseName(connection);

    if(db->open()){
        statusBar->showMessage("Connection Opened!");
    }
    else {
        statusBar->showMessage(db->lastError().text());
    }
    emit finished();
}

void ConnectionTask::setServerName(const QString &serverName){
    this->serverName = serverName;
}

void ConnectionTask::setDatabaseName(const QString &databaseName){
    this->databaseName = databaseName;
}
