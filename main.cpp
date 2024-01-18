#include "widget.h"
#include <QApplication>
#include <QFile>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QFile styleSheetFile("://src/stylesheet/styleSheet.qss");
    if (!styleSheetFile.open(QFile::ReadOnly)) {
        qDebug() << "Error opening file:" << styleSheetFile.errorString();
        return 1;
    }
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    a.setStyleSheet(styleSheet);

    Widget w;
    w.show();
    return a.exec();
}
