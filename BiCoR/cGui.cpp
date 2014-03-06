//
// Created by Benno Schilling on 21.02.2014
// Released under the GNU General Public License v3
// 

#include "cGui.h"

CGUI::CGUI(QWidget* parent) : QMainWindow(parent){

	firstRun = true;
	user = new CUserCredentials();
	http = new CHTTP(user);

	personList.clear();

	createActions();
	createMenu();
	createWidgets();
	createConnections();

	//Sprache und Login-Daten laden
	loadSettings();
	

	syncGUI();

	if(firstRun == true){
		QMessageBox::StandardButton reply;
		reply = QMessageBox::question(this, tr("First run of Application"), tr("Create a new Account?"), QMessageBox::Yes|QMessageBox::No);
		if(reply == QMessageBox::Yes)
			openBrowserNew();
		else
			tryLogin();
	}
	else
		tryLogin();
	

}
CGUI::~CGUI(){
	cleanupPersonList();
	saveSettings();
	delete user;
	delete http;
}

void CGUI::loadSettings(void){
	
    QSettings settings;
    QString email = settings.value("email", "user@example.org").toString();
	QString password = settings.value("password", "user@example.org").toString();
	firstRun = settings.value("firstRun", true).toBool();
	actLangGerman->setChecked(settings.value("germanSelected", false).toBool());
	actLangEnglish->setChecked(settings.value("englishSelected", true).toBool());

	triggerSelectedLanguage();

	user->setEmail(email);
	user->setPassword(password);
    
}
void CGUI::saveSettings(void){
	QSettings settings;
    settings.setValue("email", user->getEmail());
	settings.setValue("password", user->getPassword());
	settings.setValue("germanSelected", actLangGerman->isChecked());
	settings.setValue("englishSelected", actLangEnglish->isChecked());

	settings.setValue("firstRun", false);
}

void CGUI::createActions(void){
	//Close
	actCloseApp = new QAction(this);
	actCloseApp->setShortcut(Qt::Key_Escape);

	actAddUser = new QAction(this);
	actAddUser->setDisabled(true);

	actNewAccount = new QAction(this);

	actLangEnglish = new QAction(this);
	actLangEnglish->setCheckable(true);
	actLangGerman = new QAction(this);
	actLangGerman->setCheckable(true);

	actSetCredentials = new QAction(this);
	actAbout = new QAction(this);

	ag = new QActionGroup(this);
	ag->setExclusive(true);
	ag->addAction(actLangGerman);
	ag->addAction(actLangEnglish);

}
void CGUI::createMenu(void){
	menuBar = new QMenuBar(this);
	menu = new QMenu(this);
	menu->addAction(actCloseApp);

	account = new QMenu(this);
	account->addAction(actNewAccount);
	account->addAction(actSetCredentials);

	people = new QMenu(this);
	people->addAction(actAddUser);

	language = new QMenu(this);
	language->addAction(actLangGerman);
	language->addAction(actLangEnglish);

	about = new QMenu(this);
	about->addAction(actAbout);

	menuBar->addMenu(menu);
	menuBar->addMenu(account);
	menuBar->addMenu(people);
	menuBar->addMenu(language);
	menuBar->addMenu(about);

	setMenuBar(menuBar);
}
void CGUI::createWidgets(void){
	
	//Timer
	retryConnectionTimer = new QTimer(this);

	//View
	tableView = new QTableView(this);
	tableView->setSortingEnabled(true);
	tableView->horizontalHeader()->setStretchLastSection(true);
	tableView->horizontalHeader()->setStretchLastSection(true);

	//Create and fill Model
    model = new CPersonModel(tableView);
	model->setPersonList(&personList);

	//Enable Sorting via ProxyModel and assign it to View
	proxyModel = new QSortFilterProxyModel(tableView);		
	proxyModel->setSourceModel(model);
    tableView->setModel(proxyModel);	
	

	//Layout
	setCentralWidget(tableView);
}

void CGUI::createConnections(void){
	connect(actCloseApp,SIGNAL(triggered()),this,SLOT(close()));
	connect(actNewAccount,SIGNAL(triggered()),this,SLOT(openBrowserNew()));
	connect(actAddUser,SIGNAL(triggered()),this,SLOT(openBrowserEdit()));

	connect(actSetCredentials,SIGNAL(triggered()),user,SLOT(showAccountDialog()));
	connect(actAbout,SIGNAL(triggered()),this,SLOT(showAboutDialog()));

	//Language
	connect(actLangGerman,SIGNAL(triggered()),this,SLOT(setLanguageGerman()));
	connect(actLangEnglish,SIGNAL(triggered()),this,SLOT(setLanguageEnglish()));

	//Network
	connect(http,SIGNAL(noNetworkAvailable(void)),this,SLOT(showNetworkErrorMessage(void)));
	connect(http,SIGNAL(loginSuccessful(bool)),this,SLOT(loginSuccessful(bool)));
	connect(user,SIGNAL(credentialsSaved()),this,SLOT(credentialsChanged()));

	//Custom Links
	connect(tableView,SIGNAL(clicked(const QModelIndex&)), model, SLOT(reactOnClick(const QModelIndex&)));

}

void CGUI::syncGUI(void){

	//App-Titel
	setWindowTitle(tr("BiCoRem - Birthday Contact Reminder"));

	menu->setTitle(tr("&Menu"));
	language->setTitle(tr("&Language"));
	account->setTitle(tr("&Account"));
	people->setTitle(tr("&People"));
	about->setTitle(tr("A&bout"));

	actNewAccount->setText(tr("&Create"));
	actAddUser->setText(tr("&Manage"));
	actCloseApp->setText(tr("Close Application"));
	actSetCredentials->setText(tr("&Edit"));
	actLangEnglish->setText(tr("&English"));
	actLangGerman->setText(tr("&Deutsch"));
	actAbout->setText(tr("A&bout"));

	user->translate();
}

void CGUI::tryLogin(void){
	statusBar()->showMessage(tr("Try to login onto Webservice..."));
	http->login();
}

void CGUI::loginSuccessful(bool b){
	if(!b){
		statusBar()->showMessage(tr("Invalid E-Mail or Password..."));
		actAddUser->setEnabled(false);
		user->showAccountDialog();
	}
	else
	{
		statusBar()->showMessage(tr("Login successful..."));
		actAddUser->setEnabled(true);
		renewPersonList();
	}
}


void CGUI::cleanupPersonList(void){
	std::vector<CPerson*>::const_iterator it;
	it = personList.begin();
	while(it != personList.end()){
		delete *it;
		it++;
	}	
}

void CGUI::renewPersonList(void){
	cleanupPersonList();
		
	CXMLParser::parseFromString(http->getXMLContent(), &personList);
	model->enumeratePeople();

	proxyModel->invalidate();
	checkBirthdayMessage();
	//Alle 5 Minuten reicht dicke aus
	QTimer::singleShot(5*60*1000, http, SLOT(getFreshDataAfterLogin()));
}

void CGUI::setPeopleVector(std::vector<CPerson*> pl){
	personList = pl;
}

void CGUI::showNetworkErrorMessage(void){
	statusBar()->showMessage(tr("Network is currently not available... Retry in 5 seconds"));
	QTimer::singleShot(5000, this, SLOT(tryLogin()));
}

void CGUI::checkBirthdayMessage(void){

	std::vector<CPerson*>::const_iterator it;
	std::vector<CPerson*> todaysBirthday;
	it = personList.begin();
	while(it != personList.end()){
		if((*it)->hasBirthday())
			todaysBirthday.push_back(*it);
		it++;
	}	

	//Werte diejenigen aus, die Geburtstag haben
	it = todaysBirthday.begin();
	QString msg;
	while(it != todaysBirthday.end()){
		msg.push_back((*it)->getVorname());
		it++;
		if(it != todaysBirthday.end())
			msg.push_back(", ");
	}	

	if(msg.isEmpty())
		statusBar()->showMessage(tr("Nobody has birthday today"));
	else{
		msg.push_front(tr("Today's birthdays: "));
		statusBar()->showMessage(msg);
	}

}


void CGUI::openBrowserEdit(void){
	http->openSite(false);
}

void CGUI::openBrowserNew(void){
	http->openSite(true);
}

void CGUI::setLanguage(std::string locale){
	CApplication::setLanguage(QString::fromStdString(locale));
	syncGUI();
}

void CGUI::setLanguageGerman(void){
	setLanguage("de");
}

void CGUI::setLanguageEnglish(void){
	setLanguage("en");
}

void CGUI::triggerSelectedLanguage(void){
	foreach(QAction* a, ag->actions()){
		if(a->isChecked())
			a->trigger();
	}
}

void CGUI::credentialsChanged(void){
	http->logout();
	QTimer::singleShot(1000, this, SLOT(tryLogin()));
}

void CGUI::showAboutDialog(void){
	QMessageBox	msg;
	msg.setWindowTitle(tr("About"));
	msg.setText( "BiCoRem v1.0\n\n" + tr("Written by") + ": \n\tBenno Schilling (Client)\n\tMarkus Hinkelmann (iOS app)\n\tMike Feustel (Server)\n\n" + tr("Contact us") + ":\n\t" + "bicorem@mhinkelmann.de");
	msg.exec();
}
