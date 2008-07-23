/******************************************************************************
 * LAPlatform.h                                                               *
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

#ifndef _LAPLATFORM_H_
#define _LAPLATFORM_H_

/* Qt includes */
#include <QList>
#include <QObject>

/* LA4 includes */

/* Forward declarations */
class LAObjectFactory;

/*!
 * Manager of all objects factories of a platform
 */
class LAPlatform: public QObject
{

  Q_OBJECT

  /************************************************************* Public types */
public:
  /*!
   * Type Definition for the list of all factories in this platform.
   */
  typedef QList<LAObjectFactory*> LAFactoryList;

  /************************************************** Constructors/Destructor */
public:
  /*!
   * Default contructor of LAPlatform.
   *
   * The use of this constructor is forbidden. No implementation is in consequence provided.
   */
  LAPlatform();

  /*!
   * Constructor of LAPlatform.
   *
   * @param aFactoriesDirectory Directory with descriptions of all factories.
   */
  LAPlatform(const QString & aFactoriesDirectory);

  /*!
   * Destructor of LAPlatform.
   */
  ~LAPlatform();

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
  /*! Directory of the platform */
  QString            m_dir;

  /*! List of the factories of the platform */
  LAFactoryList      m_factories;

  /*! ID of the platform */
  QString            m_platformID;

  /********************************************************** Private members */
private:
  /*! Default */
  static const QString LAOBJECT_EXTENSION_FILTER;

};

#endif /* _LAPLATFORM_H_ */
