//
// Created by Benno Schilling on 21.02.2014
// Released under the GNU General Public License v3
// 

#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QHash>
#include <QStringList>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QTranslator>
#include <QIcon>


typedef QHash<QString, QTranslator*> Translators;

class CApplication : public QApplication
{
	Q_OBJECT

	public:
		explicit CApplication(int& argc, char* argv[]);
		~CApplication();

		static void loadTranslations(const QString& dir);
		static void loadTranslations(const QDir& dir);
		static const QStringList availableLanguages();

	public slots:
		static void setLanguage(const QString& locale);

	private:
		static QTranslator* current;
		static Translators translators;
};

#endif // APPLICATION_H
