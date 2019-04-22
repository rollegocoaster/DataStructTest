#ifndef RECCOMENDATIONSGUI_H
#define RECCOMENDATIONSGUI_H

#include <QWidget>
#include <QPicture>
#include <QtNetwork>
//#include "mealreccomendgui.h"

struct preferences{
    std::vector<std::string>positiveIngredients;

    std::vector<std::string>negativeIngredients;
    std::vector<int>negativeIngredientsWeight; // if 0 use default
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
class reccomendationsGUI;
}

class reccomendationsGUI : public QWidget
{
    Q_OBJECT

public:
    explicit reccomendationsGUI(QWidget *parent, QPalette* customPalette);
    ~reccomendationsGUI();

    void showReccomendations(std::string); //

private slots:
    void on_back_clicked();
    void useInfo(QNetworkReply*);

    void on_pushButton_3_clicked();

private:
    QByteArray requestOutput;
    Ui::reccomendationsGUI *ui;
    QNetworkReply* currentReply;
    QNetworkAccessManager* networkManager;
    QNetworkRequest* request;
    QString url;
    QUrl TheURL;
    QPixmap image;
    bool recipeShown = false;
    QJsonDocument json;
    QJsonObject object;
    QJsonArray info;
};

#endif // RECCOMENDATIONSGUI_H
