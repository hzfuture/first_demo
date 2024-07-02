#include "clientwindow.h"
#include "ui_clientwindow.h"
#include <QFileDialog>
#include <QtDebug>

//#include <QImage>

clientWindow::clientWindow(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::clientWindow)
{
    ui->setupUi(this);
    for(auto i = 0; i < ui->gridLayout->count(); i++)
    {
        w = ui->gridLayout->itemAt(i)->widget();
        if(w != nullptr)
        {
            w->setVisible(false);
        }
    }
    prohibit();
    ui->btnEdit->setEnabled(true);

}
clientWindow::~clientWindow()
{
    delete ui;
}

//点击编辑
void clientWindow::on_btnEdit_clicked()
{
    for(auto i = 0; i < ui->gridLayout->count(); i++)
    {
        w = ui->gridLayout->itemAt(i)->widget();
        if(w != nullptr)
        {
            w->setVisible(true);
        }
    }
    unprohibit();
}

void clientWindow::prohibit()
{
    ui->btnEdit->setEnabled(false);
    ui->btnEnter->setEnabled(false);
    ui->btnSubmit->setEnabled(false);
    ui->btnPreview->setEnabled(false);
}

void clientWindow::unprohibit()
{
    ui->btnEdit->setEnabled(true);
    ui->btnEnter->setEnabled(true);
    ui->btnSubmit->setEnabled(true);
    ui->btnPreview->setEnabled(true);
    ui->lineQQ->setEnabled(true);
    ui->lineSex->setEnabled(true);
    ui->lineName->setEnabled(true);
    ui->lineCarId->setEnabled(true);
    ui->lineHobby->setEnabled(true);
    ui->lineHouse->setEnabled(true);
    ui->lineNative->setEnabled(true);
    ui->lineBirthday->setEnabled(true);
    ui->lineNumber->setEnabled(true);
    ui->lineAddress->setEnabled(true);
    ui->lineIntroduce->setEnabled(true);
    ui->btnThis->setEnabled(true);
    ui->btnCamera->setEnabled(true);
    ui->lineNational->setEnabled(true);
}

//本地上传
void clientWindow::on_btnThis_clicked()
{
    QString filter = QString("select file(*.jpg *.png *.gif *.bmp *.jpeg)");
    QString filename = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择文件"), "./", filter);
    QPixmap image = QPixmap(filename);
    if(!image.isNull())
    {
        qDebug() << QString::fromLocal8Bit("图片显示成功");
        ui->label_13->setPixmap(image);
        ui->label_13->setScaledContents(true);
    }
    else
    {
        qDebug() << QString::fromLocal8Bit("图片路径为空");
    }
}

//摄像获取
void clientWindow::on_btnCamera_clicked()
{
    xiji = new photo(this);
    connect(xiji, &photo::acquera, this, &clientWindow::protectPath);
    xiji->show();
    this->hide();

}

void clientWindow::protectPath(QString path)
{
    pathname = path;
    QPixmap ima = QPixmap(path);
    if(!ima.isNull())
    {
        qDebug() << QString::fromLocal8Bit("图片显示成功");
        ui->label_13->setPixmap(ima);
        ui->label_13->setScaledContents(true);
    }
    else
    {
        qDebug() << QString::fromLocal8Bit("图片路径为空");
    }
}

//录入（将信息以json文件形式保存）
void clientWindow::on_btnEnter_clicked()
{
    QJsonObject object;
    object.insert("name", ui->lineName->text());
    object.insert("sex", ui->lineSex->text());
    object.insert("national", ui->lineNational->text());
    object.insert("native", ui->lineNative->text());
    object.insert("birthday", ui->lineBirthday->text());
    object.insert("house", ui->lineHouse->text());
    object.insert("number", ui->lineNumber->text());
    object.insert("QQ", ui->lineQQ->text());
    object.insert("address", ui->lineAddress->text());
    object.insert("carid", ui->lineCarId->text());
    object.insert("hobby", ui->lineHobby->text());
    object.insert("introduce", ui->lineIntroduce->text());
    object.insert("path", pathname);
    //    //实例化数组
    //    QJsonArray array;
    //    array.append(object);

    //    //最后给json数组设置键值
    //    QJsonObject allobj;
    //    allobj.insert("yonghu", array);
    //将json数据转化为文档
    QJsonDocument doc;
    doc.setObject(object);
    QByteArray msg = doc.toJson();
    ui->textBrowser->append(msg);
    qDebug() << QString::fromUtf8(msg);

}

//预览
void clientWindow::on_btnPreview_clicked()
{
    ui->lineQQ->setEnabled(false);
    ui->lineSex->setEnabled(false);
    ui->lineName->setEnabled(false);
    ui->lineCarId->setEnabled(false);
    ui->lineHobby->setEnabled(false);
    ui->lineHouse->setEnabled(false);
    ui->lineNative->setEnabled(false);
    ui->lineBirthday->setEnabled(false);
    ui->lineNumber->setEnabled(false);
    ui->lineAddress->setEnabled(false);
    ui->lineIntroduce->setEnabled(false);
    ui->btnThis->setEnabled(false);
    ui->btnCamera->setEnabled(false);
    ui->lineNational->setEnabled(false);
}
