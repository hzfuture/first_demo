#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QMainWindow>
#include<QTcpSocket>

namespace Ui
{
class TcpClient;
}

class TcpClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit TcpClient(QWidget* parent = nullptr);
    ~TcpClient();

public slots:
    void send_message(QString message);
private:
    Ui::TcpClient* ui;
    //´´½¨Ì×½Ó×Ö
    QTcpSocket msocket;
};

#endif // TCPCLIENT_H
