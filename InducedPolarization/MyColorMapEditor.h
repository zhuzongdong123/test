#pragma once

#include "GeneratedFiles/ui_DialogColorMapEditor.h"
#include <QtWidgets/QDialog>
#include <QtWidgets/QcolorMap>

class myColorMapEditor : public QDialog
{
	Q_OBJECT

public:
	myColorMapEditor(QWidget *parent = Q_NULLPTR);

	int exec();

	std::vector<QColor> getColorVector() { return m_currentColorVector; }
	QString getColorName() { return m_colorName; }

	void closeEvent(QCloseEvent *e) { this->hide(); QDialog::closeEvent(e); }

public slots:
	void getChangedText(QString text);

	void setColorValue(int red, int green, int blue);

	void changeTransparency(QString value);

signals:
	void changeColor();
	void changeTransparency(float value);

private:
	/*
	* @brief 创建颜色分组
	*/
	void createColorMap();

private:
	Ui::DialogColorMapEditor ui;
	QString m_colorName;
	std::map<QString,std::vector<QColor>> m_colorMap;
	std::vector<QColor> m_currentColorVector;
};