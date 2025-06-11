#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QObject>


class DatabaseManager
{
public:
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;


    static DatabaseManager* instance();


    QSqlDatabase database() const;
    static QString hashPassword(const QString& password);

private:
    DatabaseManager();
    ~DatabaseManager() = default;

    void initializeDatabase();
    void createTables();

    static DatabaseManager* m_instance;
    QSqlDatabase m_database;
};

#endif // DATABASEMANAGER_H
