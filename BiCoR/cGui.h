//
// Created by Benno Schilling on 21.02.2014
// Released under the GNU General Public License v3
// 

#ifndef CGUI_H
#define CGUI_H

#include <QApplication>
#include <QMainWindow>
#include <QTableView>
#include <QHeaderView>
#include <QSortFilterProxyModel>
#include <QAction>
#include <QTimer>
#include <QStatusBar>
#include <QDate>
#include <QMenuBar>
#include <QMenu>
#include <QSettings>
#include <QMessageBox>

#include "cApplication.h"
#include "cPersonModel.h"
#include "cXMLParser.h"
#include "cHTTP.h"
#include "cUserCredentials.h"

class CGUI : public QMainWindow{
	Q_OBJECT

	public:
		CGUI(QWidget* parent = NULL);
		virtual ~CGUI();

	private slots:
		void loginSuccessful(bool);
		void tryLogin(void);

		void showSSLErrorMessage(void);
		void showNetworkErrorMessage(void);

		void renewPersonList(void);
		void checkBirthdayMessage(void);

		void openBrowserNew(void);
		void openBrowserEdit(void);

		void setLanguage(std::string locale);
		void setLanguageGerman(void);
		void setLanguageEnglish(void);

		void credentialsChanged(void);
		void showAboutDialog(void);

	private:

		void loadSettings(void);
		void saveSettings(void);
		void triggerSelectedLanguage(void);

		void createActions(void);
		void createMenu(void);
		void createWidgets(void);		
		void createConnections(void);

		void cleanupPersonList(void);
		void setPeopleVector(std::vector<CPerson*>);

		void syncGUI(void);

		QTableView* tableView;
	    CPersonModel* model;
		QSortFilterProxyModel* proxyModel;
		QTimer* retryConnectionTimer;

		QMenuBar* menuBar;
		QMenu* menu;
		QMenu* account;
		QMenu* people;
		QMenu* language;
		QMenu* about;
		
		QActionGroup* ag;
		QAction* actLangGerman;
		QAction* actLangEnglish;

		QAction* actCloseApp;
		QAction* actNewAccount;
		QAction* actAddUser;
		QAction* actSetCredentials;
		QAction* actAbout;

		std::vector<CPerson*> personList;

		CHTTP* http;

		CUserCredentials* user;
		bool firstRun;
};

#endif