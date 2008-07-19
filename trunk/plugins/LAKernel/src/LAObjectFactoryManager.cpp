/******************************************************************************
 * LAObjectFactoryManager.cpp                                                 *
 ******************************************************************************
 *                                                                            *
 *   This program is free software; you can redistribute it and/or modify     *
 *   it under the terms of the GNU Lesser General Public License as           *
 *   published by the Free Software Foundation; either version 2 of the       *
 *   License, or (at your option) any later version.                          *
 *                                                                            *
 *   This program is distributed in the hope that it will be useful,          *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *   GNU Lesser General Public License for more details.                      *
 *                                                                            *
 *   You should have received a copy of the GNU Lesser General Public License *
 *   along with this program; if not, write to the                            *
 *   Free Software Foundation, Inc.,                                          *
 *   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.                 *
 *                                                                            *
 ******************************************************************************
 * LA4: Tool for real-time systems design                                     *
 * Copyright (C) 2002-2008 by LA4 team <la4-dev@lists.berlios.de>             *
 ******************************************************************************/

#include "LAObjectFactoryManager.h"

/* Qt includes */

/* LA4 includes */
#include "LAObjectFactory.h"

/* Debugging levels */
#undef DEBUG

/************************************************** Constructors/Destructor */
LAObjectFactoryManager::LAObjectFactoryManager(const QString& aFactoriesDirectory):
    m_dir(aFactoriesDirectory)
{
    /* All factories of the zone are destroyed with the zone */
}

LAObjectFactoryManager::~LAObjectFactoryManager()
{
    /* Factories are owned by the manager that must destroy them */
    LAObjectFactory* aFactoryPtr;
    foreach (aFactoryPtr, m_factories)
        {
            delete aFactoryPtr;
        }
}

/*********************************************************** Public methods */
LAObjectFactoryManager::LAFactoryList* LAObjectFactoryManager::GetFactories()
{
	return &m_factories;
}

int LAObjectFactoryManager::Load()
{
    /* Returned value */
    int numberOfFactories = 0;

// 	QDir factDir(dir);
// 	QString fullPath;

// 	LAObjectFactory * aFactory;

// 	if (!(factDir.exists()))
// 		{
// 			qWarning("LAObjectFactoryManager: Failed to load %s", dir.latin1());
// 			return -1;
// 		}

// 	/*! \todo Put filter in preferences ?? */
// 	factDir.setNameFilter("*.xml");

// 	if(!factDir.entryList().count())
// 		{
// 			qWarning("LAObjectFactoryManager: Nothing to load from %s\n", dir.latin1());
// 			return -1;
// 		}

// 	QStringList list = factDir.entryList();

// 	/* For all files, load the factory */
// 	for (QStringList::Iterator it = list.begin() ; it != list.end() ; ++it )
// 		{

// #ifdef DEBUG
// 			qDebug("LAObjectFactoryManager: Processing %s", (*it).latin1());
// #endif /* DEBUG */

// 			aFactory = new LAObjectFactory(this);
// 			/* \todo Test not clear here!!! */
// 			if (aFactory->LoadDescription(dir, (*it)))
// 				{
// 					delete aFactory;
// 					aFactory = NULL;
// 				}
// 			else
// 				{
// 					factories.append(aFactory);
// 					numFact++;
// 				}
// 		}

#ifdef DEBUG
    qDebug("LAObjectFactoryManager: %d factories read from %s", numFact, m_dir.latin1());
#endif /* DEBUG */

    return numberOfFactories;
}
