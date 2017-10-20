#include "model.h"
#include <QtGlobal>
#include <QTime>


Model::Model(QObject *parent) : QObject(parent)
{
	sequence = QVector<int>(10);
    position = 0;
    timer.setInterval(1000);

    //This causes the next button in the pattern to be sent every time the timer ticks.
    connect(&timer, SIGNAL(timeout()), this, SLOT(sendNextButton()));
}

//when the start button is pressed
void Model::startButtonPressed()
{
    position = 0;
    sequence.clear();
	srand(QTime::currentTime().msec());

    //Here we will first make sure the UI is setup for a start of a game. Then it sends back a signal asking to show the pattern.
    emit initializeUi();
}

//When the UI sends a signal asking for the next game pattern this slot adds the next move then starts a timer which will
//send one move per tick.
void Model::recieveGamePattern(){
    timer.setInterval(1000 - position * 50);
    int temp = rand() % 4;
    sequence.push_back(temp);
    position = 0;

    timer.start();
}

//This function sends a signal to the UI to show each move in the pattern. It ends by stopping the timer.
void Model::sendNextButton(){
    if (sequence[position] == 0){
        emit showLeftButton(1000 - position * 50);
    }
    else if (sequence[position] == 1) {
        emit showRightButton(1000 - position * 50);
    }
    else if (sequence[position] == 2){
        emit showTopButton(1000 - position * 50);
    }
    else {
        emit showBottomButton(1000 - position * 50);
    }
    position++;

    if (position == sequence.size()){
        timer.stop();
        position = 0;
        emit beginInput();
    }



}

//This Slot is recieved after the player sends a signal by pressing one of the two gameplay buttons. We verify
//whether it was a correct move and respond accordingly.
void Model::verifyButtonPressed(int buttonNumber){
    //The player successfully input the right button.
    if(sequence[position] == buttonNumber){
        position++;
        emit successfulPlay(position * 1.0 / sequence.size());
    }
    //Player makes a mistake, show the gameOver message and reset the game.
    else{
		emit gameOver(sequence.length());
        emit resetUi();
    }
    //If the entire sequence is input correctly
    if (position == sequence.size()){
        emit initializeUi();
    }

}

//user presses the left button
void Model::leftButtonPressed()
{
    verifyButtonPressed(0);
}
//User presses the right button.
void Model::rightButtonPressed()
{
    verifyButtonPressed(1);
}
//User presses the right button.
void Model::topButtonPressed()
{
    verifyButtonPressed(2);
}
//User presses the right button.
void Model::bottomButtonPressed()
{
    verifyButtonPressed(3);
}

//User presses reset button.
void Model::resetButtonPressed()
{
    //Reset the model values.
    position = 0;
    sequence.clear();

    //This stops a AI move if it is currently ongoing.
    if(timer.isActive()){
        timer.stop();
    }

    //Tells the Ui to reset
    emit resetUi();
}

