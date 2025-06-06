#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QObject>

/**
 * @brief Manages SQLite database connection and schema initialization
 *
 * Implements Singleton pattern to provide single database connection
 */
class DatabaseManager
{
public:
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    /**
     * @brief Get the singleton instance
     */
    static DatabaseManager* instance();

    /**
     * @brief Get the database connection
     */
    QSqlDatabase database() const;

private:
    DatabaseManager();
    ~DatabaseManager() = default;

    void initializeDatabase();
    void createTables();

    static DatabaseManager* m_instance;
    QSqlDatabase m_database;
};

#endif // DATABASEMANAGER_H
