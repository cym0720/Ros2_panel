#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>

int main (int argc, char **argv) {
  QApplication app(argc, argv);
  QWidget window;
  window.resize(400, 300);
  window.setWindowTitle("Calculator");

  QLabel* label_num1 = new QLabel("Enter first number:");
  QLineEdit* input_num1 = new QLineEdit();
  QLabel* label_num2 = new QLabel("Enter second number:");
  QLineEdit* input_num2 = new QLineEdit();
  QPushButton* button_add = new QPushButton("Add");
  QLabel* result = new QLabel("Result: ");

  QVBoxLayout* layout = new QVBoxLayout();

  layout->addWidget(label_num1);
  layout->addWidget(input_num1);
  layout->addWidget(label_num2);
  layout->addWidget(input_num2);
  layout->addWidget(button_add);
  layout->addWidget(result);

  window.setLayout(layout);

  auto add_callback = [&]() {
    int num1 = input_num1->text().toInt();
    int num2 = input_num2->text().toInt();
    int result_add = num1 + num2;
    result->setText(QString::number(result_add));
  };

  QObject::connect(button_add, &QPushButton::clicked, //触发函数
                     add_callback);

  window.show();
  return app.exec();
}