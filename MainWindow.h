#pragma once

#include <QMainWindow>
#include <QProcess>

class QPushButton;
class QLineEdit;
class QTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void browseInput();
    void browseOutput();
    void startConversion();
    void readProcessOutput();

private:
    QLineEdit* inputEdit;
    QLineEdit* outputEdit;

    QPushButton* inputButton;
    QPushButton* outputButton;
    QPushButton* convertButton;

    QTextEdit* logView;

    QProcess* ffmpegProcess;
};
