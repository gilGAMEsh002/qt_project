#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "SyntaxHighlighter.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        void newFile();
        void openFile();
        void saveFile();
        void runCompiler();
        void exitPro();
        void saveAs();

    private:
        Ui::MainWindow *ui;
        QString currentFile; // 声明currentFile作为一个QString类型的变量
        SyntaxHighlighter *highlighter; // 声明语法高亮器
        QString currentFileName = "untitled.a66";

        QTextCodec *codec;

};
#endif // MAINWINDOW_H
