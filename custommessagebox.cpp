#include "./ui_custommessagebox.h"
#include "custommessagebox.h"
#include <QPainter>

CustomMessageBox::CustomMessageBox(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::CustomMessageBox)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    setAttribute(Qt::WA_TranslucentBackground);

    // Connections

    connect(ui->closeButton, &QPushButton::clicked, this, &CustomMessageBox::closeButton_clicked);
    connect(ui->okButton, &QPushButton::clicked, this, &CustomMessageBox::closeButton_clicked);
}

CustomMessageBox::~CustomMessageBox()
{
    delete ui;
}

// Make close button do something
void CustomMessageBox::closeButton_clicked()
{
    close();
}

void CustomMessageBox::setMessage(const QString& message)
{
    ui->label->setText(message);
}

void CustomMessageBox::mousePressEvent(QMouseEvent* evt)
{
    oldPos = evt->globalPosition().toPoint();
}

void CustomMessageBox::mouseMoveEvent(QMouseEvent* evt)
{
    const QPoint delta = evt->globalPosition().toPoint() - oldPos;
    move(x() + delta.x(), y() + delta.y());
    oldPos = evt->globalPosition().toPoint();
}

void CustomMessageBox::paintEvent(QPaintEvent*)
{

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    // Draw outer rectangle (toolbar)
    painter.setBrush(QColor(50, 50, 50, 220)); // Adjust the alpha value for transparency
    painter.drawRect(0, 0, width(), height());
    // You can add more custom painting code here

    painter.setCompositionMode(QPainter::CompositionMode_SoftLight);
    painter.setBrush(QColor(50, 50, 50, 220)); // Adjust the alpha value for transparency
    // Base height of "inner" box on exit button size
    painter.drawRect(0, 20, width(), height());
}
