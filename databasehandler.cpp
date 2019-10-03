#include "databasehandler.h"
#include <QSqlError>

DatabaseHandler::DatabaseHandler(QObject *parent) : QObject(parent)
{

}

void DatabaseHandler::setStatusBar(QStatusBar *statusBar){
    this->statusBar = statusBar;
}

bool DatabaseHandler::openDatabase(){
    db = QSqlDatabase::addDatabase("QODBC");
    QString connection = QString("DRIVER={SQL SERVER};SERVER=%1;DATABASE=%2;").arg(server).arg(database);
    db.connectOptions();
    db.setDatabaseName(connection);
    return db.open();
}

void DatabaseHandler::exec(QSqlQueryModel *model, const QString &query){
    if(!query.isEmpty()){
        model->setQuery(query);
    }
}

void DatabaseHandler::setServerName(const QString &serverName){
    this->server = serverName;
}

void DatabaseHandler::setDatabaseName(const QString &databaseName){
    this->database = databaseName;
}

void DatabaseHandler::close(){
    db.close();
}

void DatabaseHandler::connectDB(){
    if(statusBar != nullptr){
        if(openDatabase()){
            statusBar->showMessage("Connected!");
        }
        else {
            statusBar->showMessage(db.lastError().text());
        }
    }
}

void DatabaseHandler::execSql(QSqlQueryModel* model,QString query){
    model->setQuery(query);
}

void DatabaseHandler::disconnectDB(){
    db.close();
}

bool DatabaseHandler::isOpen(){
    return db.isOpen();
}
