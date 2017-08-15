#ifndef CLOUDCONNECTOR_H
#define CLOUDCONNECTOR_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class CloudConnector : public QObject
{
    Q_OBJECT
public:
    explicit CloudConnector(QObject *parent = nullptr);
    Q_INVOKABLE void uploadPhoto(QString photoPath);

public slots:
    void replyFinished(QNetworkReply* reply);

private:
    void printPictures();
    QNetworkAccessManager* m_pManager;
    QString m_baseUrl;
    QString m_firstImage;
    QString m_secondImage;
};

#endif // CLOUDCONNECTOR_H
