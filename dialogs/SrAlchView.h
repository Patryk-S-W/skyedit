/*===========================================================================
 *
 * File:		SrAlchView.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	16 December 2011
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SRALCHVIEW_H
#define __SRALCHVIEW_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
	#include "dialogs/srrecorddialog.h"
	#include "windows/srrecordlistctrl.h"
	#include "afxwin.h"
	#include "afxcmn.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


struct sralch_effectdata_t
{
	CSrFormidSubrecord*	pEffect;
	CSrEfitSubrecord*	pEffectData;
	CSrConditionArray	Conditions;

	sralch_effectdata_t()
	{
		pEffect = NULL;
		pEffectData = NULL;
	}

	~sralch_effectdata_t()
	{
		delete pEffect;
		delete pEffectData;
	}
};

typedef CSrPtrArray<sralch_effectdata_t> CSrAlchEffectArray;


/*===========================================================================
 *
 * Begin Class CSrAlchView Definition
 *
 *=========================================================================*/
class  CSrAlchView: public CSrRecordDialog 
{
  DECLARE_DYNCREATE(CSrAlchView);
  DECLARE_SRRECUIFIELDS();

  /*---------- Begin Protected Class Members ---------------------*/
protected:
	CSrAlchEffectArray		m_Effects;
	sralch_effectdata_t*	m_pCurrentEffect;
	bool					m_IsInitialized;
	


  /*---------- Begin Protected Class Methods ---------------------*/
protected:

		/* Protected constructor used by dynamic creation */
	CSrAlchView();

	void CreateEffectArray (void);

	void SetEffectList    (void);
	int  AddEffectList    (sralch_effectdata_t* pEffectData);
	void UpdateEffectList (const int ListIndex, const bool Update);

	void GetCurrentEffect (void);
	void SetCurrentEffect (sralch_effectdata_t* pEffectData);
	void EnableEffectControls (const bool Enable);
  

  /*---------- Begin Public Class Methods ------------------------*/
public:

	enum { IDD = IDD_ALCH_VIEW };
	CEdit		m_EditorID;
	CEdit		m_FormID;
	CEdit		m_ItemName;
	CSrRecordListCtrl m_EffectList;
	CEdit		m_EffectName;
	CButton		m_SelectEffectButton;
	CButton		m_EditEffectButton;
	CButton		m_EffectConditions;
	CEdit		m_Magnitude;
	CEdit		m_Area;
	CEdit		m_Duration;
	CEdit		m_Value;
	CEdit		m_Weight;
	CEdit		m_PickupSound;
	CEdit		m_DropSound;
	CEdit		m_UseSound;
	CListBox	m_Keywords;
	CEdit		m_Model;
	CEdit		m_EquipSlot;
	CEdit		m_InventoryIcon;
	CEdit		m_MessageIcon;
	CButton		m_AutoCalc;
	CButton		m_Food;
	CButton		m_Medicine;
	CButton		m_Poison;

public:
	virtual void  GetControlData   (void);
	virtual void  SetControlData   (void);
	virtual int   OnPreSaveRecord  (void);

protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
  virtual ~CSrAlchView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

  DECLARE_MESSAGE_MAP();

public:
	
	afx_msg void OnLvnItemchangedEffectList(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnBnClickedConditionButton();
	afx_msg void OnBnClickedEditEffect();
	afx_msg void OnBnClickedSelecteffectButton();
	afx_msg void OnBnClickedAddButton();
	afx_msg void OnBnClickedDeleteButton();	
	afx_msg void OnDropUseSound (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropEquipSlot (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnBnClickedEditUsesound();
	afx_msg void OnBnClickedSelectusesoundButton();
	afx_msg void OnConditionrecordCopy();
	afx_msg void OnConditionrecordPaste();
	afx_msg void OnConditionrecordDeleteAll();
	afx_msg void OnUpdateConditionrecordCopy(CCmdUI *pCmdUI);
	afx_msg void OnUpdateConditionrecordPaste(CCmdUI *pCmdUI);
	afx_msg void OnUpdateConditionrecordDeleteAll(CCmdUI *pCmdUI);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint Point);
	afx_msg void OnBnClickedSelectInventoryicon();
	afx_msg void OnBnClickedSelectMessageicon();
	afx_msg void OnBnClickedEditEquipslot();
	afx_msg void OnBnClickedSelectEquipslot();
	afx_msg void OnDropInventoryIcon (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDropMessageIcon (NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnDropEffectList (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg int  OnDropCustomEffectData (srrldroprecords_t& DropItems);  
	afx_msg void OnDropEffect (NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg	LRESULT OnEditEffectMsg (WPARAM wParam, LPARAM lParam);
};
/*===========================================================================
 *		End of Class CSrAlchView Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File SrAlchView.H
 *=========================================================================*/
