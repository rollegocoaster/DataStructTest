#include "reccomendationsgui.h"
#include "ui_reccomendationsgui.h"
#include <sstream>
#include <QtScript>
reccomendationsGUI::reccomendationsGUI(QWidget *parent, QPalette* customPalette) :
    QWidget(parent),
    ui(new Ui::reccomendationsGUI)
{
    ui->setupUi(this);
    this->setPalette(*customPalette);
    this->update();
    this->networkManager = new QNetworkAccessManager();
    this->request = new QNetworkRequest();
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(useInfo(QNetworkReply*)));
    ui->outputText->hide();

}

reccomendationsGUI::~reccomendationsGUI()
{
    delete ui;
    delete request;
    delete networkManager;
}

void reccomendationsGUI::on_back_clicked()
{
    this->hide();
    this->activateWindow();

}


// testing sending preferences
void reccomendationsGUI::showReccomendations(std::string reccomended){
    ui->name->setText(QString::fromStdString(reccomended));
    qDebug() << "beginning of showReccomendations";
    this->url = "https://www.themealdb.com/api/json/v1/1/search.php?s=";
    while(reccomended.find(' ')!=std::string::npos){
        reccomended.replace(reccomended.find(' '),1,"_");
    }
    qDebug() << "after while loop";

    this->url += QString::fromStdString(reccomended);
    this->TheURL = (url);
    qDebug() << "before setting url";
    this->request->setUrl(TheURL);
    qDebug() << "after setting url";
    this->currentReply = networkManager->get(*this->request);
    qDebug() << "after getting request";

}


void reccomendationsGUI::useInfo(QNetworkReply* reply){
    QUrl tempUrl = reply->url();

    QString tempString = tempUrl.toString();
    qDebug() << tempString;
    if(tempString.endsWith(".jpg")){
        this->requestOutput = reply->readAll();
        if(this->image.loadFromData(this->requestOutput)) qDebug() << "success";
        else qDebug() << "fail";
        this->image.scaledToWidth(this->width()-20);
        ui->image->setPixmap(image);
    } else {
        this->json = QJsonDocument::fromJson(reply->readAll());
        qDebug() << json.isEmpty() << json.isArray() << json.isNull() << json.isObject();
        this->object = json.object();
        this->info = object.value("meals").toArray();
        object = info.at(0).toObject();

        this->TheURL = object.value("strMealThumb").toString();
        this->request->setUrl(TheURL);
        this->currentReply = networkManager->get(*this->request);
        QString recipe = "";
        QString lable;
        for(int i=1; i<20; i++){
            lable = "strIngredient";
            lable += QString::number(i);
            if(object.value(lable).toString() != ""){
                recipe += object.value(lable).toString();
                recipe += " - ";
                lable = "strMeasure";
                lable += QString::number(i);
                recipe += object.value(lable).toString();
                recipe += '\n';
            }
        }
        recipe += "\n     Instructions \n";
        recipe += object.value("strInstructions").toString();
        ui->outputText->setText(recipe);


    }
}

void reccomendationsGUI::on_pushButton_3_clicked()
{
    if(recipeShown){
        ui->outputText->hide();
        ui->image->show();
        recipeShown = false;
    }else{
        ui->outputText->show();
        ui->image->hide();
        recipeShown = true;
    }
}
