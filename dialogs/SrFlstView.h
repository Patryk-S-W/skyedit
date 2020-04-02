/*===========================================================================
 *
 * File:		SrFlstView.H
 * Author:		Dave Humphrey (uesp@sympatico.ca)
 * Created On:	9 January 2012
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRFLSTVIEW_H
#define __SRFLSTVIEW_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
	#include "dialogs/srrecorddialog.h"
	#include "windows/srrecordlistctrl.h"
	#include "afxwin.h"
 /*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CSrFlstView Definition
 *
 *=========================================================================*/
class CSrFlstView : public CSrRecordDialog 
{
	DECLARE_DYNCREATE(CSrFlstView)
	DECLARE_SRRECUIFIELDS()

  /*---------- Begin Protected Class Members ----------------------------*/
protected:
	

  /*---------- Begin Protected Class Methods ----------------------------*/
protected:

		/* Protected constructor used by dynamic creation */
	CSrFlstView();         
	virtual ~CSrFlstView();

		/* Helper update methods */
	void FillItemList   (void);
	void SaveSubrecords (void);
	int  AddItemList    (const srformid_t FormID);

		/* Drag/drop helpers */
	int OnDropCustomData (srrldroprecords_t& DropItems);
	int OnDropRecords    (srrldroprecords_t& DropItems);


  /*---------- Begin Public Class Methods -------------------------------*/
public:

		/* Get and set data */
	virtual void  GetControlData   (void);
	virtual void  SetControlData   (void);

  		/* Listener events */
	virtual int OnListenCleanRecord     (CSrListenEvent* pEvent);
	virtual int OnListenUpdateRecord    (CSrListenEvent* pEvent);
	virtual int GetListenEvents         (void) { return (SR_EVENT_CLEANRECORD | SR_EVENT_UPDATERECORD); }

	enum { IDD = IDD_FLST_VIEW };
	CEdit			m_EditorID;
	CEdit			m_FormID;
	CSrRecordListCtrl	m_ItemList;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
  

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	virtual void OnInitialUpdate (void);
	afx_msg void OnContextMenu (CWnd* pWnd, CPoint Point);
	afx_msg LRESULT OnEditRecordMsg (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEditBaseRecordMsg (WPARAM wParam, LPARAM lParam);
	afx_msg void OnDropItemList (NMHDR* pNotifyStruct, LRESULT* pResult);
	  
	DECLARE_MESSAGE_MAP();

public:
	afx_msg void OnFlstlistAdd();
	afx_msg void OnFlstlistEdit();
	afx_msg void OnFlstlistDelete();
	afx_msg void OnFlsttlistEditbase();
	afx_msg void OnUpdateFlstlistEdit(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedAddButton();
	afx_msg void OnBnClickedEditButton();
	afx_msg void OnBnClickedDeleteButton4();
};
/*===========================================================================
 *		End of Class CSrFlstView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrFlstView.H
 *=========================================================================*/
