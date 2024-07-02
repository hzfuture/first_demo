#include "clientlogin.h"
#include <QApplication>
#include <QSplashScreen>  //����
#include <QThread> //�߳�
#include <QPixmap>
#include <QtDebug>
#include <QSqlDatabase>
#include <QSqlQuery>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    //����ͼƬ
    QPixmap pix(":/res/donghua.png");
    //pix = pix.scaled(410, 270);
    //���嶯��
    QSplashScreen splash(pix);
    //��������
    splash.show();
    //��ʱ
    QThread::sleep(2);
    //�رն���
    splash.close();

    //�������ݿ�----��ȫ�ֵģ�
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //�������ݿ���
    db.setDatabaseName("pwd.db");
    //������
    if(db.open())
    {

        qDebug() << "open database suc";
    }

    else
    {
        qDebug() << "open database failed";
    }

    //����һ�����ݿ��洢�û�������
    QString cmd = "create table if not exists userinfo(username varchar(64),password varchar(64))";
    //ִ��sql���
    QSqlQuery query;
    if(query.exec(cmd))
    {
        qDebug() << "create cmd success";
    }
    clientLogin w;
    w.show();

    return a.exec();
}
