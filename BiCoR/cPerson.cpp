//
// Created by Benno Schilling on 21.02.2014
// Released under the GNU General Public License v3
// 

#include "cPerson.h"

CPerson::CPerson(){}
CPerson::CPerson(QString vorname, QString nachname, QString geburtstag){
	setVorname(vorname);
	setNachname(nachname);
	setGeburtstag(geburtstag);
}
CPerson::~CPerson(){}

void CPerson::setVorname(QString s){
	vorname = s;
}
void CPerson::setNachname(QString s){
	nachname = s;
}
void CPerson::setGeburtstag(QString s){
	geburtstag = s;
}

void CPerson::setTelefonFest(QString s){
	telefonFest = s;
}
void CPerson::setTelefonMobil(QString s){
	telefonMobil = s;
}
void CPerson::setEmail(QString s){
	email = s;
}

QString CPerson::getVorname(void) const{
	return vorname;
}
QString CPerson::getNachname(void) const{
	return nachname;
}
QString CPerson::getGeburtstag(void) const{
	return geburtstag;
}
QString CPerson::getTelefonFest(void) const{
	return telefonFest;
}
QString CPerson::getTelefonMobil(void) const{
	return telefonMobil;
}
QString CPerson::getEmail(void) const{
	return email;
}



unsigned int CPerson::getAktuellesAlter(void) const{
	QDate date = QDate::currentDate();
	QDate birthday = QDate::fromString(geburtstag,"yyyy-MM-dd");

	unsigned int age;
	age = date.year() - birthday.year();
	//Geburtstag kommt noch		
	if(birthdayComes())
		age--;

	return age;
}

unsigned int CPerson::getNeuesAlter(void) const{
	return (getAktuellesAlter() + 1);
}

bool CPerson::hasBirthday(void) const{
	QDate date = QDate::currentDate();
	QDate birthday = QDate::fromString(geburtstag,"yyyy-MM-dd");
	return (birthday.month() == date.month() && birthday.day() == date.day());
}

bool CPerson::birthdayComes(void) const{
	QDate date = QDate::currentDate();
	QDate birthday = QDate::fromString(geburtstag,"yyyy-MM-dd");
	if(!hasBirthday())
	{
		//Geburtstag kommt noch		
		if(birthday.month() > date.month() 	|| (birthday.month() == date.month() && birthday.day() > date.day()) )
			return true;
	}
	return false;
}

bool CPerson::birthdayIsOver(void) const{
	return !birthdayComes();
}

bool CPerson::birthdayIsNear(int days) const{
	QDate date = QDate::currentDate();
	QDate birthday = QDate::fromString(geburtstag,"yyyy-MM-dd");
	QDate birthdayThisYear(date.year(),birthday.month(),birthday.day());
	int result = birthdayThisYear.daysTo(date);
	return (result < 0 && abs(result) <= days);
}

QString CPerson::formatGeburtstag(void) const{
	QDate birthday = QDate::fromString(geburtstag,"yyyy-MM-dd");
	QString day,month;
	convertToLeadingZeros(birthday,day,month);

	return QString("%1.%2.%3").arg(day).arg(month).arg(birthday.year());
}

QString CPerson::formatGeburtstagSort(void) const{
	QDate birthday = QDate::fromString(geburtstag,"yyyy-MM-dd");
	QString day,month;
	convertToLeadingZeros(birthday,day,month);
	return QString("%2.%1").arg(day).arg(month);
}

void CPerson::convertToLeadingZeros(QDate& d, QString& day, QString& month) const{
	day = QString("%1").arg(d.day());
	month = QString("%1").arg(d.month());

	if(d.day() < 10)
		day = "0" + day;
	if(d.month() < 10)
		month = "0" + month;
}

//Komparatoren
bool CPerson::compareByDate(CPerson* a,CPerson* b){	
	//Wenn derjenige Geburtstag hat, nach links
	if( a->hasBirthday() && !b->hasBirthday() )	return true;
	if( !a->hasBirthday() && b->hasBirthday() )	return false;
	//Wenn derjenige bald Geburtstag hat, nach links
	if( a->birthdayComes() && !b->birthdayComes())	return true;
	if( !a->birthdayComes() && b->birthdayComes())	return false;
	//Wenn a eher als b Geburtstag hat, nach links
	return (a->formatGeburtstagSort() < b->formatGeburtstagSort());
}

void CPerson::setPosition(unsigned int p){
	position = p;
}
unsigned int CPerson::getPosition(void) const{
	return position;
}



