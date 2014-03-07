//
// Created by Benno Schilling on 21.02.2014
// Released under the GNU General Public License v3
// 


#include "cApplication.h"


QTranslator* CApplication::current = 0;
Translators CApplication::translators;

CApplication::CApplication(int& argc, char* argv[])
	: QApplication(argc, argv)
{
	//Icon
	QIcon icon("./bicorem.png");
	setWindowIcon(icon);	
	//Für Settings (Speichern und Laden) benötigt
	setOrganizationName("BiCoRem");
	setOrganizationDomain("DE");
	setApplicationName("BiCoRem");
	setApplicationVersion("BiCoRem v1.1");
	//Lokalisierung und Internationalisierung
	loadTranslations("./lang");
}

CApplication::~CApplication(){
	delete current;
}

void CApplication::loadTranslations(const QString& dir)
{
	loadTranslations(QDir(dir));
}

void CApplication::loadTranslations(const QDir& dir)
{
	// <language>_<country>.qm
	QString filter = "*_*.qm";
	QDir::Filters filters = QDir::Files | QDir::Readable;
	QDir::SortFlags sort = QDir::Name;
	QFileInfoList entries = dir.entryInfoList(QStringList() << filter, filters, sort);
	foreach (QFileInfo file, entries)
	{
		qDebug() << file.absoluteFilePath();
		// pick country and language out of the file name
		QStringList parts = file.baseName().split("_");
		QString language = parts.at(parts.count() - 2).toLower();
		QString country  = parts.at(parts.count() - 1).toLower();

		// construct and load translator
		QTranslator* translator = new QTranslator(instance());
		if (translator->load(file.absoluteFilePath()))
		{
			QString locale = language + "_" + country;
			translators.insert(locale, translator);
		}
	}
}

const QStringList CApplication::availableLanguages()
{
	// the content won't get copied thanks to implicit sharing and constness
	return QStringList(translators.keys());
}

void CApplication::setLanguage(const QString& locale)
{
	// remove previous
	if (current)
		removeTranslator(current);

	// install new
	current = translators.value("bicorem_"+locale, 0);
	if (current)
		installTranslator(current);
}
