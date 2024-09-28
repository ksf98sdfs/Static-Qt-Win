#include <QApplication>
#include <QPushButton>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>

int main(int argc, char **argv)
{
 QApplication app (argc, argv);

 QWidget window;
 window.setFixedSize(100, 50);

 QPushButton *button = new QPushButton("Hello World", &window);
 button->setGeometry(10, 10, 80, 30);

 QNetworkAccessManager* manager = new QNetworkAccessManager(button);
 QNetworkRequest request(QUrl(QStringLiteral("https://www.svt.se/text-tv/100")));
 QNetworkReply* reply = manager->get(request);
 QObject::connect(reply, &QNetworkReply::finished, [button, reply]() {
   reply->manager()->deleteLater();
   reply->deleteLater();
   button->setText(QString::number(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()));
 });
 
 window.show();
 return app.exec();
}
