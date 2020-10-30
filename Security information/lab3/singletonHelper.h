#ifndef SINGLETONHELPER_H
#define SINGLETONHELPER_H

#include <QtCore>
#include "user.h"


class SingletonHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant currentUser READ currentUser WRITE setCurrentUser NOTIFY currentUserChanged)

public:
    static SingletonHelper &instance();

    Q_INVOKABLE void logout();

    User& user();
    QVariant currentUser() const;
    void setCurrentUser(const QVariant &currentUser);

signals:
    void currentUserChanged();

private:
    explicit SingletonHelper(QObject *parent = nullptr);

private:
    User currentUser_;
};

#endif // SINGLETONHELPER_H
