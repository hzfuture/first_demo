#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QWidget>
#include "photo.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>



namespace Ui
{
class clientWindow;
}

class clientWindow : public QWidget
{
    Q_OBJECT

public:
    explicit clientWindow(QWidget* parent = nullptr);
    ~clientWindow();


private slots:
    void on_btnEdit_clicked();

    void on_btnThis_clicked();

    void on_btnCamera_clicked();

    void protectPath(QString path);

    void on_btnEnter_clicked();

    void on_btnPreview_clicked();

private:
    Ui::clientWindow* ui;
    QWidget* w;
    void prohibit();
    void unprohibit();
    photo* xiji;
    QString pathname;
};

#endif // CLIENTWINDOW_H
