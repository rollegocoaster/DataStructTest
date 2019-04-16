#include "reccomendations.h"
#include "ui_reccomendations.h"
#include <QString>

reccomendations::reccomendations(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::reccomendations)
{
    ui->setupUi(this);
}

void reccomendations::sendInformation(preferences *inputtedPreference)
{
    this->update();
    QString string = "";
    string+= inputtedPreference->foodStylePositive[0];
    for(unsigned i=1; i<inputtedPreference->foodStylePositive.size(); i++){
        string.append("\n");
        string+= inputtedPreference->foodStylePositive[i];
    }
    ui->TextDisplay->setText(string);
}

reccomendations::~reccomendations()
{
    delete ui;
}



void reccomendations::on_backButton_clicked()
{
   this->hide();
   this->activateWindow();
}
