//
// Created by Benno Schilling on 21.02.2014
// Released under the GNU General Public License v3
// 

#ifndef CHTTP_H
#define CHTTP_H

#include <QObject>
#include <QDebug>

#include <QNetworkAccessManager>

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QTimer>


#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>


#include "cWebView.h"
#include "cXMLParser.h"
#include "cUserCredentials.h"

class CHTTP : public QObject{

	Q_OBJECT

	signals:
		void loginSuccessful(bool);
		void logoutSuccessful(bool);
		void noNetworkAvailable(void);

	public slots:
		void getFreshDataAfterLogin(void);
		

	private slots:
		void response(QNetworkReply*);
		void fillForm(bool);
		void showSignupForm(bool);
		

	public:
		CHTTP(CUserCredentials*);
		virtual ~CHTTP();

		void login(void);
		void logout(void);
		void openSite(bool isNew);

		QString& getXMLContent(void);


	private:
		void replyInfo(QNetworkReply*,bool detail);
		void doGet(const QUrl& url);
		void doPost(const QUrl& url, QUrlQuery data);
		QUrl redirectUrl(const QUrl& possibleRedirectUrl, const QUrl& oldRedirectUrl) const;


		QUrlQuery getParams(void);
		QNetworkAccessManager *manager;
		QUrl _originalUrl;
		QUrl _urlRedirectedTo;
		

		int state;
		QString myToken;
		QString xmlContent;

		QUrl newUrl;
		QUrl editUrl;
		QUrl targetUrl;

		CWebView* view;
		CUserCredentials* user;
		
};

#endif
