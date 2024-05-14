#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>// библиотека диалоговых окон работы с файлом
#include <QMessageBox>
#include <QCloseEvent>// библиотека закрытия окон

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_open_triggered();

    void on_action_saveAs_triggered();

    void on_action_exit_triggered();

    void closeEvent(QCloseEvent * event);

    void on_action_save_triggered();

    void on_action_create_triggered();

    void on_textEdit_textChanged();

private:
    Ui::MainWindow *ui;

    bool fileSave;
    bool isNewFile;
    QString fileName;//имя файла

};

#endif // MAINWINDOW_H
