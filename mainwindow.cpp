#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "model.h"


MainWindow::MainWindow(Model& model, QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui ->resetButton->setEnabled(false);
	ui->leftButton->setEnabled(false);
	ui->rightButton->setEnabled(false);
	ui->topButton->setEnabled(false);
	ui->bottomButton->setEnabled(false);
	ui->progressBar->setValue(0);

    timer.setInterval(1000);

	//code to set up the color of buttons and such
	ui->leftButton->setStyleSheet( QString("QPushButton {background-color: rgb(200,50,50);} QPushButton:pressed {background-color: rgb(255,150,150);}"));
	ui->rightButton->setStyleSheet( QString("QPushButton {background-color: rgb(17, 41, 255);} QPushButton:pressed {background-color: rgb(91, 154, 255);}"));
    ui->topButton->setStyleSheet( QString("QPushButton {background-color: rgb(60, 140, 100);} QPushButton:pressed {background-color: rgb(80, 200, 100);}"));
    ui->bottomButton->setStyleSheet( QString("QPushButton {background-color: rgb(255, 255, 0);} QPushButton:pressed {background-color: rgb(255, 255, 200);}"));

	//connections
    connect(&model, SIGNAL(initializeUi()), this, SLOT(setup()));
    connect(&model, SIGNAL(resetUi()), this, SLOT(resetUi()));
    connect(&model, SIGNAL(successfulPlay(double)), this, SLOT(updateProgressBar(double)));
    connect(&model, SIGNAL(beginInput()), this, SLOT(enableButtons()));
    connect(&model, SIGNAL(showLeftButton(int)), this, SLOT(pressLeftButton(int)));
    connect(&model, SIGNAL(showRightButton(int)), this, SLOT(pressRightButton(int)));
    connect(&model, SIGNAL(showTopButton(int)), this, SLOT(pressTopButton(int)));
    connect(&model, SIGNAL(showBottomButton(int)), this, SLOT(pressBottomButton(int)));
	connect(&model, SIGNAL(gameOver(int)), this, SLOT(displayMessage(int)));

    connect(ui->startButton, &QPushButton::clicked, &model, &Model::startButtonPressed);
    connect(ui->leftButton, &QPushButton::clicked, &model, &Model::leftButtonPressed);
    connect(ui->rightButton, &QPushButton::clicked, &model, &Model::rightButtonPressed);
    connect(ui->topButton, &QPushButton::clicked, &model, &Model::topButtonPressed);
    connect(ui->bottomButton, &QPushButton::clicked, &model, &Model::bottomButtonPressed);
    connect(ui->resetButton, &QPushButton::clicked, &model, &Model::resetButtonPressed);

    connect(this, SIGNAL(recieveGamePattern()), &model, SLOT(recieveGamePattern()));

    connect(&timer, SIGNAL(timeout()), this, SLOT(unpressButtons()));

}

void MainWindow::setup(){
	//First we need to change the buttons.
	ui->startButton->setEnabled(false);
	ui->resetButton->setEnabled(true);
	ui->leftButton->setEnabled(false);
	ui->rightButton->setEnabled(false);
	ui->topButton->setEnabled(false);
	ui->bottomButton->setEnabled(false);
	//also need to reset progress bar.
	emit recieveGamePattern();
}

//If you hit the reset button then we reset the buttons and the gamestate.
void MainWindow::resetUi(){
	ui->startButton->setEnabled(true);
	ui->resetButton->setEnabled(false);
	ui->leftButton->setEnabled(false);
	ui->rightButton->setEnabled(false);
	ui->topButton->setEnabled(false);
	ui->bottomButton->setEnabled(false);
	ui->progressBar->setValue(0);
}


void MainWindow::updateProgressBar(double progress){
    ui->progressBar->setValue(progress*100);

}

void MainWindow::displayMessage(int round){
	messageBox.setText(QStringLiteral("You messed up! You made it to round %1. Try again using the start button.").arg(round));
    messageBox.exec();
}


void MainWindow::enableButtons(){
    ui->leftButton->setEnabled(true);
    ui->rightButton->setEnabled(true);
    ui->topButton->setEnabled(true);
    ui->bottomButton->setEnabled(true);
}


//simulates pressing the left button, for AI's turn
void MainWindow::pressLeftButton(int length)
{
	timer.setInterval(length/(4));
    ui->leftButton->setStyleSheet("background-color: rgb(255,150,150);");
    timer.start();

}

//simulates pressing the right button, for AI's turn
void MainWindow::pressRightButton(int length)
{
	timer.setInterval(length/(4));
    ui->rightButton->setStyleSheet("background-color: rgb(91, 154, 255);");
    timer.start();

}
//simulates pressing the top button, for AI's turn
void MainWindow::pressTopButton(int length)
{
	timer.setInterval(length/(4));
    ui->topButton->setStyleSheet("background-color: rgb(80, 200, 100);");
    timer.start();

}
//simulates pressing the bottom button, for AI's turn
void MainWindow::pressBottomButton(int length)
{
	timer.setInterval(length/4);
    ui->bottomButton->setStyleSheet("background-color: rgb(255, 255, 200);");
    timer.start();

}

void MainWindow::unpressButtons()
{
    ui->leftButton->setStyleSheet( QString("QPushButton {background-color: rgb(200,50,50);} QPushButton:pressed {background-color: rgb(255,150,150);}"));
    ui->rightButton->setStyleSheet( QString("QPushButton {background-color: rgb(17, 41, 255);} QPushButton:pressed {background-color: rgb(91, 154, 255);}"));
    ui->topButton->setStyleSheet( QString("QPushButton {background-color: rgb(60, 140, 100);} QPushButton:pressed {background-color: rgb(80, 200, 100);}"));
    ui->bottomButton->setStyleSheet( QString("QPushButton {background-color: rgb(255, 255, 0);} QPushButton:pressed {background-color: rgb(255, 255, 200);}"));
    timer.stop();

}


MainWindow::~MainWindow()
{
    delete ui;
}

