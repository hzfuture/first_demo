#ifndef CLIENTLOGIN_H
#define CLIENTLOGIN_H

#include <QMainWindow>
#include "clientwindow.h"
#include "tcpclient.h"

namespace Ui
{
class clientLogin;
}

class clientLogin : public QMainWindow
{
    Q_OBJECT

public:
    explicit clientLogin(QWidget* parent = nullptr);
    ~clientLogin();

signals:
    void loginsign(QString message);

private slots:
    void on_checkBox_clicked(bool checked);

    void on_btn_zhuche_clicked();

    void on_btn_loginin_clicked();

    void send_message(QString message);
private:
    Ui::clientLogin* ui;
    clientWindow* C;
    //´´½¨Ì×½Ó×Ö
    QTcpSocket msocket;
};

#endif // CLIENTLOGIN_H
