/**
 * @file About.h
 * @author shaozk (913667678@qq.com)
 * @brief 关于界面
 * @version 0.1
 * @date 2025-03-26
 * 
 * @copyright Copyright (c) shaozk
 * 
 */

#pragma once

#include <QDialog>

namespace Ui {
	class About;
}

class About : public QDialog 
{
	Q_OBJECT
public:
	About(QWidget* parent = nullptr);

private:
	Ui::About* ui;
};

