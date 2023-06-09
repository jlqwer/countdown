#include "countdown.h"

#include <QApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QPainterPath>
#include <QPalette>
#include <QMessageBox>
#include <Windows.h>
#include <tchar.h>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HANDLE hMutex = CreateMutex(NULL, FALSE, _T("CountDownWindows"));
    if(GetLastError() == ERROR_ALREADY_EXISTS) {
        CloseHandle(hMutex);
        QMessageBox::warning(NULL,"提示","已经有正在运行的窗口!");
        return false;
    }

    QFontDatabase::addApplicationFont(":/resources/font/MiSans.ttf");

    Countdown w;
    w.setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);

    //设置窗口透明
    w.setAttribute(Qt::WA_TranslucentBackground);
    w.setWindowOpacity(0.7);

    w.show();

    return a.exec();
}
