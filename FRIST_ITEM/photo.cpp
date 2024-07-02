#include "photo.h"
#include "ui_photo.h"

photo::photo(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::photo)
{
    ui->setupUi(this);
    //��ȡ��������豸
    foreach(const QCameraInfo& info, QCameraInfo::availableCameras())
    {
        Ca = new QCamera((QString("%1").arg(info.deviceName()).toUtf8()));
    }
    ui->widget->show();

    //ʵ������ͼ����
    Cap = new QCameraImageCapture(Ca);
    connect(Cap, &QCameraImageCapture::imageCaptured
            , this, &photo::show_image);
    //��������ͷ���λ��
    V = new QCameraViewfinder(ui->widget);
    V->resize(ui->widget->size());//���ô�С
    //��������ͷ���λ��
    Ca->setViewfinder(V);
    V->show();
    //��������ͷ
    Ca->start();
}

photo::~photo()
{
    delete ui;
}

//��ͼ
void photo::on_btnShot_clicked()
{
    // ��ȡ��ǰʱ��
    QTime time = QTime::currentTime();
    filename = "D:/qtfiles/QTITEM/" + time.toString("hh-mm-ss") + ".jpg";
    //����
    Cap->capture(filename);
    QPixmap pix(filename);
    pix = pix.scaled(ui->label->size());
    ui->label->setPixmap(pix);
}

//ȷ��
void photo::on_btnComfirm_clicked()
{
    emit acquera(filename);
    this->parentWidget()->show();
    this->close();
}

//ȡ��
void photo::on_btnCancel_clicked()
{
    ui->label->clear();
}

void photo::show_image(int id, const QImage& preview)
{
    qDebug() << id;
    //ת������
    QPixmap pix = QPixmap::fromImage(preview);
    pix = pix.scaled(ui->label->size());
    ui->label->setPixmap(pix);
}
