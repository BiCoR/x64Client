//
// Created by Benno Schilling on 21.02.2014
// Released under the GNU General Public License v3
// 

#include "cApplication.h"
#include "cGui.h"


#ifdef DEBUG
	#include <vld.h>
#endif

int main(int argc, char *argv[])
{
	CApplication application(argc, argv);

	//Für Settings (Speichern und Laden) benötigt
	application.setOrganizationName("BiCoRem");
	application.setOrganizationDomain("DE");
	application.setApplicationName("BiCoRem");
	application.setApplicationVersion("1.0");

	//Lokalisierung und Internationalisierung
	application.loadTranslations("./lang");

	CGUI w;
	w.showMaximized();
	int i = application.exec();
	return i;
}
