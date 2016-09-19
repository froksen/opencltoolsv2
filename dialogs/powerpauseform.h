#ifndef POWERPAUSEFORM_H
#define POWERPAUSEFORM_H

#include <QDialog>

namespace Ui {
class PowerPauseForm;
}

class PowerPauseForm : public QDialog
{
    Q_OBJECT

public:
    explicit PowerPauseForm(QWidget *parent = 0);
    ~PowerPauseForm();

    QString title() const;
    void setTitle(const QString &title);

    QString helptext() const;
    void setHelptext(QString helptext);

    QPixmap image() const;
    void setImage(const QPixmap &image);

    bool viewOnly() const;
    void setViewOnly(bool viewOnly);

private slots:
    void on_buttonBox_accepted();
    void on_btnChangeImage_clicked();
    void on_tbBold_clicked(bool checked);
    void on_tbInsertLink_clicked();

private:
    Ui::PowerPauseForm *ui;

    void refreshUI();
    void manageViewOnly();

    bool _viewOnly;
    QString _title;
    QString _helptext;
    QPixmap _image;

protected:
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
};

#endif // POWERPAUSEFORM_H
