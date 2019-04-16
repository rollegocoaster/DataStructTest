#ifndef RECCOMENDATIONS_H
#define RECCOMENDATIONS_H

#include <QWidget>
#include <string>
#include <QCloseEvent>

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
class reccomendations;
}

class reccomendations : public QWidget
{
    Q_OBJECT

public:
    explicit reccomendations(QWidget *parent = nullptr);
    ~reccomendations();
    void sendInformation(preferences*);

private slots:


    void on_backButton_clicked();

private:
    Ui::reccomendations *ui;
};

#endif // RECCOMENDATIONS_H
