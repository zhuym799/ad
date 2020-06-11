#include "registrationcode.h"
#include "ui_registrationcode.h"
#include <QDebug>
#include <QMessageBox>
#include <QPalette>
#include <QPainter>
RegistrationCode::RegistrationCode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrationCode)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint );
    ui->dateEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateEdit->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
    ui->dateEdit->setCalendarPopup(true);
    ui->dateEdit->setVisible(false);
    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(18, 118, 116));
    setAutoFillBackground(true);
    setPalette(pal);
}
void RegistrationCode::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(QColor(18, 118, 116), 2));
    painter.setBrush(QColor(243, 251, 255));
    painter.drawRect(20, 20, width()-40, height()-40);
}
void RegistrationCode::mousePressEvent(QMouseEvent *event)
{
    mMoveing = true;
    mMovePosition = event->globalPos() - pos();
    return QWidget::mousePressEvent(event);
}

//重写鼠标移动事件
void RegistrationCode::mouseMoveEvent(QMouseEvent *event)
{
    if (mMoveing && (event->buttons() == Qt::LeftButton)
            && (event->globalPos() - mMovePosition).manhattanLength() > QApplication::startDragDistance() && event->pos().y() <= 45 )
    {
        move(event->globalPos() - mMovePosition);
        mMovePosition = event->globalPos() - pos();
    }
    return QWidget::mouseMoveEvent(event);
}
void RegistrationCode::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    mMoveing = false;
}
RegistrationCode::~RegistrationCode()
{
    delete ui;
}
QString RegistrationCode::createRegistrationCode()
{
    QString machineCode = ui->lineEdit->text();
    QString macAddress = machineCode.replace("-","");
    macAddress = macAddress.mid(0,2)+macAddress.mid(4,2)+macAddress.mid(8,2)+macAddress.mid(12,2)+macAddress.mid(16,2)+macAddress.mid(20,2);

    return macAddress;
}
QString RegistrationCode::getCPUId()
{
    QString machineCode = ui->lineEdit->text();
    QString cpuId = machineCode.replace("-","");
    cpuId = cpuId.mid(2,2)+cpuId.mid(6,2)+cpuId.mid(10,2)+cpuId.mid(14,2)+cpuId.mid(18,2)+cpuId.mid(22);

    return cpuId;
}
bool RegistrationCode::isMacAddress(QString mac)
{
    QRegExp rx("^([A-Fa-f0-9]{2}){5}[A-Fa-f0-9]{2}$");//^([A-Fa-f0-9]{2}[-,:]){5}[A-Fa-f0-9]{2}$
    QRegExpValidator v(rx, 0);
    int pos = 0;
    if(v.validate(mac, pos) == QValidator::Acceptable)
        return true;
    else
        return false;
}
void RegistrationCode::on_pushButton_clicked()
{
    QString macAddress = createRegistrationCode();
    if(isMacAddress(macAddress) == false)
    {
        QMessageBox::warning(NULL, "warning", "无效的机器码", QMessageBox::Ok);
        return;
    }
    macAddress = eversedOrder(macAddress);
    QString time = eversedOrder(ui->dateEdit->dateTime().toString("yyyyMMddhhmmss").mid(2));
    time="000000623091";
    qDebug()<<time<<endl;
    QString RegistrationCode = macAddress.mid(0,2)+time.mid(0,2)+"-"+macAddress.mid(2,2)+time.mid(2,2)+"-"
            +macAddress.mid(4,2)+time.mid(4,2)+"-"+macAddress.mid(6,2)+time.mid(6,2)+"-"
            +macAddress.mid(8,2)+time.mid(8,2)+"-"+macAddress.mid(10,2)+time.mid(10,2);
    ui->lineEdit_2->setText(RegistrationCode);
}
QString RegistrationCode::eversedOrder(QString str)
{
    for(int i = str.size()-1;i>=0;i--)
    {
        str+=str.mid(i,1);
    }
    str = str.mid(str.size()/2);
    return str;
}

void RegistrationCode::on_pushButton_2_clicked()
{
    close();
}
