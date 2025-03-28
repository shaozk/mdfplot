

#include "About.h"
#include "ui_About.h"

#include "Globals.h"

About::About(QWidget* parent) 
    : QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
	// 移除问号按钮
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	// 填充关于信息
    setWindowTitle(tr("About %1").arg(Globals::name()));
    ui->labelVersion->setText(Globals::versionString());
    ui->labelReleaseDate->setText(Globals::releaseDateString());
    ui->labelBuild->setText(QSysInfo::buildCpuArchitecture());
    ui->labelAuthor->setText(Globals::author());
    ui->labelOS->setText(QString("%1 %2-bit")
                            .arg(QSysInfo::prettyProductName(),
                                  QSysInfo::currentCpuArchitecture()));
}
