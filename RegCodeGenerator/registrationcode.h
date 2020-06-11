#ifndef REGISTRATIONCODE_H
#define REGISTRATIONCODE_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
namespace Ui {
class RegistrationCode;
}

class RegistrationCode : public QWidget
{
    Q_OBJECT

public:
    explicit RegistrationCode(QWidget *parent = 0);
    ~RegistrationCode();
    QString createRegistrationCode();
    QString getCPUId();
    QString eversedOrder(QString str);
    bool isMacAddress(QString mac);
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *e);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::RegistrationCode *ui;
    bool mMoveing;
    QPoint mMovePosition;
};

#endif // REGISTRATIONCODE_H
