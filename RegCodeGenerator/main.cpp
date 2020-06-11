#include "registrationcode.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RegistrationCode w;
    w.show();

    return a.exec();
}
