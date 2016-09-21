#include "powerpausepicker.h"
#include "ui_powerpausepicker.h"
#include "dialogs/powerpauseadmin.h"
#include "dialogs/powerpauseform.h"
#include "classes/animationshade.h"
#include <QSqlRecord>
#include <QDebug>

PowerPausePicker::PowerPausePicker(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PowerPausePicker)
{
    ui->setupUi(this);

    _ppmgr = new PowerPauseManager(this);
    _ppmgr->loadAll(true);


    _randomNumber = new RandomNumber();
    _randomNumber->setAllowSameOutcomeTwice(false);
    _randomNumber->setUpper(ppmgr()->getItemsModel()->rowCount()-1);
    _randomNumber->setLower(0);


    //Skyggeanimationen
    AnimationShade *animationShade = new AnimationShade(this);
    connect(ui->btnNewPowerPause,SIGNAL(clicked(bool)),animationShade,SLOT(runAnimation()));
    connect(ui->cbViewShade,SIGNAL(clicked(bool)),animationShade,SLOT(showShade(bool)));
}

PowerPausePicker::~PowerPausePicker()
{
    delete ui;
}


void PowerPausePicker::on_btnAdminPowerPause_clicked()
{
    PowerPauseAdmin *ppa = new PowerPauseAdmin(this);
    ppa->exec();

    _ppmgr->loadAll(true);
    _randomNumber->setUpper(ppmgr()->getItemsModel()->rowCount()-1);
    _randomNumber->setLower(0);
}

void PowerPausePicker::on_btnNewPowerPause_clicked()
{
    int number = randomNumber()->getRandomValue();

    setCurrentRecord(ppmgr()->getItemsModel()->record(number));

    ui->title->setText(currentRecord().value("title").toString());

    QPixmap img;
    img.loadFromData(currentRecord().value("image").toByteArray());
    img = img.scaled(ui->image->width()-50,ui->image->height()-50,Qt::KeepAspectRatio,Qt::SmoothTransformation);

    ui->image->setPixmap(img);

}

PowerPauseManager *PowerPausePicker::ppmgr() const
{
    return _ppmgr;
}

void PowerPausePicker::resizeEvent(QResizeEvent *)
{
    QPixmap img;
    img.loadFromData(currentRecord().value("image").toByteArray());
    img = img.scaled(ui->image->width()-50,ui->image->height()-50,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->image->setPixmap(img);
}

RandomNumber *PowerPausePicker::randomNumber() const
{
    return _randomNumber;
}

void PowerPausePicker::on_commandLinkButton_clicked()
{
    PowerPauseForm frm;
    frm.setViewOnly(true);

    frm.setTitle(currentRecord().value("title").toString());
    frm.setHelptext(currentRecord().value("helptext").toString());
    QPixmap img;
    img.loadFromData(currentRecord().value("image").toByteArray());
    frm.setImage(img);

    frm.exec();
}

QSqlRecord PowerPausePicker::currentRecord() const
{
    return _currentRecord;
}

void PowerPausePicker::setCurrentRecord(const QSqlRecord &currentRecord)
{
    _currentRecord = currentRecord;
}
