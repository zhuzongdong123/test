#include "DialogMultiColoringDetails.h"

DialogMultiColoringDetails::DialogMultiColoringDetails(QWidget *parent)
{
	m_ui.setupUi(this);

	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);

	m_contourLevels = new DialogContourLevels(this);
}

DialogMultiColoringDetails::~DialogMultiColoringDetails()
{
	if (NULL != m_contourLevels)
	{
		delete m_contourLevels;
		m_contourLevels = NULL;
	}
}

//�����Enter New Level...����ť��
void DialogMultiColoringDetails::enterNewLevel()
{
	//ģ̬��ʾ
	if ( QDialog::Accepted == m_contourLevels->exec() )
	{
		//m_levelCreationMode = m_contourLevels->getlevelCreationMode();
		//m_rangeDistribution = m_contourLevels->getRangeDistribution();
		m_minLevel = m_contourLevels->getMinLevel();
		m_maxLevel = m_contourLevels->getMaxLevel();
		m_numberOfLevel = m_contourLevels->getNumberOfLevel();
		m_delta = m_contourLevels->getDelta();

		emit setTextRange(m_minLevel, m_maxLevel, m_numberOfLevel);
	};
}
