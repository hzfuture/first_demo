#include "clientlogin.h"
#include <QApplication>
#include <QSplashScreen>  //动画
#include <QThread> //线程
#include <QPixmap>
#include <QtDebug>
#include <QSqlDatabase>
#include <QSqlQuery>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    //定义图片
    QPixmap pix(":/res/donghua.png");
    //pix = pix.scaled(410, 270);
    //定义动画
    QSplashScreen splash(pix);
    //启动动画
    splash.show();
    //延时
    QThread::sleep(2);
    //关闭动画
    splash.close();

    //创建数据库----（全局的）
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //设置数据库名
    db.setDatabaseName("pwd.db");
    //打开数据
    if(db.open())
    {

        qDebug() << "open database suc";
    }

    else
    {
        qDebug() << "open database failed";
    }

    //创建一张数据库表存储用户名密码
    QString cmd = "create table if not exists userinfo(username varchar(64),password varchar(64))";
    //执行sql语句
    QSqlQuery query;
    if(query.exec(cmd))
    {
        qDebug() << "create cmd success";
    }
    clientLogin w;
    w.show();

    return a.exec();
}
