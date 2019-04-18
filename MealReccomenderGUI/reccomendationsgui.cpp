#include "reccomendationsgui.h"
#include "ui_reccomendationsgui.h"

reccomendationsGUI::reccomendationsGUI(QWidget *parent, QPalette* customPalette) :
    QWidget(parent),
    ui(new Ui::reccomendationsGUI)
{
    ui->setupUi(this);
    this->setPalette(*customPalette);
    this->update();
}

reccomendationsGUI::~reccomendationsGUI()
{
    delete ui;
}

void reccomendationsGUI::on_back_clicked()
{
    this->hide();
    this->activateWindow();
}


// testing sending preferences
void reccomendationsGUI::preferencesSent(preferences *pref){
    QString text = "              Ingredients:";
    text += '\n';

    for(unsigned int i=0; i<pref->positiveIngredients.size(); i++){
        text += QString::fromStdString(pref->positiveIngredients.at(i));
        text += ",  ";
    }
    text += "\n\n negative ingredients: \n";
    for(unsigned int i=0; i<pref->negativeIngredients.size(); i++){
        text += QString::fromStdString(pref->negativeIngredients.at(i));
        text += ":";
        text += QString::number(pref->negativeIngredientsWeight.at(i));
        text += ",   ";
    }

    ui->outputText->setText(text);
}
