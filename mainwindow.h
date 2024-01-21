#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QCheckBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addTask_clicked();

    void on_Delete_clicked();

    void on_input_returnPressed();

    void on_modify_clicked();
    void loadTasks();
    void saveTasks();
    void applyCheckBoxStyles(QCheckBox *checkBox);
public slots:
    void onTaskWidgetStateChanged(bool checked);

private:
    Ui::MainWindow *ui;
    QListWidget *listWidget;
};
#endif // MAINWINDOW_H
