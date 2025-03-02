#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QMap>

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
    void on_start_clicked();
    void Hide();
    void Button_Choosing();
    void on_Restart_clicked();

private:
    Ui::MainWindow *ui;

    QList<QString> button_pics;
    QList<QPushButton*> buttons;
    QList<int> random_list;
    QMap <QPushButton* , QString> button_pics_storage;
    QSet<int> unique_numbers; // Tekrar etmeyen sayıları sakla

    QPushButton *firstButton = nullptr;
    QPushButton *secondButton = nullptr;

    void Assign_Pics();
    void Win_Check();
    void Crash_Handler();
    void Restart_Game();

    QString firstIconPath;
    QString secondIconPath;
    int failed = 0;
    int matched = 0;


};
#endif // MAINWINDOW_H
