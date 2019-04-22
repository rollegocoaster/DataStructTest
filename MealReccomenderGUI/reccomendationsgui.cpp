#include "reccomendationsgui.h"
#include "ui_reccomendationsgui.h"
#include <sstream>
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
        QByteArray removingQuotes = reply->readAll();
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

            if(splitData[0]=="\"strMealThumb\""){
                qDebug() << QString::fromStdString(splitData[1]);
                QString info = QString::fromStdString(splitData[1]);
                while(info.indexOf('\\') != -1){
                    info.remove(info.indexOf('\\'),1);
                }
                while(info.indexOf('\"') != -1){
                    info.remove(info.indexOf('\"'),1);
                }
                qDebug() << info;
                this->TheURL.setUrl(info);
                this->request->setUrl(TheURL);
                qDebug() << "after setting url";
                this->currentReply = networkManager->get(*this->request);
                qDebug() << "after getting request";
            } else if(splitData[0] =="\"strInstructions\""){
                QString info = QString::fromStdString(splitData[1]);

                qDebug() << QString::fromStdString(splitData[1]);
                std::getline(output,data,'"');
                while(info.indexOf('\"') != -1){
                    info.remove(info.indexOf('\"'),1);
                }
                info.replace("\u2019","'");
                info.replace("\r\n"," ");
                info.push_back(QString::fromStdString(data));
                ui->outputText->setText(info);
            }
        }
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
