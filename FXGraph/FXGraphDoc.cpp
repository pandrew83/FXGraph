
// FXGraphDoc.cpp : ���������� ������ CFXGraphDoc
//

#include "stdafx.h"
// SHARED_HANDLERS ����� ���������� � ������������ �������� ��������� ���������� ������� ATL, �������
// � ������; ��������� ��������� ������������ ��� ��������� � ������ �������.
#ifndef SHARED_HANDLERS
#include "FXGraph.h"
#endif

#include "FXGraphDoc.h"
#include "FXGraphView.h"

#include "MainFrm.h"

#include <propkey.h>
#include "FXBlock.h"
#include "FXBlockLogicalAnd.h"
#include "FXBlockFunctional.h"
#include "FXBlockLogicalOr.h"
#include "FXBlockLogicalNot.h"
#include "FXBlockLogicalXor.h"
#include "ChildFrm.h"
#include "ProjectDlg.h"
#include "FindByIDDlg.h"
#include <iostream>
#include "shunting-yard.h"
#include "./cparse/builtin-features.inc"
#include "FXScenarioItem.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFXGraphDoc

IMPLEMENT_DYNCREATE(CFXGraphDoc, CDocument)

BEGIN_MESSAGE_MAP(CFXGraphDoc, CDocument)
//	ON_COMMAND(ID_DEBUG_RESTART, &CFXGraphDoc::OnDebugRestart)
//	ON_COMMAND(ID_DEBUG_START, &CFXGraphDoc::OnDebugStart)
//	ON_COMMAND(ID_DEBUG_STEP, &CFXGraphDoc::OnDebugStep)
//	ON_COMMAND(ID_DEBUG_STOP, &CFXGraphDoc::OnDebugStop)
//	ON_COMMAND(ID_PARAMS, &CFXGraphDoc::OnParams)
//	ON_COMMAND(ID_DEBUG_STEP_INTO, &CFXGraphDoc::OnDebugStepInto)
//	ON_COMMAND(ID_DEBUG_STEP_OVER, &CFXGraphDoc::OnDebugStepOver)
//	ON_COMMAND(ID_DEBUG_STEP_TO, &CFXGraphDoc::OnDebugStepTo)
	ON_COMMAND(ID_PROJECT_PROPERTIES, &CFXGraphDoc::OnProjectProperties)
	ON_COMMAND(ID_FINDBYID, &CFXGraphDoc::OnFindbyid)
	ON_COMMAND(ID_PROJECT_SCENARIO, &CFXGraphDoc::OnProjectScenario)
END_MESSAGE_MAP()


// ��������/����������� CFXGraphDoc

CFXGraphDoc::CFXGraphDoc()
	: m_pDebugCur(NULL)
	, m_bDebug(false)
	
	, m_DebugTimer(0)
	, m_DebugScenario(_T(""))
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphDoc::CFXGraphDoc");
	m_pBlock = NULL;	
	m_pDebugCur = NULL;
}

CFXGraphDoc::~CFXGraphDoc()
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphDoc::~CFXGraphDoc");
	POSITION pos = m_InputParams.GetHeadPosition();
	while (pos)
		delete m_InputParams.GetNext(pos);
	
	pos = m_OutputParams.GetHeadPosition();
	while (pos)
		delete m_OutputParams.GetNext(pos);
	delete m_pBlock;
	RemoveScenario();
}

BOOL CFXGraphDoc::OnNewDocument()
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphDoc::OnNewDocument");
	if (!CDocument::OnNewDocument())
		return FALSE;
	POSITION pos = GetFirstViewPosition();
	m_pBlock = new CFXBlockFunctional(NULL);

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CFXGraphView* pView = (CFXGraphView*)GetNextView(pos);
	pView->m_pBlock = m_pBlock;
	m_CycleTicks = 200;
	m_SysTick = 0;
	m_DebugTimer = 1000;
	m_DebugScenario = "// Debug scenario\r\n// {tick},{id},{expression}\r\n// {tick} - ������ ������� ��� ���������� ������ (��������� ������ ����������), ���� * - ��� ������� �������\r\n// {id} - ������������� ������� ��� �������� ����� ��������� ��������� {expression}\r\n// {expression} = {value} - ��������� ����������� � ������ ������� tick ��� ������� � ��������������� id\r\n// {value}=value(<value>), <value> �������� ���� Logical, Int, Float";
//	m_pBlock = pView->m_pBlock;
//	m_LastID = 1;
	// TODO: �������� ��� ��������� �������������
	// (��������� SDI ����� �������� ������������ ���� ��������)

	//m_InputParams.AddTail(new CFXParam(_T("Started"),Logical));
	//m_InputParams.AddTail(new CFXParam(_T("P1Max"),Float));
	//m_InputParams.AddTail(new CFXParam(_T("P1Min"),Float));
	//m_InputParams.AddTail(new CFXParam(_T("dP"),Float));
	//m_OutputParams.AddTail(new CFXParam(_T("P1"),Float));
	return TRUE;
}




// ������������ CFXGraphDoc

void CFXGraphDoc::Serialize(CArchive& ar)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphDoc::Serialize");
	if (ar.IsStoring()){
		ar << VERSION_MAJOR;
		ar << VERSION_MINOR;
		ar << m_CycleTicks;
		ar << m_DebugTimer;
		ar << m_DebugScenario;
		ar.WriteCount(m_InputParams.GetCount());
		POSITION pos = m_InputParams.GetHeadPosition();
		while (pos){
			ar << m_InputParams.GetNext(pos);
		}
		ar.WriteCount(m_OutputParams.GetCount());
		pos = m_OutputParams.GetHeadPosition();
		while (pos){
			ar << m_OutputParams.GetNext(pos);
		}
		m_pBlock->Serialize(ar);
	}
	else{
		int version_major;
		int version_minor;
		ar >> version_major;
		ar >> version_minor;
		ar >> m_CycleTicks;
		ar >> m_DebugTimer;
		ar >> m_DebugScenario;
		if (version_major != VERSION_MAJOR || version_minor != VERSION_MINOR){
			AfxMessageBox(_T("������ ������������ ����� �� ������������� ������ ���������"));
			throw new CArchiveException();
			return;
		}
		int c = ar.ReadCount();
		for(int i=0; i<c; i++){
			CFXParam* p;
			ar >> p;
			m_InputParams.AddTail(p);
		}
		c = ar.ReadCount();
		for (int i=0; i<c; i++){
			CFXParam* p;
			ar >> p;
			m_OutputParams.AddTail(p);
		}
		POSITION pos = GetFirstViewPosition();
		CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
		CFXGraphView* pView = (CFXGraphView*)GetNextView(pos);

		pView->m_pBlock = new CFXBlockFunctional(NULL);
		m_pBlock = pView->m_pBlock;
		m_pBlock->Serialize(ar);
	}
}

#ifdef SHARED_HANDLERS

// ��������� ��� �������
void CFXGraphDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �������� ���� ��� ��� ����������� ������ ���������
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ��������� ������������ ������
void CFXGraphDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������� ���������� ������ �� ������ ���������. 
	// ����� ����������� ������ ����������� ������ � ������� ";"

	// ��������:  strSearchContent = _T("�����;�������������;����;������ ole;");
	SetSearchContent(strSearchContent);
}

void CFXGraphDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// ����������� CFXGraphDoc

#ifdef _DEBUG
void CFXGraphDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFXGraphDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// ������� CFXGraphDoc




//
//CFXLink* CFXGraphDoc::AddLink(CFXPin* pPin1, CFXPin* pPin2)
//{
//	CFXLink* pLink = m_pBlock->GetLink(pPin1,pPin2);
//	if (pLink){
//		Log(Build,_T("��������� ���� ��� ��������� ������"));
//		return pLink;
//	}
//	pLink = m_pBlock->AddLink(pPin1,pPin2);
//	if (!pLink)
//		return NULL;
//	pLink->m_pPin1 = pPin1;
//	pLink->m_pPin2 = pPin2;
//	pLink->m_ID = m_pBlock->GetNewID();
//	if (pPin1->m_Dir == Input)
//		pPin1->SetName(pPin2->GetName());
//	else
//		pPin2->SetName(pPin1->GetName());
//	return NULL;
//}


BOOL CFXGraphDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphDoc::OnOpenDocument");
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  �������� ������������������ ��� ��������
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pMainFrame->m_wndFileView.UpdateFileView(this);
	return TRUE;
}


//void CFXGraphDoc::OnDebugRestart()
//{
//	TracePrint(TRACE_LEVEL_1,"CFXGraphDoc::OnDebugRestart");
//	if (m_bDebug){
//		if (!m_pBlock->Check()){
//			AfxMessageBox(_T("�������� ������� �� ��������!"));
//			return;
//		}
//		m_pDebugCur = m_pBlock->m_pDebugFirst;
//		m_SysTick = 0;
//		InitializeBlocks();
//	}
//	else
//		AfxMessageBox(_T("������� �� ������"));
//}


void CFXGraphDoc::DebugStart()
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphDoc::OnDebugStart"); 
	
	if (!m_pBlock->Check()){
		AfxMessageBox(_T("�������� ������� �� ��������!"));
		m_bDebug = false;
		return;
	}
	m_pBlock->CalcOrder();
	InitializeBlocks();
	InitializeScenario();
	m_pDebugCur = m_pBlock->m_pDebugFirst;
	if (!m_pBlock->m_pDebugFirst){
		AfxMessageBox(_T("������ ������"));
		m_bDebug = false;
		return;
	}
	m_SysTick = 0;
	m_bDebug = true;
	
	UpdateAllViews(NULL);
}




//void CFXGraphDoc::OnDebugStop()
//{
//	TracePrint(TRACE_LEVEL_1,"CFXGraphDoc::OnDebugStop");
//	m_bDebug = false;
//	m_pDebugCur = NULL;
//	m_SysTick = 0;
//	UpdateAllViews(NULL);
//}

void CFXGraphDoc::UpdateCalcOrder(void)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphDoc::UpdateCalcOrder");
	m_pBlock->CalcOrder();
}


bool CFXGraphDoc::InitializeBlocks(void)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphDoc::InitializeBlocks");
	m_pBlock->Initialize();
	//CFXBlock* pCur = m_pBlock->m_pDebugFirst;
	//while (pCur){
	//	POSITION pos = pCur->m_InputPins.GetHeadPosition();
	//	while (pos){
	//		CFXPin* pPin = pCur->m_InputPins.GetNext(pos);
	//		if (pPin->m_pParam){
	//			pPin->SetValue(pPin->m_pParam->m_Value);
	//		}
	//	}
	//	pCur = pCur->m_pNextBlock;
	//}
	return true;
}


//void CFXGraphDoc::OnParams()
//{
//}


//void CFXGraphDoc::OnDebugStepInto()
//{
//	TracePrint(TRACE_LEVEL_1,"OnDebugStepInto");
//	if (m_bDebug){
//		CFXBlockFunctional* pCur = dynamic_cast<CFXBlockFunctional*>(m_pDebugCur);
//		if (pCur){
//			m_pDebugCur = pCur->m_pDebugFirst;
//			if (!m_pDebugCur->m_bCalc)
//				OnDebugStepOver();
//			UpdateAllViews(NULL);
//			return;
//		}
//		else{
//			OnDebugStepOver();
//		}
//	}
//	// TODO: �������� ���� ��� ����������� ������
//}


//void CFXGraphDoc::OnDebugStepOver()
//{
//	TracePrint(TRACE_LEVEL_1,"CFXGraphDoc::OnDebugStepOver");
//	if (m_bDebug){
//		do {
//			if (!m_pDebugCur->Calc()){
//				m_bDebug = false;
//				Log(Debug,_T("������ ������� �����"));
//				return;
//			}
//			m_pDebugCur->UpdateConnectedPins();
//			m_pDebugCur = m_pDebugCur->m_pNextBlock;
//			if (!m_pDebugCur){
//				// �������� ����� �������
//				// ��������� �� ������
//				// �������� ������� �������� �� ������ �������
//				OnDebugCycleEnd();
//			}
//		}
//		while (!m_pDebugCur->m_bCalc);
//		UpdateAllViews(NULL);
//	}
//	// TODO: �������� ���� ��� ����������� ������
//}

//void CFXGraphDoc::OnDebugStepTo()
//{
//	TracePrint(TRACE_LEVEL_1,"CFXGraphDoc::OnDebugStepTo");
//	CMDIChildWnd* pFrame = ((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd))->MDIGetActive();
//	CFXGraphView* pView = (CFXGraphView*)pFrame->GetActiveView();
//	if (m_bDebug && m_pDebugCur && pView && pView->m_pCur){
//		do{
//			OnDebugStepInto();
//		}
//		while(m_pDebugCur != pView->m_pCur);
//	}
//}


CFXParam* CFXGraphDoc::GetInputParam(CString param)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphDoc::GetInputParam");
	POSITION pos = m_InputParams.GetHeadPosition();
	while (pos){
		CFXParam* pParam = m_InputParams.GetNext(pos);
		if (pParam->m_Name == param)
			return pParam;
	}
	return NULL;
}


CFXParam* CFXGraphDoc::GetOutputParam(CString paramName)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphDoc::GetOutputParam");
	POSITION pos = m_OutputParams.GetHeadPosition();
	while (pos){
		CFXParam* pParam = m_OutputParams.GetNext(pos);
		if (pParam->m_Name == paramName)
			return pParam;
	}
	return NULL;
}

void ParameterUpdateRecurse(CFXBlockFunctional* pCur){
	TracePrint(TRACE_LEVEL_1,"ParameterUpdateRecurse");
	POSITION pos = pCur->m_Blocks.GetHeadPosition();
	while (pos){
		CFXBlock* pBlock = pCur->m_Blocks.GetNext(pos);
		CFXBlockFunctional* pBlockFunc = dynamic_cast<CFXBlockFunctional*>(pBlock);
		if (pBlock){
			POSITION pos = pBlock->m_InputPins.GetHeadPosition();
			while (pos){
				CFXPin* pPin = pBlock->m_InputPins.GetNext(pos);
				if (pPin->m_pParam){
					if (pPin->m_Type != pPin->m_pParam->m_Type){
						pPin->m_pParam = NULL;
					}
					else{
						pPin->SetValue(pPin->m_pParam->m_Value);
					}
				}
			}
		}
		if (pBlockFunc){
			ParameterUpdateRecurse(pBlockFunc);
		}

	}
}

void CFXGraphDoc::OnParameterUpdated(CFXParam* pParam)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphDoc::OnParameterUpdated");
	ParameterUpdateRecurse(m_pBlock);
}


bool CFXGraphDoc::CheckParamName(CString paramName)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphDoc::CheckParamName");
	return GetInputParam(paramName) || GetOutputParam(paramName);
}


CFXGraphView* CFXGraphDoc::OpenBlock(CFXBlockFunctional* pBlockFunc)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphDoc::OpenBlock");
	CFXGraphView* pView = GetBlockView(pBlockFunc);
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CChildFrame* pChildFrame = (CChildFrame*)pMainFrame->GetActiveFrame();
	if (!pView){
		CDocTemplate* pDT = GetDocTemplate();
		 pChildFrame = (CChildFrame*)pDT->CreateNewFrame(this,NULL);
			
		pDT->InitialUpdateFrame(pChildFrame,this);
		pView = (CFXGraphView*)pChildFrame->GetActiveView();
		pView->m_pBlock = pBlockFunc;
	}
	else{
		pView->GetParentFrame()->ActivateFrame(SW_RESTORE);
		//pChildFrame = (CChildFrame*)pView->GetParent();
		//pChildFrame->SetActiveView(pView);
	}
	return pView;
}



CFXGraphView* CFXGraphDoc::GetBlockView(CFXBlockFunctional* pBlockFunc)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphDoc::GetBlockView");
	POSITION pos = GetFirstViewPosition();
	while (pos){
		CFXGraphView* pView = dynamic_cast<CFXGraphView*>(GetNextView(pos));
		if (pView && pView->m_pBlock == pBlockFunc){
			return pView;
		}
	}
	return NULL;
}


void CFXGraphDoc::OnRemoveBlock(CFXBlock* pBlock)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphDoc::OnRemoveBlock");
	CFXBlockFunctional* pBlockFunc = dynamic_cast<CFXBlockFunctional*>(pBlock);
	if (pBlockFunc){
		CFXGraphView* pView = GetBlockView(pBlockFunc);
		if (pView)
			pView->GetParentFrame()->DestroyWindow();
	}
}




void CFXGraphDoc::OnDebugCycleEnd(void)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphDoc::OnDebugCycleEnd");
	m_SysTick += m_CycleTicks;
//	m_pBlock->UpdateView();
//	UpdateAllViews(NULL);

}


void CFXGraphDoc::OnProjectProperties()
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphDoc::OnProjectProperties");
	// 50;100;200;250;500;1000
	int ar[6] = {50,100,200,250,500,1000};
	CProjectDlg dlg;
	for (int i=0; i<6; i++){
		if (ar[i] == m_CycleTicks)
			dlg.m_CycleTicks = i;
	}
	dlg.m_DebugTimer = m_DebugTimer;
	if (dlg.DoModal() == IDOK){
		m_CycleTicks = ar[dlg.m_CycleTicks];
		m_DebugTimer = dlg.m_DebugTimer;
	}
	// TODO: �������� ���� ��� ����������� ������
}


void CFXGraphDoc::OnFindbyid()
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphDoc::OnFindbyid");
	CFindByIDDlg dlg;
	if (dlg.DoModal() == IDOK){
		CFXObject* pObject = m_pBlock->GetByID(dlg.m_ID);
		if (pObject){
			CFXObject* pObj;
			CFXPin* pPin = dynamic_cast<CFXPin*>(pObject);
			if (pPin)
				pObj = pPin->m_pBlock;
			else 
				pObj = pObject;
			CFXBlockFunctional* pParent = dynamic_cast<CFXBlockFunctional*>(pObj->m_pBlock);
			if (pParent){
				CFXGraphView* pView = OpenBlock(pParent);
				pView->SetActiveObject(pObject);
				pView->SetViewAt(pObject);
			}
		}
	}
}

void CFXGraphDoc::DebugStep(){
	// Step into
	TracePrint(TRACE_LEVEL_1,"CFXGraphDoc::DebugStep()");
	if (m_pDebugCur){
		m_pDebugCur->Calc();
		UpdateBlock(m_pDebugCur);
		// next
		CFXBlockFunctional* pBlockFunc = dynamic_cast<CFXBlockFunctional*>(m_pDebugCur);
		if (pBlockFunc){
			m_pDebugCur = pBlockFunc->m_pDebugFirst;
		}
		else{
			m_pDebugCur = m_pDebugCur->m_pNextBlock;
		}
		if (!m_pDebugCur){
			OnDebugCycleEnd();
			m_pDebugCur = m_pBlock->m_pDebugFirst;
		}
		UpdateBlock(m_pDebugCur);
	}
}

void CFXGraphDoc::DebugRun(void)
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphDoc::DebugRun");
	ASSERT(m_bDebug);
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	ASSERT(pMainFrame);
	if (m_pDebugCur){
		// ��������� ��������
		POSITION pos = m_Scenario.GetHeadPosition();
		while (pos) {
			CFXScenarioItem* pItem = m_Scenario.GetNext(pos);
			using namespace cparser;
			TokenMap vars;
			vars["ticks"] = m_SysTick;
			switch (pItem->m_pPin->m_Type) {
			case Int:
				vars["value"] = (int)pItem->m_pPin->GetValue();
				break;
			case Float:
				vars["value"] = (double)pItem->m_pPin->GetValue();
				break;
			case Logical:
				vars["value"] = (bool)pItem->m_pPin->GetValue();
				break;
			}
			if (pItem->EvalCondition(vars)) {
				pItem->EvalExpression(vars);
				switch (pItem->m_pPin->m_Type) {
				case Int:
					pItem->m_pPin->SetValue(vars["value"].asInt());
					break;
				case Float:
					pItem->m_pPin->SetValue(vars["value"].asDouble());
					break;
				case Logical:
					pItem->m_pPin->SetValue(vars["value"].asBool());
					break;
				}
				UpdateBlock((CFXBlock*)pItem->m_pPin->m_pBlock, false);
				// execute scenario

			}
		
		}
		do{
//			DebugStep();
			m_pDebugCur->Calc();
//			UpdateBlock(m_pDebugCur);
			UpdateBlock(m_pDebugCur, false);
			CFXBlockFunctional* pBlockFunc = dynamic_cast<CFXBlockFunctional*>(m_pDebugCur);
			if (pBlockFunc){
				m_pDebugCur = pBlockFunc->m_pDebugFirst;
			}
			else{
				m_pDebugCur = m_pDebugCur->m_pNextBlock;
			}
			if (m_pDebugCur && m_pDebugCur->m_bBreakPoint){
				//UpdateBlock(m_pDebugCur,true);
				UpdateAllViews(NULL);
				
				pMainFrame->OnDebugBreakPoint(this);
				break;
			}
		}
		while (m_pDebugCur);
		if (!m_pDebugCur){
			OnDebugCycleEnd();
			m_pDebugCur = m_pBlock->m_pDebugFirst;
		}
	}
}


void CFXGraphDoc::CalcOrder(void)
{
	
}


void CFXGraphDoc::DebugStop(void)
{
	m_bDebug = false;
	UpdateAllViews(NULL);
}


void CFXGraphDoc::UpdateBlock(CFXBlock* pBlock, bool activate)
{
	CFXGraphView* pView = GetBlockView(dynamic_cast<CFXBlockFunctional*>(pBlock->m_pBlock));
	if (pView){
		pBlock->Invalidate(pView,REGION_BLOCK|REGION_PIN|REGION_VALUE);
		if (activate){
			pView->UnselectAll();
			pView->SelectObject(pBlock);
			pView->SetActiveObject(pBlock);
			pView->GetParentFrame()->ActivateFrame(SW_RESTORE);
		}

	}
}


void CFXGraphDoc::DebugStepOver(void)
{
}


void CFXGraphDoc::DebugPause(void)
{
	if (m_pDebugCur){
		UpdateBlock(m_pDebugCur,true);
	}
}


void CFXGraphDoc::OnProjectScenario()
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphDoc::OnProjectScenario");
	CFXGraphViewScenario* pView = NULL;//GetBlockView(pBlockFunc);
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CChildFrame* pChildFrame;// = (CChildFrame*)pMainFrame->GetActiveFrame();
	CDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_FXGraphTYPE,
		RUNTIME_CLASS(CFXGraphDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CFXGraphViewScenario));
		CDocTemplate* pDT = pDocTemplate;
		 pChildFrame = (CChildFrame*)pDT->CreateNewFrame(this,NULL);
			
		pDT->InitialUpdateFrame(pChildFrame,this);
		pView = (CFXGraphViewScenario*)pChildFrame->GetActiveView();
		
		pView->GetEditCtrl().SetWindowText(m_DebugScenario);
//		pView->m_pBlock = pBlockFunc;
	//}
	//else{
	//	pView->GetParentFrame()->ActivateFrame(SW_RESTORE);
	//	//pChildFrame = (CChildFrame*)pView->GetParent();
	//	//pChildFrame->SetActiveView(pView);
	//}
}


bool CFXGraphDoc::InitializeScenario(void)
{
	RemoveScenario();
	cparse_startup();
	int curpos = 0;
	CString line;
	do{
		line = m_DebugScenario.Tokenize(_T("\r\n"),curpos);
		if (!line.IsEmpty()){
			TRACE(line);
			if (line.Left(2) == "//")
				continue;
			int curpos1 = 0;
			int n = 0;
			CString ar[3];
			do {
				CString s = line.Tokenize(_T(","), curpos1);
				if (s.IsEmpty())
					break;
				ar[n++] = s;
			} while (true);
			if (n != 3) {
				AfxMessageBox(_T("������ ��� ������� ������ ��������"));
				return false;
			}
			CFXScenarioItem* pItem = new CFXScenarioItem;
			pItem->m_Condition = ar[0];
			CStringA s = CW2A(ar[1],CP_UTF8);
			pItem->m_pPin = dynamic_cast<CFXPin*>(m_pBlock->GetByID(atoi(s)));
			pItem->m_Expression = ar[2];
			if (!pItem->m_pPin) {
				CString msg;
				msg.Format(_T("������ � ��������: ������ � ��������������� %s �� ������ � ������� �������"), ar[1]);
				AfxMessageBox(msg);
				delete pItem;
				return false;
			}
			m_Scenario.AddTail(pItem);

		}
	} while(!line.IsEmpty());
	return true;
}	


void CFXGraphDoc::RemoveScenario()
{
	while (!m_Scenario.IsEmpty()) {
		CFXScenarioItem* pCur = m_Scenario.RemoveTail();
		delete pCur;
	}
}
