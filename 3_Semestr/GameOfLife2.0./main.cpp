#include "Window.h"
#include "Model.h"
#include "Controller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model model;
    Window window( &model );
    Controller controller( &model, &window );
    window.show();

    return a.exec();
}
