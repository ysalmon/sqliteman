/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/

#ifndef CREATEVIEWDIALOG_H
#define CREATEVIEWDIALOG_H

#include <qwidget.h>

#include "litemanwindow.h"
#include "tableeditordialog.h"

class QTreeWidgetItem;
class QPushButton;

/*! \brief GUI for view creation
\author Petr Vanek <petr@scribus.info>
*/
class CreateViewDialog : public TableEditorDialog
{
	Q_OBJECT

	public:
		CreateViewDialog(LiteManWindow * parent = 0,
						  QTreeWidgetItem * item = 0);
		~CreateViewDialog(){};
		void setText(QString query);
		void setSql(QString query);
		bool event(QEvent * e);

	private:

		int oldColumnNumber(int i) { return -1; };
		bool checkRetained(int i);
		bool checkColumn(int i, QString cname,
						 QString ctype, QString cextra);

		QPushButton * m_createButton;
		
	signals:
		/*! \brief Rebuild part of the tree */
		void rebuildViewTree(QString schema, QString name);

	private slots:
		void createButton_clicked();
		void checkChanges();
		void databaseChanged(int);
};

#endif
