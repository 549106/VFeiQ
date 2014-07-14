#ifndef ICONSERVICE_H
#define ICONSERVICE_H

#include <QObject>
#include <QUuid>
#include <QIcon>

class IconService : public QObject
{
    Q_OBJECT
public:
    static IconService *getService();
    QIcon getIconByUuid(const QUuid &uuid = QUuid());
signals:

public slots:
private:
    explicit IconService(QObject *parent = 0);
};

#endif // ICONSERVICE_H
