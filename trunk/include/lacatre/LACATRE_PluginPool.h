/******************************************************************************
 * LACATRE_PluginPool.h                                                       *
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
 * Copyright (C) 2002-2007 by LA4 team <la4-dev@lists.berlios.de>             *
 ******************************************************************************/

#ifndef LACATRE_PLUGIN_POOL_H_
#define LACATRE_PLUGIN_POOL_H_

/* Qt includes */
#include <QMap>
#include <QObject>

/* LA4 includes */

/* Forward declarations */
class LACATRE_Plugin;

/*!
 * Pool for registering/unregistering the plugins
 */
class LACATRE_PluginPool : QObject
{
	Q_OBJECT

	/************************************************************* Public types */
public:
	/*! This enumeration is used to denote the role of the plugin: if
	 * it will read, write or read/write the document
	 */
	typedef enum {
		READ,
		WRITE,
		BOTH
	} PluginType;

	/************************************************** Constructors/Destructor */
public:
	/*!
	 * No constructor is public as it is a singleton pattern, 
	 * use getInstance() to get one.
	 */

	/*********************************************************** Public methods */
public:
	/*!
	 * Returns the plugin associated with the given name
	 * 
	 * \param pluginName Name of the plugin.
	 */
	LACATRE_Plugin * plugin(const QString & pluginName);

	/*!
	 * Register a new plugin in the pool
	 * 
	 * \param plugin Plugin to add
	 * \param type Plugin type (READ, WRITE, BOTH)
	 * \param name Name of the plugin, used as an identifier to find plugins.
	 * It must in consequence be unique for each plugin. We therefore
	 * define constants in this namespace to handle them.
	 * \param description Description of the plugin
	 * 
	 * \return 0 in any case
	 */
	int registerPlugin(LACATRE_Plugin * plugin, PluginType type, QString name, QString description = "");

	/**************************************************** Public static methods */
public:
	/*!
	 * Returns the singleton instance of plugin pool.
	 * 
	 * This instance may be used to registe other plugins or get plugins
	 * out of the pool.
	 */
	static LACATRE_PluginPool * getInstance();

	/********************************************************** Private methods */
private:
	/*!
	 * This default constructor is private.
	 */
	LACATRE_PluginPool();

	/*************************************************** Private static members */
private:
	/*! Unique instance of PluginPool (singleton pattern) */
	static LACATRE_PluginPool * M_instance;

	/*! List of plugins registered in the pool */
	QMap<QString, LACATRE_Plugin*> m_plugins;

};

#endif /* LACATRE_PLUGIN_POOL_H_ */
