#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qvector>
#include <QMessageBox>
#include "model.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Model& model, QWidget *parent = 0);
	~MainWindow();


	void setEnabled(std::string buttonName, bool enabled);

	void setEnabled(int buttonNumber, bool enabled);

signals:
    void recieveGamePattern();

    void sendGamePattern(int buttonnumber);

private slots:
    void resetUi();
    void updateProgressBar(double progress);
	void displayMessage(int round);

    void setup();

    void enableButtons();

    void pressLeftButton(int length);
    void pressRightButton(int length);
    void pressTopButton(int length);
    void pressBottomButton(int length);
    void unpressButtons();

private:
    QMessageBox messageBox;
    QTimer timer;
	Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
