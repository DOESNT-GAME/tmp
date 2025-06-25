#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>

class DatabaseManager
{
public:
    static DatabaseManager& instance();
    QSqlDatabase database() const;

private:
    DatabaseManager();
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
