#ifndef PRODUCT_H
#define PRODUCT_H

#include <QMainWindow>

#include <QObject>
#include<QTcpSocket>
#include<QTcpServer>
#include<QDebug>
#include<QTimer>


namespace Ui {
class product;
}

class product : public QMainWindow
{
    Q_OBJECT

public:
    explicit product(QWidget *parent = 0);
    ~product();
    QTcpSocket *socket;
    QTimer *timer;
     void Connect();
//    void Connect_aa();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();
    void addproduct(int i);
    void deletion();
    void keyPressEvent(QKeyEvent *e);
    void sort11();
    void remove();

    //void Connect();
    void Connect_aa();

    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void on_tableWidget_clicked(const QModelIndex &index);

    void on_tableWidget_customContextMenuRequested(const QPoint &pos);

    //void on_tableWidget_cellClicked(int row, int column);

    //void on_tableWidget_doubleClicked(const QModelIndex &index);

//    void on_tableWidget_entered(const QModelIndex &index);

  //  void on_tableWidget_pressed(const QModelIndex &index);

    //void on_tableWidget_itemClicked(QTableWidgetItem *item);

    //void on_tableWidget_cellEntered(int row, int column);



    void on_tableWidget_doubleClicked(const QModelIndex &index);

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::product *ui;
};

#endif // PRODUCT_H
