#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QTime>
#include <QList>
#include <QRandomGenerator>
#include <QPixmap>
#include <QPushButton>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QRect screenGeometry = screen()->geometry();  // Ekranın boyutlarını al
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);

    ui->Restart->hide();
    ui->label->hide();
    ui->false_counter->hide();

    button_pics = { ":/new/pics/pictures/1.jpg", ":/new/pics/pictures/1.jpg",
                   ":/new/pics/pictures/2.jpg", ":/new/pics/pictures/2.jpg",
                   ":/new/pics/pictures/3.jpg", ":/new/pics/pictures/3.jpg",
                   ":/new/pics/pictures/4.jpg", ":/new/pics/pictures/4.jpg",
                   ":/new/pics/pictures/5.jpg", ":/new/pics/pictures/5.jpg" };

    buttons = { ui->pic_button_1, ui->pic_button_2,
               ui->pic_button_3, ui->pic_button_4,
               ui->pic_button_5, ui->pic_button_6,
               ui->pic_button_7, ui->pic_button_8,
               ui->pic_button_9, ui->pic_button_10 };

    connect(ui->pic_button_1, SIGNAL(clicked(bool)), this, SLOT(Button_Choosing()));
    connect(ui->pic_button_2, SIGNAL(clicked(bool)), this, SLOT(Button_Choosing()));
    connect(ui->pic_button_3, SIGNAL(clicked(bool)), this, SLOT(Button_Choosing()));
    connect(ui->pic_button_4, SIGNAL(clicked(bool)), this, SLOT(Button_Choosing()));
    connect(ui->pic_button_5, SIGNAL(clicked(bool)), this, SLOT(Button_Choosing()));
    connect(ui->pic_button_6, SIGNAL(clicked(bool)), this, SLOT(Button_Choosing()));
    connect(ui->pic_button_7, SIGNAL(clicked(bool)), this, SLOT(Button_Choosing()));
    connect(ui->pic_button_8, SIGNAL(clicked(bool)), this, SLOT(Button_Choosing()));
    connect(ui->pic_button_9, SIGNAL(clicked(bool)), this, SLOT(Button_Choosing()));
    connect(ui->pic_button_10, SIGNAL(clicked(bool)), this, SLOT(Button_Choosing()));

    for (int i = 0; i < buttons.length(); i++) {
        buttons[i]->hide();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_clicked()
{
    ui->Restart->show();
    ui->start->hide();
    ui->label->show();
    ui->false_counter->show();

    for (int i = 0; i < buttons.length(); ++i) {
        buttons[i]->show();
    }

    Assign_Pics();
}



void MainWindow::Button_Choosing()
{
    QPushButton* clickedbutton = (QPushButton*)sender();

    if (!clickedbutton)
        return;

    if (!firstButton) {
        // İlk buton seçildi
        firstButton = clickedbutton;

        firstIconPath = button_pics_storage[firstButton];
        firstButton->setIcon(QIcon(firstIconPath));
    }
    else if (firstButton == clickedbutton) {
        return;
    }
    else {
        // İkinci buton seçildi
        secondButton = clickedbutton;

        QString secondIconPath = button_pics_storage[secondButton];
        secondButton->setIcon(QIcon(secondIconPath));

        Crash_Handler();

        if (firstIconPath == secondIconPath) {
            matched++;

            firstButton->setEnabled(false);
            secondButton->setEnabled(false);

            firstButton = nullptr;
            secondButton = nullptr;

            for(QPushButton* button : buttons){
                button->setEnabled(true);
            }

            if(matched == 5){
                QMessageBox win_message;
                win_message.setText("Tebrikler! Oyunu kazandınız.");
                win_message.setStandardButtons(QMessageBox::Ok);
                win_message.setDefaultButton(QMessageBox::Ok);

                if (win_message.exec() == QMessageBox::Ok) {
                    Restart_Game();
                }
            }

        } else {
            failed++;
            ui->false_counter->setText(QString::number(failed));
            QTimer::singleShot(1000, this, [=]() {
                firstButton->setIcon(QIcon(":/new/pics/pictures/6.jpg"));
                secondButton->setIcon(QIcon(":/new/pics/pictures/6.jpg"));
                firstButton->setEnabled(true);
                secondButton->setEnabled(true);

                for(QPushButton* button : buttons){
                    button->setEnabled(true);
                }

                firstButton = nullptr; // Seçimleri sıfırlayalım
                secondButton = nullptr;
            });
        }
    }
}

void MainWindow::Hide()
{
    QSize pic_size;
    pic_size.setHeight(80);
    pic_size.setWidth(100);
    for (int i = 0; i < buttons.length(); ++i) {
        buttons[i]->setIcon(QIcon(":/new/pics/pictures/6.jpg"));
        buttons[i]->setIconSize(pic_size);
    }
}


void MainWindow::on_Restart_clicked()
{
    Restart_Game();
}

void MainWindow::Assign_Pics()
{
    QSize pic_size;
    pic_size.setHeight(100);
    pic_size.setWidth(80);

    std::shuffle(button_pics.begin(), button_pics.end(), std::default_random_engine(QTime::currentTime().msec()));

    // Butonlara QMap'e ata
    for (int i = 0; i < buttons.size(); ++i) {
        QPixmap pixmap(button_pics[i]);
        button_pics_storage[buttons[i]]=button_pics[i];
        buttons[i]->setIcon(pixmap);
        buttons[i]->setIconSize(pic_size);
    }

    QTimer::singleShot(2000,this,SLOT(Hide()));
}

void MainWindow::Crash_Handler()
{
    for( QPushButton* button : buttons){
        button->setEnabled(false);
    }


}

void MainWindow::Restart_Game()
{
    for (int i = 0; i < buttons.length(); ++i) {
        buttons[i]->setEnabled(true);
    }
    Assign_Pics();
    matched =0;
    failed=0;
    ui->false_counter->setText(QString::number(failed));
}


