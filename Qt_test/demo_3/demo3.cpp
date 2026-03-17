#include <QApplication>
#include <QWidget>
#include <QPushButton>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  QWidget window;
  window.resize(400, 300);
  window.setWindowTitle("Qt Button Demo");

  QPushButton button("Click me!");

  button.setParent(&window);
  button.move(100, 100);

  window.show();
  return app.exec();
}