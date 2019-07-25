#include "DialogProgress.h"
#include "QScrollBar"
#include "LogSystem.h"
#include "GlobalClass\GlobalParam.h"

DialogProgress::DialogProgress(QWidget *parent /*= nullptr*/)
{
	_isCompleted = false;
    _ui.setupUi(this);

    //setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowMinMaxButtonsHint;
    flags |= Qt::WindowCloseButtonHint;
    setWindowFlags(flags);

    _ui.progressBar->setRange(0, 100);
    _ui.progressBar->setValue(0);
}

DialogProgress::~DialogProgress()
{
}

bool DialogProgress::initAndShow()
{
    return true;
}

void DialogProgress::setProgressValue(int value)
{
	if (100 <= value)
	{
		_isCompleted = true;
	}

    _ui.progressBar->setValue(value);
}

void DialogProgress::writeMessage(int level, QString msg)
{
// 	unsigned int lineCount = GlobalParam::instance()->getCommonSetting().maxLineForShowLog;
// 
// 	_messages.push_back(msg);
// 
// 	while (_messages.size() > lineCount)
// 	{
// 		_messages.pop_front();
// 	}
// 
// 	QString str = "";
// 
// 	for (auto x : _messages)
// 	{
// 		str += x;
// 		str += "\n";
// 	}

    _ui.textEdit->append(msg);
    QScrollBar *scrollbar = _ui.textEdit->verticalScrollBar();

    scrollbar->setSliderPosition(scrollbar->maximum());
}

void DialogProgress::closeEvent(QCloseEvent *e)
{
	LogSystem::instance()->stopThreadLog();

    _ui.textEdit->setText("");

	_messages.clear();

    emit onClose();

//	QDialog::hide();

    QDialog::closeEvent(e);
}

void DialogProgress::showEvent(QShowEvent *)
{
	_isCompleted = false;

    LogSystem::instance()->startThreadLog();
}
