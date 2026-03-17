#include <QApplication>
#include <QWidget>
#include <iostream>

int main (int argc, char** argv)
{
  std::cout << "Program start" << std::endl;

    QApplication app(argc, argv);

    std::cout << "QApplication created" << std::endl;

    QWidget window;
    window.resize(400, 300);
    window.setWindowTitle("Qt Event Loop Demo");

    window.show();

    int result = app.exec();

    return result;
}

