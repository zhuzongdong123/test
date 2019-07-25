/*
*
*/

#ifndef DIALOG_SETUP_H
#define DIALOG_SETUP_H

#include <QDialog>
#include "GeneratedFiles/ui_DialogSetup.h"

#pragma execution_character_set("utf-8")

class DialogSetup : public QDialog
{
    Q_OBJECT

  public:
    DialogSetup(QWidget *parent = nullptr);
    ~DialogSetup();

  public slots:

    void onOkButton();

  protected:
    virtual void showEvent(QShowEvent *) override;

    void setValidator();

  private:
    Ui::DialogSetup _ui;
};

#endif