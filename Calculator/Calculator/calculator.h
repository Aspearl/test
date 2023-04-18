#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QtWidgets/QMainWindow>
#include "ui_calculator.h"

class Calculator : public QMainWindow
{
	Q_OBJECT

public:
	Calculator(QWidget *parent = 0);
	~Calculator();

private:
	Ui::CalculatorClass ui;
};

#endif // CALCULATOR_H
