/*===========================================================================
 *
 * File:		SrContView.CPP
 * Author:		Dave Humphrey (uesp@sympatico.ca)
 * Created On:	17 December 2011
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "sredit.h"
#include "srcontview.h"
#include "dialogs/sreditdlghandler.h"
#include "SrContItemDlg.h"
#include <vector>


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
	IMPLEMENT_DYNCREATE(CSrContView, CSrRecordDialog)
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CSrContView, CSrRecordDialog)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_LVLLIST_EDIT, OnLvllistEdit)
	ON_UPDATE_COMMAND_UI(ID_LVLLIST_EDIT, OnUpdateLvllistEdit)
	ON_UPDATE_COMMAND_UI(ID_LVLLIST_DELETE, OnUpdateLvllistDelete)
	ON_UPDATE_COMMAND_UI(ID_LVLLIST_EDITRECORD, OnUpdateLvllistEdit)
	ON_COMMAND(ID_LVLLIST_ADD, OnLvllistAdd)
	ON_COMMAND(ID_LVLLIST_DELETE, OnLvllistDelete)
	ON_COMMAND(ID_MINUS_COUNT, OnMinusCount)
	ON_COMMAND(ID_ADD_COUNT, OnAddCount)
	ON_MESSAGE(ID_SRRECORDLIST_ACTIVATE, OnEditRecordMsg)
	ON_MESSAGE(ID_SRRECORDLIST_ALTACTIVATE, OnEditBaseRecordMsg)
	ON_COMMAND(ID_DELETE_ITEM, OnLvllistDelete)
	ON_COMMAND(ID_LVLLIST_EDITRECORD, OnLvlEditrecord)
	ON_NOTIFY(ID_SRRECORDLIST_CHECKDROP, IDC_ITEM_LIST, OnDropItemList)
	ON_NOTIFY(ID_SRRECORDLIST_DROP, IDC_ITEM_LIST, OnDropItemList)
	ON_NOTIFY(ID_SRRECORDLIST_KEYDOWN, IDC_ITEM_LIST, OnKeydownItemList)
	ON_BN_CLICKED(IDC_EDIT_OPENSOUND, &CSrContView::OnBnClickedEditOpensound)
	ON_BN_CLICKED(IDC_SELECT_OPENSOUND, &CSrContView::OnBnClickedSelectOpensound)
	ON_BN_CLICKED(IDC_EDIT_CLOSESOUND, &CSrContView::OnBnClickedEditClosesound)
	ON_BN_CLICKED(IDC_SELECT_CLOSESOUND, &CSrContView::OnBnClickedSelectClosesound)
END_MESSAGE_MAP()
/*===========================================================================
 *		End of Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin UI Field Map
 *
 *=========================================================================*/
BEGIN_SRRECUIFIELDS(CSrContView)
	ADD_SRRECUIFIELDS( SR_FIELD_EDITORID,		IDC_EDITORID,		128,	IDS_TT_EDITORID)
	ADD_SRRECUIFIELDS( SR_FIELD_FORMID,			IDC_FORMID,			16,		IDS_TT_FORMID)
	ADD_SRRECUIFIELDS( SR_FIELD_MODEL,			IDC_MODEL,			200,	IDS_TT_MODEL)
	ADD_SRRECUIFIELDS( SR_FIELD_TYPE,			IDC_TYPE,			16,		IDS_TT_TYPE)
	ADD_SRRECUIFIELDS( SR_FIELD_ITEMNAME,		IDC_NAME,			128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_OPENSOUND,		IDC_OPENSOUND,		128,	0)
	ADD_SRRECUIFIELDS( SR_FIELD_CLOSESOUND,		IDC_CLOSESOUND,		128,	0)
END_SRRECUIFIELDS()
/*===========================================================================
 *		End of UI Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Special callback functions for list sorting.
 *
 *=========================================================================*/
static int CALLBACK s_ItemCountRecListSort(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) 
{
	SRRL_SORTFUNC_GETPARAMS(lParam1, lParam2, lParamSort);
	CSrCntoSubrecord* pItem1 = SrCastClassNull(CSrCntoSubrecord, pCustomData1->Subrecords[0]);
	CSrCntoSubrecord* pItem2 = SrCastClassNull(CSrCntoSubrecord, pCustomData2->Subrecords[0]);

	if (pItem1 == NULL || pItem2 == NULL) return (0);
  
	if (pSortData->Reverse) return -((int)pItem1->GetCount() - (int)pItem2->GetCount());
	return ((int)pItem1->GetCount() - (int)pItem2->GetCount());
}


static int CALLBACK s_ItemFormIDRecListSort(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) 
{
	SRRL_SORTFUNC_GETPARAMS(lParam1, lParam2, lParamSort);
	CSrCntoSubrecord* pItem1 = SrCastClassNull(CSrCntoSubrecord, pCustomData1->Subrecords[0]);
	CSrCntoSubrecord* pItem2 = SrCastClassNull(CSrCntoSubrecord, pCustomData2->Subrecords[0]);
  
	if (pItem1 == NULL || pItem2 == NULL) return (0);

	if (pSortData->Reverse) return -(int)(pItem1->GetFormID() - pItem2->GetFormID());
	return (int)(pItem1->GetFormID() - pItem2->GetFormID());
}
/*===========================================================================
 *		End of Function CALLBACK s_DefaultRecListSort()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin List Column Definitions
 *
 *=========================================================================*/
static srreclistcolinit_t s_ContainerListInit[] = {
	{ SR_FIELD_EDITORID,		175,	LVCFMT_LEFT },
	{ SR_FIELD_FORMID,			5,		LVCFMT_LEFT,  s_ItemFormIDRecListSort},
	{ SR_FIELD_FLAGS,			40,		LVCFMT_CENTER },
	{ SR_FIELD_ITEMCOUNT,		50,		LVCFMT_CENTER, s_ItemCountRecListSort},
	{ SR_FIELD_RECORDTYPE,		50,		LVCFMT_CENTER },
	{ SR_FIELD_LISTFACTION,		100,	LVCFMT_CENTER },
	{ SR_FIELD_LISTMINRANK,		50,		LVCFMT_CENTER },
	{ SR_FIELD_LISTCONDITION,	50,		LVCFMT_CENTER },
	{ SR_FIELD_NONE, 0, 0 }
 };

static srrecfield_t s_ContainerListFields[] = {
	{ "Count",		SR_FIELD_ITEMCOUNT,		0, NULL },
	{ "Faction",	SR_FIELD_LISTFACTION,	0, NULL },
	{ "MinRank",	SR_FIELD_LISTMINRANK,	0, NULL },
	{ "Condition",	SR_FIELD_LISTCONDITION, 0, NULL },
	{ NULL,	SR_FIELD_NONE, 0, NULL }
 };
/*===========================================================================
 *		End of List Column Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Constructor
 *
 *=========================================================================*/
CSrContView::CSrContView() : CSrRecordDialog(CSrContView::IDD) 
{
	m_pScriptList = &m_Scripts;
	m_InitialSetData = false;
}
/*===========================================================================
 *		End of Class CSrContView Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Destructor
 *
 *=========================================================================*/
CSrContView::~CSrContView() 
{
	if (m_pRecordHandler != NULL) m_pRecordHandler->GetEventHandler().RemoveListener(this);
}
/*===========================================================================
 *		End of Class CSrContView Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Method - void DoDataExchange (pDX);
 *
 *=========================================================================*/
void CSrContView::DoDataExchange (CDataExchange* pDX) 
{
	CSrRecordDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDITORID, m_EditorID);
	DDX_Control(pDX, IDC_FORMID, m_FormID);
	DDX_Control(pDX, IDC_ITEM_LIST, m_ItemList);
	DDX_Control(pDX, IDC_NAME, m_ItemName);
	DDX_Control(pDX, IDC_TYPE, m_Type);
	DDX_Control(pDX, IDC_MODEL, m_Model);
	DDX_Control(pDX, IDC_OPENSOUND, m_OpenSound);
	DDX_Control(pDX, IDC_CLOSESOUND, m_CloseSound);
	DDX_Control(pDX, IDC_SCRIPT_LIST, m_Scripts);
 }
/*===========================================================================
 *		End of Class Method CSrContView::DoDataExchange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Method - void GetControlData (void);
 *
 *=========================================================================*/
void CSrContView::GetControlData (void) 
{
	CSrContRecord*    pContainer;

	CSrRecordDialog::GetControlData();
	if (m_EditInfo.pNewRecord == NULL) return;

	pContainer = SrCastClass(CSrContRecord, GetOutputRecord());
	if (pContainer == NULL) return;

	SrSaveLvlListInfo(m_LvlListInfo, *pContainer);
}
/*===========================================================================
 *		End of Class Method CSrContView::GetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSrContView Diagnostics
 *
 *=========================================================================*/
#ifdef _DEBUG

void CSrContView::AssertValid() const {
  CSrRecordDialog::AssertValid();
}


void CSrContView::Dump(CDumpContext& dc) const {
  CSrRecordDialog::Dump(dc);
}

#endif
/*===========================================================================
 *		End of CSrContView Diagnostics
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - void OnInitialUpdate (void);
 *
 *=========================================================================*/
void CSrContView::OnInitialUpdate (void) 
{
	CSrRecordDialog::OnInitialUpdate();

	SrFillComboList(m_Type, s_SrContainerTypes, 0);

		/* Setup the list */
	m_ItemList.SetListName("ContainerList");
	m_ItemList.DefaultSettings();
	m_ItemList.SetupCustomList(s_ContainerListInit, &CSrContRecord::s_FieldMap, s_ContainerListFields);
	m_ItemList.SetOwner(this);
	m_ItemList.SetDragType(SR_RLDRAG_CUSTOM | SR_RLDRAG_RECORD);
	m_ItemList.SetSortEnable(false);

	m_pRecordHandler->GetEventHandler().AddListener(this);

	SaveSubrecords();
	SetControlData();
}
/*===========================================================================
 *		End of Class Event CSrContView::OnInitialUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Method - void SaveSubrecords (void);
 *
 *=========================================================================*/
void CSrContView::SaveSubrecords (void) 
{
	SrCreateLvlListInfo(m_LvlListInfo, GetInputRecord());
}
/*===========================================================================
 *		End of Class Method CSrContView::SaveSubrecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Method - void SetControlData (void);
 *
 *=========================================================================*/
void CSrContView::SetControlData (void) 
{
	CSrRecordDialog::SetControlData();

	FillItemList();
}
/*===========================================================================
 *		End of Class Method CSrContView::SetControlData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Method - void FillItemList (void);
 *
 *=========================================================================*/
void CSrContView::FillItemList (void) 
{
	m_ItemList.DeleteAllItems();
  
	for (dword i = 0; i < m_LvlListInfo.GetSize(); ++i)
	{
		AddItemList(m_LvlListInfo[i]);
	}
}
/*===========================================================================
 *		End of Class Method CSrContView::FillItemList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Method - int AddItemList (pInfo);
 *
 *=========================================================================*/
int CSrContView::AddItemList (srlvllistinfo_t* pInfo) 
{
	srrlcustomdata_t  CustomData;
	int               ListIndex;

	if (pInfo->pCnto == NULL) return -1;
	SrCreateLvlListInfoCustomData(CustomData, *pInfo, m_pRecordHandler);

	ListIndex = m_ItemList.AddCustomRecord(CustomData);
	if (ListIndex < 0) return -1;

	UpdateItem(ListIndex, pInfo);
	return ListIndex;
}
/*===========================================================================
 *		End of Class Method CSrContView::AddItemList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Method - void UpdateItem (ListIndex, pInfo);
 *
 *=========================================================================*/
void CSrContView::UpdateItem (const int ListIndex, srlvllistinfo_t* pInfo) 
{
	CSrBaseRecord*    pBaseRecord;
	CSrIdRecord*	  pRecord;
	CString           Buffer;

	m_ItemList.UpdateRecord(ListIndex);

	pBaseRecord = m_pRecordHandler->FindFormID(pInfo->GetFormID());
	pRecord = SrCastClassNull(CSrIdRecord, pBaseRecord);
  
	if (pRecord == NULL) 
	{
		Buffer.Format("0x%08X", pInfo->GetFormID());
		m_ItemList.SetCustomField(ListIndex, SR_FIELD_FORMID, Buffer);

		m_ItemList.SetCustomField(ListIndex, SR_FIELD_EDITORID, "");
	}

		/* Set custom fields */
	Buffer.Format("%u", (dword) pInfo->GetCount());
	m_ItemList.SetCustomField(ListIndex, SR_FIELD_ITEMCOUNT, Buffer);

	if (pInfo->pCoed != NULL)
	{
		m_ItemList.SetCustomField(ListIndex, SR_FIELD_LISTFACTION, m_pRecordHandler->GetEditorID(pInfo->pCoed->GetCoedData().FactionID));

		Buffer.Format("%d", (int) pInfo->pCoed->GetCoedData().MinRank);
		m_ItemList.SetCustomField(ListIndex, SR_FIELD_LISTMINRANK, Buffer);

		Buffer.Format("%g", pInfo->pCoed->GetCoedData().Condition);
		m_ItemList.SetCustomField(ListIndex, SR_FIELD_LISTCONDITION, Buffer);
	}
	else
	{
		m_ItemList.SetCustomField(ListIndex, SR_FIELD_LISTFACTION, "");
		m_ItemList.SetCustomField(ListIndex, SR_FIELD_LISTMINRANK, "");
		m_ItemList.SetCustomField(ListIndex, SR_FIELD_LISTCONDITION, "");
	}
}
/*===========================================================================
 *		End of Class Method CSrContView::UpdateItem()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - void OnContextMenu (pWnd, Point);
 *
 *=========================================================================*/
void CSrContView::OnContextMenu (CWnd* pWnd, CPoint Point) 
{
  CMenu  Menu;
  CMenu* pSubMenu;
  int    Result;

  if (pWnd->GetDlgCtrlID() == IDC_ITEM_LIST) {
    Result = Menu.LoadMenu(IDR_CONTAINERLIST_MENU);
    if (!Result) return;

    pSubMenu = Menu.GetSubMenu(0);
    if (pSubMenu == NULL) return;

    pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, Point.x, Point.y, this, NULL);
  }
  else {  
    CSrRecordDialog::OnContextMenu(pWnd, Point);
  }
    
}
/*===========================================================================
 *		End of Class Event CSrContView::OnContextMenu()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - void OnLvllistEdit ();
 *
 *=========================================================================*/
void CSrContView::OnLvllistEdit() 
{
	CSrCntoSubrecord*	pSubrecord;
	srrlcustomdata_t*	pCustomData;
	srlvllistinfo_t*	pListInfo;
	int					ListIndex;
	int					Result;

	ListIndex = m_ItemList.GetSelectedItem();
	if (ListIndex < 0) return;

	pCustomData = m_ItemList.GetCustomData(ListIndex);
	if (pCustomData == NULL) return;

	pSubrecord = SrCastClassNull(CSrCntoSubrecord, pCustomData->Subrecords[0]);
	if (pSubrecord == NULL) return;

	pListInfo = SrFindLvlListInfo(m_LvlListInfo, pSubrecord);
	if (pListInfo == NULL) return;

	Result = SrEditContItemDlg(pListInfo, m_pDlgHandler, GetInputRecord()->GetFormID());
	if (Result == SR_CONTITEMDLG_RESULT_CANCEL) return;

	if (Result == SR_CONTITEMDLG_RESULT_DELETE) 
	{
		m_LvlListInfo.Delete(pListInfo);
		m_ItemList.RemoveItem(ListIndex);
		return;
	}
  
	SrCreateLvlListInfoCustomData(*pCustomData, *pListInfo, m_pRecordHandler);
	UpdateItem(ListIndex, pListInfo); 
}
/*===========================================================================
 *		End of Class Event CSrContView::OnLvllistEdit()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - LRESULT OnEditRecordMsg (wParam, lParam);
 *
 *=========================================================================*/
LRESULT CSrContView::OnEditRecordMsg (WPARAM wParam, LPARAM lParam) 
{
	OnLvllistEdit();
	return 0;
}
/*===========================================================================
 *		End of Class Event CSrContView::OnEditRecordMsg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - void OnLvllistAdd ();
 *
 *=========================================================================*/
void CSrContView::OnLvllistAdd() 
{
	srlvllistinfo_t*  pNewInfo;
	int				  Result;

	pNewInfo = m_LvlListInfo.AddNew();
	pNewInfo->InitializeNew(SR_NAME_CONT);
	Result = SrEditContItemDlg(pNewInfo, m_pDlgHandler, GetInputRecord()->GetFormID());

	if (Result == SR_CONTITEMDLG_RESULT_CANCEL || Result == SR_CONTITEMDLG_RESULT_DELETE) 
	{
		m_LvlListInfo.Delete(pNewInfo);
		return;
	}

	AddItemList(pNewInfo);
}
/*===========================================================================
 *		End of Class Event CSrContView::OnLvllistAdd()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - void OnLvllistDelete ();
 *
 *=========================================================================*/
void CSrContView::OnLvllistDelete() 
{
	std::vector<int> IndexList;
	POSITION         ListPos;
	int				 ListIndex;

	ListPos = m_ItemList.GetFirstSelectedItemPosition();

	while (ListPos != NULL) 
	{
		ListIndex = m_ItemList.GetNextSelectedItem(ListPos);
		IndexList.push_back(ListIndex);
	}

	while (IndexList.size() > 0)
	{
		ListIndex = IndexList.back();
		IndexList.pop_back();

		m_ItemList.DeleteItem(ListIndex);
		m_LvlListInfo.Delete(ListIndex);
	}

	m_ItemList.SelectRecord(0);
}
/*===========================================================================
 *		End of Class Event CSrContView::OnLvllistDelete()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - void OnUpdateLvllistDelete (pCmdUI);
 *
 *=========================================================================*/
void CSrContView::OnUpdateLvllistDelete (CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_ItemList.GetSelectedCount() > 0);	
}
/*===========================================================================
 *		End of Class Event CSrContView::OnUpdateLvllistDelete()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - void OnUpdateLvllistEdit (pCmdUI);
 *
 *=========================================================================*/
void CSrContView::OnUpdateLvllistEdit (CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_ItemList.GetSelectedCount() > 0);	
}
/*===========================================================================
 *		End of Class Event CSrContView::OnUpdateLvllistEdit()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - void OnAddCount ();
 *
 *=========================================================================*/
void CSrContView::OnAddCount() 
{
	srrlcustomdata_t*	pCustomData;
	CSrCntoSubrecord*	pItem;
	POSITION			ListPos;
	CString				Buffer;
	int				ListIndex;

	ListPos = m_ItemList.GetFirstSelectedItemPosition();

	while (ListPos != NULL) 
	{
		ListIndex = m_ItemList.GetNextSelectedItem(ListPos);
    
		pCustomData = m_ItemList.GetCustomData(ListIndex);
		if (pCustomData == NULL) continue;

		pItem = SrCastClassNull(CSrCntoSubrecord, pCustomData->Subrecords[0]);
		if (pItem == NULL) continue; 

		if (pItem->GetCount() >= 32768) continue;
		pItem->SetCount(pItem->GetCount() + 1);

		Buffer.Format("%u", (dword) pItem->GetCount());
		m_ItemList.SetCustomField(ListIndex, SR_FIELD_ITEMCOUNT, Buffer);
	}
	
}
/*===========================================================================
 *		End of Class Event CSrContView::OnAddCount()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - void OnMinusCount ();
 *
 *=========================================================================*/
void CSrContView::OnMinusCount() 
{
	srrlcustomdata_t*	pCustomData;
	CSrCntoSubrecord*	pItem;
	POSITION			ListPos;
	CString				Buffer;
	int					ListIndex;

	ListPos = m_ItemList.GetFirstSelectedItemPosition();

	while (ListPos != NULL) 
	{
		ListIndex = m_ItemList.GetNextSelectedItem(ListPos);
    
		pCustomData = m_ItemList.GetCustomData(ListIndex);
		if (pCustomData == NULL) continue;

		pItem = SrCastClassNull(CSrCntoSubrecord, pCustomData->Subrecords[0]);
		if (pItem == NULL) continue; 

		if (pItem->GetCount() == 0) continue;
		pItem->SetCount(pItem->GetCount() - 1);

		Buffer.Format("%u", (dword) pItem->GetCount());
		m_ItemList.SetCustomField(ListIndex, SR_FIELD_ITEMCOUNT, Buffer);
	}

}
/*===========================================================================
 *		End of Class Event CSrContView::OnMinusCount()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - int OnListenCleanRecord (pEvent);
 *
 *=========================================================================*/
int CSrContView::OnListenCleanRecord (CSrListenEvent* pEvent) 
{
	int ListIndex;

	ListIndex = m_ItemList.FindRecord(pEvent->GetOldRecord());
	if (ListIndex >= 0) m_ItemList.UpdateRecord(pEvent->GetNewRecord(), pEvent->GetOldRecord());

	return (SR_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CSrContView::OnListenCleanRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - int OnListenUpdateRecord (pEvent);
 *
 *=========================================================================*/
int CSrContView::OnListenUpdateRecord (CSrListenEvent* pEvent) 
{
	int ListIndex;

	ListIndex = m_ItemList.FindRecord(pEvent->GetOldRecord());
	if (ListIndex >= 0) m_ItemList.UpdateRecord(pEvent->GetNewRecord(), pEvent->GetOldRecord());

	return (SR_EVENT_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CSrContView::OnListenUpdateRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - void OnLvlEditrecord ();
 *
 *=========================================================================*/
void CSrContView::OnLvlEditrecord() 
{
	CSrRecord* pRecord;
	CWnd*      pWnd;

	pRecord = m_ItemList.GetSelectedRecord();
	if (pRecord == NULL) return;
  
	pWnd = GetOwner();
	if (pWnd != NULL) m_pDlgHandler->EditRecord(pRecord);
}
/*===========================================================================
 *		End of Class Event CSrContView::OnLvlEditrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - LRESULT OnEditBaseRecordMsg (wParam, lParam);
 *
 *=========================================================================*/
LRESULT CSrContView::OnEditBaseRecordMsg (WPARAM wParam, LPARAM lParam) 
{
	OnLvlEditrecord();
	return 0;
}
/*===========================================================================
 *		End of Class Event CSrContView::OnEditBaseRecordMsg()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - void OnDropItemList (pNotifyStruct, pResult);
 *
 *=========================================================================*/
void CSrContView::OnDropItemList (NMHDR* pNotifyStruct, LRESULT* pResult) 
{
	srrldroprecords_t* pDropItems = (srrldroprecords_t *) pNotifyStruct;

	*pResult = SRRL_DROPCHECK_ERROR;
  
	if (pDropItems->pCustomDatas != NULL && pDropItems->pCustomDatas->GetSize() > 0) 
	{
		*pResult = OnDropCustomData(*pDropItems);
	}
	else if (pDropItems->pRecords != NULL) 
	{
		*pResult = OnDropRecords(*pDropItems);
	} 

}
/*===========================================================================
 *		End of Class Event CSrContView::OnDropItemList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - int OnDropCustomData (DropItems);
 *
 *=========================================================================*/
int CSrContView::OnDropCustomData (srrldroprecords_t& DropItems) 
{
	CSrCntoSubrecord*  pItem;
	srlvllistinfo_t*   pInfo;
	srrlcustomdata_t*  pCustomData;
	dword			   Index;

	for (Index = 0; Index < DropItems.pCustomDatas->GetSize(); ++Index) 
	{
		pCustomData = DropItems.pCustomDatas->GetAt(Index);
		if (pCustomData == NULL) return (SRRL_DROPCHECK_ERROR);
		if (pCustomData->pRecord == NULL) return (SRRL_DROPCHECK_ERROR);

		if (!SrIsValidContainerRecord(pCustomData->pRecord->GetRecordType())) return (SRRL_DROPCHECK_ERROR);
		pItem = SrCastClassNull(CSrCntoSubrecord, pCustomData->Subrecords[0]);
		if (pItem == NULL) return (SRRL_DROPCHECK_ERROR);
    
			/* If we're just checking */
		if (DropItems.Notify.code == ID_SRRECORDLIST_CHECKDROP) continue;

		pInfo = m_LvlListInfo.AddNew();
		pInfo->CopyFrom(pCustomData->Subrecords);
		AddItemList(pInfo);
  }

  return (SRRL_DROPCHECK_OK);
}
/*===========================================================================
 *		End of Class Event CSrContView::OnDropCustomData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - int OnDropRecords (DropItems);
 *
 *=========================================================================*/
int CSrContView::OnDropRecords (srrldroprecords_t& DropItems) 
{
	srlvllistinfo_t*	pInfo;
	CSrRecord*			pRecord;
	dword				Index;

	for (Index = 0; Index < DropItems.pRecords->GetSize(); ++Index) 
	{
		pRecord = DropItems.pRecords->GetAt(Index);
    
			/* Don't drag onto ourself */
		if (pRecord == m_EditInfo.pOldRecord) return (SRRL_DROPCHECK_ERROR);
		if (pRecord->GetFormID() == m_EditInfo.pOldRecord->GetFormID()) return (SRRL_DROPCHECK_ERROR);

			/* Ignore any invalid record types */
		if (!SrIsValidContainerRecord(pRecord->GetRecordType())) return (SRRL_DROPCHECK_ERROR);

			/* If we're just checking */
		if (DropItems.Notify.code == ID_SRRECORDLIST_CHECKDROP) continue;

		pInfo = m_LvlListInfo.AddNew();
		pInfo->InitializeNew(SR_NAME_CONT);
		pInfo->SetFormID(pRecord->GetFormID());
		AddItemList(pInfo);
	}

	return (SRRL_DROPCHECK_OK);
}
/*===========================================================================
 *		End of Class Event CSrContView::OnDropRecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CSrContView Event - void OnKeydownItemList (pHdr, lResult);
 *
 *=========================================================================*/
void CSrContView::OnKeydownItemList (NMHDR* pHdr, LRESULT* lResult) 
{
	srrlkeydown_t* pNotify = (srrlkeydown_t *) pHdr;
	*lResult = 0;
	
	if (pNotify->KeyDown.nVKey == VK_DELETE || pNotify->KeyDown.nVKey == VK_BACK) 
	{
		if (!pNotify->Ctrl && !pNotify->Alt) OnLvllistDelete();
	}
	else if (pNotify->KeyDown.nVKey == VK_ADD) 
	{
		OnAddCount();
	}
	else if (pNotify->KeyDown.nVKey == VK_SUBTRACT) 
	{
		OnMinusCount();
	}

}
/*===========================================================================
 *		End of Class Event CSrContView::OnKeydownItemList()
 *=========================================================================*/


void CSrContView::OnBnClickedEditOpensound()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_OpenSound, SR_NAME_SNDR);
}


void CSrContView::OnBnClickedSelectOpensound()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_OpenSound, SR_NAME_SNDR, &CSrSndrRecord::s_FieldMap);
}


void CSrContView::OnBnClickedEditClosesound()
{
	if (m_pDlgHandler) m_pDlgHandler->EditRecordHelper(&m_CloseSound, SR_NAME_SNDR);
}


void CSrContView::OnBnClickedSelectClosesound()
{
	if (m_pDlgHandler) m_pDlgHandler->SelectRecordHelper(&m_CloseSound, SR_NAME_SNDR, &CSrSndrRecord::s_FieldMap);
}
