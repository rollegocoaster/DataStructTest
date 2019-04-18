#include "mealreccomendgui.h"
#include "ui_mealreccomendgui.h"
#include <QLineEdit>
#include <QString>
#include <string>
#include <QtDebug>
#include <QResizeEvent>

MealReccomendGUI::MealReccomendGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MealReccomendGUI)
{
    ui->setupUi(this);
    this->setMinimumHeight(500);

    Cpalette = this->palette();
    BackgroundGradient = new QLinearGradient(0,0,0,this->height());
    BackgroundGradient->setColorAt(0,QColor(3,104,202));
    BackgroundGradient->setColorAt(1,QColor(3,104,140));

    Cpalette.setBrush(QPalette::Window,*BackgroundGradient);

    ButtonGradient = new QLinearGradient(0,ui->Generate->y(),0,ui->Generate->y()+ui->Generate->height());
    ButtonGradient->setColorAt(.5,QColor(255,207,71));
    ButtonGradient->setColorAt(1, QColor(194,68,35));
    ButtonGradient->setColorAt(0, QColor(194,68,35));

    this->setPalette(Cpalette);
    Cpalette.setBrush(QPalette::Button,*ButtonGradient);
    this->setFont(QFont("Montserrat"));
    ui->Generate->setPalette(Cpalette);
    QList<QLabel*>  allLabels = this->findChildren<QLabel*>();
    for(int i=0; i < allLabels.count(); i++){
       //allLabels.at(i)->setFont(QFont("Garamond"));
    }
    this->update();
    ui->deletePositive->hide();
    ui->deleteNegative->hide();
    ui->Slider_Frame->hide();
    UserPreferences = new preferences();
    window2 = new reccomendationsGUI(this,&Cpalette);
    window2->hide();
    ui->errorMessages->hide();

}




MealReccomendGUI::~MealReccomendGUI()
{
    qDebug() << "MealReccomendGUI destructor called";
    delete BackgroundGradient;
    delete ButtonGradient;
    delete ui;
    delete UserPreferences;
    delete window2;

}

void MealReccomendGUI::on_Generate_clicked()
{
    if(ui->complexity->value() == 1){
        ui->errorMessages->setText("unable to generate suggestions, try setting complexity value to a higher number");
        ui->errorMessages->show();
        return;
    }else if(ui->complexity->value()==0){
        UserPreferences->recipeComplexity = -1;
    }else{
        UserPreferences->recipeComplexity = ui->complexity->value();
    }
    ui->errorMessages->hide();
    UserPreferences->positiveIngredients.clear();
    for(int i=0; i < ui->Positives_list->count(); i++){
        UserPreferences->positiveIngredients.push_back(ui->Positives_list->item(i)->text().toStdString());
    }
    UserPreferences->negativeIngredients.clear();
    UserPreferences->negativeIngredientsWeight.clear();
    for(int i=0; i < ui->Negatives_list->count(); i++){
        QString inputtedText = ui->Negatives_list->item(i)->text();
        if(inputtedText.endsWith("0")){
            UserPreferences->negativeIngredientsWeight.push_back(10);
            inputtedText.remove("10");
        } else {
            UserPreferences->negativeIngredientsWeight.push_back(inputtedText.at(inputtedText.length()-1).digitValue());
            inputtedText.remove(inputtedText.length()-1, 1);
        }
        inputtedText.remove(" - ");
        UserPreferences->negativeIngredients.push_back(inputtedText.toStdString());
    }

    if(ui->regionalFood->currentIndex()>0) UserPreferences->regionPositive = ui->regionalFood->currentText().toStdString();
    else UserPreferences->regionPositive = "";

    if(ui->neg_Region->currentIndex()>0) UserPreferences->regionNegative = ui->neg_Region->currentText().toStdString();
    else UserPreferences->regionNegative = "";

    if(ui->food_type->currentIndex()>0)
        UserPreferences->foodStylePositive = ui->food_type->currentText().toStdString();
    else
        UserPreferences->foodStylePositive = "";

    if(ui->negFood_type->currentIndex()>0) UserPreferences->foodStyleNegative = ui->negFood_type->currentText().toStdString();
    else UserPreferences->foodStyleNegative = "";

    window2->preferencesSent(UserPreferences);
    //this->hide();
    window2->show();



}

void MealReccomendGUI::on_add_Ingredient_clicked()
{
    if(ui->pos_Ingredients->text() != ""){
        QString inputtedIngredient = ui->pos_Ingredients->text();
        ui->Positives_list->addItem(inputtedIngredient);
        ui->pos_Ingredients->clear();
    }
    resetConfirmed = false;
    ui->reset->setText("Reset Inputs");

}

void MealReccomendGUI::on_deletePositive_clicked()
{
    ui->Positives_list->takeItem(ui->Positives_list->currentRow());
    ui->deletePositive->hide();
    resetConfirmed = false;
    ui->reset->setText("Reset Inputs");
}

void MealReccomendGUI::on_deleteNegative_clicked()
{
    ui->Negatives_list->takeItem(ui->Negatives_list->currentRow());
    ui->deleteNegative->hide();
    resetConfirmed = false;
    ui->reset->setText("Reset Inputs");
}






void MealReccomendGUI::on_add_neg_ingredient_clicked()
{
    if(ui->neg_Ingredients->text() != ""){
        QString inputtedIngredient = ui->neg_Ingredients->text();
        inputtedIngredient += " - ";
        inputtedIngredient += QString::number(ui->ingredientIngoreSlider->sliderPosition());
        ui->Negatives_list->addItem(inputtedIngredient);
        ui->neg_Ingredients->clear();
        ui->Slider_Frame->hide();
        resetConfirmed = false;
        ui->reset->setText("Reset Inputs");
    }

}

void MealReccomendGUI::on_reset_clicked()
{
    if(!resetConfirmed){
        ui->reset->setText("Are you sure?");
        resetConfirmed = true;
    } else {
        ui->reset->setText("Reset Inputs");
        ui->Positives_list->clear();
        ui->Negatives_list->clear();
        ui->neg_Ingredients->clear();
        ui->food_type->setCurrentIndex(0);
        ui->regionalFood->setCurrentIndex(0);
        ui->complexity->setValue(0);
        ui->negFood_type->setCurrentIndex(0);
        resetConfirmed = false;
    }
}

void MealReccomendGUI::somethingHappened(){

}

void MealReccomendGUI::on_regionalFood_currentIndexChanged(int index)
{
    resetConfirmed = false;
    ui->reset->setText("Reset Inputs");
}

void MealReccomendGUI::on_food_type_currentIndexChanged(int index)
{
    resetConfirmed = false;
    ui->reset->setText("Reset Inputs");
}

void MealReccomendGUI::on_negFood_type_currentIndexChanged(int index)
{
    resetConfirmed = false;
    ui->reset->setText("Reset Inputs");
}

void MealReccomendGUI::on_complexity_valueChanged(int arg1)
{
    resetConfirmed = false;
    ui->reset->setText("Reset Inputs");
    ui->errorMessages->hide();
}

void MealReccomendGUI::on_ingredientIngoreSlider_valueChanged(int value)
{
    QString text = "Importance: ";
    text.append(QString::number(value));
    ui->label_8->setText(text);

}
