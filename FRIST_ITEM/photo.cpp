#include "photo.h"
#include "ui_photo.h"

photo::photo(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::photo)
{
    ui->setupUi(this);
    //获取所有输出设备
    foreach(const QCameraInfo& info, QCameraInfo::availableCameras())
    {
        Ca = new QCamera((QString("%1").arg(info.deviceName()).toUtf8()));
    }
    ui->widget->show();

    //实例化截图对象
    Cap = new QCameraImageCapture(Ca);
    connect(Cap, &QCameraImageCapture::imageCaptured
            , this, &photo::show_image);
    //设置摄像头输出位置
    V = new QCameraViewfinder(ui->widget);
    V->resize(ui->widget->size());//设置大小
    //设置摄像头输出位置
    Ca->setViewfinder(V);
    V->show();
    //启动摄像头
    Ca->start();
}

photo::~photo()
{
    delete ui;
}

//截图
void photo::on_btnShot_clicked()
{
    // 获取当前时间
    QTime time = QTime::currentTime();
    filename = "D:/qtfiles/QTITEM/" + time.toString("hh-mm-ss") + ".jpg";
    //保存
    Cap->capture(filename);
    QPixmap pix(filename);
    pix = pix.scaled(ui->label->size());
    ui->label->setPixmap(pix);
}

//确认
void photo::on_btnComfirm_clicked()
{
    emit acquera(filename);
    this->parentWidget()->show();
    this->close();
}

//取消
void photo::on_btnCancel_clicked()
{
    ui->label->clear();
}

void photo::show_image(int id, const QImage& preview)
{
    qDebug() << id;
    //转化数据
    QPixmap pix = QPixmap::fromImage(preview);
    pix = pix.scaled(ui->label->size());
    ui->label->setPixmap(pix);
}
