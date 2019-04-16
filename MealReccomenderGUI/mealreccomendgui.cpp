#include "mealreccomendgui.h"
#include "ui_mealreccomendgui.h"
#include <QLineEdit>
#include <QString>
#include <string>


MealReccomendGUI::MealReccomendGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MealReccomendGUI)
{
    ui->setupUi(this);
    Cpalette = this->palette();
    BackgroundGradient = new QLinearGradient(0,0,0,this->height());
    BackgroundGradient->setColorAt(0,QColor(3,104,202));
    BackgroundGradient->setColorAt(1,QColor(3,104,140));
    Cpalette.setBrush(QPalette::Window,*BackgroundGradient);
    //Cpalette.setColor(QPalette::Base,QColor(225,255,225));

    ButtonGradient = new QLinearGradient();
    ButtonGradient->setColorAt(0,QColor(75,191,137));
    ButtonGradient->setColorAt(1,QColor(5,242,131));
    //Cpalette.setColor(QPalette::Button, QColor(194, 68, 35));
    this->setPalette(Cpalette);
    this->update();
    this->testString = "";
    window2 = new reccomendations(this);
    window2->hide();
    timer = startTimer(100);
    ui->deletePositive->hide();
    UserPreferences = new preferences();
}




MealReccomendGUI::~MealReccomendGUI()
{
    delete ui;
    delete BackgroundGradient;
    delete ButtonGradient;
    delete window2;
    delete UserPreferences;
    killTimer(timer);
}

void MealReccomendGUI::on_Generate_clicked()
{
    UserPreferences->positiveIngredients.clear();
    for(int i=0; i < ui->Positives_list->count(); i++){
        UserPreferences->positiveIngredients.push_back(ui->Positives_list->item(i)->text().toStdString());
    }

    window2->sendInformation(UserPreferences);
    window2->show();

}

void MealReccomendGUI::on_add_Ingredient_clicked()
{
    if(ui->pos_Ingredients->text() != ""){
        QString inputtedIngredient = ui->pos_Ingredients->text();
        ui->Positives_list->addItem(inputtedIngredient);
    }
}



void MealReccomendGUI::on_deletePositive_clicked()
{
    ui->Positives_list->takeItem(ui->Positives_list->currentRow());
    ui->deletePositive->hide();
}
