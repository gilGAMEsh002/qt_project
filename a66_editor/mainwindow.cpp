#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QProcess>
#include <QMessageBox>
#include <QDebug>
#include<conio.h>
#include"tokenize.h"
#include"var.h"
#include"parse.h"

#include <QTextCodec>
#include <QLineEdit>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextCursor>
#include <QPlainTextEdit>
#include <QLabel>
#include <QDateTime>
#include <QTextCharFormat>
#include <QFontDialog>
#include <QToolBar>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    /*工具栏图片资源添加*/

//    ui->actionnew->setIcon(QIcon(":/new/xinjian1.png"));
/*    ui->actionNew->setIcon(QIcon(":/icon/new.png"))*/;

    // 连接菜单项的槽函数
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));


    // 设置默认文件名
    currentFileName = "untitled.a66";

    // 创建语法高亮器并关联到文本编辑器
    SyntaxHighlighter *highlighter = new SyntaxHighlighter(ui->textEdit->document());

    // 连接界面上所有按钮的点击事件到槽函数
    connect(ui->pushButton_run, SIGNAL(clicked()), this, SLOT(runCompiler()));// run 运行
    connect(ui->pushButton_new,SIGNAL(clicked()), this,SLOT(newFile()));//new 新建
//    connect(ui->runButton, SIGNAL(clicked()), this, SLOT(runCompiler()));
//    connect(ui->runButton, SIGNAL(clicked()), this, SLOT(runCompiler()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::newFile() {
    // 清除文本编辑器内容并重置文件名
    ui->textEdit->clear();
    currentFileName = "untitled.a66";
}

void MainWindow::openFile() {
    // 打开文件对话框以选择文件
    QString fileName = QFileDialog::getOpenFileName(this, "打开文件", "", "a66文件 (*.a66)");

    // 如果用户选择了文件，则加载文件内容
    if (!fileName.isEmpty()) {
        currentFileName = fileName;
         qDebug()<<currentFileName<<"\n";
        QFile file(currentFileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            ui->textEdit->setPlainText(file.readAll());
            file.close();
        }
    }
}

void MainWindow::saveFile() {
    // 保存文件
    if (currentFileName != "untitled.a66") {
        QFile file(currentFileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << ui->textEdit->toPlainText();
            file.close();
        }
    } else {
        // 如果文件名是默认的，则另存为文件
        QString fileName = QFileDialog::getSaveFileName(this, "另存为", "", "a66文件 (*.a66)");
        if (!fileName.isEmpty()) {
            currentFileName = fileName;
        }
    }
}

void MainWindow::runCompiler() {
    // 运行编译器
    ifstream fin(currentFileName.toStdString());
    stringstream ss;
    ss << fin.rdbuf();
    //	cout << ss.str() << endl;
    string s = ss.str();
    s += "                 ";
//            qDebug()<<currentFileName<<"\n";
    auto vec = tokenize::tokenize(s);
    parse::results.clear();
    parse::run(vec);
    vector<string>results = parse::results;
    results.push_back("<br>程序执行结束<br>");
    QString message;
    for (auto& str : results) {
        if (str == "\n") str = "<br>";
        message += QString::fromStdString(str);
    }

    // 使用 QMessageBox 显示弹窗，设置消息框的文本格式为 HTML
    QMessageBox msgBox;
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setWindowTitle("Output");
    msgBox.setText(message);
    msgBox.exec();

}

void MainWindow::exitPro(){
    exit(0);
}

void MainWindow::saveAs(){
    QString path ;
    path=QFileDialog::getSaveFileName();//选择文件保存路径
    if(path.isEmpty()) {return;}
    qDebug()<<path;

    char *fileName=codec->fromUnicode(path).data();//将utf-8替换成gbk，同时将QString转换为char*

    FILE* fp=fopen(fileName,"wb");//打开文件，fopen(),需要的路径为char*，有中文要gbk
    if(fp==NULL) {return;}//打开失败

        QString str=ui->textEdit->toPlainText();//获取编辑区内容QString

        const char * buf=str.toStdString().data();//将编辑区内容QString转为char*

        fputs(buf,fp);//将编辑区内容写入文件fputs

        fclose(fp);//关闭文件
}
