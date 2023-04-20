#include "calculator.h"
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>


Calculator::Calculator(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	this->setFixedSize(500, 500);


	QLabel* show_label = new QLabel(this);
	show_label->setFixedSize(400, 150);
	show_label->setStyleSheet("QLabel { border: 1px solid #000000; padding: 5px; }");
	show_label->move(40, 20);
	show_label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);


	QLabel* label = new QLabel(this);
	label->setFixedSize(200, 200);
	label->move(90, 230);

	// 创建栅格布局
	QGridLayout* gridLayout = new QGridLayout;
	auto SetBtnToLabel = [=](int row, int col, int max_col){
		QPushButton* btn = new QPushButton(this);
		btn->setText(QString::number(row * max_col + col));

		int btn_value = row * max_col + col;
		connect(btn, &QPushButton::clicked, [=](){
			real_value *= 10; 
			real_value += btn_value; 
			show_label->setText(QString::number(real_value));
		});

		gridLayout->addWidget(btn, row, col);
	};

	SetBtnToLabel(0, 0, 3);
	SetBtnToLabel(0, 1, 3);
	SetBtnToLabel(0, 2, 3);
	SetBtnToLabel(1, 0, 3);
	SetBtnToLabel(1, 1, 3);
	SetBtnToLabel(1, 2, 3);
	SetBtnToLabel(2, 0, 3);
	SetBtnToLabel(2, 1, 3);
	SetBtnToLabel(2, 2, 3);
	SetBtnToLabel(3, 0, 3);

	QVBoxLayout* v_layout = new QVBoxLayout;
	auto AddAlgorimBtn = [=](const QString algoim){
		QPushButton* btn = new QPushButton(this);
		btn->setText(algoim);

		connect(btn, &QPushButton::clicked, [=](){



			int final_value = 0;
			if (1 == algorithm)
			{
				final_value = real_value + save_value;
				save_value = final_value;
			}
			else if (2 == algorithm)
			{
				final_value = save_value - real_value;
				save_value = final_value;
			}
			else if (3 == algorithm)
			{
				final_value = save_value * real_value;
				save_value = final_value;
			}
			else if (4 == algorithm)
			{
				final_value = save_value / real_value;
				save_value = final_value;
			}

			if (algoim == "C")
			{
				show_label->setText("");
				save_value = 0;
				real_value = 0;
				algorithm = 0;
			}
			else
			{
				if (0 != algorithm)
				{
					show_label->setText(QString::number(final_value));
				}
				if (5 == algorithm)
				{
					save_value = 0;
					real_value = 0;
					algorithm = 0;
				}
			}

			if (0 == algorithm)
			{
				save_value = real_value;
			}
			if (algoim == "+")
			{
				algorithm = 1;
			}
			else if (algoim == "-")
			{
				algorithm = 2;
			}
			else if (algoim == "*")
			{
				algorithm = 3;
			}
			else if (algoim == "/")
			{
				algorithm = 4;
			}
			else if (algoim == "=")
			{
				algorithm = 5;
			}


			real_value = 0;
		});

		v_layout->addWidget(btn);
	};


	QLabel* algroim_label = new QLabel(this);
	algroim_label->setFixedSize(120, 200);
	algroim_label->setStyleSheet("QLabel { border: 1px solid #000000; padding: 5px; }");
	algroim_label->move(330, 230);
	AddAlgorimBtn("C");
	AddAlgorimBtn("+");
	AddAlgorimBtn("-");
	AddAlgorimBtn("*");
	AddAlgorimBtn("/");
	AddAlgorimBtn("=");
	algroim_label->setLayout(v_layout);
	label->setLayout(gridLayout);





}

Calculator::~Calculator()
{

}
