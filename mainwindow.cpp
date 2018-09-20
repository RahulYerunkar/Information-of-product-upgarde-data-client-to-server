#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFile>
#include<QTextStream>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ser=new QTcpServer(this);
    soc=new QTcpSocket(this);
    QFile f("test_proj.csv");
    if(f.open(QIODevice::ReadOnly))
    {

        int zz=0;
        QString d;
        QTextStream u(&f);
        d=u.readAll();
        QStringList gg=d.split(";",QString::SkipEmptyParts);
        int r=gg.count()/4,i,c;
     ui->tableWidget->setSortingEnabled(false);
         for(i=0;i<r;i++)
         {
             ui->tableWidget->insertRow(i);
             for(c=0;c<4;c++)
             {
                 ui->tableWidget->setItem(i,c,new QTableWidgetItem(gg[zz++]));
             }
         }
    }
    f.close();
    //ui->tableWidget->setSortingEnabled(true);

    connect(ser,SIGNAL(newConnection()),this,SLOT(con_suc()));
    if(!ser->listen(QHostAddress::Any,1234))
    {
        qDebug()<<"server not started";
    }
    else
    {
        qDebug()<<"server started";
    }
}

MainWindow::~MainWindow()
{   soc->disconnect();
    delete ui;
}
void MainWindow::con_suc()
{
    QMessageBox::information(this,"connection","sucessfull");
    soc=ser->nextPendingConnection();
    connect(soc,SIGNAL(readyRead()),this,SLOT(readclient()));
}
void MainWindow::readclient()
{
    //ui->tableWidget->setSortingEnabled(false);
    int ty=ui->tableWidget->rowCount();
    for(int bb=ty-1;bb>=0;bb--)
        ui->tableWidget->removeRow(bb);
    //qDebug()<<"start reading";
    char buffer[512] = {0};
    soc->read(buffer,soc->bytesAvailable());
    QString string(buffer);
   // qDebug()<<buffer;
    QString req="send information";
      int x=QString::compare(string,req);
      QString th(buffer);
      QStringList tl=th.split(";",QString::SkipEmptyParts);
      qDebug()<<string;
    if(x!=0)
    {
        qDebug()<<"reading";



    QFile ser_fil("test_proj.csv");
    if(ser_fil.open(QIODevice::WriteOnly))
    {
        QTextStream j(&ser_fil);
       int r=tl.count()/4,i,c,k=0;
        for(i=0;i<r;i++,j<<endl)
        {
            ui->tableWidget->insertRow(i);
            for(c=0;c<4;c++)
            {
                ui->tableWidget->setItem(i,c,new QTableWidgetItem(tl[k]));
                j<<tl[k++];
                j<<";";
            }
        }
    }
    ui->tableWidget->setSortingEnabled(true);
    ser_fil.close();
    }
    else
    {
        qDebug()<<"file on request sending";
        QByteArray ba;
        QFile ser_wr_fil("test_proj.csv");
        if(ser_wr_fil.open(QIODevice::ReadOnly))
        {
            QTextStream ser_sen(&ser_wr_fil);
            QString a=ser_sen.readAll();
            ba.append(a);

        }ser_wr_fil.close();
        soc->write(ba);
        soc->waitForBytesWritten(1000);
        //qDebug()<<"file transfer complete";
}
}

