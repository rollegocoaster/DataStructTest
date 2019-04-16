#include "mealreccomendgui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MealReccomendGUI w;
    w.show();

    return a.exec();
}
