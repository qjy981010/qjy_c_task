#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    char org_file[] = "../org.dat";
    char achi_file[] = "../achi.dat";
    char contr_file[] = "../contr.dat";
    load_data(org_file, achi_file, contr_file);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    int exit_code = a.exec();

    write_data(org_file, achi_file, contr_file);
    return exit_code;
}
