#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DialogDisplayImage.h"

/*
* @brief �������̶Ի�����
*/
class DialogDisplayImage : public QDialog
{
	Q_OBJECT

public:
	/**
	* @brief ���캯��
	*
	* @param [in] parent �����ھ����Ĭ�Ͽ�
	*/
	DialogDisplayImage(QWidget *parent = Q_NULLPTR);

	/**
	* @brief ��������
	**/
	~DialogDisplayImage() {}

	void setOsgFilePath(QString fileName);

private:
	Ui::DialogDisplayImage m_ui; ///< UI�ļ�

};