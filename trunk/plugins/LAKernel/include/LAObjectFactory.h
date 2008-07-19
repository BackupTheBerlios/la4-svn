/******************************************************************************
 * LAObjectFactory.h                                                          *
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

#ifndef _LAOBJECT_FACTORY_H_
#define _LAOBJECT_FACTORY_H_

/* Qt includes */
#include <QDomDocument>
#include <QObject>

/* LA4 includes */

/* Forward declarations */
class LAObjectFactoryManager;
class LAObject;

/*!
 * Object factory: creates Lacatre objects.
 */
class LAObjectFactory: public QObject
{
    Q_OBJECT

    /************************************************ Constructors/Destructor */
public:
    /*!
     * Default constructor of LAObjectFactory.
     *
     * Using this constructor is forbidden. So no implementation is provided.
     */
    LAObjectFactory();

    /*!
     * Constructor of LAObjectFactory that must be used.
     *
     * @param aFactoryManager Factory manager that owns this factory.
     */
    LAObjectFactory(LAObjectFactoryManager* aFactoryManager);

    /*!
     * Destructor of LAObjectFactory
     */
    ~LAObjectFactory();

    /********************************************************* Public methods */
public:
    /*!
     * Returns the name of the factory.
     *
     * \retval name Name of the factory.
     */
    QString getName() const;

    /*!
     * Returns the type identifier of the object that is created by this factory.
     *
     * @retval typeID ID of the type of object created by this factory.
     */
    int getTypeID();

    /*!
     * Loads the object description from the file of a given name.
     *
     * @param aFactoryDirectory    The directory of the factory	
     * @param aFactoryFile         Name of the file from the directory to load.
     *
     * @retval  0                  The loading was a success.
     * @retval -1                  Their has been an error while loading.
     */
    int LoadDescription(const QString & aFactoryDirectory, const QString & aFactoryFile);

    /*!
     * Creates the new instance of the object that this factory "produces" using the
     * user data.
     *
     * All parameters of the object will be set to their default values except for
     * coordinates, height and width.
     *
     * @param x X coordinate of the created object.
     * @param y Y coordinate of the created object.
     * @param w Width of the created object.
     * @param h Height of the created object.
     *
     * @retval objectPointer Pointer to a new object.
     */
    LAObject * NewInstance(const double x, const double y, const double w = -1, const double h = -1);

    /*!
     * Creates the new instance of the object that this factory "produces" using
     * the XML document data.
     *
     * @param element XML element to load.
     *
     * @retval objectPointer Pointer to a new object.
     */
    LAObject * NewInstance(const QDomElement& element);

    /************************************************** Public static methods */
public:
    /*!
     * Returns the next valid ID for objects or connectors.
     *
     * @param ID ID we would like to give to the object. If ID is inferior 
     *        to 0, nextID is returned
     *
     * This design is ok if only one document is associated to a set of factories.
     * In consequence, it is important that each document is associated
     * to only one factory manager.
     *
     * @todo Put it in the factory manager that will delegate it to the workspace 
     * or to the document + keep a pointer on the manager
     *
     * @retval ID ID that must be given to the object or connector.
     */
    static int TakeNextID(int ID = -1);

    /****************************************************** Protected members */
protected:
    /*! Base object used as base for instance creation */
    LAObject*            m_factoryObject;

    /*! Human-language, translated name of the object created by the factory */
    QString              m_name;

    /*********************************************** Protected static members */
protected:
    /*! Next available ID for object creation */
    static int           M_nextID;

};

#endif /* _LAOBJECT_FACTORY_H_ */
