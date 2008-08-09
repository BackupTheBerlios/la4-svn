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
 * Copyright (C) 2002-2008 by LA4 team <la4-dev@lists.berlios.de>             *
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

  /************************************************** Constructors/Destructor */
public:
  /*!
   * Default constructor
   */
  LoadFilePlugin();

  /*!
   * Destructor
   */
  ~LoadFilePlugin();

  /*********************************************************** Public methods */
public:
  /*!
   * Clone the plugin
   *
   * @param aDocument     Document to which the plugin is to be associated to
   */
  virtual LACATRE_Plugin* Clone(LACATRE_Doc * aDocument);

  /*!
   * Update the document content to the loaded content
   */
  virtual void UpdateDocument();

  /************************************************************* Public slots */
public slots:
  /*!
   * Perform action of the plugin
   *
   * LA4::Load action will, if the document has a filename associated to it load
   * the given file, otherwise, it will ask the user to give the filename with
   * an open file dialog.
   */
  virtual QWidget* Action(QWidget* aParentWidget, int aAction = LA4::Load, const char* aParameter = NULL);

  /******************************************************** Protected methods */
protected:
  /*!
   * Copy constructor
   *
   * @param plugin Plugin to copy
   *
   * @retval pointer A new load plugin copied from the plugin passed in parameter
   */
  LoadFilePlugin(const LoadFilePlugin& plugin, LACATRE_Doc* aDocument);

  /*!
   * Loads the document from the filename the plugin knows
   */
  int loadDoc();

  /********************************************************** Private members */
private:
  /*! Filename of the last loaded file */
  QString                  m_fileName;

  /*! Local copy of the XML content of the document */
  QDomDocument*            m_localDocument;

  /************************************************* Private static constants */
private:
  static const char* XML_VERSION_TAG;            /// Tag containing file version

};

#endif /* LOAD_FILE_PLUGIN_H_ */
