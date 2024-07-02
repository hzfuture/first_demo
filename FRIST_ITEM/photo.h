#ifndef PHOTO_H
#define PHOTO_H

#include <QMainWindow>
#include <QCameraInfo>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include<QTime>

namespace Ui
{
class photo;
}

class photo : public QMainWindow
{
    Q_OBJECT

public:
    explicit photo(QWidget* parent = nullptr);
    ~photo();


signals:
    void acquera(QString path);
private slots:
    void on_btnShot_clicked();

    void on_btnComfirm_clicked();

    void on_btnCancel_clicked();

    void show_image(int id, const QImage& preview);
private:
    Ui::photo* ui;
    QCamera* Ca;//…„œÒÕ∑∂‘œÛ
    QCameraImageCapture* Cap;
    QString filename;
    QCameraViewfinder* V;
};

#endif // PHOTO_H
