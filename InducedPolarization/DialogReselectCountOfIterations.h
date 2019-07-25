/*
*
*/

#ifndef DIALOGRESELECTCOUNTOFITERATIONS_H
#define DIALOGRESELECTCOUNTOFITERATIONS_H

#include <QtWidgets/QDialog>
#include "GeneratedFiles/ui_DialogReselectCountOfIterations.h"
#pragma execution_character_set("utf-8")
class DialogReselectCountOfIterations : public QDialog
{
  public:
    DialogReselectCountOfIterations(QWidget *parent = nullptr);
    ~DialogReselectCountOfIterations();

    /**
	* @brief 重载父类的accept接口，关闭创建工程对话框之前要进行判定
	*/
    virtual void accept();

    int getCount() { return m_count; }

  protected:
    Ui::DialogReselectCountOfIterations m_ui;

    int m_count;

  private:
    void setValidator();
};

#endif