/******************************************************************************
 * LAPlatform.cpp                                                             *
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

#include "LAPlatform.h"

/* Qt includes */
#include <QDir>
#include <QtDebug>

/* LA4 includes */
#include "LAObjectFactory.h"

/* Debugging levels */
#undef DEBUG

/* Constants */
const QString LAPlatform::LAOBJECT_EXTENSION_FILTER = "*.xml";

/************************************************** Constructors/Destructor */
LAPlatform::LAPlatform(const QString& aFactoriesDirectory):
  m_dir       (aFactoriesDirectory),
  m_name      (""),
  m_platformID("")
{
    /* All factories of the zone are destroyed with the zone */
}

LAPlatform::~LAPlatform()
{
    /* Factories are owned by the platform that must destroy them */
    LAObjectFactory* aFactoryPtr;
    foreach (aFactoryPtr, m_factories)
        {
            delete aFactoryPtr;
        }
}

/*********************************************************** Public methods */
const LAPlatform::LAFactoryList* LAPlatform::getFactories() const
{
	return &m_factories;
}

const QString LAPlatform::getName() const
{
	return m_name;
}

int LAPlatform::Load()
{
  /* Returned value */
  int numberOfFactories = 0;

#ifdef DEBUG
  qDebug() << "LAPlatform::Load: Path =" << m_dir;
#endif /* DEBUG */

  QDir             factoriesDirectory(m_dir);
  QString          fullPath = "";
 	LAObjectFactory* factory  = NULL;

  if (!(factoriesDirectory.exists()))
    {
      qWarning() << "LAPlatform::Load: Failed to load factories from" << m_dir << "- Directory does not exist";
      numberOfFactories = -1;
    }

  /*! Filter files */
  factoriesDirectory.setNameFilters(QStringList(LAOBJECT_EXTENSION_FILTER));
  QStringList factoriesList = factoriesDirectory.entryList();

	if (-1 != numberOfFactories &&
       0 >= factoriesList.count())
		{
			qWarning() << "LAPlatform::Load: No definition to load from" << m_dir;
			numberOfFactories = -1;
		}
  else
    {

      /* For all files, load the factory */
      for (QStringList::Iterator factoryFilename = factoriesList.begin(); factoriesList.end() != factoryFilename; factoryFilename++)
        {

#ifdef DEBUG
          qDebug() << "LAPlatform::Load: Processing" << *factoryFilename;
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

  /* If more than one factory exists */
  if (0 < numberOfFactories)
    {
      /* Set a non empty name to the platform */
      /* We assume that directory is not root directory  */
      /* Otherwise, the dirName() method will return "" */
      m_name = factoriesDirectory.dirName();

#ifdef DEBUG
    qDebug() << "LAPlatform::Load: Platform" << m_name << "loaded";
#endif /* DEBUG */

    }

#ifdef DEBUG
    qDebug() << "LAPlatform::Load:" << numberOfFactories << "factories read from" << m_dir;
#endif /* DEBUG */

    return numberOfFactories;
}
