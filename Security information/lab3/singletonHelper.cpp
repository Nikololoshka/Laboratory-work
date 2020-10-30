#include "singletonHelper.h"

SingletonHelper::SingletonHelper(QObject *parent)
    : QObject(parent)
{

}

SingletonHelper &SingletonHelper::instance()
{
    static SingletonHelper helper;
    return helper;
}

void SingletonHelper::logout()
{
    User empty;
    currentUser_.swap(empty);

    emit currentUserChanged();
}

User &SingletonHelper::user()
{
    return currentUser_;
}

QVariant SingletonHelper::currentUser() const
{
    return QVariant::fromValue(currentUser_);
}

void SingletonHelper::setCurrentUser(const QVariant &currentUser)
{
    auto user = currentUser.value<User>();
    currentUser_.swap(user);

    emit currentUserChanged();
}
