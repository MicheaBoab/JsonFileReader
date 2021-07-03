#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_openNewButton_clicked();

    void on_openTransButton_clicked();

    void on_saveButton_clicked();

    void read_new(QJsonObject &obj);

    QString searchingValueFromKey(const QJsonObject &obj, QString t_key);

private:
    Ui::MainWindow *ui;

    void saveFile();
    void load_new_File();
    void load_old_File();
    int item_count = 0;

    QString curSaveFile;
    QString curOpenFile;
    QString key;
    QString value;

    enum Column
    {
        Keys,Values,Results,
    };
};
#endif // MAINWINDOW_H
