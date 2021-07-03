#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QFile"
#include "QFileDialog"
#include "QDebug"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonValue"
#include "QJsonArray"
#include "QTableWidgetItem"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList title_col;
    ui->tableWidget->setColumnCount(3);
    title_col << "Keys" << "Values" << "Results";
    ui->tableWidget->setHorizontalHeaderLabels(title_col);
    //自动调整宽度缩进
    ui->tableWidget->resizeColumnsToContents();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//主文件
void MainWindow::on_openNewButton_clicked()
{
    QString filename1 = QFileDialog::getOpenFileName(
                this,
                "TextEditor - Open",
                "",
                "Json File (*.json);;All Files (*.*)");
    curOpenFile = filename1;
    if(!filename1.isEmpty())
    {
        load_new_File();
    }
    else
    {
        return;
    }
}

void MainWindow::load_new_File()
{
    QString val;
    QFile file(curOpenFile);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Can not open file";
        return;
    }
    val = file.readAll();

    file.close();

    QJsonDocument document = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject object = document.object();

    ui->tableWidget->setRowCount(0);

    //循环读取所以level的key
    read_new(object);
    //qDebug() << item_count;
    ui->tableWidget->resizeColumnsToContents();
}

//循环读取所有level的key
void MainWindow::read_new(QJsonObject &obj)
{
    QJsonObject::iterator i;
    for(i = obj.begin(); i != obj.end(); ++i)
    {
        item_count++;

        key =i.key();
        value = obj.value(i.key()).toString();

        //set the table column by column
        if(!i.value().isObject())
        {
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            int temp = ui->tableWidget->rowCount() - 1;
            ui->tableWidget->setItem(temp, Keys, new QTableWidgetItem(key));
            ui->tableWidget->setItem(temp, Values, new QTableWidgetItem(value));
        }

        QJsonObject inner = i.value().toObject();
        read_new(inner);
    }
}

//输入参考/旧文件
void MainWindow::on_openTransButton_clicked()
{
    QString filename1 = QFileDialog::getOpenFileName(
                this,
                "TextEditor - Open",
                "",
                "Json File (*.json);;All Files (*.*)");
    curOpenFile = filename1;
    if(!filename1.isEmpty())
    {
        load_old_File();
    }
    else
    {
        return;
    }
}

void MainWindow::load_old_File()
{
    QString val;
    QFile file(curOpenFile);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Can not open file";
        return;
    }
    val = file.readAll();

    file.close();

    QJsonDocument document = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject object = document.object();

    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        QString t_value = searchingValueFromKey(object, ui->tableWidget->item(i,0)->text());
        //qDebug() << t_value;
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(t_value));
    }

    ui->tableWidget->resizeColumnsToContents();
}

QString MainWindow::searchingValueFromKey(const QJsonObject &obj, QString t_key)
{
    QString result = "Nothing was been Found";
/*
    if(t_key=="Aimbot")
    {
        qDebug()<<"Searching bot";
    }
*/
    if(obj.contains(t_key))
    {
        if(!obj[t_key].isObject())
        {
            result = obj[t_key].toString();
            /*
            if(t_key=="Aimbot")
            {
                qDebug()<<"Found result: "<<result;
            }
            */
            return result;
        }
    }
    //QJsonObject::iterator i;
    for(auto i = obj.constBegin(); i != obj.constEnd(); ++i)
    {
        if(i.value().isObject())
        {
            QJsonObject inner = i.value().toObject();
            result = searchingValueFromKey(inner, t_key);
            //确认key找到对应值
            if(result != "Nothing was been Found")
            {
                /*
                if(t_key=="Aimbot")
                {
                    qDebug()<<"Recursive found: "<<result;
                }
                */
                return result;
            }

        }
    }
    /*
    if(t_key=="Aimbot")
    {
        qDebug()<<"Returning default result";
    }
    */
    return result;
}

void MainWindow::on_saveButton_clicked()
{
    QString filename1 = QFileDialog::getSaveFileName(
                this,
                "TextEditor - save as",
                "",
                "Json File (*.json);;All Files (*.*)");
    curSaveFile = filename1;
    if(!filename1.isEmpty())
    {
        saveFile();
    }
    else
    {
        return;
    }
}

void MainWindow::saveFile()
{
    //get number of rows in the table

    QFile file(curSaveFile);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(
                    this,
                    "TextEditor",
                    tr("Cannot write file %1.\nError: %2")
                    .arg(curSaveFile)
                    .arg(file.errorString()));
    }
    else
    {
        QTextStream stream(&file);
        //stream << text << endl;
    }

    file.close();
}
