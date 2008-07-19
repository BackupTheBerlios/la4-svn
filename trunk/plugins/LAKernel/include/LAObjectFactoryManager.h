/******************************************************************************
 * LAObjectFactoryManager.h                                                  *
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

#ifndef _LAOBJECT_FACTORY_MANAGER_H_
#define _LAOBJECT_FACTORY_MANAGER_H_

/* Qt includes */
#include <QList>
#include <QObject>

/* LA4 includes */

/* Forward declarations */
class LAObjectFactory;

/*!
 * Manager of all objects factories
 */
class LAObjectFactoryManager: public QObject
{

  Q_OBJECT

	/************************************************************* Public types */
public:
  /*!
	 * Type Definition for the list of all factories in this zone.
   */
  typedef QList<LAObjectFactory*> LAFactoryList;

	/************************************************** Constructors/Destructor */
public:
	/*!
	 * Default contructor of LAObjectFactoryManager.
	 *
	 * The use of this constructor is forbidden. No implementation is in consequence provided.
	 */
  LAObjectFactoryManager();

  /*!
	 * Constructor of LAObjectFactoryManager.
	 *
   * @param aFactoriesDirectory Directory with descriptions of all factories.
   */
  LAObjectFactoryManager(const QString & aFactoriesDirectory);

  /*!
	 * Destructor of LAObjectFactoryManager.
   */
  virtual ~LAObjectFactoryManager();

	/*********************************************************** Public methods */
public:
  /*!
	 * Returns the list of factories.
   */
  LAFactoryList * GetFactories();

  /*!
   * Loads the factories descriptions and creates the factories.
   */
  int Load();

	/******************************************************** Protected members */
protected:
	/*! Directory of the zone */
  QString            m_dir;

	/*! List of the factories of the factory manager */
  LAFactoryList      m_factories;

	/*! ID of the factory manager */
  QString            m_factoryID;

};

#endif /* _LAOBJECT_FACTORY_MANAGER_H_ */
