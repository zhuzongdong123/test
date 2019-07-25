#pragma once

#include "GeneratedFiles/ui_DialogInversionParaSetting.h"

class DialogInversionParaSetting : public QDialog
{
    Q_OBJECT
  public:
    DialogInversionParaSetting(QWidget *parent = nullptr);
    ~DialogInversionParaSetting();

    void saveDialogData();

	public slots:
    void onClickedNotUseLAMDA();
    void onClickedUseLAMDA();

  protected:
    Ui::DialogInversionParaSetting m_ui;

    void closeEvent(QCloseEvent *e);


	virtual void showEvent(QShowEvent *) override;

private:
    void setValidator();
};