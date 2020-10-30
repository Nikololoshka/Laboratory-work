#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <QtCore>
#include "user.h"
#include "database.h"


class UserRepository : public QObject
{
    Q_OBJECT

public:
    explicit UserRepository(QObject *parent = nullptr);

    Q_INVOKABLE void create(const QString &login, const QString &password = "");
    Q_INVOKABLE void login(const QString &login, const QString &password);
    Q_INVOKABLE void updateCurrentUserPassword(const QString &oldPassword,
                                               const QString &newPassword,
                                               const QString &confirmNewPassword);
    Q_INVOKABLE void setPassphrase(const QString& passphrase);
    Q_INVOKABLE void firstLogin(const QString &oldPassword,
                                const QString &newPassword,
                                const QString &confirmNewPassword);
    Q_INVOKABLE void updateUser(const QString &userLogin, const QString &newLogin, bool blocked, bool limit);
    Q_INVOKABLE void removeUser(const QString &userLogin);
    Q_INVOKABLE QVariant user(const QString &userLogin);
    Q_INVOKABLE QVariantList users();

signals:
    void passphraseValid(bool valid);

    void loginSuccessfully(const QVariant &user);
    void loginError(const QString &errorMessage);

    void createSuccessfully();
    void createError(const QString &errorMessage);

    void changePasswordSuccessfully();
    void changePasswordError(const QString &errorMessage);

    void userRemoved();
    void userUpdatedSuccessfully();
    void userUpdatedError(const QString &errorMessage);

private:
    static Database database_;
};

#endif // USERREPOSITORY_H
