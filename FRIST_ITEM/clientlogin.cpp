#include "clientlogin.h"
#include "ui_clientlogin.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QMessageBox>
#include <QSqlTableModel>



clientLogin::clientLogin(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::clientLogin)
{
    ui->setupUi(this);

}

clientLogin::~clientLogin()
{
    delete ui;
}

void clientLogin::on_checkBox_clicked(bool checked)
{
    if(checked)
    {
        ui->linepassword->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->linepassword->setEchoMode(QLineEdit::Password);
    }
}

//注册
void clientLogin::on_btn_zhuche_clicked()
{
    QString id = ui->lineid->text();
    QString password = ui->linepassword->text();

    //查询数据库验证
    QSqlTableModel* model = new QSqlTableModel;
    model->setTable("userinfo");
    model->setFilter(QString("username ='%1'").arg(id));
    model->select();
    qDebug() << id;
    //检测是否查询到数据
    int row = model->rowCount();
    if(row > 0)
    {
        QMessageBox::information(this, QString::fromLocal8Bit("注册提示"), QString::fromLocal8Bit("该账号已注册"));
        ui->lineid->clear();
        ui->linepassword->clear();
    }
    else
    {
        QString cmd = QString("insert into userinfo values('%1','%2')").arg(id).arg(password);
        qDebug() << cmd;
        QSqlQuery query;
        if(query.exec(cmd))
        {
            //获取连接ip地址和端口号
            QString ip = "192.168.31.71";
            QString port = "8080";
            msocket.connectToHost(ip, port.toUShort());
            connect(this, &clientLogin::loginsign, this, &clientLogin::send_message);
            qDebug() << QString::fromLocal8Bit("注册成功");
            emit loginsign("1" + id + " " + password);
            QMessageBox::information(this, QString::fromLocal8Bit("提示信息"), QString::fromLocal8Bit("注册成功"));

        }
        else
        {
            QMessageBox::information(this, QString::fromLocal8Bit("提示信息"), QString::fromLocal8Bit("注册失败"));
        }
    }
    delete model;

    //qDebug() << "hehehehe";


}


//登录
void clientLogin::on_btn_loginin_clicked()
{
    //登录
    QString username = ui->lineid->text();
    QString password =  ui->linepassword->text();

    //查询数据库验证
    QSqlTableModel* model = new QSqlTableModel;
    model->setTable("userinfo");
    model->setFilter(QString("username ='%1' and password = '%2'").arg(username).arg(password));
    model->select();

    //检测是否查询到数据
    int row = model->rowCount();
    if(row > 0)
    {
        QMessageBox::information(this, QString::fromLocal8Bit("login提示"), QString::fromLocal8Bit("login成功"));
        C = new clientWindow;
        //主界面隐藏
        this->close();
        C->show();

    }
    else
    {
        QMessageBox::information(this, QString::fromLocal8Bit("login提示"), QString::fromLocal8Bit("login失败"));
    }
    delete model;
}


void clientLogin::send_message(QString message)
{
    qDebug() << QString::fromLocal8Bit("%1").arg(message);
    msocket.write(message.toUtf8());
}
