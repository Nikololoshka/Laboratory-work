#include "database.h"
#include <cryptoWrapper.h>


Database::Database()
{

}

Database::~Database()
{
    if (!key_.isEmpty()) {
        saveDatabase();
    }
}

void Database::setKey(const QString &key)
{
    key_ = key;

    if (!QFile::exists(DATABASE_PATH)) {
        initDatabase();
        saveDatabase();
    } else {
        loadDatabase();
    }
}

User Database::get(const QString &userLogin)
{
    auto it = users_.find(userLogin);
    if (it == users_.end()) {
        throw std::logic_error("Не удалось найти пользователя: " + userLogin.toStdString());
    }

    return it.value();
}

User Database::find(const QString &login, const QString &password)
{
    for (const auto& user : users_) {
        if (user.login(login, password)) {
            return user;
        }
    }

    return User();
}

Database::TransactionStatus Database::createUser(const QString &login, const QString &password)
{
    if (users_.contains(login)) {
        return TransactionStatus::EXISTED;
    }

    users_[login] = User(login, password);
    saveDatabase();

    return TransactionStatus::CREATED;
}

Database::TransactionStatus Database::updateUser(const QString &userLogin, const User &user)
{
    if (userLogin != user.userLogin()) {
        if(users_.contains(user.userLogin())) {
            return TransactionStatus::EXISTED;
        }

        users_.remove(userLogin);
    }

    users_[user.userLogin()] = user;
    saveDatabase();

    return TransactionStatus::UPDATED;
}

Database::TransactionStatus Database::removeUser(const QString &userLogin)
{
    users_.remove(userLogin);
    saveDatabase();

    return TransactionStatus::REMOVED;
}

QList<User> Database::allUsers() const
{
    return users_.values();
}

bool Database::isValid() const
{
    return !users_.isEmpty();
}

void Database::initDatabase()
{
    QFile database(DATABASE_PATH);
    if (!database.open(QIODevice::WriteOnly)) {
        throw std::runtime_error("Не удалось открыть БД");
    }

    User admin("admin", "", User::Role::AdminUser, false, false);
    users_[admin.userLogin()] = admin;
}

void Database::loadDatabase()
{
    QFile database(DATABASE_PATH);
    if (!database.open(QIODevice::ReadOnly)) {
        throw std::runtime_error("Не удалось открыть БД");
    }


    auto json = database.readAll();
    json = CryptoWrapper(key_).decrypt(json).toUtf8();

    qDebug() << json;

    auto doc = QJsonDocument::fromJson(json);
    auto users = doc.array();

    for (int i = 0; i < users.size(); ++i) {
        auto jsonUser = users[i].toObject();
        auto user = User::fromJson(jsonUser);
        users_.insert(user.userLogin(), user);
    }

    if (!users_.contains("admin")) {
        key_ = "";
        throw std::runtime_error("not valid key");
    }
}

void Database::saveDatabase()
{
    QFile database(DATABASE_PATH);
    if (!database.open(QIODevice::WriteOnly)) {
        throw std::runtime_error("Не удалось открыть БД");
    }

    QJsonArray jsonUsers;
    for (const auto& user : users_) {
        jsonUsers.append(user.toJson());
    }

    QJsonDocument doc(jsonUsers);
    auto json = doc.toJson(QJsonDocument::Compact);
    json = CryptoWrapper(key_).encrypt(json).toUtf8();

    database.write(json);
}
