#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    videoPlayer = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);
    videoPlayer->setVideoOutput(videoWidget);

    this->setCentralWidget(videoWidget);

    slider = new QSlider(this);

    slider->setOrientation(Qt::Horizontal);

    ui->statusbar->addPermanentWidget(slider);
    ui->statusbar->showMessage("Please select video.");

    connect(videoPlayer,&QMediaPlayer::durationChanged,slider,&QSlider::setMaximum);
    connect(videoPlayer,&QMediaPlayer::positionChanged,slider,&QSlider::setValue);
    connect(slider,&QSlider::sliderMoved,videoPlayer,&QMediaPlayer::setPosition);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open a video","","Video File (*.mp4 *.avi *.ogv)");

    on_actionStop_triggered();

    videoPlayer->setSource(QUrl::fromLocalFile(filename));

    on_actionPlay_triggered();
}

void MainWindow::on_actionPlay_triggered()
{
    videoPlayer->play();
    ui->statusbar->showMessage("Playing");
}

void MainWindow::on_actionPause_triggered()
{
    videoPlayer->pause();
    ui->statusbar->showMessage("Paused...");
}

void MainWindow::on_actionStop_triggered()
{
    videoPlayer->stop();
    ui->statusbar->showMessage("Stopped");
}
