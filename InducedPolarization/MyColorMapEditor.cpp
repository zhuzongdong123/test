#include "myColorMapEditor.h"

myColorMapEditor::myColorMapEditor(QWidget *parent /*= Q_NULLPTR*/) :QDialog(parent)
{
	ui.setupUi(this);
	setParent(parent);
	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);

	ui.lineEdit_A->setValidator(new QIntValidator(0, 255, this));

	//创建颜色列表
	createColorMap();

	//显示初始值
	getChangedText("custom");
}

int myColorMapEditor::exec()
{
	return QDialog::exec();
}

void myColorMapEditor::getChangedText(QString text)
{
	m_colorName = text;

	m_currentColorVector.clear();
	if (m_colorMap.find(text) != m_colorMap.end())
	{
		m_currentColorVector = m_colorMap.find(text)->second;
		ui.colorButtonV->changeColor(m_currentColorVector);
		setColorValue(m_currentColorVector[0].red(), m_currentColorVector[0].green(), m_currentColorVector[0].blue());
		emit changeColor();
	}
}

void myColorMapEditor::setColorValue(int red, int green, int blue)
{
	ui.lineEdit_R->setText(QString::number(red));
	ui.lineEdit_G->setText(QString::number(green));
	ui.lineEdit_B->setText(QString::number(blue));
}

void myColorMapEditor::changeTransparency(QString value)
{
	float v = value.toFloat() / 255;
	emit changeTransparency(v);
}

void myColorMapEditor::createColorMap()
{
	std::vector<QColor> colorVector;

	//custom 的颜色组【】
	colorVector.clear();
	colorVector.push_back(QColor(255, 0, 0));
	colorVector.push_back(QColor(141, 31, 10));
	colorVector.push_back(QColor(98, 65, 0));
	colorVector.push_back(QColor(64, 104, 0));
	colorVector.push_back(QColor(52, 208, 0));
	colorVector.push_back(QColor(0, 255, 0));
	colorVector.push_back(QColor(0, 99, 66));
	colorVector.push_back(QColor(0, 63, 94));
	colorVector.push_back(QColor(0, 30, 130));
	colorVector.push_back(QColor(0, 4, 194));
	m_colorMap.insert(std::make_pair("custom", colorVector));

	//accents 的颜色组【从上往下~6000到1000：绿色到红色】
	colorVector.clear();
	colorVector.push_back(QColor(130, 230, 131));
	colorVector.push_back(QColor(156, 188, 170));
	colorVector.push_back(QColor(205, 178, 193));
	colorVector.push_back(QColor(253, 199, 140));
	colorVector.push_back(QColor(255, 245, 154));
	colorVector.push_back(QColor(137, 168, 167));
	colorVector.push_back(QColor(75, 97, 171));
	colorVector.push_back(QColor(208, 20, 135));
	colorVector.push_back(QColor(211, 55, 65));
	colorVector.push_back(QColor(192, 89, 25));
	m_colorMap.insert(std::make_pair("accents", colorVector));

	//color1 的颜色组【从上往下~6000到1000】
	colorVector.clear();
	colorVector.push_back(QColor(230, 230, 230));
	colorVector.push_back(QColor(204, 204, 255));
	colorVector.push_back(QColor(178, 204, 229));
	colorVector.push_back(QColor(165, 216, 204));
	colorVector.push_back(QColor(230, 255, 204));
	colorVector.push_back(QColor(255, 242, 204));
	colorVector.push_back(QColor(255, 228, 204));
	colorVector.push_back(QColor(255, 206, 204));
	colorVector.push_back(QColor(255, 232, 232));
	colorVector.push_back(QColor(255, 242, 242));
	m_colorMap.insert(std::make_pair("color1", colorVector));

	//color2 的颜色组
	colorVector.clear();
	colorVector.push_back(QColor(0, 0, 255));
	colorVector.push_back(QColor(30, 144, 255));
	colorVector.push_back(QColor(0, 191, 255));
	colorVector.push_back(QColor(135, 206, 235));
	colorVector.push_back(QColor(0, 255, 255));
	colorVector.push_back(QColor(95, 158, 160));
	colorVector.push_back(QColor(60, 179, 113));
	colorVector.push_back(QColor(238, 238, 0));
	colorVector.push_back(QColor(238, 201, 0));
	colorVector.push_back(QColor(255, 193, 193));
	m_colorMap.insert(std::make_pair("color2", colorVector));

	//color3 的颜色组
	colorVector.clear();
	colorVector.push_back(QColor(0, 255, 127));
	colorVector.push_back(QColor(255, 106, 106));
	colorVector.push_back(QColor(50, 99, 99));
	colorVector.push_back(QColor(208, 32, 144));
	colorVector.push_back(QColor(238, 130, 238));
	colorVector.push_back(QColor(148, 0, 211));
	colorVector.push_back(QColor(238, 59, 59));
	colorVector.push_back(QColor(255, 235, 204));
	colorVector.push_back(QColor(34, 139, 34));
	colorVector.push_back(QColor(102, 205, 170));
	m_colorMap.insert(std::make_pair("color3", colorVector));

	//color4 的颜色组【蓝色，黄色】
	colorVector.clear();
	colorVector.push_back(QColor(0, 0, 255));
	//colorVector.push_back(QColor(0, 0, 255));
	//colorVector.push_back(QColor(0, 0, 255));
	//colorVector.push_back(QColor(0, 0, 255));
	//colorVector.push_back(QColor(0, 0, 255));
	//colorVector.push_back(QColor(255, 255, 0));
	//colorVector.push_back(QColor(255, 255, 0));
	//colorVector.push_back(QColor(255, 255, 0));
	//colorVector.push_back(QColor(255, 255, 0));
	colorVector.push_back(QColor(255, 255, 0));
	m_colorMap.insert(std::make_pair("color4", colorVector));
}
