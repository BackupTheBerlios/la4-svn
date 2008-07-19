/******************************************************************************
 * LACATRE_PluginPool.cpp                                                     *
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

#include "LACATRE_PluginPool.h"
 
/* Qt includes */
 
/* LA4 includes */
#include "LACATRE_Plugin.h"
 
/* Debugging levels */
#undef DEBUG

/*! The instance will be created on first call of getInstance() */
LACATRE_PluginPool * LACATRE_PluginPool::M_instance = 0;

/************************************************** Constructors/Destructor */
/* This constructor is private */
LACATRE_PluginPool::LACATRE_PluginPool()
{
	/* There is nothing to initialiaze */
}

/*********************************************************** Public methods */
int LACATRE_PluginPool::registerPlugin(LACATRE_Plugin * plugin, PluginType pluginType, QString pluginName, QString pluginDescription)
{

#ifdef DEBUG
	qDebug("LACATRE_PluginPool::registerPlugin: Registering plugin " + pluginName);
#endif /* DEBUG */

	/* Plugin type and plugin description are not used at all */
	(void)pluginType; /* Avoid warning */
	(void)pluginDescription; /* Avoid warning */

	m_plugins[pluginName] = plugin;

	return 0;

}

LACATRE_Plugin * LACATRE_PluginPool::plugin(const QString& pluginName)
{
	return m_plugins[pluginName];
}

/**************************************************** Public static methods */
LACATRE_PluginPool * LACATRE_PluginPool::getInstance()
{

	/* Singleton design pattern (SE) */
	if (M_instance == 0)
		{
			M_instance = new LACATRE_PluginPool();
		}

	return M_instance;

}
