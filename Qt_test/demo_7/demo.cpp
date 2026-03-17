#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <iostream>

void onButtonClicked(){
  std::cout<< "Button clicked" << std::endl;
}

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QWidget window;
  window.resize(400, 300);
  window.setWindowTitle("My First Qt Window");

  QPushButton* button = new QPushButton("Click me");
  
  QVBoxLayout* layout = new QVBoxLayout();
  layout->addWidget(button);
  window.setLayout(layout);

  QObject::connect(button, &QPushButton::clicked, //触发函数
                     &onButtonClicked);

  window.show();

  return app.exec();
}