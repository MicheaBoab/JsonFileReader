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
        loadFile();
    }
    else
    {
        return;
    }
}

void MainWindow::loadFile()
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

    QJsonObject::iterator i;

    //读取并返回每个level的key
    for(i = object.begin(); i != object.end(); ++i)
    {
        qDebug() << "Object " << i.key();
        if(i.value().isObject())
        {
            if(i.value().isObject())
            {
                qDebug() << "OBJECT " << i.key();
                QJsonObject innerObject = i.value().toObject();
                QJsonObject::iterator j;
                for(j = innerObject.begin(); j != innerObject.end(); j++)
                {
                    qDebug() << "Object " << j.key();
                }
            }
        }
    }
}

//输入参考/旧文件
void MainWindow::on_openTransButton_clicked()
{
/*
    QFile file("地址");
    file.open(QIODevice::ReadOnly);

    if(!file.isOpen())
    {
        qDebug() << "error: couldn't open scratch.json";
        return 0;
    }
    //用findkey找对应key的值
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    qDebug() << "value:" << findKey("treasure", doc.object());
*/
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

/*
//在json文件中自动搜寻特定key并返回特定值
QJsonValue MainWindow::findKey(const QString& key, const QJsonValue& value)
{
    if (value.isObject())
    {
        const QJsonObject obj = value.toObject();
        if (obj.contains(key))
        {
            return obj.value(key);           // return 'early' if object contains key
        }
        for (const auto& value : obj)
        {
            QJsonValue recurse = findKey(key, value);  // call itself, forwarding a value
            if (!recurse.isNull())
            {
                return recurse;              // value found, return 'early'
            }
        }
    }else if (value.isArray())
    {
        for (const auto& value : value.toArray())
        {
            QJsonValue recurse = findKey(key, value);
            if (!recurse.isNull())
            {
                return recurse;
            }
        }
    }
}
*/
