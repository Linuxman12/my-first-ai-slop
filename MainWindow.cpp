#include "MainWindow.h"

#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto *central = new QWidget;
    auto *layout = new QVBoxLayout;

    inputEdit = new QLineEdit;
    outputEdit = new QLineEdit;

    inputButton = new QPushButton("Browse Input");
    outputButton = new QPushButton("Browse Output");
    convertButton = new QPushButton("Convert");

    logView = new QTextEdit;
    logView->setReadOnly(true);

    auto *inputRow = new QHBoxLayout;
    inputRow->addWidget(inputEdit);
    inputRow->addWidget(inputButton);

    auto *outputRow = new QHBoxLayout;
    outputRow->addWidget(outputEdit);
    outputRow->addWidget(outputButton);

    layout->addLayout(inputRow);
    layout->addLayout(outputRow);
    layout->addWidget(convertButton);
    layout->addWidget(logView);

    central->setLayout(layout);
    setCentralWidget(central);

    ffmpegProcess = new QProcess(this);

    connect(inputButton,
            &QPushButton::clicked,
            this,
            &MainWindow::browseInput);

    connect(outputButton,
            &QPushButton::clicked,
            this,
            &MainWindow::browseOutput);

    connect(convertButton,
            &QPushButton::clicked,
            this,
            &MainWindow::startConversion);

    connect(ffmpegProcess,
            &QProcess::readyReadStandardError,
            this,
            &MainWindow::readProcessOutput);

    setWindowTitle("FFmpeg GUI");
    resize(800, 500);
}

void MainWindow::browseInput()
{
    QString file =
        QFileDialog::getOpenFileName(this, "Select Input");

    if (!file.isEmpty())
        inputEdit->setText(file);
}

void MainWindow::browseOutput()
{
    QString file =
        QFileDialog::getSaveFileName(this, "Select Output");

    if (!file.isEmpty())
        outputEdit->setText(file);
}

void MainWindow::startConversion()
{
    QString input = inputEdit->text();
    QString output = outputEdit->text();

    QStringList args;
    args << "-i"
         << input
         << "-c:v"
         << "libx264"
         << output;

    logView->append("Starting FFmpeg...");
    ffmpegProcess->start("ffmpeg", args);
}

void MainWindow::readProcessOutput()
{
    QByteArray data =
        ffmpegProcess->readAllStandardError();

    logView->append(QString::fromUtf8(data));
}
