/******************************************************************************
 * LoadFilePlugin.h                                                           *
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

#ifndef LOAD_FILE_PLUGIN_H_
#define LOAD_FILE_PLUGIN_H_

/* Qt includes */
#include <QObject>

/* LA4 includes */
#include "LACATRE_Plugin.h"

/*!
 * This plugin is able to handle the user interaction involded
 * in the loading of a file.
 * 
 * The default action can either directly load a file, or
 * ask the user for it. If the document filename has been
 * set before calling the action, the plugin will load it,
 * otherwise it will ask for the filename via a QFileDialog
 * and load the document if there is one.
 * 
 * TODO Several things should be fixed in the future:
 * - The error dialog should be delegated to the caller that
 * would dispose of the error message
 * - The conversion of files may be better placed in a dedicated
 * plugin
 */
class LoadFilePlugin : public LACATRE_Plugin
{
	Q_OBJECT

		public:
		LoadFilePlugin();
		~LoadFilePlugin();

		virtual LACATRE_Plugin *Clone(LACATRE_Doc * d);
		virtual void UpdateDocument(QDomDocument & d);


	public slots:
		virtual QWidget * Action(QWidget *parentWidget,int action = LA4::Load, const char * parameter = NULL);

//		signals:
	/** Fired to indicate that
		 we have modified the content
		 of the document.
		 \param p Normally it is always "this" pointer.
		 */
//		void modified(LACATRE_Plugin * p);

	protected:
	/*!
	 * Copy constructor
	 *
	 * \param plugin Plugin to copy
	 *
	 * \retval pointer A new load plugin copied from the plugin passed in parameter
	 */
		LoadFilePlugin(const LoadFilePlugin& plugin);

		int loadDoc(const QString &);

		QString fileName;
		QDomDocument* localDoc;

};

#endif /* LOAD_FILE_PLUGIN_H_ */
