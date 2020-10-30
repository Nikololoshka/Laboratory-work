#include "userRepository.h"
#include "singletonHelper.h"

UserRepository::UserRepository(QObject *parent)
    : QObject(parent)
{
}

void UserRepository::create(const QString &login, const QString &password)
{
    auto& helper = SingletonHelper::instance();
    if (!helper.user().isAdmin()) {
        emit createError("Текущий пользователь не имеет прав на создание учетных записей");
        return;
    }

    if (login.isEmpty()) {
        emit createError("Логин пользователя имеет нулевую длину");
        return;
    }

    auto result = database_.createUser(login, password);
    if (result == Database::TransactionStatus::EXISTED) {
        emit createError("Пользователь с таким именем уже существует");
        return;
    }

    emit createSuccessfully();
}

Database UserRepository::database_ = Database();

void UserRepository::login(const QString &login, const QString &password)
{
    if (login.isEmpty()) {
        emit loginError("Пустое поле с логином");
        return;
    }

    auto user = database_.find(login, password);
    if (user.isNull()) {
        emit loginError("Неправильный логин или пароль. ");
        return;
    }
    if (user.isBlocked()) {
        emit loginError("Учетная запись заблокирована. ");
        return;
    }

    emit loginSuccessfully(QVariant::fromValue(user));
}

void UserRepository::updateCurrentUserPassword(const QString &oldPassword, const QString &newPassword,
                                               const QString &confirmNewPassword)
{
    auto& helper = SingletonHelper::instance();
    auto& currentUser = helper.user();

    if (currentUser.isNull()) {
        return;
    }

    if (newPassword != confirmNewPassword) {
        emit changePasswordError("Пароли не совпадают");
        return;
    }

    if (newPassword.isEmpty() || confirmNewPassword.isEmpty()) {
        emit changePasswordError("Не заполнены поля для смены пароля");
        return;
    }

    auto result = currentUser.changePassword(oldPassword, newPassword);
    if (result.isEmpty()) {
        database_.updateUser(currentUser.userLogin(), currentUser);
        emit changePasswordSuccessfully();
        return;
    }

    emit changePasswordError(result);
}

void UserRepository::firstLogin(const QString &oldPassword,const QString &newPassword, const QString &confirmNewPassword)
{
    auto& helper = SingletonHelper::instance();
    auto& currentUser = helper.user();

    if (currentUser.isNull()) {
        return;
    }

    if (newPassword != confirmNewPassword) {
        emit changePasswordError("Пароли не совпадают");
        return;
    }

    if (newPassword.isEmpty() || confirmNewPassword.isEmpty()) {
        emit changePasswordError("Не заполнены поля для смены пароля");
        return;
    }

    auto result = currentUser.changePassword(oldPassword, newPassword);
    if (result.isEmpty()) {
        database_.updateUser(currentUser.userLogin(), currentUser);
        emit changePasswordSuccessfully();
        return;
    }

    emit changePasswordError(result);
}

void UserRepository::updateUser(const QString &userLogin, const QString &newLogin, bool blocked, bool limit)
{
    auto user = database_.get(userLogin);
    user.setUserLogin(newLogin);
    user.setBlocked(blocked);
    user.setPasswordLimit(limit);

    auto result = database_.updateUser(userLogin, user);
    if (result == Database::TransactionStatus::EXISTED) {
        emit userUpdatedError("Пользователь с таким именем уже существует");
        return;
    }

    emit userUpdatedSuccessfully();
}

void UserRepository::removeUser(const QString &userLogin)
{
    database_.removeUser(userLogin);
    emit userRemoved();
}

QVariant UserRepository::user(const QString &userLogin)
{
    return QVariant::fromValue(database_.get(userLogin));
}

QVariantList UserRepository::users()
{
    QVariantList list;
    for (const auto& user : database_.allUsers()) {
        if (!user.isAdmin()) {
            list.append(QVariant::fromValue(user));
        }
    }
    return list;
}
