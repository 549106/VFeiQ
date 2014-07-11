#include "UdpService.h"

UdpService::UdpService(QObject *parent) :
    QObject(parent),
    chatPort(9514)
{
    listen();
}
UdpService::UdpService(quint16 chatPort, QObject *parent) :
    QObject(parent),
    chatPort(chatPort)
{
    listen();
}

void UdpService::listen(){
    mUdpSocket = new QUdpSocket(this);
    mUdpSocket->bind(QHostAddress::Any, chatPort);
    connect(mUdpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

UdpService::~UdpService(){
    mUdpSocket->close();
    delete mUdpSocket;
}

void UdpService::send(ChatMessage &message, const QHostAddress &receiverIp){
    QByteArray data;
    data.append(message.toString());
    mUdpSocket->writeDatagram(data, receiverIp, chatPort);
    mUdpSocket->flush();
}

void UdpService::readyRead (){
    QByteArray buffer;
    buffer.resize(mUdpSocket->pendingDatagramSize());

    QHostAddress senderIp;
    quint16 senderPort;
    mUdpSocket->readDatagram(buffer.data(), buffer.size(), &senderIp, &senderPort);

    qDebug() << "message from : " << senderIp.toString();
    qDebug() << "message port : " << senderPort;
    qDebug() << "message : " << buffer;

    ChatMessage message(buffer);

//    connect(message, SIGNAL(parseError(QString)), this, SIGNAL(receiveError(QString)));

    if(message.getType() == ChatMessage::Request) { // request message
        ChatMessage respMes(message.getUuid(), ChatMessage::Response, SettingUtil::getUtil()->getSender()->getUuid(), "accepted");
        send(respMes, senderIp);
        emit receiveSuccess(senderIp, senderPort, message);
    } else if (message.getType() == ChatMessage::Response) { // response message
        if(message.getContent().trimmed().toLower() == "accepted") {
            emit sendSuccess(message.getUuid());
        } else {
            emit sendError(message.getUuid(), QString("unaccepted"));
        }
    }
}
