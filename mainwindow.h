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
    //QJsonValue findKey(const QString& key, const QJsonValue& value);

private:
    Ui::MainWindow *ui;

    void saveFile();
    void loadFile();

    QString curSaveFile;
    QString curOpenFile;

    enum Column
    {
        Keys,Values,Results,
    };
};
#endif // MAINWINDOW_H
