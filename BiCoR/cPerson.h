//
// Created by Benno Schilling on 21.02.2014
// Released under the GNU General Public License v3
// 

#ifndef CPERSON_H
#define CPERSONL_H

#pragma once

#include <QString>
#include <QDate>
#include <QDebug>

class CPerson{

	public:
		CPerson();
		CPerson(QString vorname, QString nachname, QString geburtstag);
		virtual ~CPerson();

		void setVorname(QString);
		void setNachname(QString);
		void setGeburtstag(QString);
		void setTelefonFest(QString);
		void setTelefonMobil(QString);
		void setEmail(QString);

		void setPosition(unsigned int);

		QString getVorname(void) const;
		QString getNachname(void) const;
		QString getGeburtstag(void) const;
		QString getTelefonFest(void) const;
		QString getTelefonMobil(void) const;
		QString getEmail(void) const;

		unsigned int getPosition(void) const;
		unsigned int getAktuellesAlter(void) const;
		unsigned int getNeuesAlter(void) const;

		bool hasBirthday(void) const;
		bool birthdayComes(void) const;
		bool birthdayIsOver(void) const;
		bool birthdayIsNear(int days) const;
		bool birthdayIsFuture(void) const;

		static bool compareByDate(CPerson* a,CPerson* b);

		QString formatGeburtstag(void) const;
		QString formatGeburtstagSort(void) const;
		void convertToLeadingZeros(QDate& d, QString& day, QString& month) const;

	private:
		QString vorname;
		QString nachname;
		QString geburtstag;

		//Additional Info
		QString telefonFest;
		QString telefonMobil;
		QString email;

		unsigned int position;
};

#endif