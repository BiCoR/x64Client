//
// Created by Benno Schilling on 21.02.2014
// Released under the GNU General Public License v3
// 

#include "cXMLParser.h"

bool CXMLParser::parseFromFilename(QString filename, std::vector<CPerson*>* targetList){
	QFile xmlFile(filename);
	bool result;
	if (!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)){
		qDebug("Error reading source file");
		result = false;
	}
	else
		result = parseFromFile(&xmlFile, targetList);	

	xmlFile.close();
	return result;

}

bool CXMLParser::parseFromFile(QFile* file, std::vector<CPerson*>* targetList){
	QXmlStreamReader xmlReader(file);
	return parse(xmlReader, targetList);
}

bool CXMLParser::parseFromString(QString xmlData, std::vector<CPerson*>* targetList){
	QXmlStreamReader xmlReader(xmlData);
	return parse(xmlReader, targetList);
}

bool CXMLParser::parseToken(QString xmlData, QString& token){
	QXmlStreamReader xmlReader(xmlData);
	return parseToken(xmlReader, token);
}

bool CXMLParser::parse(QXmlStreamReader& xmlReader, std::vector<CPerson*>* targetList){

	//Liste leer machen
	targetList->clear();

	QStringRef tagName;

	//Parse the XML until we reach end of it
	while(!xmlReader.atEnd() && !xmlReader.hasError()) {
		// Read next element
		QXmlStreamReader::TokenType token = xmlReader.readNext();

		//If token is just StartDocument - go to next
		if(token == QXmlStreamReader::StartDocument) 
			continue;

		tagName = xmlReader.name();

		//Start-Tags
		if(token == QXmlStreamReader::StartElement) {
			if(tagName == "person"){
				//qDebug("Creating Person (adding to List)");
				targetList->push_back(new CPerson());
			}

			if(tagName == "first-name")
				targetList->back()->setVorname(xmlReader.readElementText());
			if(tagName == "last-name")
				targetList->back()->setNachname(xmlReader.readElementText());
			if(tagName == "geburtsdatum")
				targetList->back()->setGeburtstag(xmlReader.readElementText());		
		}

		//End-Tags
		if(token == QXmlStreamReader::EndElement) {
			/*
			if(tagName == "person")
				qDebug("Closing Person (finished read Attributes)");
			*/
		}

	}

	bool error = xmlReader.hasError();
	xmlReader.clear();

	if(error) {
		qDebug(QString("Errors occured: %1").arg(xmlReader.errorString()).toLatin1());
		return false;
	}
	else
		return true;
}


bool CXMLParser::parseToken(QXmlStreamReader& xmlReader, QString& authToken){

	QStringRef tagName;

	//Parse the XML until we reach end of it
	while(!xmlReader.atEnd() && !xmlReader.hasError()) {
		// Read next element
		QXmlStreamReader::TokenType token = xmlReader.readNext();

		//If token is just StartDocument - go to next
		if(token == QXmlStreamReader::StartDocument) 
			continue;

		tagName = xmlReader.name();

		//Start-Tags
		if(token == QXmlStreamReader::StartElement) {
			if(tagName == "authenticity-token"){
				authToken = xmlReader.readElementText();
				return true;
			}
		}

	}

	return false;
}