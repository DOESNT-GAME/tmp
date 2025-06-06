#include "dbmanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

DatabaseManager* DatabaseManager::m_instance = nullptr;

DatabaseManager::DatabaseManager()
{
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName("project_data.db");

    if (!m_database.open()) {
        qCritical() << "Failed to open database:" << m_database.lastError().text();
        return;
    }

    qInfo() << "Database opened successfully";
    initializeDatabase();
}

DatabaseManager* DatabaseManager::instance()
{
    if (!m_instance) {
        m_instance = new DatabaseManager();
    }
    return m_instance;
}

QSqlDatabase DatabaseManager::database() const
{
    return m_database;
}

void DatabaseManager::initializeDatabase()
{
    QSqlQuery query(m_database);

    if (!query.exec("PRAGMA foreign_keys = ON")) {
        qWarning() << "Failed to enable foreign keys:" << query.lastError().text();
    }

    createTables();
}

void DatabaseManager::createTables()
{
    QSqlQuery query(m_database);

    const QStringList tables = {
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "login TEXT UNIQUE NOT NULL, "
        "password TEXT NOT NULL)",

        "CREATE TABLE IF NOT EXISTS messages ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "message TEXT, "
        "aes_key TEXT, "
        "sha_hash TEXT, "
        "image_path TEXT)"
    };

    for (const auto& tableSql : tables) {
        if (!query.exec(tableSql)) {
            qCritical() << "Failed to create table:" << query.lastError().text();
        }
    }
}
