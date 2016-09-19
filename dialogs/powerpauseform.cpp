#include "powerpauseform.h"
#include "ui_powerpauseform.h"
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QInputDialog>
#include <QDropEvent>
#include <QByteArray>
#include <QMimeData>

PowerPauseForm::PowerPauseForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PowerPauseForm)
{
    ui->setupUi(this);

    setViewOnly(false);
}

PowerPauseForm::~PowerPauseForm()
{
    delete ui;
}

QString PowerPauseForm::title() const
{
    return _title;
}

void PowerPauseForm::setTitle(const QString &title)
{
    _title = title;
    if(ui->title->text().isEmpty()){
       refreshUI();
    }
}

QString PowerPauseForm::helptext() const
{
    return _helptext;
}

void PowerPauseForm::setHelptext(QString helptext)
{
    _helptext = helptext;

    if(ui->txtboxHelptext->toHtml().isEmpty()){
       refreshUI();
    }

}

QPixmap PowerPauseForm::image() const
{
    return _image;
}

void PowerPauseForm::setImage(const QPixmap &image)
{
    _image = image;
    if(ui->image->pixmap()->isNull()){
       refreshUI();
    }
}

void PowerPauseForm::refreshUI()
{
    ui->title->setText(title());
    ui->titleBig->setText(title());
    ui->txtboxHelptext->setHtml(helptext());
    ui->image->setPixmap(image().scaled(ui->image->width(),ui->image->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation));

}

void PowerPauseForm::manageViewOnly()
{
    ui->title->setDisabled(viewOnly());
    ui->txtboxHelptext->setReadOnly(viewOnly());
    ui->btnChangeImage->setHidden(viewOnly());
    ui->tbBold->setHidden(viewOnly());
    ui->tbInsertLink->setHidden(viewOnly());
    ui->title->setHidden(viewOnly());
    ui->titleBig->setVisible(viewOnly());
    ui->label_2->setHidden(viewOnly());

    ui->tabWidget->setCurrentIndex(1);
}

bool PowerPauseForm::viewOnly() const
{
    return _viewOnly;
}

void PowerPauseForm::setViewOnly(bool viewOnly)
{
    _viewOnly = viewOnly;
    manageViewOnly();
}

void PowerPauseForm::on_buttonBox_accepted()
{
    if(ui->title->text().isEmpty()){
        //QMessageBox::information(this,"Oprettelse af PowerPause","Du skal som minimum give PowerPausen en titel");
        return;
    }

    setTitle(ui->title->text());
    setImage(*ui->image->pixmap());
    setHelptext(ui->txtboxHelptext->toHtml());
}

void PowerPauseForm::on_btnChangeImage_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Vælg billede"), QDir::homePath(), tr("Billeder (*.png *.jpg *.bmp)"));

    if(!fileName.isEmpty()){
        ui->image->setPixmap(QPixmap(fileName).scaled(640,480,Qt::KeepAspectRatio));
    }
}

void PowerPauseForm::on_tbBold_clicked(bool checked)
{
    if(checked){
        ui->txtboxHelptext->setFontWeight(QFont::Bold);
        return;
    }
    ui->txtboxHelptext->setFontWeight(QFont::Normal);
}

void PowerPauseForm::on_tbInsertLink_clicked()
{
    bool ok;
   QString text = QInputDialog::getText(this, tr("Indsæt link"),
                                        tr("LINK:"), QLineEdit::Normal,
                                        "http://", &ok);
   if (ok && !text.isEmpty()){
        ui->txtboxHelptext->textCursor().insertHtml(QString("<a href=%1>%1</a>").arg(text));
   }

}



void PowerPauseForm::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

//        QLabel *newIcon = new QLabel(this);
//        newIcon->setPixmap(pixmap);
//        newIcon->move(event->pos() - offset);
//        newIcon->show();
//        newIcon->setAttribute(Qt::WA_DeleteOnClose);

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
            qDebug() << "DROPPED";
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void PowerPauseForm::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << "ENTER";
}
