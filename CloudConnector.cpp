#include "CloudConnector.h"
#include <config.h>

#include <QFile>
#include <QHttpMultiPart>
#include <QNetworkReply>

#include <QImage>
#include <QPoint>
#include <QMatrix>
#include <QPixmap>
#include <QPainter>

CloudConnector::CloudConnector(QObject *parent)
    : QObject(parent)
    , m_pManager(new QNetworkAccessManager(this))
    , m_firstImage("")
    , m_secondImage("")
{
    m_baseUrl = CLOUD_URL;
}

void CloudConnector::uploadPhoto(QString photoPath)
{
    qDebug() << "Changing image orientation";
    QImage srcImg(photoPath);
    QPoint center = srcImg.rect().center();
    QMatrix matrix;
    matrix.translate(center.x(), center.y());
    matrix.rotate(270);
    QImage dstImg = srcImg.transformed(matrix);
    dstImg.save(photoPath);

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

    if(m_firstImage != "")
    {
        if(m_secondImage  == "")
        {
            m_secondImage = photoPath;
        }
        else
        {
            printPictures();
        }
    }
    else
    {
        m_firstImage = photoPath;
    }

    connect(m_pManager, &QNetworkAccessManager::finished, this, &CloudConnector::replyFinished);
}

void CloudConnector::replyFinished(QNetworkReply *reply)
{
    QByteArray bytes = reply->readAll();
    qDebug() << "Reply received:";
    QString replyStr(bytes);
    qDebug() << replyStr;
}

void CloudConnector::printPictures()
{
    // combine both images
    QImage first = QImage(m_firstImage);
    QImage second = QImage(m_secondImage);
    QImage final = QImage(first.width() * 2, first.height(), QImage::Format_RGB32);
    QPainter imgPainter(&final);
    imgPainter.drawImage(0,0, first);
    imgPainter.drawImage(first.width(),0, second);
    imgPainter.end();
    final.save("~/photobooth-print/" + QString::number(QDateTime::currentMSecsSinceEpoch()) + ".jpg");

/*    // print image
    QPainter painter(&m_printer);
    painter.drawImage(0,0,final);
    painter.end();*/
}
