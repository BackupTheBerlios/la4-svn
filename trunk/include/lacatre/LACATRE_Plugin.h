/******************************************************************************
 * LACATRE_Plugin.h                                                           *
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

#ifndef LACATRE_PLUGIN_H_
#define LACATRE_PLUGIN_H_

/* Qt includes */
#include <QtXml/QDomDocument>
#include <QObject>
#include <QWidget>

/* LA4 includes */
#include "LA4Namespace.h"
#include "LACATRE_Doc.h"
#include "LACATRE_PluginPool.h"

/* Forward declarations */
class LACATRE_Doc;

/*!
 *	Generic interface to all plugins.
 *
 * As the implementation is straightforward and is not meant
 * to change a lot, it has been chosen to leave it here in the 
 * interface definition.
 * 
 * The plugin is not intended to be dynamically loaded, in the sense
 * that a plugin is always present in memory and no plugin that
 * has not been compiled within the executable may be used. It provides
 * modularisation of the code and a flexibility during execution
 * to remove or add some features in the application.
 */
class LACATRE_Plugin : public QObject
{

	Q_OBJECT

	/************************************************** Constructors/Destructor */
public:
	/*!
	 * Creates the plugin and registers it to the plugin pool
	 *
	 * \param type Type of the plugin
	 * \param name Name of the plugin
	 * \param d Description of the plugin
	 */
	LACATRE_Plugin(LACATRE_PluginPool::PluginType type, QString name, QString d = ""): QObject(NULL)
		{
			LACATRE_PluginPool::getInstance()->registerPlugin(this, type, name, d);
		}

	/*********************************************************** Public methods */
public:
	/*!
	 * Returns a copy of the plugin already set up for the specified document.
	 *
	 * \param doc Document of the newly created plugin
	 */
	virtual LACATRE_Plugin * Clone(LACATRE_Doc * doc) = 0;

	/****************************************************************** Signals */
signals:
	/*!
	 * Fired to indicate that the plugin has modified the document content.
	 *
	 * \param p Normally this is always "this" pointer.
	 */
	void modified(LACATRE_Plugin * p);

	/************************************************************* Public slots */
public slots:
	/*!
	 * Updates the document with the changes the plugin has made.
	 *
	 * \param doc The document to update.
	 */
	virtual void UpdateDocument(QDomDocument & doc) = 0;

	/*!
	 * Fires an action of the plugin.
	 *
	 * \param parentWidget Passes the widget to the plugin in order to let
	 * it initialize its own widgets if it has any.
	 * \param action Type of the action to do. For custom plugins, this is 0
	 * \param parameter Parameter of the action (depends on the action performed)
	 * the caller is responsible of given the "good" argument for the action, if
	 * the parameter is not what was intended, the action must not be performed.
	 *
	 * <b>Note:</b> Most actions don't need any argument.
	 *
	 * \return Returns a pointer to the widget plugin, if any.
	 */
	virtual QWidget * Action(QWidget * parentWidget, int action = LA4::DefaultAction, const char * parameter = NULL) = 0;

	/******************************************************** Protected methods */
protected:
	/*!
	 * Copy constructor.
	 *
	 * This constructor is protected!
	 */
	LACATRE_Plugin(const LACATRE_Plugin& p): QObject(), m_doc(NULL)
		{
			/* The copy does not retain the document */
			/* Nothing else has to be done */
			/* Note that the plugin is meant to be constructed only once with
			 * the public constructor */
			(void)p;
		};

	/*!
	 * Changes the document handled by the plugin.
	 * 
	 * \param d New document associated to the plugin 
	 */
	void SetDoc(LACATRE_Doc * d)
		{
			m_doc = d;
		};

	/******************************************************** Protected members */
protected:
	/*! Pointer to the version handled by the plugin */
	/* This version may not be up to date if the plugin has not emitted modified() */
	LACATRE_Doc * m_doc;

};

#endif /* LACATRE_PLUGIN_H_ */
