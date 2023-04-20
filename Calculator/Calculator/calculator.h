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
	unsigned long long  save_value = 0;

	unsigned long long real_value = 0;
	int algorithm = 0;//1--+, 2---, 3--*, 4--/

private:
	Ui::CalculatorClass ui;
};

#endif // CALCULATOR_H
