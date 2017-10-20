#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QVector>
#include <QTimer>

class Model : public QObject
{
	Q_OBJECT
public:
	explicit Model(QObject *parent = nullptr);

signals:

	void setEnabled(std::string buttonName, bool enabled);
    void resetUi();
    void initializeUi();
    void beginInput();
    void endInput();
    void successfulPlay(double progress);
	void gameOver(int round);

	void setEnabled(int buttonNumber, bool enabled);

    void showLeftButton(int);
    void showRightButton(int);
    void showTopButton(int);
    void showBottomButton(int);

public slots:
	void startButtonPressed();

	void leftButtonPressed();

	void rightButtonPressed();

    void topButtonPressed();

    void bottomButtonPressed();

	void resetButtonPressed();

    void recieveGamePattern();

    void sendNextButton();



private:
	QTimer timer;

    void verifyButtonPressed(int);

	QVector<int> sequence; //sequence of AI button presses

	int position; //keeps track of # of human inputs this turn

};

#endif // MODEL_H
