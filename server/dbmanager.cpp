#include "dbmanager.h"

DbManager::DbManager()
{
    QString dbPath = QDir::currentPath() + "/database.db";

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbPath);

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database failed";
    }
    else
    {
        qDebug() << "Database: connection ok";
        initDatabase();
    }
}

DbManager::~DbManager()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

void DbManager::initDatabase()
{
    QFile dbFile(m_db.databaseName());
    if (!dbFile.exists() || dbFile.size() == 0)
    {
        createTables();
    }
}

void DbManager::createTables()
{
    QSqlQuery query;

    if (!query.exec("CREATE TABLE users ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "username TEXT UNIQUE NOT NULL, "
                    "password TEXT NOT NULL"))
    {
        qDebug() << "Error creating users table:" << query.lastError().text();
    }
}

bool DbManager::userExists(const QString& username) const
{
    QSqlQuery query;
    query.prepare("SELECT username FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec())
    {
        qDebug() << "Error checking user existence:" << query.lastError().text();
        return false;
    }

    return query.next();
}

bool DbManager::addUser(const QString& username, const QString& password)
{
    if (userExists(username))
    {
        qDebug() << "User already exists:" << username;
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password); // + hash pass

    if (!query.exec())
    {
        qDebug() << "Error adding user:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DbManager::validateUser(const QString& username, const QString& password) const
{
    QSqlQuery query;
    query.prepare("SELECT username FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password); // + hash pass

    if (!query.exec())
    {
        qDebug() << "Error validating user:" << query.lastError().text();
        return false;
    }

    return query.next();
}
