#include "selectorthing.h"
#include "ui_selectorthing.h"
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QFontMetrics>
#include <QPainter>
#include <QMainWindow>
#include "dialogs/simplesqlmanager.h"


SelectorThing::SelectorThing(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectorThing)
{
    ui->setupUi(this);

    //Tjekker standard Udfaldene.
    loadOutcomes();

    //Skyggeanimationen
    animationShade = new AnimationShade(this);
    animationShade->setVisible(false);
    connect(ui->btnNewOutcome,SIGNAL(clicked(bool)),animationShade,SLOT(runAnimation()));
    connect(ui->cbShowChoosingAnimation,SIGNAL(clicked(bool)),animationShade,SLOT(showShade(bool)));
}

SelectorThing::~SelectorThing()
{
    delete ui;
}

void SelectorThing::resizeEvent(QResizeEvent *evt)
{
    fitTextToLabel();
}


void SelectorThing::loadOutcomes()
{
    //Forbindelse til DB
    QSqlDatabase db = QSqlDatabase::database("default_connection",true);
    if(!db.isOpen()){
        qDebug() << "Læsning af databasen mislykkedes.";
        qDebug() << db.lastError().text();
    }

    QScopedPointer<QSqlTableModel> model(new QSqlTableModel(this,db));
    model->setTable("startbythings");
    if(!model->select()){
        qDebug() << "Læsning af tabel" << "startbythings" << "mislykkedes!";
        qDebug() << model->lastError().text();
    }

    //Hvis der ikke er nogle værdier i tabellen, da udfyldes den med disse
    if(model->rowCount()<=0){
        QStringList defaultTexts;
        defaultTexts.append("Højeste");
        defaultTexts.append("Laveste");
        defaultTexts.append("Seneste haft fødselsdag");
        defaultTexts.append("Største skostørrelse");
        defaultTexts.append("Mindste skostørrelse");
        defaultTexts.append("Længste hår");
        defaultTexts.append("Korteste hår");
        defaultTexts.append("Mørkeste hår");
        defaultTexts.append("Lysteste hår");
        defaultTexts.append("Længste ben");
        defaultTexts.append("Korteste ben");
        defaultTexts.append("Længste pegefinger");
        defaultTexts.append("Korteste pegefinger");
        defaultTexts.append("Længste højre arm");
        defaultTexts.append("Korteste højre arm");
        defaultTexts.append("Mørkeste bukser");
        defaultTexts.append("Længste lillefingernegl");
        defaultTexts.append("Kan hoppe højst");
        defaultTexts.append("Mest strøm tilbage på sin mobiltelefon");
        defaultTexts.append("Mest køllede hår");
        defaultTexts.append("Korteste venstre fod");
        defaultTexts.append("Bredeste højre fod");
        defaultTexts.append("Sten, Saks, Papir (Bedst ud af tre)");

        //Tilføjer standard sætningerne
        foreach(QString txt, defaultTexts){
            db.exec((QString("insert into startbythings ('text') VALUES('%1')").arg(txt)));

            if(db.lastError().text()!= " "){
                qDebug() << "Fejl ved oprettelse af udfald. Fejl:" << db.lastError().text();
            }
        }

//        //Genindlæser modellen
        model->select();
    }

//    //Sletter evt. gamle
    QStringList list;
    setOutcomes(list);

//    //Tilføjer nye værdier
    for(int i=0;i<model->rowCount();i++){
        appendOutcomes(model->record(i).value("text").toString());
    }

}

QStringList SelectorThing::getOutcomes() const
{
    return outcomes;
}

void SelectorThing::appendOutcomes(const QString value)
{
    outcomes.append(value);
}

void SelectorThing::setOutcomes(QStringList list)
{
    outcomes = list;
}

QString SelectorThing::getNewOutcome()
{
    if(getOutcomes().count()-1 <= 0){
        return "For få indtastninger. Tilføj nogle flere :-)";
    }

    rndNum.setUpper(getOutcomes().count()-1);
    rndNum.setLower(0);
    rndNum.setAllowSameOutcomeTwice(false);

    return getOutcomes().at(rndNum.getRandomValue());
}

void SelectorThing::fitTextToLabel()
{
    //Sikre, at vinduet ikke looper amok
    ui->lblSelectedThing->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    //Teksten der skal undersøges størrelsen af
    QString text = ui->lblSelectedThing->text();

    //Fonten der skal bruges i sidste ende
    QFont font;
    font.setPixelSize(1);

    int w = 1;
    while(w<ui->lblSelectedThing->width()){
        //Forøger pixelSize med 1
        font.setPixelSize(font.pixelSize()+1);

        //Undersøger den nye fontstørrelse
        QFontMetrics fm(font);
        w = fm.width(text);
    }

    ui->lblSelectedThing->setFont(font);
}

DatabaseManager *SelectorThing::getDatabasemanager() const
{
    return _databasemanager;
}

void SelectorThing::setDatabasemanager(DatabaseManager *databasemanager)
{
    _databasemanager = databasemanager;
}

void SelectorThing::on_btnNewOutcome_clicked()
{
    ui->lblSelectedThing->setText(getNewOutcome());
    fitTextToLabel();

    //AnimationShade *shade = new AnimationShade(this);

}

void SelectorThing::on_btnManageOptions_clicked()
{
    QScopedPointer<SimpleSqlManager> dialog(new SimpleSqlManager);
    dialog->setVisibleColumn(1);
    dialog->loadTable("startbythings");
    dialog->setDataType("Sætning");
    dialog->exec();

    //Genindlæser værdierne
    loadOutcomes();
}
