#include "notepadwindow.h"
#include <QApplication>
#include <QCoreApplication>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    NotepadWindow w;
    if(argc == 2)
    {
        w.openfile(QCoreApplication::arguments().at(1));
    }

    w.show();
    return a.exec();

}
