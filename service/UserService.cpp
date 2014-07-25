#include "UserService.h"

UserService::UserService(QObject *parent) :
    QObject(parent),
    mStorageService(StorageService::getService())
{
    myself = mStorageService->getMyself();
    myself->setStatus(User::Online);
}

UserService *UserService::getService(){
    static UserService Service;
    return &Service;
}

User *UserService::getMyself(){
    return myself;
}

void UserService::saveMyself(){
    mStorageService->storeMyself(myself);
    emit myselfInfoChanged(myself);
}

QHash<QUuid, User> *UserService::getFriends(){
    return &mFriends;
}

QHash<QString, User> *UserService::getRecentFriends(){
    return &mRecentFriends;
}

void UserService::insertRecentFriend(const User &user){
    mRecentFriends[QDateTime::currentDateTime().toString()] = user;
}

UserService::~UserService(){
}
