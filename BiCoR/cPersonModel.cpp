//
// Created by Benno Schilling on 21.02.2014
// Released under the GNU General Public License v3
// 

#include "cPersonModel.h"

CPersonModel::CPersonModel(QObject* parent) : QAbstractTableModel(parent){}
CPersonModel::~CPersonModel(){}

int CPersonModel::rowCount(const QModelIndex & /*parent*/) const
{
   return personList->size();
}

int CPersonModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 8;
}

QVariant CPersonModel::data(const QModelIndex &index, int role) const
{
	//Person abfragen
	CPerson* p = (*personList)[index.row()];

	//QDecorationRole)
	if (role == Qt::BackgroundRole){            
		if (p->hasBirthday())                
			return QColor(Qt::white);            
		else if(p->birthdayIsNear(BIRTHDAY_VERY_SOON))
			return QColor(Qt::white);
		else if(p->birthdayIsNear(BIRTHDAY_SOON))                
			return QColor(Qt::white);
		else if(p->birthdayIsOver())
			return QColor(Qt::white);
		else //Birthday comes but it is enough time
			return QColor(Qt::white);
	}
	else if(role == Qt::ForegroundRole){
		if (p->hasBirthday())                
			return QColor(Qt::darkGreen);
		else if(p->birthdayIsNear(BIRTHDAY_VERY_SOON))
			return QColor(Qt::red);
		else if(p->birthdayIsNear(BIRTHDAY_SOON))                
			return QColor(255,127,0);
		else if(p->birthdayIsOver())
			return QColor(Qt::gray);
		else //Birthday comes but it is enough time                
			return QColor(Qt::black);	
	} 
	else if(role == Qt::FontRole){
		if (p->hasBirthday())                
			return QFont("Arial",10);
		else if(p->birthdayIsOver())
			return QFont("Arial",10);
		else                
			return QFont("Arial",10);
	} 
	else if (role == Qt::DisplayRole){

		switch(index.column()){		
			case 0:
				if(p->getPosition() < 10)
					return QString("0%1").arg(p->getPosition());
				else
					return QString("%1").arg(p->getPosition());
			break;
			case 1:
				return QString("%1").arg(p->getVorname());
			break;
			case 2:
				return QString("%1").arg(p->getNachname());
			break;
			case 3:
				return QString("%1").arg( p->formatGeburtstag());
			break;
			case 4:
				if(p->birthdayIsFuture())
					return QString("---");
				else
					return QString("%1").arg(p->getAktuellesAlter());
			break;
			case 5:
				return QString("%1").arg(p->getTelefonMobil());
			break;
			case 6:
				return QString("%1").arg(p->getTelefonFest());				
			break;
			case 7:
				return QString("%1").arg(p->getEmail());
			break;

			default:
				return QString("no data");
			break;
		}
	}
	return QVariant();
}

QVariant CPersonModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role == Qt::DisplayRole){
        if (orientation == Qt::Horizontal) {
            switch (section){
				case 0:
					return QString(tr("Birthday soon"));
				break;
				case 1:
					return QString(tr("First name"));
				break;
				case 2:
					return QString(tr("Surname"));
				break;
				case 3:
					return QString(tr("Birthday"));
				break;
				case 4:
					return QString(tr("Current age"));
				break;
				case 5:
					return QString(tr("Mobile"));
				break;
				case 6:
					return QString(tr("Telephone"));
				break;
				case 7:
					return QString(tr("Email"));
				break;

				default:
					return QString("No description");
				break;
            }
        }
    }
    return QVariant();
}


void CPersonModel::setPersonList(std::vector<CPerson*>* targetList){
	personList = targetList;
}

void CPersonModel::enumeratePeople(void){

	//Sortierung (alle, die Geburtstag oder demnächst Geburtstag haben stehen ganz oben
	std::sort(personList->begin(), personList->end(), &CPerson::compareByDate);
	
	std::vector<CPerson*>::const_iterator it = personList->begin();
	int pos = 1;
	while (it != personList->end()){
		(*it)->setPosition(pos);
		pos++;
		it++;
	}
}

void CPersonModel::reactOnClick(const QModelIndex& index){
	if(index.data().toString().contains("@")){
		QUrl u = QString("mailto:%1").arg(index.data().toString());
		QDesktopServices::openUrl(u);
	}
}
