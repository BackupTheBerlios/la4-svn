/******************************************************************************
 * LAObject.h                                                                 *
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
 * Copyright (C) 2002-2006 by LA4 team <la4-dev@lists.berlios.de>             *
 ******************************************************************************/

#ifndef _LAOBJECT_H_
#define _LAOBJECT_H_

/* Qt includes */
#include <QDomNode>
#include <QObject>

/* LA4 includes */

/* Forward declarations */
class LAMetaObject;
class LAObjectFactory;

/*!
 * This class is used to represent all Lacatre objects except connectors
 */
class LAObject : public QObject
{

  Q_OBJECT
  /****************************************************** Friend declarations */
public:
  friend class LAObjectFactory;

  /************************************************** Constructors/Destructor */
public:
  /*!
   * Default constructor is protected.
   */

  /*!
   * Destructor of LAObject.
   */
  virtual ~LAObject();

  /*********************************************************** Public methods */
public:
  /*!
   * Creates a copy of the object itself and return a pointer on the new object
   *
   * @param x X-coordinate of the new object
   * @param y Y-coordinate of the new object
   * @param w Width of the new object. If -1, it is created with the default width
   * @param h Height of the new object. If -1, it is created with the default height
   *
   * @retval pointer Pointer on the created object
   */
  virtual LAObject* Clone(double x, double y, double w = -1, double h = -1);

  /*!
   * Indicates the object ID
   *
   * @retval objectID The ID of the object
   */
  int getObjectID() { return m_objectID; };

  /*!
   * Indicates the type ID of the object
   *
   * @retval typeID The type ID of the object
   */
  int getTypeID() { return m_typeID; };

  /*!
   * Loads information about the object from the given XML node
   *
   * This method always return 0.
   *
   * @param aNode Node containing the information to load
   *
   * @retval 0 Normal execution
   */
  virtual int LoadDescription(QDomNode& aNode);

  /******************************************************** Protected methods */
protected:
  /*!
   * Default constructor of LAObject.
   */
  LAObject();
  
  /*!
   * The copy constructor is used for internal purposes ONLY.
   *
   * Use Clone() method instead.
   *
   * @param object Object to copy.
   */
  LAObject(const LAObject& object);

  /******************************************************** Protected members */
protected:
  /*! Height of the object */
  double        m_height;

  /*! Meta object of the object */
  LAMetaObject* m_metaObject;

  /*! ID of the object */
  int           m_objectID;

  /*! Type ID of the object */
  int           m_typeID;

  /*! Width of the object */
  double        m_width;

  /*! X coordinate of the object */
  double        m_xCoordinate;

  /*! Y coordinate of the object */
  double        m_yCoordinate;

  /******************************************************** Private constants */
private:
  /* Attribute names */
  static const QString XML_DEFAULT_HEIGHT_ATTRIBUTE;
  static const QString XML_DEFAULT_WIDTH_ATTRIBUTE;
  static const QString XML_TYPE_ID_ATTRIBUTE;

};

#endif /* _LAOBJECT_H_ */
