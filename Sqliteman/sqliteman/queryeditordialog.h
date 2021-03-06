/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/

#ifndef QUERYEDITORDIALOG_H
#define QUERYEDITORDIALOG_H

class QTreeWidgetItem;

#include "database.h"
#include "ui_queryeditordialog.h"

/*!
 * @brief A dialog for creating and editing queries
 * \author Igor Khanin
 * \author Petr Vanek <petr@scribus.info>
 */
class QueryEditorDialog : public QDialog, public Ui::QueryEditorDialog
{
	Q_OBJECT

	public:
		/*!
		 * @brief Creates the query editor.
		 * @param parent The parent widget for the dialog.
		 */
		QueryEditorDialog(QWidget * parent = 0);
		~QueryEditorDialog();
		void setItem(QTreeWidgetItem * item);
		//! \brief generates a valid SQL statement using the values in the dialog
		QString statement();
		void treeChanged();
		void tableAltered(QString oldName, QTreeWidgetItem * item);
};

#endif //QUERYEDITORDIALOG_H
