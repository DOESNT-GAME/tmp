#include "dbmanager.h"

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

DatabaseManager::DatabaseManager()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(":memory:");
    m_db.open();
}

QSqlDatabase DatabaseManager::database() const
{
    return m_db;
}
