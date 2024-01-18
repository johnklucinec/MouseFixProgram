#ifndef WIDGET_H
#define WIDGET_H

#include "./src/code/markC.h"
#include <QMouseEvent>
#include <QWidget>
#include <Windows.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT

public:
    explicit Widget(QWidget* parent = nullptr);
    ~Widget();

    void paintEvent(QPaintEvent*) override;

protected:
    void mousePressEvent(QMouseEvent* evt) override;
    void mouseMoveEvent(QMouseEvent* evt) override;
    void installButtonEventFilters();
    bool eventFilter(QObject* watched, QEvent* event) override;

private slots:
    void applyBufferButton_clicked();
    void revertBufferButton_clicked();
    void applyCsrssButton_clicked();
    void revertCsrssButton_clicked();
    void closeButton_clicked();
    void unlockWindow();
    void applyMarkCButton_clicked();
    void revertMarkCButton_clicked();
    void displayOkMessage(const QString& message);
    void displayErrorMessage(const LONG errorCode);
    void displayRestartMessage();

private:
    Ui::Widget* ui;
    bool locked;
    QPoint oldPos;
    std::map<int, Scale> scaleMap;
};

#endif // WIDGET_H
