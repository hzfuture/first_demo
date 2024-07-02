#include "tcpclient.h"
#include "ui_tcpclient.h"

TcpClient::TcpClient(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::TcpClient)
{
    ui->setupUi(this);
    //��ȡ����ip��ַ�Ͷ˿ں�
    QString ip = "192.168.7.112";
    QString port = "8080";
    msocket.connectToHost(ip, port.toUShort());

}

TcpClient::~TcpClient()
{
    delete ui;
}

void TcpClient::send_message(QString message)
{
    qDebug() << QString::fromLocal8Bit("%1").arg(message);
    msocket.write(message.toUtf8());
}
