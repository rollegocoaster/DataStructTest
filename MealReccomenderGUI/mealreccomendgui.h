#ifndef MEALRECCOMENDGUI_H
#define MEALRECCOMENDGUI_H

#include <QMainWindow>
#include <QPushButton>
#include <QPalette>
#include <QGradient>
#include <string>
#include <vector>
#include <QTimer>

struct preferences{
    std::vector<std::string>positiveIngredients;
    std::vector<std::string>negativeIngredients;
    std::string foodStylePositive;
    std::string foodStyleNegative;
    std::string regionPositive;
    std::string regionNegative;
    int recipeComplexity; // if -1 user has no preference

    preferences(){
        recipeComplexity = -1;
        foodStylePositive = foodStyleNegative = "";
        regionPositive = regionNegative = "";

    }
};







namespace Ui {
class MealReccomendGUI;
}


class MealReccomendGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit MealReccomendGUI(QWidget *parent = nullptr);
    ~MealReccomendGUI();
    preferences *UserPreferences;

signals:
    void timeOut();
    //void valueChanged();



private slots:
    void on_Generate_clicked();
   // void reformat();

    void on_add_Ingredient_clicked();

    void on_deletePositive_clicked();

    void on_deleteNegative_clicked();

protected:
    //void timerEvent(QTimerEvent *event);
    //void resizeEvent(QResizeEvent *event);

private:
    Ui::MealReccomendGUI *ui;
    QPushButton *ui_generate;
    QPalette Cpalette;
    QLinearGradient *BackgroundGradient;
    QLinearGradient *ButtonGradient;


    /*Color palette
    lightBlue: #0597F2, rgb(5,151,242)
    darkBlue: #03658C, rgb(3,101,140)
    lime-mint: #05F283, rgb(5,242,131)
    darker-mint: #4BBF89, rgb(75,191,137)
    orange: #F27B13, rgb(242,123,19)

    background: rgb(110, 168, 39);
    real light green: rgb(144, 245, 19);
    background: rgb(54, 88, 199);
    background: rgb(168, 39, 5);
    background: rgb(194, 68, 35);

    */

};

#endif // MEALRECCOMENDGUI_H
