#include "user.h"

User::User()
    : QObject()
{
}

User::~User()
{
}

User::User(const QString& name, const QString& password, const Role& role,
    bool blocked, bool passwordLimit)
    : QObject()
    , login_(name)
    , password_(password)
    , role_(role)
    , blocked_(blocked)
    , passwordLimit_(passwordLimit)
{
}

User::User(const User& other)
    : QObject()
    , login_(other.login_)
    , password_(other.password_)
    , role_(other.role_)
    , blocked_(other.blocked_)
    , passwordLimit_(other.passwordLimit_)
{
}

User& User::operator=(const User& other)
{
    this->clone(other);
    return *this;
}

void User::clone(const User& other)
{
    login_ = other.login_;
    password_ = other.password_;
    role_ = other.role_;
    blocked_ = other.blocked_;
    passwordLimit_ = other.passwordLimit_;
}

void User::swap(User& other)
{
    login_.swap(other.login_);
    password_.swap(other.password_);
    qSwap(role_, other.role_);
    qSwap(blocked_, other.blocked_);
    qSwap(passwordLimit_, other.passwordLimit_);
}

User User::fromJson(const QJsonObject& obj)
{
    auto login = obj.value("login").toString();
    auto password = obj.value("password").toString();
    auto role = static_cast<Role>(obj.value("role").toInt(1));
    auto blocked = obj.value("blocked").toBool();
    auto passwordLimit = obj.value("password_limit").toBool(true);

    return User(login, password, role, blocked, passwordLimit);
}

QJsonObject User::toJson() const
{
    return {
        { "login", login_ },
        { "password", password_ },
        { "role", static_cast<int>(role_) },
        { "blocked", blocked_ },
        { "password_limit", passwordLimit_ }
    };
}

User User::fromString(const std::string &str)
{

}

std::string User::toString() const
{
    QStringList list;
    list << login_
         << password_
         << QString::number(static_cast<int>(role_))
         << QString::number(static_cast<int>(blocked_))
         <<QString::number(static_cast<int>(passwordLimit_));

    return list.join(",").toStdString();
}

bool User::isAdmin() const
{
    return role_ == Role::AdminUser;
}

bool User::isNull() const
{
    return login_.isEmpty();
}

bool User::isFirstLogin() const
{
    return password_.isEmpty() || !isPasswordValid(password_);
}

bool User::login(const QString& login, const QString& password) const
{
    return login_ == login && password_ == password;
}

QString User::changePassword(const QString& oldPassword, const QString& newPassword)
{
    if (oldPassword != password_) {
        return "Неверный старый пароль";
    }

    if (!isPasswordValid(newPassword)) {
        return "Пароль не соотвествует требованием";
    }

    password_ = newPassword;

    return "";
}

QString User::userLogin() const
{
    return login_;
}

void User::setUserLogin(const QString& login)
{
    login_ = login;
}

bool User::isBlocked() const
{
    return blocked_;
}

void User::setBlocked(bool blocked)
{
    blocked_ = blocked;
}

bool User::isPasswordLimit() const
{
    return passwordLimit_;
}

void User::setPasswordLimit(bool passwordLimit)
{
    passwordLimit_ = passwordLimit;
}

bool User::isPasswordValid(const QString& password) const
{
    if (!passwordLimit_) {
        return true;
    }

    QRegularExpression digits("\\d");
    QRegularExpression operations("[+-/*]");

    return password.contains(digits) && password.contains(operations);
}
