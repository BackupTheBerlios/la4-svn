/******************************************************************************
 * LAProject.h                                                                *
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

#ifndef _LAPROJECT_H_
#define _LAPROJECT_H_

/* Qt include */

/* LA4 includes */
#include <LACATRE_Doc.h>

/* Forward declarations */
class LAWindow;

/*!
 * A LAProject is responsible of one project and therefore of one user window.
 *
 *
 */
class LAProject : public QObject
{
  Q_OBJECT

  /************************************************************* Public types */
public:
  /*!
   * Start project mode
   */
  typedef enum {
    NEW_PROJECT,   /* The project is a new one */
    EXISTING_FILE  /* We should load a file or ask to the user to select one */
  } LAProjectMode;

  /************************************************** Constructors/Destructor */
public:
  /*!
   * Default constructor
   *
   * Does nothing
   */
  LAProject();

  /*!
   * Destructor
   */
  ~LAProject();

  /*********************************************************** Public methods */
public:
  /*!
   * Starts a new project, loads plugins and opens the main project window.
   *
   * @param aMode          Mode of the new project
   * @param aFilename      Name of the file to load (only used if mode is EXISTING_FILE
   *
   * @retval continue false if the user didn't want to continue, true otherwise
   */
  bool StartProject(LAProjectMode aMode = NEW_PROJECT, QString aFilename = "");

  /*!
   * Returns the pointer to  the (main) lacatre document  of the project
   *
   * \retval pointer Pointer to the document
   */
  LACATRE_Doc* doc() { return &m_document; };

  /************************************************************* Public slots */
public slots:

  /********************************************************** Private members */
private:
  /*! Document of the project */
  LACATRE_Doc        m_document;

  /*! Project load file plugin */
  LACATRE_Plugin*    m_loadfilePlugin;

  /*! Window where the document is displayed */
  LAWindow*          m_projectWindow;
};

#endif /* _LAPROJECT_H_ */
