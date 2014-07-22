/**********************************************************************
** Copyright (C) 2014 vell001
** Author: VellBibi
** Description:
**
**********************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QDebug>
#include <QHash>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QCloseEvent>
#include <QMessageBox>
#include <QTableWidget>
#include "service/BroadcastService.h"
#include "service/ChatService.h"
#include "service/UserService.h"
#include "model/User.h"
#include "ChatForm.h"
#include "model/ChatRecord.h"
#include "service/ChatRecordService.h"
#include "service/IconService.h"
#include "MessageDialog.h"
#include "model/FileReceiver.h"
#include "model/FileSender.h"
#include <QFile>
#include <QMenu>
#include "SetShareFilesDialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static MainWindow *getMainWindow();
    QHash<QUuid, ChatForm *> *getChatForms();

public slots:
    void doubleClickedContents(QModelIndex);
    void doubleClickedRecentContents(QModelIndex);
    void broadcastReceived(QHostAddress senderIp, quint16 senderPort, ChatMessage message);
    void chatReceiveSuccess(QHostAddress senderIp, quint16 senderPort, ChatMessage message);
    void fMsgReceiveSuccess(QHostAddress senderIp, quint16 senderPort, ChatMessage message);

protected:
    virtual void closeEvent ( QCloseEvent * event );
private slots:
    void activated ( QSystemTrayIcon::ActivationReason reason );
    void chatFormClosed(QUuid);
    void openChatForm(const QUuid &receiverUuid);
    void on_searchEdit_textChanged(const QString &arg1);
    void doubleClickedSearchResult(QModelIndex);

    void on_contentsTreeWidget_customContextMenuRequested(const QPoint &pos);

    void on_setShareFilesButton_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;
    BroadcastService *mBroadcastService;
    ChatService *mChatService;
    IconService *mIconService;
    User *myself;
    void updateContentsTreeWidget();


    QHash<QUuid, User> *mFriends;
    QHash<QUuid, ChatForm *> *mChatForms;
    QList<ChatRecord> *mChatRecords;

    /* system tray */
    void createActions();
    void createTrayIcon();
    QIcon logoIcon;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    QListWidget *searchResultWidget;

    void updateRecentFriendsListWidget();
};

#endif // MAINWINDOW_H
