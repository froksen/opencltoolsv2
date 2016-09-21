#include "powerpausemanager.h"
#include <QSqlRecord>
#include <QSqlQuery>
#include "classes/powerpause.h"
#include <QSqlError>
#include <QDebug>
#include <QPixmap>
#include <QByteArray>
#include <QBuffer>

PowerPauseManager::PowerPauseManager(QObject *parent) : QObject(parent)
{
    _items = new QList<PowerPause*>;
}

bool PowerPauseManager::loadAll()
{
    getFromDatabase();
    qDebug() << "PowerPauseManager: LoadAll()";

    if(!getModel()->select()){
        qDebug() << getModel()->lastError();
        return false;
    }
    return true;

    //getModel()->setQuery(QSqlQuery("SELECT * FROM powerpauses"));
}

bool PowerPauseManager::loadAll(bool isActive)
{
    getFromDatabase();
    qDebug() << "PowerPauseManager: loadAll(isActive)";

    getModel()->setFilter(QString("isActive=%1").arg(isActive));
    if(!getModel()->select()){
        qDebug() << getModel()->lastError();
        return false;
    }
    return true;
}

bool PowerPauseManager::load(int id)
{
    getFromDatabase();
    qDebug() << "PowerPauseManager: load()";

    getModel()->setFilter(QString("id=%1").arg(id));
    if(!getModel()->select()){
        qDebug() << getModel()->lastError();
        return false;
    }
    return true;

    //getModel()->setQuery(QSqlQuery(QString("SELECT * FROM powerpauses WHERE id=%1").arg(id)));
}

bool PowerPauseManager::remove(int id)
{
    load(id);

    bool rlt = getModel()->removeRow(0);
    qDebug() << "PowerPauseManager: remove()";
    getModel()->submitAll();
    return rlt;
}

bool PowerPauseManager::append(QString title, QString helpText, QByteArray image) //
{
    QSqlRecord record = getModel()->record();

    record.setValue("title",title);
    record.setValue("helptext",helpText);
    record.setValue("image",image);
    record.setValue("isActive",true);

    bool rlt = getModel()->insertRecord(-1,record);

    getModel()->submitAll();
    return rlt;
}

bool PowerPauseManager::append(QString title, QString helpText, QPixmap image)
{
    QPixmap newPicture(image);
                QByteArray bytes;
                QBuffer buffer(&bytes);
                buffer.open(QIODevice::WriteOnly);
                newPicture.save(&buffer, "PNG");

    append(title,helpText,bytes);
}



bool PowerPauseManager::save()
{
    _model->submitAll();
}

Database *PowerPauseManager::database() const
{
    return _database;
}

bool PowerPauseManager::getFromDatabase()
{
    //Database
   _database = new Database(this);

   QString createQry = "CREATE TABLE `powerpauses` ("
           "`id`	INTEGER PRIMARY KEY AUTOINCREMENT,"
           "`isActive`	INTEGER DEFAULT 1,"
            "`title`	TEXT,"
           "`helptext`	TEXT,"
           "`image`	BLOB);";

   _model = _database->selectTable("powerpauses",createQry);

   if(!_model->rowCount()<1){
       return true;
   }

   //Tilføjer standard PowerPauser
    QString title = "Vaskehallen";
    QString materialer = "Ingen";
    QString instruktion = "Eleverne står på to rækker med en halv meters tafstand skulder ved skulder. Det første par er dem, som først får en tur i vaskehallen. De går en og en ned igennem vaskehallen, hvor de i første omgang ’vaskes’ med små, rolige klap på kroppen af de andre elever. På vejen tilbage bliver de ’tørret’ med rolige, cirkulære bevægelser af de andre elever. På den sidste tur bliver de ’vokset’ af de andre, som masserer dem roligt. Når det første par er blevet vasket, tørret og vokset, stiller de sig nederst i rækken, og dernæst er det næste pars tur.";
    QString variation = "Aktiviteten kan udvikles, så vaskehallen bliver skiftet ud med ’en tur i skoven’ (regn, blæst, sol) eller ’en tur i zoo’ (aber, pingviner, elefanter), der ud over at klappe og massere måske nu også kilder og napper let.";
    QString helptext = htmlHelpText(materialer,instruktion,variation,"http://www.aktivaaretrundt.dk/sundhedsugerne/inspirationsmaterialer/powerpauser");

    append(title,helptext,QPixmap(":/img/PowerPause_Vaskehallen.png"));

    title = "Grib mig";
    materialer = "Ingen";
    instruktion = "Eleverne er sammen i mindre grupper på tre elever, hvor en af eleverne stiller sig med ryggen til de to andre. Når de siger ’nu’, lader han/hun sig falde bagover og gribes af de to andre. Den, der falder, kan også prøve med lukkede øjne.";
    variation = "";
    helptext = htmlHelpText(materialer,instruktion,variation,"http://www.aktivaaretrundt.dk/sundhedsugerne/inspirationsmaterialer/powerpauser");

    append(title,helptext,QPixmap(":/img/PowerPause_GribMig.png"));

    title = "Dragens Hale";
    materialer = "Ingen";
    instruktion = "Eleverne stiller sig i en række (minimum seks elever) med hænderne på hinandens skuldre. Den forreste elev er dragens hoved, og den bageste er dragens hale. Dragens hoved skal nu forsøge at fange halen, uden at rækken brydes. Når halen fanges, bliver den det nye hoved.";
    variation = "";
    helptext = htmlHelpText(materialer,instruktion,variation,"http://www.aktivaaretrundt.dk/sundhedsugerne/inspirationsmaterialer/powerpauser");
    append(title,helptext,QPixmap(":/img/PowerPause_DragesHale.png"));

    title = "Styr Bilen";
    materialer = "Eventuelt bind for øjnene";
    instruktion = "Eleverne er sammen parvis inden for et afgrænset inde- eller udeområde. Den ene bliver ’bil’ og lukker øjnene/får bind for øjnene. Den anden elev, føreren, stiller sig bag ved sin bil. Føreren styrer sin bil ved at trykke den anden på ryggen/skuldrene. Hvis der trykkes på højre skulder, drejes der til højre, og modsat til venstre. Hvis der trykkes midt på ryggen, skal man ’køre’ forlæns, og bliver der trykket dobbelt på ryggen, skal der køres baglæns. Som tilvænning til aktiviteten kan man starte med, at parrene holder i hånd, eller at den blinde holder en finger i den andens håndflade.";
    variation = "<br>1) Bilerne styres verbalt af makkerne uden for det afgrænsede område med signaler såsom frem, tilbage, højre, venstre. <br> 2) Der kan stilles krav om, at bilerne kun må styres verbalt med forskellige aftalte koder for hvert makkerpar, fx øst/vest, styrbord/bagbord eller forskellige tal.<br>3) Aktiviteten kan udvikles til en nervepirrende fangeleg, hvor den ene bil udvælges som fanger. Herefter gælder det for denne bil om at fange de andre, som enten kører ud af legen, hvis de bliver fanget, eller skal køre en omgang, før de er med i legen igen.<br>4) Aktiviteten kan også udvikles til ’bil-bold’, hvor bilerne spiller i to hold mod hinanden med en skumbold, og hvor det gælder om at score ved at kaste eller trille bolden ind i modstanderens mål.";
    helptext = htmlHelpText(materialer,instruktion,variation,"http://www.aktivaaretrundt.dk/sundhedsugerne/inspirationsmaterialer/powerpauser");
    append(title,helptext,QPixmap(":/img/PowerPause_Styrbilen.png"));

}

QString PowerPauseManager::htmlHelpText(QString materialer, QString instruktion, QString variation,QString fraUrl)
{
    return  "<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">MATERIALER</span>: "+materialer+" </p>"
            "<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">INSTRUKTION</span>: "+instruktion+" </p>"
            "<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">VARIATION</span>: "+variation+" </p>"
            "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Fra 'Aktiv året rundt' <a href=\" "+fraUrl+" \"><span style=\" text-decoration: underline; color:#0000ff;\">"+fraUrl+"</span></a></p>";

}

QList<PowerPause *> *PowerPauseManager::getItems() const
{
    _items->clear();

    for(int i=0; i<=getModel()->rowCount();i++){
        PowerPause *pp = new PowerPause();

        pp->setTitle(getModel()->record(i).value("title").toString());
        pp->setHelptext(getModel()->record(i).value("helptext").toString());
        pp->setImage(QImage(getModel()->record(i).value("title").toByteArray()));

        _items->append(pp);
    }

    return _items;
}

QSqlTableModel *PowerPauseManager::getItemsModel() const
{
    return getModel();
}

QSqlTableModel *PowerPauseManager::getModel() const
{
    return _model;
}

DatabaseManager *PowerPauseManager::getDatabaseMgr() const
{
    return _databaseMgr;
}

void PowerPauseManager::setDatabaseMgr(DatabaseManager *databaseMgr)
{
    _databaseMgr = databaseMgr;
}
