#include "databasemanager.h"
#include <QDebug>

DataBase* DataBase::p_instance = nullptr;
DatabaseDestroyer DataBase::destroyer;

DataBase::DataBase() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Database.db");
    if (!db.open()) {
        qDebug() << "Error: failed to open database";
    }
}

bool DataBase::createTable() {
    QSqlQuery query(db);
    bool success = query.exec("create table if not exists users(id integer primary key not null, "
                              "login text not null unique, password text not null, email text not null unique, "
                              "stat integer default 0, sockid integer not null);");

    if (!success) {
        qDebug() << "Create table error:" << query.lastError().text();
    }
    return success;
}

DataBase::~DataBase() {
    db.close();
}

DataBase& DataBase::getInstance() {
    if(!p_instance) {
        p_instance = new DataBase();
        destroyer.initialize(p_instance);
        p_instance->createTable();
    }
    return *p_instance;
}

QSqlDatabase& DataBase::getDatabase() {
    return db;
}

DatabaseDestroyer::~DatabaseDestroyer() {
    delete p_instance;
}

void DatabaseDestroyer::initialize(DataBase *p) {
    p_instance = p;
}

QStringList DataBase::queryToDatabase(QStringList src) {
    QSqlQuery query(db);
    QStringList res;

    if (src.isEmpty()) {
        res.append("error");
        res.append("Empty query");
        return res;
    }

    query.prepare(src[0]);

    // Bind values if provided
    for (int i = 1; i < src.size(); i += 2) {
        if (i + 1 < src.size()) {
            query.bindValue(src[i], src[i+1]);
        }
    }

    if (src[0].contains("SELECT", Qt::CaseInsensitive)) {
        if (query.exec()) {
            if (query.next()) {
                res.append("found");
                QSqlRecord record = query.record();
                for (int i = 0; i < record.count(); ++i) {
                    res.append(record.value(i).toString());
                }
            } else {
                res.append("not_found");
            }
        } else {
            res.append("error");
            res.append(query.lastError().text());
        }
    } else {
        if (query.exec()) {
            res.append("ok");
        } else {
            res.append("error");
            res.append(query.lastError().text());
        }
    }

    return res;
}
