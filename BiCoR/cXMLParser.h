//
// Created by Benno Schilling on 21.02.2014
// Released under the GNU General Public License v3
// 

#ifndef CXMLPARSER_H
#define CXMLPARSER_H

#pragma once

#include <vector>

#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>
#include <QString>

#include "cPerson.h"

class CXMLParser{

	public:
		static bool parseFromFilename(QString filename, std::vector<CPerson*>* targetList);
		static bool parseFromString(QString xmlData, std::vector<CPerson*>* targetList);
		static bool parseToken(QString xmlData, QString& token);

	protected:
		static bool parseFromFile(QFile* file, std::vector<CPerson*>* targetList);
		static bool parse(QXmlStreamReader& xmlReader, std::vector<CPerson*>* targetList);
		static bool parseToken(QXmlStreamReader& xmlReader, QString& token);

};

#endif