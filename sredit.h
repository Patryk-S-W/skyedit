/*===========================================================================
 *
 * File:		Sredit.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	Thursday, 27 July, 2006
 *
 * Main header file for the SREDIT application.
 *
 *=========================================================================*/
#ifndef __SREDIT_H
#define __SREDIT_H


/*===========================================================================
 *
 * Begin Required Include Files
 *
 *=========================================================================*/
#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

	#include "resource.h"
	#include "modfile/srespfile.h"
	#include "srprogressdlg.h"
	#include "windows/srrecordfilter.h"
	#include "srerrordlg.h"
	#include "modfile/srmultirecordhandler.h"
	#include "common/srconfigfile.h"
	#include "bsafile/srresourcehandler.h"
	#include "mainfrm.h"
	#include "srresourceview.h"
	#include "dialogs/SrScriptView.h"
/*===========================================================================
 *		End of Required Include Files
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Default options filename */
  #define SREDIT_OPTIONS_FILE "skyedit.ini"

	/* Default colors */
  #define SREDIT_COLOR_GRAY RGB(212,208,200)

	/* Base registry section */
  #define SREDIT_REGISTRY_BASE "Software\\UESP\\skyedit\\"

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrEditApp Definition
 *
 *=========================================================================*/
class CSrEditApp : public CWinAppEx {

  /*---------- Begin Protected Class Members -----------------------*/
protected:
  CMainFrame*			m_pMainFrame;

  srfileloadinfo_t*		m_pCurrentLoadInfo;		/* Used when loading a file */
  CSrProgressDlg*		m_pCurrentProgressDlg;
  CSrCallback*			m_pCurrentLoadCallback;

  CSrConfigFile			m_ConfigFile;

  CSString				m_AppPath;

  dword					m_NewFileIndex;

  CSrResourceHandler	m_ResourceHandler;
  CSrBsaFileArray		m_BsaFiles;
  bool					m_InitResourceHandler;
  bool					m_LoadAllScripts;

public:
	bool	m_EditScriptExternalByDefault;

protected:
	

  /*--------- Begin Public Class Methods ---------------------------*/
public:

		/* Class Constructor */
	CSrEditApp();
	virtual ~CSrEditApp();

	bool CreateNewScript (CString& ScriptName);

	bool LoadAllScripts (void);

	bool EditScriptFromData			(const char* pFilename, const bool UseInternal);
	bool EditScript					(const char* pFilename, const bool UseInternal);
	bool EditScript					(const char* pFilename);
	bool EditScriptExternal			(const char* pFilename);
	bool EditScriptFromData			(const char* pFilename);
	bool EditScriptExternalFromData (const char* pFilename);
	bool EditScriptName				(const char* pScriptName, const bool UseInternal);

	bool EditResourceExternal (const char* pFilename);

	dword FindInScripts (srfinddata_t& FindData, CSrCallback* pCallback);

		/* Get class members */
	srfileloadinfo_t*  GetCurrentLoadInfo     (void) { return (m_pCurrentLoadInfo); }
	CSrProgressDlg*    GetCurrentProgressDlg  (void) { return (m_pCurrentProgressDlg); }
	CSrCallback*       GetCurrentLoadCallback (void) { return (m_pCurrentLoadCallback); }
	CSrConfigFile&     GetConfigFile          (void) { return (m_ConfigFile); }
	const char*        GetAppPath             (void) { return (m_AppPath); }
	
		/* Load/save/update options */
	bool LoadOptions              (const TCHAR* pFilename);
	bool SaveOptions              (const TCHAR* pFilename);
	void UpdateOptions            (const bool Set);
	//void UpdateScriptColorOptions (CCustomCompiler& Compiler, const bool Set);
	//void UpdateScriptErrorOptions (const bool Set);
	void ResolveOptionPaths       (void);
	
	bool OpenWebHelp (const char* pPage);
	bool OpenWebHelp (const char* pUESPPage, const char* pCSPage);
	
	void             OpenResourceView    (const char* pResource);
	CFrameWnd*       FindResourceView    (void);
	bool             InitResourceHandler (void);
	CSrResourceView* CreateResourceView  (void);
	CSrResourceView* OpenResourceView    (void);
	
	CFrameWnd*       FindScriptsFrame    (void);
	CSrScriptView*   CreateScriptsView   (void);
	CSrScriptView*   OpenScriptsView     (void);
	CSrScriptView*   FindScriptsView     (void);
	void OpenScriptsResourceView (void);
	CSrScriptFile*	FindScriptName (const char* pScriptName);
	bool UpdateScript     (const char* pScriptName);
	bool UpdateScriptView (const char* pScriptName);

	void ResetListState (void);
	
	bool AddBsaFile      (const char* pFilename);

public:
  virtual BOOL InitInstance();
  virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
  virtual int ExitInstance();
  afx_msg void OnAppAbout();
  afx_msg void OnFileOpen();
  afx_msg void OnFileNew();

  DECLARE_MESSAGE_MAP()
};
/*===========================================================================
 *		End of Class CSrEditApp Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin External Definitions
 *
 *=========================================================================*/

	CSrEditApp&    GetSrEditApp        (void);
	CSrConfigFile& GetSrEditConfigFile (void);

	bool SrEditShowError     (const dword Flags, const TCHAR* pTitle, const TCHAR* pString, ...);
	bool SrEditShowError     (const TCHAR* pTitle, const TCHAR* pString, ...);
	bool SrEditShowError     (const TCHAR* pString, ...);
	bool SrEditShowLastError (const TCHAR* pString, ...);

	bool OpenWebPage (const char* pAddress);

	void SrLockUndoUpdates (const bool Lock);

	void WINAPI SetInternalWindowText(HWND hwnd, LPCTSTR lpText);

	void SrGlobClipAddCondition(srconditioninfo_t* pCondition, const bool Clear = false);
	void SrGlobClipClearConditions();
	CSrConditionArray& SrGlobClipGetConditions (void);

	void SrGlobClipAddScript(srvmadscript_t* pScript, const bool Clear = false);
	void SrGlobClipClearScripts();
	CSrVmadScriptArray& SrGlobClipGetScripts (void);

	void OnInitMenuPopupHelper (CWnd* pThis, CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);

/*===========================================================================
 *		End of External Definitions
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrEdit.h
 *=========================================================================*/
