#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //1.获取本地主机的主机名
    QString name= QHostInfo::localHostName();
    //2.根据主机名字获取到配套的所有的网络信息
    QHostInfo info= QHostInfo::fromName(name);
    //3.只要网络地址（ipv4 ipv6）
    QList<QHostAddress> addr=info.addresses();

    //4.只要ipv4地址
    for(auto iter=addr.begin();iter !=addr.end();iter++){
        if(iter->protocol()==QAbstractSocket::IPv4Protocol){
            ui->comboBox->addItem(iter->toString());
        }
    }
    //实例化server对象
    server=new QTcpServer(this);
    //监听
    server->listen(QHostAddress::Any,8080);
    //绑定客户端连接成功的信号与槽
    connect(server,&QTcpServer::newConnection,this,&MainWindow::slot_newConnection);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
   QString msg= ui->lineEdit->text();
   client_socket->write(msg.toUtf8());
}

void MainWindow::slot_newConnection()
{
    qDebug()<<"客户端来了";
    //获取客户端的socket
    client_socket=server->nextPendingConnection();

    //绑定接收
    connect(client_socket,&QTcpSocket::readyRead,this,&MainWindow::slot_readyRead);

    //绑定断开连接的信号与槽
    connect(client_socket,&QTcpSocket::disconnected,this,&MainWindow::slot_disconnected);



}

void MainWindow::slot_readyRead()
{
    //读取
    QByteArray arr =client_socket->readAll();
    //显示
   // ui->textBrowser->append(QString::fromUtf8(arr));
    //获取客户端ip地址
    QString client_ip= client_socket->peerAddress().toString();
    //显示ip地址
    ui->textBrowser->append("客户端ip"+client_ip+"发送的消息:"+QString::fromUtf8(arr));

}
//断开连接
void MainWindow::slot_disconnected()
{
    qDebug()<<"客户端断开连接";
    client_socket->close();
}







