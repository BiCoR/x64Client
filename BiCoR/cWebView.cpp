//
// Created by Benno Schilling on 21.02.2014
// Released under the GNU General Public License v3
// 

#include "cWebView.h"

void CWebView::closeEvent(QCloseEvent* e){
	emit webViewClosed();
}