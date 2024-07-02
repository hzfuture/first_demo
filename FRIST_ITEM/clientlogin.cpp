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

//ע��
void clientLogin::on_btn_zhuche_clicked()
{
    QString id = ui->lineid->text();
    QString password = ui->linepassword->text();

    //��ѯ���ݿ���֤
    QSqlTableModel* model = new QSqlTableModel;
    model->setTable("userinfo");
    model->setFilter(QString("username ='%1'").arg(id));
    model->select();
    qDebug() << id;
    //����Ƿ��ѯ������
    int row = model->rowCount();
    if(row > 0)
    {
        QMessageBox::information(this, QString::fromLocal8Bit("ע����ʾ"), QString::fromLocal8Bit("���˺���ע��"));
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
            //��ȡ����ip��ַ�Ͷ˿ں�
            QString ip = "192.168.31.71";
            QString port = "8080";
            msocket.connectToHost(ip, port.toUShort());
            connect(this, &clientLogin::loginsign, this, &clientLogin::send_message);
            qDebug() << QString::fromLocal8Bit("ע��ɹ�");
            emit loginsign("1" + id + " " + password);
            QMessageBox::information(this, QString::fromLocal8Bit("��ʾ��Ϣ"), QString::fromLocal8Bit("ע��ɹ�"));

        }
        else
        {
            QMessageBox::information(this, QString::fromLocal8Bit("��ʾ��Ϣ"), QString::fromLocal8Bit("ע��ʧ��"));
        }
    }
    delete model;

    //qDebug() << "hehehehe";


}


//��¼
void clientLogin::on_btn_loginin_clicked()
{
    //��¼
    QString username = ui->lineid->text();
    QString password =  ui->linepassword->text();

    //��ѯ���ݿ���֤
    QSqlTableModel* model = new QSqlTableModel;
    model->setTable("userinfo");
    model->setFilter(QString("username ='%1' and password = '%2'").arg(username).arg(password));
    model->select();

    //����Ƿ��ѯ������
    int row = model->rowCount();
    if(row > 0)
    {
        QMessageBox::information(this, QString::fromLocal8Bit("login��ʾ"), QString::fromLocal8Bit("login�ɹ�"));
        C = new clientWindow;
        //����������
        this->close();
        C->show();

    }
    else
    {
        QMessageBox::information(this, QString::fromLocal8Bit("login��ʾ"), QString::fromLocal8Bit("loginʧ��"));
    }
    delete model;
}


void clientLogin::send_message(QString message)
{
    qDebug() << QString::fromLocal8Bit("%1").arg(message);
    msocket.write(message.toUtf8());
}
