#include "CoopWorkGUI.h"

CoopWorkGUI::CoopWorkGUI(QWidget *parent)
	: QWidget(parent)
{
	
	ui.setupUi(this);

	//禁止窗口缩放
	this->setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
	this->setFixedSize(this->width(), this->height());
	
	this->setWindowIcon(QIcon(":/CoopWorkGUI/Resources/title.png"));
	this->setWindowTitle("LJC&FUJI");

	//设置列表项：双击编辑
	connect(ui.listWidget, &QListWidget::itemDoubleClicked, this, &CoopWorkGUI::editListItem);

	//设置列表项：右键菜单
	ui.listWidget->setProperty("contextMenuPolicy", Qt::CustomContextMenu);
	QMenu* popMenu = new QMenu(this);
	QAction* atn_add = new QAction(tr("Add"), this);
	QAction* atn_delete = new QAction(tr("Delete"), this);
	popMenu->addAction(atn_add);
	popMenu->addSeparator();
	popMenu->addAction(atn_delete);
	connect(atn_add, &QAction::triggered, this, &CoopWorkGUI::onActionAdd);
	connect(atn_delete, &QAction::triggered, this, &CoopWorkGUI::onActionDelete);
	connect(ui.listWidget, &QListWidget::customContextMenuRequested, [=]() {
		popMenu->exec(QCursor::pos());
		isRepaint = true;
		update();
		});

	//设置打开文件的按钮
	connect(ui.pbtn_open, &QPushButton::clicked, [=]() {
		m_FilePath = QFileDialog::getOpenFileName(this, "Open", "C:\\Users\\54135\\Desktop");
		ui.le_filepath->setText(m_FilePath);
		isRepaint = true;
		showList();
		update();
		});

	//设置绘图区域：背景色
	QPalette palette = ui.wdt_scroll->palette();
	palette.setBrush(QPalette::Window, QBrush(QColor(204, 213, 240)));
	ui.wdt_scroll->setAutoFillBackground(true);
	ui.wdt_scroll->setPalette(palette);
	
	//设置绘图区域：滚动条
	QScrollArea* scrollArea = new QScrollArea(ui.widget);
	scrollArea->setWidget(ui.wdt_scroll);
	ui.wdt_scroll->setMinimumSize(1000, 1000);
	QHBoxLayout* pLayout = new QHBoxLayout();
	pLayout->addWidget(scrollArea);
	pLayout->setMargin(0);
	pLayout->setSpacing(0);
	ui.widget->setLayout(pLayout);

	//设置初始位置

	//设置缩放按钮
	void(QSpinBox:: * spinboxSignal)(int) = &QSpinBox::valueChanged;
	connect(ui.spinBox, spinboxSignal, ui.horizontalSlider, &QSlider::setValue);
	connect(ui.spinBox, spinboxSignal, ui.horizontalSlider, [=]() {isRepaint = true; update(); });
	connect(ui.horizontalSlider, &QSlider::valueChanged, ui.spinBox, &QSpinBox::setValue);
	connect(ui.horizontalSlider, &QSlider::valueChanged, this, &CoopWorkGUI::resizeWidget);

	//设置事件分发器
	ui.wdt_scroll->installEventFilter(this);
}

void CoopWorkGUI::showList()
{
	if (m_FilePath.size() == 0) { return; }
	
	QFile file(m_FilePath);
	QStringList graphics;
	QString graphic;

	file.open(QIODevice::ReadOnly);
		
	if (!file.atEnd()) { 
		graphic = file.readLine(); 
	}
	while (!file.atEnd()) {
		graphic = file.readLine();
		graphic.remove('\n');
		graphics << graphic;
	}
	file.close();

	ui.listWidget->clear();
	ui.listWidget->addItems(graphics);
}
void CoopWorkGUI::editListItem(QListWidgetItem* item)
{
	item->setFlags(item->flags() | Qt::ItemIsEditable);
	m_EditIndex = ui.listWidget->currentRow();
	isRepaint = true;
	CoopWorkGUI::update();
}

void CoopWorkGUI::onActionDelete()
{
	QList<QListWidgetItem*> items = ui.listWidget->selectedItems();
	
	if (items.count() <= 0) { return; }

	if (QMessageBox::Yes == QMessageBox::question(this, QStringLiteral("Remove Item")
		, QStringLiteral("Remove %1 items").arg(QString::number(items.count()))
		, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes)) {
		foreach(QListWidgetItem * var, items) {
			ui.listWidget->removeItemWidget(var);
			items.removeOne(var);
			delete var;
		}
	}
	isRepaint = true;
	CoopWorkGUI::update();
}
void CoopWorkGUI::onActionAdd()
{
	ui.listWidget->addItem(tr(""));
	//CoopWorkGUI::update();
}

void CoopWorkGUI::painteGraphics()
{
	QStringList graphics;
	QString graphic;
	vector<string> s_graphics;
	int width = ui.wdt_scroll->width();
	int height = ui.wdt_scroll->height();
	int side = qMin(width, height);
	QPainter painter(ui.wdt_scroll);
	QPen pen;
	int m_scale = 10;

	//设置坐标轴格式
	//pen.setStyle(Qt::DotLine);
	pen.setColor(QColor(0, 0, 0));
	pen.setWidth(2);
	painter.setPen(pen);
	painter.translate(width / 2, height / 2);
	//painter.scale(rect().width(), rect().height());
	//painter.scale(1, -1);
	painter.drawText(QPoint(5, 15), "0");
	painter.drawLine(QPoint(-width, 0), QPoint(width, 0));
	painter.drawLine(QPoint(0, -height), QPoint(0, height));
	for (int i = 100; i < width / 2; i = i + 100) {
		painter.drawLine(QPoint(i, 0), QPoint(i, -5));
		painter.drawText(QPoint(i - 10, 15), QString::number(i / m_scale));
		painter.drawLine(QPoint(-i, 0), QPoint(-i, -5));
		painter.drawText(QPoint(-i - 10, 15), QString::number(-i / m_scale));
	}
	for (int i = 100; i < height / 2; i = i + 100) {
		painter.drawLine(QPoint(0, i), QPoint(5, i));
		painter.drawText(QPoint(-30, i + 5), QString::number(-i / m_scale));
		painter.drawLine(QPoint(0, -i), QPoint(5, -i));
		painter.drawText(QPoint(-25, -i + 5), QString::number(i / m_scale));
	}

	painter.scale(1, -1);

	//逐行画图
	pen.setStyle(Qt::SolidLine);
	pen.setColor(QColor(0, 0, 0));
	pen.setWidth(1);
	painter.setPen(pen);
	for (int i = 0; i < ui.listWidget->count(); i++) {
		graphic = ui.listWidget->item(i)->text();
		graphics << graphic;

		graphic.simplified();

		s_graphics.push_back(graphic.toUtf8().data());

		QStringList paras = graphic.split(" ");
		if (paras.at(0) == "L") {
			long long int x1 = paras.at(1).toInt();
			long long int y1 = paras.at(2).toInt();
			long long int x2 = paras.at(3).toInt();
			long long int y2 = paras.at(4).toInt();
			long long int a = y1 - y2;
			long long int b = x2 - x1;
			long long int c = x1 * y2 - x2 * y1;
			addLine(x1, y1, x2, y2, 0);
			if (b == 0) {
				painter.drawLine(QPoint(x1 * m_scale, -200000 * m_scale), QPoint(x2 * m_scale, 200000 * m_scale));
			}
			else {
				painter.drawLine(QPointF(-200000.0 * m_scale, (-c - a * -200000) / b * m_scale), QPointF(200000.0 * m_scale, (-c - a * 200000) / b * m_scale));
			}
		}
		else  if (paras.at(0) == "R") {
			long long int x1 = paras.at(1).toInt();
			long long int y1 = paras.at(2).toInt();
			long long int x2 = paras.at(3).toInt();
			long long int y2 = paras.at(4).toInt();
			long long int a = y1 - y2;
			long long int b = x2 - x1;
			long long int c = x1 * y2 - x2 * y1;
			addLine(x1, y1, x2, y2, 1);
			if (b == 0) {
				painter.drawLine(QPoint(x1 * m_scale, y1 * m_scale), QPoint(x2 * m_scale, 200000 * m_scale));
			}
			else if (b > 0) {
				painter.drawLine(QPointF(x1 * m_scale, y1 * m_scale), QPointF(200000.0 * m_scale, (-c - a * 200000) / b * m_scale));
			}
			else {
				painter.drawLine(QPointF(x1 * m_scale, y1 * m_scale), QPointF(-200000.0 * m_scale, (-c - a * -200000) / b * m_scale));

			}
		}
		else if (paras.at(0) == "S") {
			addLine(paras.at(1).toInt(), paras.at(2).toInt(), paras.at(3).toInt(), paras.at(4).toInt(), 2);
			painter.drawLine(QPoint(paras.at(1).toInt() * m_scale, paras.at(2).toInt() * m_scale),
				QPoint(paras.at(3).toInt() * m_scale, paras.at(4).toInt() * m_scale));
		}
		else if (paras.at(0) == "C") {
			addCircle(paras.at(1).toInt(), paras.at(2).toInt(), paras.at(3).toInt());
			painter.drawEllipse(QPoint(paras.at(1).toInt() * m_scale, paras.at(2).toInt() * m_scale),
				paras.at(3).toInt() * m_scale, paras.at(3).toInt() * m_scale);
		}
		else {
		}
	}
	
	if (!ui.radioButton->isChecked()) { return;	}
	pen.setColor(QColor(255, 0, 0));
	pen.setWidth(5);
	painter.setPen(pen);
	vector < pair<double, double> > realIntersections;
	solve(realIntersections);
	qDebug() << realIntersections.size();
	for each (pair<double, double> var in realIntersections) {
		painter.drawPoint(var.first* m_scale, var.second* m_scale);
	}

}

void CoopWorkGUI::resizeWidget(int value) 
{
	qDebug() << "resize";
	ui.wdt_scroll->resize(1000 + 3990 * value, 1000 + 3990 * value);
	isRepaint = true;
	CoopWorkGUI::update();
}


bool CoopWorkGUI::eventFilter(QObject* obj, QEvent* ev)
{
	if (obj == ui.wdt_scroll && ev->type() == QEvent::Paint/* && isRepaint*/) {
		//画图
		isRepaint = false;
		painteGraphics();

		return true;
	}
	else {
		return QWidget::eventFilter(obj, ev);
	}
}



