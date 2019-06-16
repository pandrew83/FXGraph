#include "StdAfx.h"
#include "FXBlockFunctional.h"
#include "FXGraphView.h"
#include "FXBlockFunctionalPin.h"
#include "FXBlockLogicalAnd.h"
#include "FXException.h"
#include "FXBlockController.h"
#include "FXBlockExtension.h"
#include "FXBlockComment.h"

IMPLEMENT_SERIAL(CFXBlockFunctional,CFXBlock,1)

CFXBlockFunctional::CFXBlockFunctional(void)
{
	m_pDebugFirst = NULL;
	m_LastID = 0;
}


CFXBlockFunctional::~CFXBlockFunctional(void)
{
	POSITION pos = m_Links.GetHeadPosition();
	while (pos){
		CFXLink* pLink = m_Links.GetNext(pos);
		delete pLink;
	}
	pos = m_Blocks.GetHeadPosition();
	while (pos){
		CFXBlock* pBlock = m_Blocks.GetNext(pos);
		delete pBlock;
	}
}

CFXPin* CFXBlockFunctional::AddInputPin(CFXPinType type, CString funcName, bool bAllowConst, bool bAllowParam, bool bConst, bool bLinkable){
	CFXPin* pPin = CFXBlock::AddInputPin(type,funcName,bAllowConst,bAllowParam,bConst,0,bLinkable);
	if (pPin){
		CString name;
		name.Format(_T("pin.%d"),pPin->m_ID);
		pPin->SetName(name);
		CFXBlockFunctionalPin* pBlock = new CFXBlockFunctionalPin(this,pPin);
		m_Blocks.AddTail(pBlock);
	}
	return pPin;
}

CFXPin* CFXBlockFunctional::AddOutputPin(CFXPinType type, CString funcName, bool bAllowConst, bool bAllowParam, bool bConst, bool bLinkable){
	CFXPin* pPin = CFXBlock::AddOutputPin(type,funcName,bAllowConst,bAllowParam,bConst,0,bLinkable);
	if (pPin){
		CFXBlockFunctionalPin* pBlock = new CFXBlockFunctionalPin(this,pPin);
		m_Blocks.AddTail(pBlock);
	}
	return pPin;
}


void CFXBlockFunctional::AddBlock(CFXBlock* pBlock)
{
	CFXBlockController* pController = dynamic_cast<CFXBlockController*>(pBlock);
	CFXBlockExtension* pExtension = dynamic_cast<CFXBlockExtension*>(pBlock);
	CFXBlockComment* pComment = dynamic_cast<CFXBlockComment*>(pBlock);
	if (pController && !IsRootBlock()){
		AfxMessageBox(_T("Нельзя добавить блок-контроллер в текущий функциональный блок"));
		delete pBlock;
		return;
	}
	if (pController ){
		POSITION pos = m_Blocks.GetHeadPosition();
		while (pos){
			CFXBlock* pCur = m_Blocks.GetNext(pos);
			CFXBlockController* pController = dynamic_cast<CFXBlockController*>(pCur);
			if (pController){
				AfxMessageBox(_T("Только один контроллер может быть в одном проекте"));
				delete pBlock;
				return;
			}
		}
	}
	if (pExtension && IsRootBlock()){
		AfxMessageBox(_T("Нельзя добавить блок расширения в текущий функциональный блок"));
		delete pBlock;
		return;
	}
	if (!pComment && !pController && IsRootBlock()){
		AfxMessageBox(_T("В корневой функцильный блок можно добавить только контроллеры и комментарии"));
		delete pBlock;
		return;
	}
	pBlock->m_pBlock = this;
	m_Blocks.AddTail(pBlock);
}

void CFXBlockFunctional::Draw(CFXGraphView*pView){
	if (pView->m_pBlock != this){
		CFXBlock::Draw(pView);
		return;
	}
	// определить порядок отрисовки

	// Сначала рисуем линии связи, если они включены
	if (pView->m_bShowLinks){
		POSITION pos = m_Links.GetHeadPosition();
		while (pos){
			CFXLink* pLink = m_Links.GetNext(pos);
			pLink->Draw(pView);
		}
	}
	POSITION pos = m_Blocks.GetHeadPosition();
	while (pos){
		CFXBlock* pBlock = m_Blocks.GetNext(pos);
		pBlock->Draw(pView);
	}
}


CFXObject* CFXBlockFunctional::GetByID(int ID)
{
	int object_id = ID & MASK1_ID;
	
	CFXObject* pObject = CFXBlock::GetByID(object_id);
	if (pObject)
		return pObject;
	POSITION pos;
	pos = m_Links.GetHeadPosition();
	while (pos){
		CFXLink* pLink = m_Links.GetNext(pos);
		if (pLink->m_ID == object_id)
			return pLink;
	}
	pos = m_Blocks.GetHeadPosition();
	while (pos){
		CFXBlock* pBlock = m_Blocks.GetNext(pos);
		CFXObject* pObj = pBlock->GetByID(ID);
		if (pObj){
			return pObj;
		}
	}
	return NULL;
}


void CFXBlockFunctional::Serialize(CArchive& ar)
{
	TracePrint(TRACE_LEVEL_3,"CFXBlockFunctional::Serialize");
	CFXBlock::Serialize(ar);
	if (ar.IsStoring()){
		ar << m_LastID;
		ar.WriteCount(m_Blocks.GetCount());
		POSITION pos = m_Blocks.GetHeadPosition();
		while (pos){
			CFXBlock* pBlock = m_Blocks.GetNext(pos);
			ar << pBlock;
		}
		ar.WriteCount(m_Links.GetCount());
		pos = m_Links.GetHeadPosition();
		while (pos){
			CFXLink* pLink = m_Links.GetNext(pos);
			ar << pLink;
		}

	}
	else{
		int count = 0;
		CString block;
		ar >> m_LastID;
		count = ar.ReadCount();
		for (int i=0; i<count; i++){
			CFXBlock* pBlock;
			ar >> pBlock;
			pBlock->m_pBlock = this;
			pBlock->AfterSerialize();
			m_Blocks.AddTail(pBlock);
		}
		count = ar.ReadCount();
		for (int i=0; i<count; i++){
			CFXLink* pLink;
			ar >> pLink;
			pLink->m_pBlock = this;
			pLink->AfterSerialize();
			m_Links.AddTail(pLink);
		}
	}
}


CFXLink* CFXBlockFunctional::AddLink(CFXPin* pPinOut, CFXPin* pPinIn)
{
	if (!pPinOut->m_bLinkable || !pPinIn->m_bLinkable){
		return NULL;
	}
	if (pPinIn->IsConnectedPin(pPinOut)){
		// Уже есть связь у этого пина
		return NULL;
	}

	CFXLink* pLink = new CFXLink(this,pPinOut,pPinIn);
	CString name;
	pPinIn->SetName(pPinOut->GetName());
	if (pPinIn->m_bConst){
		pPinIn->m_bConst = false;
	}
	if (pPinIn->m_pParam){
		pPinIn->m_pParam = NULL;
	}
	CFXBlockFunctionalPin* pFuncPin = dynamic_cast<CFXBlockFunctionalPin*>(pPinIn->m_pBlock);
	if (pFuncPin){
		pFuncPin->m_pLinkedPin->SetName(pPinOut->GetName());
	}
	name.Format(_T("Link.%d"),pLink->m_ID);

	pLink->SetName(name);
	CPoint p1 = pPinIn->GetXY();
	CPoint p2 = pPinOut->GetXY();
	CPoint p( (p1.x+p2.x)/2,(p1.y+p2.y)/2 );
	pLink->SetXY(p);
	m_Links.AddTail(pLink);
	return pLink;
}

void CFXBlockFunctional::RemoveLink(CFXLink* pLink){
	pLink->m_pIn->SetName(_T(""));
	m_Links.RemoveAt(m_Links.Find(pLink));
	pLink->m_pIn->RemoveConnectedPin(pLink->m_pOut);
	delete pLink;
}

CFXLink* CFXBlockFunctional::GetLink(CFXPin* pPin1, CFXPin* pPin2)
{
	POSITION pos = m_Blocks.GetHeadPosition();
	while (pos){
		CFXLink* pLink = m_Links.GetNext(pos);
		ASSERT(pLink);
		if ( (pLink->m_pIn == pPin1 && pLink->m_pOut == pPin2) || (pLink->m_pIn == pPin2 && pLink->m_pOut == pPin1)){
			return pLink;
		}
	}
	return NULL;
}

void CFXBlockFunctional::RemoveBlock(CFXBlock* pBlock)
{
	m_Blocks.RemoveAt(m_Blocks.Find(pBlock));
	delete pBlock;
}


void CFXBlockFunctional::GetPinLinks(CListLink& lst, CFXPin* pPin)
{
	POSITION pos = m_Links.GetHeadPosition();
	while (pos){
		CFXLink* pLink = m_Links.GetNext(pos);
		ASSERT(pLink);
		if (pLink->m_pIn == pPin || pLink->m_pOut == pPin){
			lst.AddTail(pLink);
		}
	}
}

void CFXBlockFunctional::CalcOrder(void){
	// Формируем список блоков
	CArray<CFXBlock*,CFXBlock*> lst;
	POSITION pos = m_Blocks.GetHeadPosition();
	while (pos){
		CFXBlock* pBlock = m_Blocks.GetNext(pos);
		CFXBlockFunctional* pBlockFunc = dynamic_cast<CFXBlockFunctional*>(pBlock);
		if (pBlock)
			lst.Add(pBlock);
		//if (pBlockFunc){
		//	pBlockFunc->CalcOrder();
		//}
	}
	// Сортируем список блоков
	int c = lst.GetCount();
	for (int i=0; i<c-1; i++){
		for (int j=i+1; j<c; j++){
			CFXBlock* pBlock1 = lst.GetAt(i);
			CFXBlock* pBlock2 = lst.GetAt(j);
			if (pBlock1->GetX() > pBlock2->GetX()){
				lst.SetAt(i,pBlock2);
				lst.SetAt(j,pBlock1);
			}
			else
				if (pBlock1->GetX() == pBlock2->GetX()){
					if (pBlock1->GetY() > pBlock2->GetY()){
						lst.SetAt(i,pBlock2);
						lst.SetAt(j,pBlock1);
					}
				}
		}
	}
	// Устанавливаем порядок выполнения
	// Устанавливаем указатели следующего блока в цепочке выполнения
	// Устанавливает текущий блок на первый в цепочке выполнения
	int nOrder = 1;
	CFXBlock* pCur=NULL;
	CFXBlock* pPrev = NULL;
	m_pDebugFirst = NULL;
	for (int i=0; i<c; i++){
		pCur = lst.GetAt(i);
		pCur->m_pNextBlock = NULL;
		pCur->m_CalcOrder = nOrder++;
		if (!m_pDebugFirst)
			m_pDebugFirst = pCur;
		if (pPrev){
			pPrev->m_pNextBlock = pCur;
		}
		pPrev = pCur;
	}
	if (pCur) {
		pCur->m_pNextBlock = m_pNextBlock;
		pCur = m_pDebugFirst;
	}
	while (pCur){
		CFXBlockFunctional* pBlockFunc = dynamic_cast<CFXBlockFunctional*>(pCur);
		if (pBlockFunc)
			pBlockFunc->CalcOrder();
		pCur = pCur->m_pNextBlock;
	}
}


bool CFXBlockFunctional::Calc(void)
{
	if (!CFXBlock::Calc())
		return false;
	return true;
}


void CFXBlockFunctional::RemovePinLinks(CFXPin* pPin)
{
	TracePrint(TRACE_LEVEL_1,"CFXBlockFunctional::RemovePinLinks");
	POSITION pos = m_Links.GetHeadPosition();
	while (pos){
		CFXLink* pLink = m_Links.GetNext(pos);
		ASSERT(pLink);
		if (pLink->m_pIn == pPin || pLink->m_pOut == pPin){
			RemoveLink(pLink);
		}
	}
}


void CFXBlockFunctional::Initialize(void)
{
	CFXBlock::Initialize();
	POSITION pos;
	pos = m_Blocks.GetHeadPosition();
	while (pos){
		CFXBlock* pBlock = m_Blocks.GetNext(pos);
		pBlock->Initialize();
	}
}


void CFXBlockFunctional::UpdateView()
{
	CFXGraphDoc* pDoc = GetActiveDocument();
	CFXGraphView* pView = pDoc->GetBlockView(this);
	if (pView) {
		POSITION pos = m_Blocks.GetHeadPosition();
		while (pos) {
			CFXBlock* pBlock = m_Blocks.GetNext(pos);
			CFXBlockFunctional* pBlockFunc = dynamic_cast<CFXBlockFunctional*>(pBlock);
			if (pBlockFunc) {
				pBlockFunc->UpdateView();
			}
			else {
				pBlock->Invalidate(pView, REGION_LEFT | REGION_RIGHT);
			}
		}
	}
}
