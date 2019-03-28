========================================================================
    CONSOLE APPLICATION : GameTest Project Overview
========================================================================

AppWizard has created this GameTest application for you.

This file contains a summary of what you will find in each of the files that
make up your GameTest application.


GameTest.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

GameTest.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

GameTest.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named GameTest.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
========================================================================
    CONSOLE APPLICATION : GameTest Project : Pacman Simulation
========================================================================

The Idea is that the Player (You) can control up to 2 Pacman at a time (current Version)
and must stay away from The Ghost(AI). In this version You can add as many AI as one wishes
But i will recommend some settings that I found to be fun.

Unfortunately on this version, the simulation is endless, the AI will only follow you
until 1 tile remains for capture.

Controls:

This Simulation requires a controller for optimal Fun.

	Configurations:
		1 Pacman - Use left thumb stick the control the Player
		2 Pacman :
					- Use Left thumb stick to control the current a Pacman
					- Use Left and Right Triggers to swtich between Pacman

AI:

Each AI (Ghost) uses A* algorithm to generate a path to some Pacman.
The Ghost will then follow this path until it ends, then generates a new path after
following the Previous Path.
*Think Assassin's creed when the enemy follows you previously known location*


Enjoyable Configurations:
---------------------------
number of AI	 : 2
size of map		 : 15
number of Pacman : 2
----------------------------
number of AI	 : 3 or 4
size of map		 : 20
number of Pacman : 2
----------------------------
number of AI	 : 1
size of map		 : 10
number of Pacman : 1
----------------------------