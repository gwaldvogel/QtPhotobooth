#include "CloudConnector.h"
#include <config.h>

#include <QFile>
#include <QHttpMultiPart>
#include <QNetworkReply>

CloudConnector::CloudConnector(QObject *parent)
    : QObject(parent)
    , m_pManager(new QNetworkAccessManager(this))
{
    m_baseUrl = CLOUD_URL;
}

void CloudConnector::uploadPhoto(QString photoPath)
{
    qDebug() << "Uploading file...";
    QUrl url(m_baseUrl + "/api/photo");
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"photo\"; filename=\"photo.jpg\""));
    QFile *file = new QFile(photoPath);
    file->open(QIODevice::ReadOnly);
    imagePart.setBodyDevice(file);
    file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart
    multiPart->append(imagePart);
    QNetworkRequest request(url);
    QNetworkReply* reply = m_pManager->post(request, multiPart);
    multiPart->setParent(reply); // delete the multiPart with the reply
    connect(m_pManager, &QNetworkAccessManager::finished, this, &CloudConnector::replyFinished);
}

void CloudConnector::replyFinished(QNetworkReply *reply)
{
    QByteArray bytes = reply->readAll();
    qDebug() << "Reply received:";
    QString replyStr(bytes);
    qDebug() << replyStr;
}
