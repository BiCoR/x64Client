//
// Created by Benno Schilling on 21.02.2014
// Released under the GNU General Public License v3
// 

#include "cUserCredentials.h"

CUserCredentials::CUserCredentials(QWidget* parent) : QDialog(parent){
	
	setModal(true);
	setMinimumWidth(400);

	lEmail = new QLabel(this);
	lPassword = new QLabel(this);

	leEmail = new QLineEdit(this);
	lePassword = new QLineEdit(this);
	lePassword->setEchoMode(QLineEdit::Password);

	gb = new QGroupBox(this);
	QGridLayout* innerLayout = new QGridLayout();
	QVBoxLayout* mainLayout = new QVBoxLayout;
	QHBoxLayout* buttonLayout = new QHBoxLayout;

	//Beschreibung
	ok = new QPushButton(this);
	ok->setShortcut(QKeySequence::Save);
	cancel = new QPushButton(this);

	innerLayout->addWidget(lEmail,0,0);
	innerLayout->addWidget(leEmail,0,1);
	innerLayout->addWidget(lPassword,1,0);
	innerLayout->addWidget(lePassword,1,1);
	
	buttonLayout->addWidget(ok);
	buttonLayout->addWidget(cancel);

	gb->setLayout(innerLayout);
	mainLayout->addWidget(gb);
	mainLayout->addLayout(buttonLayout);
	setLayout(mainLayout);

	QObject::connect(ok,SIGNAL(clicked()),this,SLOT(saveExit()));
	QObject::connect(cancel,SIGNAL(clicked()),this,SLOT(reject()));

	translate();


}
CUserCredentials::~CUserCredentials(){}

void CUserCredentials::sync(void){
	leEmail->setText(getEmail());
	lePassword->setText(getPassword());
}

void CUserCredentials::showAccountDialog(void){
	sync();
	show();
}

QString CUserCredentials::getEmail(void){
	return email;
}
QString CUserCredentials::getPassword(void){
	return password;
}

void CUserCredentials::setEmail(QString s){
	email = s;
}
void CUserCredentials::setPassword(QString s){
	password = s;
}

void CUserCredentials::saveExit(void){
	setEmail(leEmail->text());
	setPassword(lePassword->text());
	accept();
	emit credentialsSaved();
}

void CUserCredentials::translate(void){
	lEmail->setText(tr("Email") + ": ");
	lPassword->setText(tr("Password") + ": ");
	gb->setTitle(tr("Account information"));
	ok->setText(tr("Save"));
	cancel->setText(tr("Cancel"));
}