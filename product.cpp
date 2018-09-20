#include "product.h"
#include "ui_product.h"
#include<QFile>
#include<QTextStream>
#include"QDebug"
#include<QTableWidgetItem>
#include<QMessageBox>
#include<string.h>
#include<QKeyEvent>
#include<QDebug>
QString name,value,market,rating;
QString z;
int flag=1,flag1=0,flag2=0,flag3=0;
int no=1,temp=0,no_add=0,addset=0,update=0,up=0,rm=0,rm1=0;
static int cnt=0;
int row;
QString tempdat;



product::product(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::product)
{
    ui->setupUi(this);
    socket =new QTcpSocket(this);
    timer =new QTimer();
    Connect_aa();
    //timer->start(1000);

}

void product::Connect()       //..................connection...sent...got...closed.....
{
 // timer->stop();
  QByteArray t;
  if(socket->waitForConnected(3000))
  {
      socket->waitForBytesWritten(1000);
      socket->waitForReadyRead(3000);
      qDebug()<<"reading"<<socket->bytesAvailable();
      qDebug()<<socket->readAll();

      int i,j;
      int sizerow=ui->tableWidget->rowCount();

      for(i=0;i<sizerow;i++)
      {
          for(j=0;j<4;j++){
              tempdat=ui->tableWidget->item(i,j)->text();
              t.append(tempdat);
              t.append(";");
          }
      }
      socket->write(t);
      socket->waitForBytesWritten(10000);
      socket->disconnect();                           // .....close............

  }
  else
  {
      qDebug()<<"Not Connection!";
  }
}

void product::Connect_aa()
{
 socket->connectToHost("127.0.0.1",1234);
 //connect(socket,SIGNAL(connected()),this,SLOT(Connect()));
  Connect();
}

product::~product()
{  socket->disconnect();
    delete ui;
}


void product::addproduct(int i)//............add data. on table..........
{


    name=ui->lineEdit->text();
    value=ui->lineEdit_2->text();
    market=ui->lineEdit_3->text();
    rating=ui->lineEdit_4->text();

    if((name>="a" && name<="z") || (name>="A" && name<="Z") || (name>="0" && name<="9"))
    {
        if((value>="0" && value<="9"))
        {
           if((market>="0" && market<="9"))
           {
               if((rating>="0" && rating<="9")|| (rating=="-"))
                  { addset=1;
    ui->tableWidget->insertRow(i);
    ui->tableWidget->setItem(i,0,new QTableWidgetItem(name));
    ui->tableWidget->setItem(i,1,new QTableWidgetItem(value));
    ui->tableWidget->setItem(i,2,new QTableWidgetItem(market));
    ui->tableWidget->setItem(i,3,new QTableWidgetItem(rating));

    return;
        }
    else
    { ui->label_5->setText("Enter a Credit Rating in Float");
    }}
    else
    { ui->label_5->setText("Enter a Market Capital in Float");
    }}
    else
    { ui->label_5->setText("Enter a Volume in Integer");
    }}
    else
    { ui->label_5->setText("Enter a Product Name");
    }
}



void product::on_pushButton_clicked()   //..........add data..........
{

  int i=cnt;
  addproduct(i);
if(addset){
  cnt++;
ui->label_5->setText("");
ui->lineEdit->clear();
ui->lineEdit_2->clear();
ui->lineEdit_3->clear();
ui->lineEdit_4->clear();
QMessageBox::about(this,"Add","Add successfully");
if(no==1)
{
    temp=1;
    no_add++;
    up=0;

}
flag=0;
flag1=1;
flag2=1;
}
}

void product::on_pushButton_3_clicked() //...........save data..............
{   if(up)
    {  int m=0; flag1=1,flag=0,temp=0;
       m= ui->tableWidget->rowCount();
        int i,j;
        QFile f("aa1.csv");
        f.open(QIODevice::WriteOnly);
        QTextStream z(&f);
        for(i=0;i<m;i++)
        {
            for(j=0;j<4;j++)
            {
                z<<ui->tableWidget->item(i,j)->text();
                z<<";";
            }
                   z<<"\n";
        } f.close();
        up=0;
        QMessageBox::about(this,"Add","Save Successfully");

    }
    else{
        if(temp)
    {   //temp=0;
        int i,j;
        QFile f("aa1.csv");
        f.open(QIODevice::Append);
        QTextStream z(&f);
        for(i=0;i<cnt;i++)
        {
            for(j=0;j<4;j++)
            {
                z<<ui->tableWidget->item(i,j)->text();
                z<<";";
            }
                   z<<"\n";
        } f.close();
        QMessageBox::about(this,"Add","Save Successfully");

    }
    else{
    if(flag2){
    QFile f("aa1.csv");
    f.open(QIODevice::Append);
    QTextStream z(&f);
    z<<name;
    z<<";";
    z<<value;
    z<<";";
    z<<market;
    z<<";";
    z<<rating;
    z<<"\n";
    QMessageBox::about(this,"Add","Save Successfully");
    f.close();
}
    }}



}

void product::on_pushButton_5_clicked()   //..........show data...............
{
    if(rm){remove();}
    int w=0,j,x;
        no=0;
   if(temp){
           { QFile f("aa1.csv");
       f.open(QIODevice::ReadOnly);
       QTextStream z(&f);
       while(!z.atEnd())
       {
      QString v=z.readLine();
      QStringList l=v.split(";");
       w++;
       }f.close();
       }
     x=w-no_add;
     for(j=0;j<x;j++)
     {
        ui->tableWidget->insertRow(j);
       }
       int i=0;
       QFile f("aa1.csv");
       f.open(QIODevice::ReadOnly);
       QTextStream z(&f);
       while(!z.atEnd())
       {
      QString v=z.readLine();
      QStringList l=v.split(";");

      ui->tableWidget->setItem(i,0,new QTableWidgetItem(l[0]));
      ui->tableWidget->setItem(i,1,new QTableWidgetItem(l[1]));
      ui->tableWidget->setItem(i,2,new QTableWidgetItem(l[2]));
      ui->tableWidget->setItem(i,3,new QTableWidgetItem(l[3]));
       i++;
       }
       f.close();
       temp=0;
       no_add=0;
       flag1=0;
       flag=0;
       }

   else {  if(flag1){
         int i=0;
        QFile f("aa1.csv");
        f.open(QIODevice::ReadOnly);
        QTextStream z(&f);
        while(!z.atEnd())
        {
       QString v=z.readLine();
       QStringList l=v.split(";");
       ui->tableWidget->setItem(i,0,new QTableWidgetItem(l[0]));
       ui->tableWidget->setItem(i,1,new QTableWidgetItem(l[1]));
       ui->tableWidget->setItem(i,2,new QTableWidgetItem(l[2]));
       ui->tableWidget->setItem(i,3,new QTableWidgetItem(l[3]));
        i++;
        }f.close();
        flag=0;
        flag1=0;
        }

   if(flag) {
    int i=0;
    QFile f("aa1.csv");
    f.open(QIODevice::ReadOnly);
    QTextStream z(&f);
    while(!z.atEnd())
    {
   QString v=z.readLine();
   QStringList l=v.split(";");
   ui->tableWidget->insertRow(i);
   ui->tableWidget->setItem(i,0,new QTableWidgetItem(l[0]));
   ui->tableWidget->setItem(i,1,new QTableWidgetItem(l[1]));
   ui->tableWidget->setItem(i,2,new QTableWidgetItem(l[2]));
   ui->tableWidget->setItem(i,3,new QTableWidgetItem(l[3]));
    i++;
   }
   f.close();flag=0;flag1=0;
} }
}


void product::on_pushButton_2_clicked()  //...............update data...........
{
    row=ui->tableWidget->currentRow();

    name=ui->lineEdit->text();
    value=ui->lineEdit_2->text();
    market=ui->lineEdit_3->text();
    rating=ui->lineEdit_4->text();

    ui->tableWidget->setItem(row,0,new QTableWidgetItem(name));
    ui->tableWidget->setItem(row,1,new QTableWidgetItem(value));
    ui->tableWidget->setItem(row,2,new QTableWidgetItem(market));
    ui->tableWidget->setItem(row,3,new QTableWidgetItem(rating));

    flag1=1;
    temp=1;
    up=1;
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();

}

void product::on_tableWidget_customContextMenuRequested(const QPoint &pos) //.....delete row......
{
    QMenu *myMenu=new QMenu(this);
    QAction* deleteaction =new QAction("Delete",this);
    connect(deleteaction,SIGNAL(triggered(bool)),SLOT(deletion()));


    QAction* sortaction =new QAction("Assending",this);
    connect(sortaction,SIGNAL(triggered(bool)),SLOT(sort11()));



    myMenu->addAction(deleteaction);
    myMenu->addAction(sortaction);
    myMenu->exec(QCursor::pos());

}
void product::deletion()  //...............deletion function...........
{
    row=ui->tableWidget->currentRow();

    int j;
       QFile f("recyclebin.csv");
       f.open(QIODevice::Append);
       QTextStream z(&f);

       for(j=0;j<4;j++)
       {
           z<<ui->tableWidget->item(row,j)->text();
           z<<";";
       }
              z<<"\n";

    ui->tableWidget->removeRow(row);
    flag1=1;
    temp=1;
    up=1;
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
}



void product::sort11() //............sort data.............
{

    ui->tableWidget->sortItems(0);

}

void product::keyPressEvent(QKeyEvent *e) //........enter a key............
{
    int kk,k;
    k=char(e->key());
    kk=k-48;
    if(kk==-44)
    {
        row=ui->tableWidget->currentRow();
        if(0<row)
        {
            name=ui->tableWidget->item(row,0)->text();
            ui->lineEdit->setText(name);
            value=ui->tableWidget->item(row,1)->text();
            ui->lineEdit_2->setText(value);
            market=ui->tableWidget->item(row,2)->text();
            ui->lineEdit_3->setText(market);
            rating=ui->tableWidget->item(row,3)->text();
            ui->lineEdit_4->setText(rating);
        }
    }


}



void product::on_tableWidget_doubleClicked(const QModelIndex &index) //.....double click show data......
{
    row=ui->tableWidget->currentRow();
    if(0<row)
    {
        name=ui->tableWidget->item(row,0)->text();
        ui->lineEdit->setText(name);
        value=ui->tableWidget->item(row,1)->text();
        ui->lineEdit_2->setText(value);
        market=ui->tableWidget->item(row,2)->text();
        ui->lineEdit_3->setText(market);
        rating=ui->tableWidget->item(row,3)->text();
        ui->lineEdit_4->setText(rating);
    }
}

void product::on_pushButton_6_clicked()  //.............recyclebin..............
{
    rm=1;
    remove();
    int i=0;
    QFile f("recyclebin.csv");
    f.open(QIODevice::ReadOnly);
    QTextStream z(&f);
    while(!z.atEnd())
    {
   QString v=z.readLine();
   QStringList l=v.split(";");
   ui->tableWidget->insertRow(i);
   ui->tableWidget->setItem(i,0,new QTableWidgetItem(l[0]));
   ui->tableWidget->setItem(i,1,new QTableWidgetItem(l[1]));
   ui->tableWidget->setItem(i,2,new QTableWidgetItem(l[2]));
   ui->tableWidget->setItem(i,3,new QTableWidgetItem(l[3]));
    i++;
   }
    f.close();

}

void product::remove() //...........remove data.........
{
    int j, w=ui->tableWidget->rowCount();

    for(j=w;j>=0;j--)
    {
    ui->tableWidget->removeRow(j);
    }
 flag=1;

}

void product::on_pushButton_7_clicked()  //.......send..on server.........
{
     Connect_aa();
}

void product::on_pushButton_4_clicked()
{

}
