/*********************************************************************************
NixNote - An open-source client for the Evernote service.
Copyright (C) 2013 Randy Baumgarte

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
***********************************************************************************/

#ifndef STARTUPCONFIG_H
#define STARTUPCONFIG_H

#include <QString>
#include <QHash>
#include <QIcon>
#include <QPixmap>
#include <QBitArray>

#include "cmdtools/addnote.h"
#include "cmdtools/cmdlinequery.h"

#define STARTUP_GUI 0
#define STARTUP_SYNC 1
#define STARTUP_SHUTDOWN 2
#define STARTUP_SHOW 3
#define STARTUP_ADDNOTE 4
#define STARTUP_QUERY 5
#define STARTUP_DELETE 6
#define STARTUP_EMAIL 7
#define STARTUP_MOVE_TO_NOTEBOOK 8
#define STARTUP_ASSIGN_TAG 9
#define STARTUP_REMOVE_TAG 10
#define STARTUP_EXPORT 11
#define STARTUP_IMPORT 12
#define STARTUP_BACKUP 13
#define STARTUP_OPTION_COUNT 14

class StartupConfig
{
private:
    void loadTheme(QString theme);
private:
    QBitArray *command;

public:
    StartupConfig();
    QString name;
    QString homeDirPath;
    QString programDirPath;
    QString queryString;
    bool forceNoStartMinimized;
    bool startupNewNote;
    bool syncAndExit;
    int accountId;
    qint32 startupNoteLid;
    bool forceStartMinimized;
    bool enableIndexing;
    bool forceSystemTrayAvailable;
    bool disableEditing;
    bool purgeTemporaryFiles;
    AddNote *newNote;
    CmdLineQuery *queryNotes;
    bool gui();
    bool sync();
    bool addNote();
    bool show();
    bool shutdown();
    bool query();

    int init(int argc, char *argv[]);
    void printHelp();
};

#endif // STARTUPCONFIG_H
