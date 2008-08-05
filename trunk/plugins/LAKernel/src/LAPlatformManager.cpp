/******************************************************************************
 * LAPlatformManager.cpp                                                      *
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

#include "LAPlatformManager.h"

/* Qt includes */
#include <QDir>
#include <QtDebug>

/* LA4 includes */
#include "LAPlatform.h"

/* Debugging levels */
#undef DEBUG

/* Singleton instance */
LAPlatformManager* LAPlatformManager::_M_ManagerSingleton = NULL;

/************************************************** Constructors/Destructor */
/* This constructor is protected */
LAPlatformManager::LAPlatformManager()
{
}

LAPlatformManager::~LAPlatformManager()
{
  /* Platformsare owned by the platform manager */
  LAPlatform* aPlatformPtr;
  foreach (aPlatformPtr, m_platforms)
    {
      delete aPlatformPtr;
    }
}

/*********************************************************** Public methods */
LAPlatformManager::LAPlatformList* LAPlatformManager::getPlatforms()
{
  /* Create singleton if needed */
  LAPlatformManager::checkSingleton();

	return &(_M_ManagerSingleton->m_platforms);
}

int LAPlatformManager::Load(const QString& aDirectory,
                            const bool&    aKeepPlatforms)
{
  /* Returned value */
  int numberOfPlatforms = 0;

  /* Create singleton if needed */
  LAPlatformManager::checkSingleton();

  /* Factories to insert */
  LAPlatformList insertedPlatforms;

  QDir             platformsDirectory(aDirectory);
  QString          fullPath = "";
 	LAPlatform*      platform = NULL;

#ifdef DEBUG
  qDebug() << "LAPlatformManager::Load: Path =" << aDirectory;
#endif /* DEBUG */

  if (!(platformsDirectory.exists()))
    {
      qWarning() << "LAPlatformManager::Load: Failed to load platforms from" << aDirectory << "- Directory does not exist";
      numberOfPlatforms = -1;
    }

  /*! Filter directories and order them */
  platformsDirectory.setFilter(QDir::Dirs);
	platformsDirectory.setSorting(QDir::Name);
  QStringList platformList = platformsDirectory.entryList();

	if (-1 != numberOfPlatforms &&
       0 >= platformList.count())
		{
			qWarning() << "LAPlatformManager::Load: No platform to load from" << aDirectory;
			numberOfPlatforms = -1;
		}
  else
    {

      /* For all directories, load the platform (if no file is in the directory, it will be ignored */
      for (QStringList::Iterator platformDirectory = platformList.begin(); platformList.end() != platformDirectory; platformDirectory++)
        {

#ifdef DEBUG
          qDebug() << "LAPlatformManager::Load: Processing" << *platformDirectory;
#endif /* DEBUG */

          /* Do not consider dot directories */
          if (!(*platformDirectory).startsWith("."))
            {

              platform = new LAPlatform(aDirectory + *platformDirectory);
              /* Load factory */
              if (-1 == platform->Load())
                {
                  delete platform;
                  platform = NULL;
                }
              else
                {
                  /* If factory is successfully loaded, add it to list */
                  insertedPlatforms.insert(platform->getName(), platform);
                  numberOfPlatforms++;
                }

            }

        }

    }

  /* If platform list to insert is not empty */
  if (0 < insertedPlatforms.count())
    {
      /* If old platforms are to be erased before */
      if (false == aKeepPlatforms)
        {
#ifdef DEBUG
    qDebug() << "LAPlatformManager::Load: Erasing old platforms";
#endif /* DEBUG */

          /* Put them in the old platforms list */
          _M_ManagerSingleton->m_oldPlatforms += _M_ManagerSingleton->m_platforms;

          /* Clear platforms */
          _M_ManagerSingleton->m_platforms.clear();
        }

#ifdef DEBUG
      qDebug() << "LAPlatformManager::Load: Adding" << insertedPlatforms.count() << "platforms";
#endif /* DEBUG */

      /* Add newly loaded platforms to current list */
      _M_ManagerSingleton->m_platforms += insertedPlatforms;
    }

#ifdef DEBUG
    qDebug() << "LAPlatformManager::Load:" << numberOfPlatforms << "platforms read from" << aDirectory;
#endif /* DEBUG */

    return numberOfPlatforms;
}

/********************************************************** Private methods */
void LAPlatformManager::checkSingleton()
{
  /* If singleton is NULL, create it */
  if (NULL == _M_ManagerSingleton)
    {

#ifdef DEBUG
      qDebug() << "LAPlatformManager::checkSingleton: Creating singleton";
#endif /* DEBUG */

      _M_ManagerSingleton = new LAPlatformManager();
    }
}
