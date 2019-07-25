#include "DialogCreateProject.h"
#include "QFileDialog"
#include "QMessageBox"
#include "ProjectManager.h"
#include "QDebug"

DialogCreateProject::DialogCreateProject(QWidget *parent /*= nullptr*/) : QDialog(parent)
{
    m_ui.setupUi(this); ///< 设置此类为处理类

    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowCloseButtonHint;
    setWindowFlags(flags);

    QObject::connect(m_ui.toolButton_path, SIGNAL(clicked()), this, SLOT(onActionOpenFileDialog()));
}

DialogCreateProject::~DialogCreateProject()
{
}

void DialogCreateProject::onActionOpenFileDialog()
{
    m_projcetName = m_ui.lineEdit_proj_name->text();

    QString filename = QFileDialog::getSaveFileName(this, QStringLiteral("Please specify path to save your project"), QString::fromStdString("./") + m_projcetName, 0, 0, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (filename == "")
    {
        QMessageBox::critical(this, "error", QString::fromUtf8("空的"));
        return;
    }

    QDir dir;

    if (dir.exists(filename))
    {
        QMessageBox::critical(this, "error", QString::fromUtf8("已存在 "));
        return;
    }

    QFileInfo info(filename);
    QString projName = info.fileName();

    m_currentProjPath = filename;
    m_projcetName = projName;
    m_ui.lineEdit_proj_name->setText(projName);
    m_ui.lineEdit_path->setText(m_currentProjPath);
}

void DialogCreateProject::accept()
{
	QString projFileName = m_currentProjPath + ".proj";

	QDir dir;

	if (!dir.mkdir(m_currentProjPath))
	{
		QMessageBox::critical(this, "error", "无法创建项目文件夹");
		return;
	}

	createFile(m_currentProjPath, projFileName);

	ProjectManager::instance()->resetProject();

	if (!ProjectManager::instance()->initProject(m_currentProjPath, m_projcetName))
	{
		QMessageBox::critical(this, "error", "创建失败");
	}

	QDialog::accept();
}

void DialogCreateProject::createFile(QString filePath, QString fileName)
{
	QDir tempDir;

	QString currentDir = tempDir.currentPath();

	if (!tempDir.exists(filePath))
	{
		qDebug() << QObject::tr("不存在该路径") << endl;
		tempDir.mkpath(filePath);
	}
}