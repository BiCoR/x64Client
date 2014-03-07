//
// Created by Benno Schilling on 21.02.2014
// Released under the GNU General Public License v3
// 

#ifndef CUSERCREDENTIALS_H
#define CUSERCREDENTIALS_H

#pragma once

#include <QString>
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QGroupBox>
#include <QLayout>
#include <QPushButton>
#include <QCheckBox>

class CUserCredentials : public QDialog{

	Q_OBJECT

	signals:
		void credentialsSaved();

	public:
		CUserCredentials(QWidget* parent = NULL);
		virtual ~CUserCredentials();

		QString getEmail(void);
		QString getPassword(void);
		bool getSavePasswordPermanently(void);

		void setEmail(QString);
		void setPassword(QString);
		void setSavePasswordPermanently(bool);

		void translate(void);

	public slots:
		void showAccountDialog(void);

	private slots:
		void saveExit(void);

	private:

		void sync(void);

		QString email;
		QString password;
		bool savePasswordPermanently;

		QLabel* lEmail;
		QLabel* lPassword;		

		QGroupBox* gb;
		QLineEdit* leEmail;
		QLineEdit* lePassword;
		QCheckBox* chkSavePassword;

		QPushButton* ok;
		QPushButton* cancel;

};

#endif