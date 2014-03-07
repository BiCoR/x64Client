//
// Created by Benno Schilling on 21.02.2014
// Released under the GNU General Public License v3
// 

#include "cHTTP.h"

CHTTP::CHTTP(CUserCredentials* _user){
	manager = new QNetworkAccessManager(this);
	view = new CWebView();
	newUrl = QUrl("https://quiet-crag-9089.herokuapp.com/sign_up");
	user = _user;
	connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(response(QNetworkReply*)));
	connect(view,SIGNAL(webViewClosed()),this,SLOT(getFreshDataAfterLogin()));
}

CHTTP::~CHTTP(){
	logout();
	delete manager;
	delete view;
	QWebSettings::clearMemoryCaches();
}

void CHTTP::login(){
	_originalUrl.clear();
	_urlRedirectedTo.clear();
	myToken.clear();
	xmlContent.clear();
	targetUrl.clear();
	editUrl.clear();
	state = 0;	
	doGet(QUrl("https://quiet-crag-9089.herokuapp.com/login.xml"));
}

void CHTTP::getFreshDataAfterLogin(void){
	doGet(targetUrl);
}

void CHTTP::response(QNetworkReply* reply){
		

	/*
		States:
			0 : getToken
			1 : login with Token
			2 : extract targetURL from redirect
			3 : getData
			4 : logout
	*/

	int statuscode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	//qDebug() << " State: " << state;
	if(statuscode == 0){
		//Entweder tatsächlich WLAN/LAN aus oder SSL-Error
		if(QSslSocket::supportsSsl() == false)
			emit sslProblem();
		else
			emit noNetworkAvailable();
		return;
	}	

	if(state == 0){
		state++;
		//Extract Token
		QString response = reply->readAll().data();
		CXMLParser::parseToken(response,myToken);
		//qDebug() << "Token is: " << myToken;

		doPost(QUrl("https://quiet-crag-9089.herokuapp.com/signin"),getParams());
	}
	else if(state == 1){
		state++;
		QVariant possibleRedirectUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
 
		// We'll deduct if the redirection is valid in the redirectUrl function
		_urlRedirectedTo = redirectUrl(possibleRedirectUrl.toUrl(), _urlRedirectedTo);

		//If Url is not empty, do request to Redirect-URL
		if(!_urlRedirectedTo.isEmpty())
			doGet(_urlRedirectedTo);
		else
			emit loginSuccessful(false);
	}
	else if(state == 2)	{		
		state++;
		QString t = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toString();
		//qDebug() << t;
		editUrl = QUrl(t);
		t.append(".xml");
		targetUrl = QUrl(t);
		getFreshDataAfterLogin();
	}
	else if(state == 3){		
		xmlContent = reply->readAll().data();
		if(statuscode == 200)
			emit loginSuccessful(true);
	}
	else
		qDebug() << "Unknown State";
}

void CHTTP::doGet(const QUrl& url){
	manager->get(QNetworkRequest(url));
}
void CHTTP::doPost(const QUrl& url, QUrlQuery params){
	QNetworkRequest req;

	//Set Headers
	if(!myToken.isEmpty()){
		QByteArray ba;
		ba.append(myToken);
		req.setRawHeader("x-csrf-token",ba);
	}
	req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");	
	req.setUrl(url);
	//Do Post Request	
	manager->post(req,QByteArray().append(params.toString()));
}


void CHTTP::replyInfo(QNetworkReply* reply, bool detail){
	qDebug() << "Response #" << state << " received";
	if(detail){
		qDebug() << "\t StatusCode: " << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
		qDebug() << "\t Redirection: " << reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
		qDebug() << "\t Header Cookie Header: " << reply->header(QNetworkRequest::CookieHeader);
		qDebug() << "\t Header User: " << reply->header(QNetworkRequest::UserAgentHeader);
		qDebug() << "\t Header Server: " << reply->header(QNetworkRequest::ServerHeader);
	}	
}

QUrl CHTTP::redirectUrl(const QUrl& possibleRedirectUrl, const QUrl& oldRedirectUrl) const {
	QUrl redirectUrl;
	/*
	 * Check if the URL is empty and
	 * that we aren't being fooled into a infinite redirect loop.
	 * We could also keep track of how many redirects we have been to
	 * and set a limit to it, but we'll leave that to you.
	 */
	if(!possibleRedirectUrl.isEmpty() &&
	   possibleRedirectUrl != oldRedirectUrl) {
		redirectUrl = possibleRedirectUrl;
	}
	return redirectUrl;
}


QUrlQuery CHTTP::getParams(void){
	QUrlQuery params;
	params.addQueryItem("authenticity-token",myToken);
	params.addQueryItem("user[email]", user->getEmail());
	params.addQueryItem("user[password]", user->getPassword());
	return params;
}

QString& CHTTP::getXMLContent(void){
	return xmlContent;
}

void CHTTP::logout(void){
	doGet(QUrl("https://quiet-crag-9089.herokuapp.com/signout"));
}

void CHTTP::openSite(bool isNew){
	
	if(isNew){
		connect(view, SIGNAL(loadFinished(bool)), this, SLOT(showSignupForm(bool)));
		view->load(newUrl);
	}
	else
	{
		connect(view, SIGNAL(loadFinished(bool)), this, SLOT(fillForm(bool)));
		view->load(editUrl);
	}

}

void CHTTP::showSignupForm(bool){
	disconnect(view, SIGNAL(loadFinished(bool)), this, SLOT(showSignupForm(bool)));
	view->showMaximized();
}

void CHTTP::fillForm(bool b){
	
	disconnect(view, SIGNAL(loadFinished(bool)), this, SLOT(fillForm(bool)));
	
	if(!b){
		qDebug() << "Not loaded";
		return;
	}

	QWebFrame* frame = view->page()->currentFrame();
	if (frame == NULL){
		qDebug() << "Frame is null";
		return;
	}

	QWebElement emailField = frame->findAllElements("input[id=user_email]").first();
	QWebElement passwordField = frame->findAllElements("input[id=user_password]").first();
	QWebElement submitButton = frame->findAllElements("input[name=commit]").first();
	
	emailField.setAttribute("value", user->getEmail());
	passwordField.setAttribute("value", user->getPassword());
    submitButton.evaluateJavaScript("this.click()");

	view->showMaximized();

}