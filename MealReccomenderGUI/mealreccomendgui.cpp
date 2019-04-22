/* Sources
Qt

MealDatabase

for assistance in accessing a JSON webservice (ie MealDatabase)
https://makina-corpus.com/blog/metier/archives/access-json-webservice-qt-c

*/
#include "mealreccomendgui.h"
#include "ui_mealreccomendgui.h"
#include <QLineEdit>
#include <QString>
#include <string>
#include <QtDebug>
#include <QResizeEvent>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <sstream>

MealReccomendGUI::MealReccomendGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MealReccomendGUI)
{

    ui->setupUi(this);
    networkManager = new QNetworkAccessManager(this);
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

    // getting info from mealDatabase

    this->timer.start(100);
    qDebug() << "test";
    this->theMealDB = new QUrl("https://www.themealdb.com/api/json/v1/1/random.php");
    qDebug() << "test2";
    this->request = new QNetworkRequest;
    this->request->setUrl(*this->theMealDB);
    for(int i=0; i<NUMBER_OF_RECIPES_ADDED; i++){
        this->currentReply = networkManager->get(*this->request);
        qDebug() << i;

    }
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(MealDBResult(QNetworkReply*)));
    connect(&this->timer, SIGNAL(timeout()), this, SLOT(updateInfo()));

}




MealReccomendGUI::~MealReccomendGUI()
{
    qDebug() << "MealReccomendGUI destructor called";
    delete BackgroundGradient;
    delete ButtonGradient;
    delete ui;
    delete UserPreferences;
    delete window2;
    delete networkManager;
    delete theMealDB;
    delete request;
}




/*
    Preparing user inputs for sending to back end and sending it to the back end
*/
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


    // adding positive ingredients to userPreferences
    UserPreferences->positiveIngredients.clear();
    for(int i=0; i < ui->Positives_list->count(); i++){
        UserPreferences->positiveIngredients.push_back(ui->Positives_list->item(i)->text().toStdString());
    }
    //Seperating negative ingredients from their weight
    // and adding both to userPreferences
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
    // Adding regional food preferences to userPreferences
    if(ui->regionalFood->currentIndex()>0) UserPreferences->regionPositive = ui->regionalFood->currentText().toStdString();
    else UserPreferences->regionPositive = "";

    if(ui->neg_Region->currentIndex()>0) UserPreferences->regionNegative = ui->neg_Region->currentText().toStdString();
    else UserPreferences->regionNegative = "";

    // adding catagory preferences to userPreferences
    if(ui->food_type->currentIndex()>0)
        UserPreferences->foodStylePositive = ui->food_type->currentText().toStdString();
    else
        UserPreferences->foodStylePositive = "";

    if(ui->negFood_type->currentIndex()>0) UserPreferences->foodStyleNegative = ui->negFood_type->currentText().toStdString();
    else UserPreferences->foodStyleNegative = "";

    // Sending userPreferences to backEnd

    // sending backend to window 2
    qDebug() << QString::fromStdString(this->testingReccomendation);
    window2->showReccomendations(this->testingReccomendation);
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



void MealReccomendGUI::on_reset_clicked()
{
    if(!resetConfirmed)
    { // two click reset functionality
        ui->reset->setText("Are you sure?");
        resetConfirmed = true;
    } else {
        // resetting all
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

//////////////////////////////////////////////////////////////////////////////
//        Getting info from meal database and storing it in backend         //
//        and elements in frontend                                          //

void MealReccomendGUI::MealDBResult(QNetworkReply* reply){
    QByteArray removingQuotes = reply->readAll();
    while(removingQuotes.indexOf('"') != -1){
        removingQuotes.remove(removingQuotes.indexOf('"'),1);
    }
    std::stringstream output;
    output << removingQuotes.toStdString();

    std::string data;
    std::stringstream dataSplitter;
    std::string splitData[2];
    std::vector<std::string>:: iterator i;
    std::getline(output,data,',');
    while(std::getline(output,data,',')){
        dataSplitter.clear();
        dataSplitter << data;
        std::getline(dataSplitter,splitData[0],':');
        std::getline(dataSplitter,splitData[1]);
        if(splitData[0]=="strCategory"){
            for(i=categories.begin(); i!=categories.end() && *i != splitData[1]; i++);
            if(i==categories.end()) categories.push_back(splitData[1]);
            //add to backend node
        } else if(splitData[0]=="strMeal"){
            this->testingReccomendation = splitData[1];
        } else if(splitData[0]=="strArea"){
            for(i=regions.begin(); i!=regions.end() && *i != splitData[1]; i++);
            if(i==regions.end()) regions.push_back(splitData[1]);
        } else if(splitData[0].size() > 12){
            if(splitData[0].substr(0,13).compare(0,13,"strIngredient")==0){
               // qDebug() << QString::fromStdString(splitData[1]);
            }
        }
    }
    this->inputsAdded++;
}



//////////////////////////////////////////////////////////////////////////////


// checks for when inputs were added and adds the food type to the respective
// combo box
void MealReccomendGUI::updateInfo(){

    if(this->inputsAdded == NUMBER_OF_RECIPES_ADDED){

        this->timer.stop();
        for(unsigned int i=0; i < categories.size(); i++){
            qDebug() << QString::fromStdString(categories.at(i));
            ui->food_type->addItem(QString::fromStdString(categories.at(i)));
            ui->negFood_type->addItem(QString::fromStdString(categories.at(i)));
        }
        for(unsigned int i=0; i< regions.size(); i++){
            qDebug() << QString::fromStdString(regions.at(i));
            ui->regionalFood->addItem(QString::fromStdString(regions.at(i)));
            ui->neg_Region->addItem(QString::fromStdString(regions.at(i)));
        }
        qDebug() << categories.size() << " " << regions.size();
    }
}







///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                              code to reset reset button if a change occures
///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void MealReccomendGUI::on_regionalFood_currentIndexChanged(int index)
{
    int justToGetThatWarningAway = index;
    justToGetThatWarningAway++;
    resetConfirmed = false;
    ui->reset->setText("Reset Inputs");

}

void MealReccomendGUI::on_food_type_currentIndexChanged(int index)
{
    int justToGetThatWarningAway = index;
    justToGetThatWarningAway++;
    resetConfirmed = false;
    ui->reset->setText("Reset Inputs");
}

void MealReccomendGUI::on_negFood_type_currentIndexChanged(int index)
{
    int justToGetThatWarningAway = index;
    justToGetThatWarningAway++;
    resetConfirmed = false;
    ui->reset->setText("Reset Inputs");
}

void MealReccomendGUI::on_complexity_valueChanged(int arg1)
{
    int justToGetThatWarningAway = arg1;
    justToGetThatWarningAway++;
    resetConfirmed = false;
    ui->reset->setText("Reset Inputs");
    ui->errorMessages->hide();
}

void MealReccomendGUI::on_ingredientIngoreSlider_valueChanged(int value)
{
    int justToGetThatWarningAway = value;
    justToGetThatWarningAway++;
    QString text = "Importance: ";
    text.append(QString::number(value));
    ui->label_8->setText(text);

}
