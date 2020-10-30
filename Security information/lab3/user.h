#ifndef USER_H
#define USER_H

#include <QtCore>


class User : public QObject
{
    Q_GADGET

public:
    /**
     * Перечисление с ролями пользователей.
     */
    enum class Role {
        AdminUser = 0,      // администратор
        StandardUser = 1    // обычный пользователь
    };

    User();
    ~User();
    User(const QString &name, const QString &password = "", const Role &role = Role::StandardUser,
         bool blocked = false, bool passwordLimit = true);
    User(const User& other);

    User &operator=(const User& other);

    void clone(const User &other);
    void swap(User &other);

    static User fromJson(const QJsonObject &obj);
    QJsonObject toJson() const;

    static User fromString(const std::string &str);
    std::string toString() const;

    Q_INVOKABLE bool isAdmin() const;
    Q_INVOKABLE bool isNull() const;
    Q_INVOKABLE bool isFirstLogin() const;
    bool login(const QString &login, const QString &password) const;
    QString changePassword(const QString &oldPassword, const QString &newPassword);

    Q_INVOKABLE QString userLogin() const;
    void setUserLogin(const QString &login);

    Q_INVOKABLE bool isBlocked() const;
    void setBlocked(bool blocked);

    Q_INVOKABLE bool isPasswordLimit() const;
    void setPasswordLimit(bool passwordLimit);

private:
    bool isPasswordValid(const QString &password) const;

private:
    QString login_;
    QString password_;
    Role role_;
    bool blocked_;
    bool passwordLimit_;
};

Q_DECLARE_METATYPE(User)

#endif // USER_H
