/*
*
*/

#ifndef DIALOG_PROGRESS_H
#define DIALOG_PROGRESS_H

#include <QtWidgets/QDialog>
#include "GeneratedFiles/ui_DialogProgress.h"
#include <QtGui/QKeyEvent>

#include <list>

using namespace std;

class DialogProgress : public QDialog
{
    Q_OBJECT

  public:
    DialogProgress(QWidget *parent = nullptr);
    ~DialogProgress();

    bool initAndShow();
	bool isCompleted() { return _isCompleted; }

    void writeMessage(int level, QString msg);

	void keyPressEvent(QKeyEvent *event)
	{
		switch (event->key())
		{
		case Qt::Key_Escape:
			break;
		default:
			QDialog::keyPressEvent(event);
		}
	}

  signals:

    void onClose();

  public slots:

    void setProgressValue(int value);

  protected:
    virtual void closeEvent(QCloseEvent *e) override;

    virtual void showEvent(QShowEvent *) override;

  private:
    Ui::DialogProgress _ui;
	list<QString> _messages;
	bool _isCompleted;
};

#endif