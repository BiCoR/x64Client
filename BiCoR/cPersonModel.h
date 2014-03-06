//
// Created by Benno Schilling on 21.02.2014
// Released under the GNU General Public License v3
// 

#ifndef CPERSONMODEL_H
#define CPERSONMODEL_H

#pragma once

#include <vector>
#include <QAbstractTableModel>
#include <QBrush>
#include <QFont>
//Link to standard mail client
#include <QDesktopServices>
#include <QUrl>

#include "cPerson.h"

#define BIRTHDAY_VERY_SOON 5 
#define BIRTHDAY_SOON 30

class CPersonModel : public QAbstractTableModel{
	Q_OBJECT

	public slots:
		void reactOnClick(const QModelIndex&);

	public:
		CPersonModel(QObject* parent);
		virtual ~CPersonModel();

		int rowCount(const QModelIndex &parent = QModelIndex()) const ;
	    int columnCount(const QModelIndex &parent = QModelIndex()) const;
		
		QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
		QVariant headerData(int section, Qt::Orientation orientation, int role) const;

		//Custom
		void setPersonList(std::vector<CPerson*>* targetList);
		void enumeratePeople(void);

	private:
		std::vector<CPerson*>* personList;

};

#endif