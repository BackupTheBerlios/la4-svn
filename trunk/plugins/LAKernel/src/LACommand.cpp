/******************************************************************************
 * LACommand.cpp                                                              *
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

#include "LACommand.h"

/* Qt includes */
#include <QVariant>

/* LA4 includes */

/* Debugging levels */
#undef DEBUG

/************************************************** Constructors/Destructor */
LACommand::LACommand(QUndoCommand* parent)
	: QUndoCommand(parent)
{
}

LACommand::~LACommand()
{
}

/*********************************************************** Public methods */
int LACommand::getCommandId()
{
    return m_commandId;
}

void LACommand::setCommandId(const int aCommandId)
{
    m_commandId = aCommandId;
}
