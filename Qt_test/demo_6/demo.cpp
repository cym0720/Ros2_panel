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
  window.setWindowTitle("My First Qt Window");

  QLabel* label = new QLabel("Enter Commend:");
  QLineEdit* input = new QLineEdit();
  QPushButton* button = new QPushButton("Call Service");
  QLabel* result = new QLabel("Result: waiting");

  QVBoxLayout* layout = new QVBoxLayout();
  layout->addWidget(label);
  layout->addWidget(input);
  layout->addWidget(button);
  layout->addWidget(result);

  window.setLayout(layout);

  window.show();

  return app.exec();
}