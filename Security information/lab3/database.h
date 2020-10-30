#ifndef DATABASE_H
#define DATABASE_H

#include <QtCore>
#include "user.h"


class Database
{
public:
    enum class TransactionStatus {
        CREATED,
        EXISTED,
        UPDATED,
        REMOVED,
        ERROR
    };

    Database();
    ~Database();

    void setKey(const QString &key);

    User get(const QString &userLogin);
    User find(const QString &login, const QString &password);
    TransactionStatus createUser(const QString& login, const QString &password);
    TransactionStatus updateUser(const QString &userLogin, const User& user);
    TransactionStatus removeUser(const QString& userLogin);
    QList<User> allUsers() const;
    bool isValid() const;

private:
    void initDatabase();
    void loadDatabase();
    void saveDatabase();

    const QString DATABASE_PATH = "database.txt";

private:
    QMap<QString, User> users_;
    QString key_;
};

#endif // DATABASE_H
