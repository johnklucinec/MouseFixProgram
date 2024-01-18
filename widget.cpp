#include "./src/code/markC.h"
#include "./src/code/MouseTweaks.h"
#include "./ui_widget.h"
#include "custommessagebox.h"
#include "QPainter"
#include "widget.h"
#include <QDebug>
#include <QMessageBox>
#include <Windows.h>
#include <memory>

Widget::Widget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , locked(false)
    , scaleMap { { 0, Scale::Scale100 }, { 1, Scale::Scale125 },
        { 2, Scale::Scale150 }, { 3, Scale::Scale175 }, { 4, Scale::Scale200 },
        { 5, Scale::Scale225 }, { 6, Scale::Scale250 }, { 7, Scale::Scale300 },
        { 8, Scale::Scale350 } } // This is for the MarkC fix

{
    // Make window frameless and remove background
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAutoFillBackground(false);

    ui->setupUi(this);

    // Connections
    connect(ui->applyBufferButton, &QPushButton::clicked, this, &Widget::applyBufferButton_clicked);
    connect(ui->revertBufferButton, &QPushButton::clicked, this, &Widget::revertBufferButton_clicked);
    connect(ui->applyCsrssButton, &QPushButton::clicked, this, &Widget::applyCsrssButton_clicked);
    connect(ui->revertCsrssButton, &QPushButton::clicked, this, &Widget::revertCsrssButton_clicked);
    connect(ui->closeButton, &QPushButton::clicked, this, &Widget::closeButton_clicked);
    connect(ui->applyMarkCButton, &QPushButton::clicked, this, &Widget::applyMarkCButton_clicked);
    connect(ui->revertMarkCButton, &QPushButton::clicked, this, &Widget::revertMarkCButton_clicked);

    /*  Edge case with combo box when user drags and releses mouse
     *  This fixes the issue if they select something */
    connect(ui->markCComboBox, &QComboBox::activated, this, &Widget::unlockWindow);
    connect(ui->mouseTweaksTab, &QTabWidget::currentChanged, this, &Widget::unlockWindow);

    // Install event filters on the buttons
    installButtonEventFilters();
}

Widget::~Widget()
{
    delete ui;
}

/* Allow user to move the window */

/* Install event filters on the buttons
 * If you try to move the window and click on a button at the same time
 * the window randomly jumps all over the place.
 * These filters disble window movement when something in being clicked.
 */
void Widget::installButtonEventFilters()
{
    ui->applyBufferButton->installEventFilter(this);
    ui->revertBufferButton->installEventFilter(this);
    ui->applyCsrssButton->installEventFilter(this);
    ui->revertCsrssButton->installEventFilter(this);
    ui->closeButton->installEventFilter(this);
    ui->markCComboBox->installEventFilter(this);
    ui->applyMarkCButton->installEventFilter(this);
    ui->revertMarkCButton->installEventFilter(this);
}

// Handle mouse movement
void Widget::mouseMoveEvent(QMouseEvent* evt)
{
    const QPoint delta = evt->globalPosition().toPoint() - oldPos;
    if (!locked)
        move(x() + delta.x(), y() + delta.y());
    oldPos = evt->globalPosition().toPoint();
}

// Handle mouse press
void Widget::mousePressEvent(QMouseEvent* evt)
{
    oldPos = evt->globalPosition().toPoint();
}

// Handle event filtering
bool Widget::eventFilter(QObject* watched, QEvent* event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        locked = true;
    } else if (event->type() == QEvent::MouseButtonRelease) {
        locked = false;
    }
    return QWidget::eventFilter(watched, event);
}

void Widget::unlockWindow()
{
    locked = false;
}

// Make close button do something
void Widget::closeButton_clicked()
{
    displayRestartMessage();
    close();
}

/* Button Functions */

/* Message Box Functions:
 * Display Ok, Error, and Restart message boxes
 */

void Widget::displayOkMessage(const QString& message)
{
    std::unique_ptr<CustomMessageBox> dialog(new CustomMessageBox(this));
    dialog->setMessage(message);
    dialog->exec();
}

void Widget::displayErrorMessage(const LONG errorCode)
{
    QString message = "Error: Could not edit registry\n"
                      "ERROR Code: "
                      + QString::number(errorCode);
    std::unique_ptr<CustomMessageBox> dialog(new CustomMessageBox(this));
    dialog->setMessage(message);
    dialog->exec();
}

void Widget::displayRestartMessage()
{
    QString message = "Please restart your PC\nto apply the changes";
    std::unique_ptr<CustomMessageBox> dialog(new CustomMessageBox(this));
    dialog->setMessage(message);
    dialog->exec();
}

/* Connection Functions:
 * Create and use my mouse tweak objects
 */

void Widget::applyBufferButton_clicked()
{

    MouseTweaks tweak;
    LONG statusCode = tweak.applyDataQueue(ui->bufferSize->value());

    if (statusCode == ERROR_SUCCESS) {
        QString message = "Mouse buffer size was set to: "
                          ""
            + QString::number(ui->bufferSize->value());
        displayOkMessage(message);
    } else {
        displayErrorMessage(statusCode);
    }
}

void Widget::revertBufferButton_clicked()
{

    MouseTweaks tweak;
    LONG statusCode = tweak.revertDataQueue();

    if (statusCode == ERROR_SUCCESS) {
        displayOkMessage("The mouse buffer size was set \n"
                         "to its default value");
    } else {
        displayErrorMessage(statusCode);
    }
}

void Widget::applyCsrssButton_clicked()
{

    MouseTweaks tweak;
    LONG statusCode = tweak.applyBoostCsrss();

    if (statusCode == ERROR_SUCCESS) {
        displayOkMessage("CSRSS priority was set to realtime");
    } else {
        displayErrorMessage(statusCode);
    }
}

void Widget::revertCsrssButton_clicked()
{
    MouseTweaks tweak;
    LONG statusCode = tweak.revertBoostCsrss();

    if (statusCode == ERROR_SUCCESS) {
        displayOkMessage("CSRSS priority was set to default");
    } else {
        displayErrorMessage(statusCode);
    }
}

void Widget::applyMarkCButton_clicked()
{
    int userSelection = ui->markCComboBox->currentIndex();
    Scale selectedScale = scaleMap[userSelection];

    MouseScaleFix fix(selectedScale);
    LONG statusCode = fix.applyMouseFix();

    if (statusCode == ERROR_SUCCESS) {
        QString message = QString("Mouse acceleration values updated.\n"
                                  "The new settings are applied for a \n"
                                  "display scale of "
            + ui->markCComboBox->currentText());
        displayOkMessage(message);
    } else {
        displayErrorMessage(statusCode);
    }
}

void Widget::revertMarkCButton_clicked()
{
    MouseScaleFix fix;
    LONG statusCode = fix.applyMouseFix();

    if (statusCode == ERROR_SUCCESS) {
        displayOkMessage("Default acceleration values applied");
    } else {
        displayErrorMessage(statusCode);
    }
}

/* Create the transparent background */
void Widget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    // Draw outer rectangle (toolbar)
    painter.setBrush(QColor(50, 50, 50, 220)); // Adjust the alpha value for transparency
    painter.drawRect(0, 0, width(), height());

    // Draw inner rectangle
    painter.setCompositionMode(QPainter::CompositionMode_SoftLight);
    painter.setBrush(QColor(50, 50, 50, 230)); // Adjust the alpha value for transparency
    // Base height of "inner" box on exit button size
    painter.drawRect(0, ui->closeButton->height(), width(), height() - ui->closeButton->height());
}
