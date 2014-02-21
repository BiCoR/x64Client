//
// Created by Benno Schilling on 21.02.2014
// Released under the GNU General Public License v3
// 

#ifndef CWebView_H
#define CWebView_H

#include <QWebView>

class CWebView : public QWebView{

	Q_OBJECT

	signals:
		void webViewClosed(void);

	protected:
		virtual void closeEvent(QCloseEvent*);

};

#endif