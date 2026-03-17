#include <QApplication>
#include <QWidget>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QWidget window;
    window.resize(300, 200);
    window.setWindowTitle("My First Qt Window");

    window.show();

    return app.exec();
}