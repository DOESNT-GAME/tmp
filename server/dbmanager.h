#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QDir>

class DbManager
{
public:
    // Статический метод для получения единственного экземпляр
    static DbManager& instance()
    {
        static DbManager instance;
        return instance;
    }

    bool userExists(const QString& username) const;
    bool addUser(const QString& username, const QString& password);
    bool validateUser(const QString& username, const QString& password) const;

private:
    DbManager();
    ~DbManager();
    DbManager(const DbManager&) = delete;
    DbManager& operator=(const DbManager&) = delete;

    QSqlDatabase m_db;
    void initDatabase();
    void createTables();
};

#endif // DBMANAGER_H
