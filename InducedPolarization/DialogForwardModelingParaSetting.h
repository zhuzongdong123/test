#pragma once

#include "GeneratedFiles/ui_DialogForwardModelingParaSetting.h"
#include "GlobalClass/GlobalParam.h"

class DialogForwardModelingParaSetting : public QDialog
{
    Q_OBJECT
  public:
    DialogForwardModelingParaSetting(QWidget *parent = nullptr);
    ~DialogForwardModelingParaSetting();

    void saveDialogData();

	void showEvent(QShowEvent * vEvent)
	{
		m_ui.lineEdit_currentINumZ->setText(QString::number(GlobalParam::instance()->getForwardModelingParaSetting().faceZInModel + 1));
		QDialog::showEvent(vEvent);
	}

  protected:
    Ui::DialogForwardModelingParaSetting m_ui;

    void closeEvent(QCloseEvent *e);

  private:
    void setValidator();
};