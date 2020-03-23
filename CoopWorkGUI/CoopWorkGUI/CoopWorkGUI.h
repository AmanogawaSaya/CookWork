#pragma once
//#pragma comment(lib,"CoopWork.lib")

#include <QtWidgets/QWidget>
#include "ui_CoopWorkGUI.h"
#include <QFile>
#include <QPushButton>
#include <QFileDialog>
#include <QAction>
#include <QMenu>
#include <QMessageBox>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QPainter>
#include <QDebug>
#include <QLabel>
#include <QLibrary>
#include <iostream>

#include "../include/combine.h"
using namespace std;


class CoopWorkGUI : public QWidget
{
	Q_OBJECT

public:
	CoopWorkGUI(QWidget *parent = Q_NULLPTR);

private:
	Ui::CoopWorkGUIClass ui;
	QString m_FilePath;
	QString m_EditIndex;
	//MySet m_Points;
	bool m_IsShowPoints;
	bool isRepaint; 
	void showList();
	void editListItem(QListWidgetItem* item);
	void onActionAdd();
	void onActionDelete();
	void painteGraphics();
	void resizeWidget(int value);
	bool eventFilter(QObject* obj, QEvent* ev);
};
