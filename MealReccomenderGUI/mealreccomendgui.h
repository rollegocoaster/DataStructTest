#ifndef MEALRECCOMENDGUI_H
#define MEALRECCOMENDGUI_H

#include <QMainWindow>
#include <QPushButton>
#include <QPalette>
#include <QGradient>
#include <string>
#include <vector>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QScriptValue>
#include "reccomendationsgui.h"

//preferences are in reccomendationsgui.h

const int NUMBER_OF_RECIPES_ADDED = 50;


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

public slots:

    void MealDBResult(QNetworkReply* reply);

private slots:

    void updateInfo();

    void on_Generate_clicked();
   // void reformat();

    void on_add_Ingredient_clicked();

    void on_deletePositive_clicked();

    void on_deleteNegative_clicked();

    void on_add_neg_ingredient_clicked();

    void on_reset_clicked();

    void on_regionalFood_currentIndexChanged(int index);

    void on_food_type_currentIndexChanged(int index);

    void on_negFood_type_currentIndexChanged(int index);

    void on_complexity_valueChanged(int arg1);

    void on_ingredientIngoreSlider_valueChanged(int value);

protected:

    //void resizeEvent(QResizeEvent *event);

private:
    Ui::MealReccomendGUI *ui;
    QPushButton *ui_generate;
    QPalette Cpalette;
    QLinearGradient *BackgroundGradient;
    QLinearGradient *ButtonGradient;
    double fontResize = 0;
    bool resetConfirmed = false;
    reccomendationsGUI* window2;
    QNetworkReply* currentReply;
    QNetworkAccessManager* networkManager;
    //QList<QScriptValue>categories;
    QNetworkRequest *request;
    QUrl *theMealDB;
    void getFromMealDB();
    std::vector<std::string>categories;
    std::vector<std::string>regions;
    int inputsAdded = 0;
    std::string testingReccomendation;
    QTimer timer;

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
