#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QWidget window;
    window.resize(400, 300);
    window.setWindowTitle("QLineEdit Demo");

    QLineEdit input(&window);
    input.move(120,100);
    input.resize(160,30);

    QPushButton button("Send",&window);
    button.move(160,150);

    window.show();

    return app.exec();
}