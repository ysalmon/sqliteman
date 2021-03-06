/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/

#ifndef LITEMANWINDOW_H
#define LITEMANWINDOW_H

#include <QMainWindow>
#include <QPointer>
#include <QMap>

class QAction;
class QLabel;
class QMenu;
class QSplitter;
class QTreeWidgetItem;

class DataViewer;
class HelpBrowser;
class QueryEditorDialog;
class SchemaBrowser;
class SqlEditor;
class SqlQueryModel;

/*!
 * @brief The main window for LiteMan
 * 
 * This class creates and manages the main window of LiteMan, and preety much everything in it. It 
 * handles actions as well as triggeres other dialogs and windows.
 *
 * \author Igor Khanin
 * \author Petr Vanek <petr@scribus.info>
 */
class LiteManWindow : public QMainWindow
{
		Q_OBJECT
	public:
		LiteManWindow(const QString & fileToOpen = 0);
		~LiteManWindow();

		//! \brief Set the chosen language (used in the translator) to localize help too.
		void setLanguage(QString l) { m_lang = l; };

		QString mainDbPath() { return m_mainDbPath; };
		bool checkForPending();
		void checkForCatalogue();
		void createViewFromSql(QString query);
		void setTableModel(SqlQueryModel * model);

		QueryEditorDialog * queryEditor;

	signals:
		void prefsChanged();

	private:
		void initUI();
		void initActions();
		void initMenus();
		void initRecentDocs();

		/*!
		\brief Reads basic window settings
		This method restores the main window to its previous state by loading the window's
 		position, size and splitter position from the settings.
 		*/
		void readSettings();

		/*!
		\brief Saves basic window settings
		This method saves the main window's state (should be done upon closure) - the window's
		position, size and splitter position - to the settings, so it could be saved over sessions.
		*/
		void writeSettings();

// 		void runQuery(QString statement);

		void updateRecent(QString fn);
		void removeRecent(QString fn);
		void rebuildRecentFileMenu();

		/*! \brief The real "open db" method.
		\param fileName a string prepared by newDB(), open(), and openRecent()
		*/
		void openDatabase(const QString & fileName);

#ifdef ENABLE_EXTENSIONS
		//! \brief Setup loading extensions actions and environment depending on prefs.
		void handleExtensions(bool enable);
#endif

		void setActiveItem(QTreeWidgetItem * item);
		void describeObject(QString type);

	protected:
		/*! \brief This method handles closing of the main window by saving the window's state and accepting
		the event. */
		void closeEvent(QCloseEvent * e);

	private slots:
		/*! \brief A slot to handle a new database file createion action */
		void newDB();

		/*! \brief A slot to handle an opening of an existing database file action.
		\param file An optional parameter denoting a file name to open. If this parameter
		is present, the file dialog will not be shown. */
		void open(const QString & file = QString());
		void openRecent();
		void about();
		void aboutQt();
		void help();
		void preferences();

		void buildQuery();
		void contextBuildQuery();
		void execSql(QString query);
		void exportSchema();
		void dumpDatabase();

		void createTable();
		void dropTable();
		void alterTable();
		void populateTable();
		void importTable();
		void emptyTable();

		void createView();
		void dropView();
		void alterView();

		void createIndex();
		void dropIndex();

		void describeTable();
		void describeTrigger();
		void describeView();
		void describeIndex();
		void reindex();

		void treeItemActivated(QTreeWidgetItem * item, int column);
		void treeContextMenuOpened(const QPoint & pos);
		void tableTree_currentItemChanged(QTreeWidgetItem* cur, QTreeWidgetItem* prev);

		void handleSqlEditor();
		void handleObjectBrowser();
		void handleDataViewer();

		void analyzeDialog();
		void vacuumDialog();
		void attachDatabase();
		void detachDatabase();
		void loadExtension();

		void createTrigger();
		void alterTrigger();
		void dropTrigger();

		void constraintTriggers();

		void refreshTable();

	private:
		QStringList recentDocs;

		QString m_mainDbPath;
		QString m_appName;
		QString m_lang;
		QTreeWidgetItem * m_activeItem;
		QLabel * m_sqliteVersionLabel;

		// \brief True if is sqlite3 binary available in the path
// 		bool m_sqliteBinAvailable;

		/*! \brief alias name - connection name mappings
		It's used for mapping of the attached databases for QSqlTableModel
		as it does not support database.table naming schema */
		QMap<QString,QString> attachedDb;

		DataViewer * dataViewer;
		QSplitter * splitter;
		SchemaBrowser * schemaBrowser;
		SqlEditor* sqlEditor;
		QSplitter* splitterSql;
		HelpBrowser * helpBrowser;
		
		QMenu * databaseMenu;
		QMenu * adminMenu;
		QMenu * recentFilesMenu;
		QMenu * contextMenu;

		QAction * newAct;
		QAction * openAct;
		QAction * recentAct;
		QAction * exitAct;
		QAction * aboutAct;
		QAction * aboutQtAct;
		QAction * helpAct;
		QAction * preferencesAct;
		
		QAction * createTableAct;
		QAction * dropTableAct;
		QAction * alterTableAct;
		QAction * describeTableAct;
		QAction * importTableAct;
		QAction * emptyTableAct;
		QAction * populateTableAct;

		QAction * createViewAct;
		QAction * dropViewAct;
		QAction * describeViewAct;
		QAction * alterViewAct;

		QAction * createIndexAct;
		QAction * dropIndexAct;
		QAction * describeIndexAct;
		QAction * reindexAct;

		QAction * createTriggerAct;
		QAction * alterTriggerAct;
		QAction * dropTriggerAct;
		QAction * describeTriggerAct;

		QAction * execSqlAct;
		QAction * objectBrowserAct;
		QAction * dataViewerAct;
		QAction * buildQueryAct;
		QAction * contextBuildQueryAct;
		QAction * exportSchemaAct;
		QAction * dumpDatabaseAct;

		QAction * analyzeAct;
		QAction * vacuumAct;
		QAction * attachAct;
		QAction * detachAct;
#ifdef ENABLE_EXTENSIONS
		QAction * loadExtensionAct;
#endif
		QAction * refreshTreeAct;

		QAction * consTriggAct;
};

#endif
