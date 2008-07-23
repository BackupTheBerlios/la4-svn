/******************************************************************************
 * LAPlatformManager.h                                                        *
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

#ifndef _LAPLATFORMMANAGER_H_
#define _LAPLATFORMMANAGER_H_

/* Qt includes */
#include <QList>
#include <QObject>

/* LA4 includes */

/* Forward declarations */
class LAPlatform;

/*!
 * Manager of all platforms
 */
class LAPlatformManager: public QObject
{

  Q_OBJECT

  /************************************************************* Public types */
public:
  /*!
   * Type Definition for the list of all platforms of the manager.
   */
  typedef QList<LAPlatform*> LAPlatformList;

  /************************************************** Constructors/Destructor */
public:
  /*!
   * Destructor of LAPlatformManager.
   */
  ~LAPlatformManager();

  /*********************************************************** Public methods */
public:
  /*!
   * Returns the list of platforms.
   */
  static LAPlatformList * GetPlatforms();

  /*!
   * Loads the platforms.
   */
  static int Load();

  /******************************************************** Protected methods */
protected:
  /*!
   * Contructor of LAPlatformManager.
   *
   * The use of this constructor is forbidden. It is only used once in the singleton.
   */
  LAPlatformManager();

  /******************************************************** Protected members */
protected:
  /*! List of platforms */
  LAPlatformList     m_platforms;

  /********************************************************** Private members */
private:
  /*! Singleton */
  static LAPlatformManager* _M_ManagerSingleton;

};

#endif /* _LAPLATFORMMANAGER_H_ */
