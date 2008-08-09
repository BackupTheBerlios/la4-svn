# LA4.pro
# ------------------------------------------------------------------------------
# qmake file for LA4.
# ------------------------------------------------------------------------------
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the
# Free Software Foundation, Inc.,
# 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
# ------------------------------------------------------------------------------
# LA4: Tool for real-time systems design
# Copyright (C) 2002-2007 by LA4 team <la4-dev@lists.berlios.de>
# Configuration section
# ######################
# By default, debug is activated
TEMPLATE = app
CONFIG += warn_on \
    qt \
    debug \
    thread # += do not override command line options

# Intermediate files and object files are place on ./tmp
MOC_DIR = objs/moc
UI_DIR = objs/ui
OBJECTS_DIR = objs
RCC_DIR = objs/res

# Additional include paths
INCLUDEPATH=./include \
    ./include/lacatre \
    ./plugins/include \
    ./plugins/LAKernel/include

# This is needed to calculate dependencies correctly
DEPENDPATH=$$INCLUDEPATH

# Qt modules
QT += core \
    gui \
    xml

# Sources section
# ################
# += is very important because configure can add its own sources.
# User interface
FORMS += ui/LAPreferencesWindow.ui \
    ui/LAAboutWindow.ui \
    ui/LAWindow.ui \
    ui/LAStartDialog.ui

# Sources
SOURCES += \
    src/lacatre/LACATRE_PluginPool.cpp \
    src/lacatre/LACATRE_Plugin.cpp \
    src/lacatre/LACATRE_Doc.cpp \
    plugins/src/LoadFilePlugin.cpp \
    plugins/LAKernel/src/LACommand.cpp \
    plugins/LAKernel/src/LAMetaObject.cpp \
    plugins/LAKernel/src/LAObject.cpp \
    plugins/LAKernel/src/LAObjectFactory.cpp \
    plugins/LAKernel/src/LAPlatform.cpp \
    plugins/LAKernel/src/LAPlatformManager.cpp \
    src/LAPreferencesDialog.cpp \
    src/LASettings.cpp \
    src/LA4Namespace.cpp \
    src/LAProject.cpp \
    src/LAStartDialog.cpp \
    src/LAWindow.cpp \
    src/LALogger.cpp \
    src/main.cpp

# Headers
HEADERS = include/lacatre/LACATRE_PluginPool.h \
    include/lacatre/LACATRE_Plugin.h \
    include/lacatre/LACATRE_Doc.h \
    plugins/include/LoadFilePlugin.h \
    plugins/LAKernel/include/LACommand.h \
    plugins/LAKernel/include/LAMetaObject.h \
    plugins/LAKernel/include/LAObject.h \
    plugins/LAKernel/include/LAObjectFactory.h \
    plugins/LAKernel/include/LAPlatform.h \
    plugins/LAKernel/include/LAPlatformManager.h \
    include/LAPreferencesDialog.h \
    include/LASettings.h \
    include/LA4Namespace.h \
    include/LAProject.h \
    include/LAStartDialog.h \
    include/LALogger.h \
    include/LAWindow.h

# Translations, only french for now
TRANSLATIONS += i18n/fr/la4_fr.ts

# Targets section
# ################
# Our default target is called la4
TARGET = la4

# For the dist file, include LICENCE, AUTHORS, ...
DISTFILES += AUTHORS INSTALL LICENCE README TODO
RESOURCES = resources/images.qrc
