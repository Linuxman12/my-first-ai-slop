#include "MainWindow.h"

#include <QApplication>
#include <QProcess>
#include <QMessageBox>

bool checkFFmpeg()
{
    QProcess ffmpegCheck;
    ffmpegCheck.start("ffmpeg", QStringList() << "-version");

    if (!ffmpegCheck.waitForFinished(3000))
        return false;

    // If ffmpeg exists, it should exit normally
    return ffmpegCheck.exitStatus() == QProcess::NormalExit &&
           ffmpegCheck.exitCode() == 0;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (!checkFFmpeg())
    {
        QMessageBox::critical(
            nullptr,
            "FFmpeg Not Found",
            "FFmpeg is not installed or not in PATH.\n\n"
            "Install FFmpeg and restart the app."
        );
        return 1;
    }

    MainWindow window;
    window.show();

    return app.exec();
}
