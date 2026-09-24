#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QHostAddress>//主机地址
#include<QHostInfo>//主机信息
#include<QTcpServer>//Tcp服务器
#include<QTcpSocket>
#include<QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    //处理新的客户端连接的槽函数
    void slot_newConnection();
    //接收客户端消息的槽函数
    void slot_readyRead();
    //断开连接的槽函数
    void slot_disconnected();


private:
    Ui::MainWindow *ui;
    //服务器对象
    QTcpServer *server;
    //客户端套接字
    QTcpSocket *client_socket;

};
#endif // MAINWINDOW_H
