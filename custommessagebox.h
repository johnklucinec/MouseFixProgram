#ifndef CUSTOMMESSAGEBOX_H
#define CUSTOMMESSAGEBOX_H

#include <QDialog>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class CustomMessageBox;
}
QT_END_NAMESPACE

class CustomMessageBox : public QDialog {
    Q_OBJECT

public:
    CustomMessageBox(QWidget* parent = nullptr);
    ~CustomMessageBox();

    void setMessage(const QString& message);

protected:
    void mousePressEvent(QMouseEvent* evt) override;
    void mouseMoveEvent(QMouseEvent* evt) override;
    void paintEvent(QPaintEvent* event) override;

private:
    Ui::CustomMessageBox* ui;
    QPoint oldPos;
    void closeButton_clicked();
};
#endif // CUSTOMMESSAGEBOX_H
