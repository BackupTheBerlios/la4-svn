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
#include <QDir>
#include <QtDebug>

/* LA4 includes */
#include "LAObjectFactory.h"

/* Debugging levels */
#define DEBUG

/* Constants */
const QString LAObjectFactoryManager::LAOBJECT_EXTENSION_FILTER = "*.xml";

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

#ifdef DEBUG
  qDebug() << "LAObjectFactoryManager::Load: Path =" << m_dir;
#endif /* DEBUG */

  QDir             factoriesDirectory(m_dir);
  QString          fullPath = "";
 	LAObjectFactory* factory  = NULL;

  if (!(factoriesDirectory.exists()))
    {
      qWarning() << "LAObjectFactoryManager::Load: Failed to load factories from" << m_dir << "- Directory does not exist";
      numberOfFactories = -1;
    }

  /*! Filter files */
  factoriesDirectory.setNameFilters(QStringList(LAOBJECT_EXTENSION_FILTER));
  QStringList factoriesList = factoriesDirectory.entryList();

	if (-1 != numberOfFactories &&
       0 >= factoriesList.count())
		{
			qWarning() << "LAObjectFactoryManager::Load: No definition to load from" << m_dir;
			numberOfFactories = -1;
		}
  else
    {

      /* For all files, load the factory */
      for (QStringList::Iterator factoryFilename = factoriesList.begin(); factoriesList.end() != factoryFilename; factoryFilename++)
        {

#ifdef DEBUG
          qDebug() << "LAObjectFactoryManager::Load: Processing" << *factoryFilename;
#endif /* DEBUG */

          factory = new LAObjectFactory(this);
          /* Load factory */
          if (-1 == factory->LoadDescription(m_dir, (*factoryFilename)))
            {
              delete factory;
              factory = NULL;
            }
          else
            {
              /* If factory is successfully loaded, add it to list */
              m_factories.append(factory);
              numberOfFactories++;
            }

        }

    }

#ifdef DEBUG
    qDebug() << "LAObjectFactoryManager::Load:" << numberOfFactories << "factories read from" << m_dir;
#endif /* DEBUG */

    return numberOfFactories;
}
