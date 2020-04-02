 
	              ackage: SkyEdit v0.060 alpha, 11 February 2012
	               Author: Dave Humphrey, dave@uesp.net
                  Website: www.uesp.net/wiki/Tes5Mod:SkyEdit


  Introduction
=======================================
SkyEdit is an alternate editor for The Elder Scrolls:Skyrim, similar to the official
"Creation Kit". This first release is mainly for testing and feedback and only a 
basic set of features is included. 


  Important Release Notes
=======================================

  - As an early alpha release there may, or will, be bugs present that may affect any 
    saved plugins. As with any third party utility, keep regular backups of plugins. 
	SkyEdit automatically backs up plugins when saved (unless disabled).
  - One main purpose for this release is to receive feedback from the modding community.
    Feedback may be given at:
               http://www.uesp.net/wiki/Tes5Mod:SkyEdit/Feedback
               http://www.uesp.net/wiki/Tes5Mod:SkyEdit/Bugs
            or dave@uesp.net
    All comments, suggestions, and bug reports are welcome.
  - Another major purpose of this release is for more extensive testing. The more people
    use it and the more different systems it is used on the more bugs can be found and
	fixed.
  - A minimum of 1GB of RAM is recommended for usable performance as loading of 
    Skyrim.esm uses around 500MB of memory. Plugins can also be edited without loading
	the master files to save time/memory but this limits what editing can be done.
  - Some help and documentation can be found at:
               http://www.uesp.net/wiki/Tes5Mod:SkyEdit


  Current Status
=======================================

  Editable Records
	- Keywords              - Containers
	- Globals				- Leveled Items
	- Game Settings			- Leveled Spells
	- Recipes				- Leveled Actors
	- Weapons				- Armor
	- Magic Effects			- Ammo
	- Enchantments			- Lights
	- Spells				- Potions
	- Ingredients			- Books
	- Misc					- Scrolls
	- Statics				- Activators
	- Armatures (ARMA)		- Soul Gems
	- Shouts				- Words of Power
	- Camera Shots			- Sounds
	- Sound Descriptors		- Sound Markers (SOPM)
	- Sound Categories		- Outfits
	- Colors				- Form Lists
	- Encounter Zones		- Races
	- Scripts				- Actor Values


  What it Can Do
=======================================
The basic capabilities of the editor in this release include:

  - Load plugins with multiple master files
  - Edit several basic record types
  - Basic find text and binary data feature
  - Viewing/selection of resources in Data path and in BSA files
  - Import/export basic data to *and* from CSV files
  - Simple undo system
  - Batch editing of multiple records for simple fields
  - Automatic backup when saving most files
  - View raw data/hex of all records


  What it Can't Do (Yet)
=======================================
Some notable lack of features in the current release are:

  - Cannot edit or view all record types yet
  - No cell view or preview windows
  - No use info display


  Installation
=======================================
  - Download the SkyEdit binary version
  - Unzip into a directory of your choice
  - Multiple installations of SkyEdit can be made in seperate directories
  - All program options are found in SKYEDIT.INI
  - There should be no specific requirements to run SkyEdit. It includes all 
    necessary external libraries so if it runs Skyrim it should run SkyEdit.
  - A minimum of 512MB of RAM is required and 1GB or more is suggested. 
  - Several 100MB of free disk space is recommended and more is better (for 
    backups and temporary resource files).


  Upgrading
=======================================
Simply overwrite an older version with the latest version. Multiple versions 
can also be kept in and run from seperate directories if desired.


  Features
=======================================
Some more specific features of the editor are listed below. A more exhaustive list 
can be found at:
               http://www.uesp.net/wiki/Tes5Mod:SkyEdit/Features

      General
  ---------------------------
  - Automatic backup of files when saving
  - Undo most actions when editing records
  - More complete find text or binary data 
  - Batch edit multiple records with common fields
  - Easily open and edit multiple plugins at once 
  - Press F1 to access appropriate help on the UESP or CS wikis

      User Interface
  ---------------------------
  - Record counts shown in record tree
  - Record list shows active and deleted records in different colors
  - Custom dialog to make selection of scripts, enchantments, etc...
  - Record list shows almost all fields for a record
  - Record tree can be customized to show different grouping of records.
  - Update a record being edited without closing its dialog (Apply)
  - Drag-and-drop operations are supported in more locations
  - Tooltips for most controls
  - View raw data/hex display of records
  - Quickly view only active records or records with a matching editor ID

      Resource Viewer
  ---------------------------
  - Seperate window for viewing and selecting game resources (textures, meshes,
    sounds, icons, etc...)
  - View resources in DATA path as well as within known BSA files.
  - Basic script editor and compiler using the official Papyrus compiler.
  
      Import/Export
  ---------------------------
  - Import/export most records from/to CSV (Comma Seperated Value) files
  - Most basic records fields supported
  - Existing records are automatically updated/overwritten when importing
  - Formids automatically assigned to new imported records

      Performance
  ---------------------------
  - Improved performance at the cost of requiring more memory
  - Skyrim.esm is only ever loaded once. This allows multiple plugins to 
    be loaded at once and decreases loading time of subsequent loads. 
  - Simple caching to defer loading of parts of master files to reduce
    memory requirements (currently only LAND and NAVM records).


  Version History
=======================================
0.07alpha - ? February 2012
	- Redid Magic Effects
	- Redid Enchantments. A few important notes:
		- AutoCalc does not change the cost/charge as I don't know the exact formula used.
		- It does not currently limit the types of effects which can be created like the
		  CK does. Using a bad type (like a contact effect type on an armor piece) has
		  unknown consequences within the game at the moment.
	- Redid Potions, Ingrediants, Spells and Scrolls
	- Scripts and string files are backed up according to their directory instead of
	  all being put into the backup root path. For example, script text files are
	  backed up into "backup\scripts\source\...".
	- Fixed a few places where keywords weren't able to be selected properly.
	- Fixed a bug in races with equip slots not saving properly.


0.06alpha - 11 February 2012
	- Basic script editing has been added!
		- NOTE: This requires the installation of the CK for the script sources and
		  the script compiler.
		- Basic built-in script editor. Click on the Script icon in the toolbar or
		  from under the View menu. No syntax highlighting (yet)
		- Use an external editor by Ctrl + double-clicking on a script. It uses whatever
		  editor is opened when you double-click a PSC file in Windows Explorer.
		- By default the internal script editor is used. If you change 
		  "EditScriptExternalByDefault" in SkyEdit.ini to "true" the external editor
		  is used by default.
		- Script compiling is done using the official command line Papyrus compiler. 
		- Script and property information can be copy/pasted between objects 
		  (right-click on selected scripts in the record dialog).
		- Searching in scripts has been added. Check the "include scripts" in the find
		  dialog.
		- Script files are backed up when saving (PSC) or compiling (PEX). This is more
		  important now as there is no version control for scripts unless otherwise 
		  implemented by the user.
	- New editable records: Actor Values (AVIF).
	- Fixed bug when creating a copy of a record.
	- Redid Perks: Should be 100% supported, needs testing.
	- Redid Conditions: Close to 100% supported, copy/paste conditions (right-click
	  on condition list or condition buttons).
	- Added context menus to keyword and ARMA lists.
	- Added "Active Only" to the View menu and shortcut key Ctrl+R
	- Added several commands to change the form ID of a record or selected records in the
	  main list accessed via the right-click context menu. When changing a form ID these
	  features try to propagate the change to all dependant records, however not all records
	  are fully deciphered or supported in SkyEdit yet so it is not 100%. In general, if you
	  can edit a record any form ID changes should be propagated into it. None of these 
	  records will overwrite an existing form ID. The form ID commands are:
	  		Change FormID: Specifically set the the form ID for one record.
			Change Mod Index: Change the upper byte of the form ID for all selected records.
			Assign New FormID: Set the mod index to a fixed value and the lower 3 bytes to 
				a guaranteed new and unused value.
	  Note that with the current implementation these commands operate around a speed
	  of 25 records/second so beware when selecting a large number of records to update.
	- Fixed bad file record count in TES4 header when saving.
	- Changed how creating a new plugin works to be similar to opening a plugin. Skyrim.esm
	  is automatically set as a master file by default. This should prevent people from 
	  creating new plugins that don't have Skyrim.esm as a master file as most should.
	- Resource and script information is now automatically loaded and initialized at startup
	  as it is needed in a variety of places. It only takes 2-5 seconds and only has to 
	  occur once until you restart SkyEdit.

0.05alpha - 17 January 2021
	- New editable records: Sound Categories (SNCT), Sound Markers (SOPM), Outfits,
	  Colors (CLFM), Form Lists (FLST), Encounter Zone (ECZN), Races (needs testing)
	- Raw data view is faster for larger records (like RACEs) but is without color.
	- Multiple MODL subrecords in ARMO can now be edited properly.
	- Fixed main view resizing issue...again (probably).
	- Containers/Leveled lists now support COED subrecords.
	- Can copy text from the error/log control bar.
	- Many small fixes and improvements.

0.046alpha - 7 January 2021
	- Fix saving crash.
	- New editable records: Sound Descriptors (SNDR)

0.045alpha - 7 January 2021
	- Added filter text (display records with an editor ID containing that text)  
	  and active only (display just the active mod records) controls.
	- Leveled lists sort records by level when being saved. Fixed level list saving bug.
	- Support for saving of plugins with localized strings (click "Edit-Use Local Strings"
	  to toggle on/off). String files are backed up on save just like plugin files.
	- Perk sections can now be added and deleted.
	- Edit mod author/description (under the Edit menu).
	- New editable records: Camera Shot, Sounds
	- Added bounds data handling to most records (only editable via batch edit currently).

0.041alpha - 4 January 2021
	- Beta of editable Perks
	- Fixed resource viewer crash
	- Fixed "HasSpell" function selection in conditions
	- Fixed condition corruption in magic related records and recipes

0.04alpha - 3 January 2021
	- New Editable Records: ACTI, ARMA, SLGM, SHOU, WOOP
	- Variety of major/minor bug fixes
	- Addition of a basic raw/hex data dialog (right-click and choose "Raw Data View...")
	  This works with any record type including "non-editable"
	- Condition data can accept script variables for param1/2 (enter as "::VariableName")
	- Added hard-coded player reference object.

0.031alpha - 22 December 2011
	- Fixed game crash from a modified record with no keywords.

0.03alpha - 22 December 2011
	- New Editable Types: AMMO, ARMO, ALCH, BOOK, CONT, INGR, LIGH, LVLI, LVLN, 
		LVSP, MISC, SCRL, STAT
	- Expand Existing Types: MGEF, WEAP
	- Find formids

0.02alpha - 16 December 2011
	- Several crash bug fixes
	- A bunch of records added to the list display
	- Addition of editable enchantments and spells
	- Expanded editing of existing records
	- Added missing record drag capabilities

0.01alpha - 10 December 2011
	- First release
	- Editable: KYWD, GLOB, GMST, COBJ, WEAP, MGEF


  Credits
=======================================
SkyEdit uses several libraries which has sped up development considerably.

  - Devil (http://openil.sourceforge.net/) for loading images.
  - zLib (http://www.zlib.net/) for loading/saving compressed data.
  - Resizable Control Bars (http://www.datamekanix.com/) for the dockable error/undo 
    control bars in the main view.
  - Tes5Lib (http://github.com/uesp/tes5lib)


