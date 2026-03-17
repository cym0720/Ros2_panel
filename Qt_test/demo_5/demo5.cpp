#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QWidget window;

  window.resize(400, 300);
  window.setWindowTitle("QLineEdit Demo");

  QLabel label("Input Text:", &window);
  label.move(120, 50);
  label.resize(100, 30);

  QLineEdit input(&window);
  input.move(120,100);

  QPushButton button("Send", &window);
  button.move(160,150);

  window.show();
  return app.exec();
}