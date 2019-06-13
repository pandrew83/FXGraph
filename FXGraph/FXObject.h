#pragma once

#define COLOR_SELECTED	RGB(255,0,0)
#define COLOR_NORMAL	RGB(0,0,0)
#define COLOR_DEBUG		RGB(0,0,255)

#include <typeinfo>
#include "FXException.h"
//#include "FXGraphDoc.h"
//#include "FXBlockFunctional.h"

enum CFXPinType {Logical,Int,Float};
enum CFXPinDir {Input,Output};


// Mem1 MASK
#define MASK1_ID				0x0fffff
//#define MASK1_PIN				0x07f000
#define MASK1_SELECTED			0x800000

#define MASK2_BORDER_TOP		0x000001
#define MASK2_BORDER_BOTTOM		0x000002
#define MASK2_BORDER_LEFT		0x000004
#define MASK2_BORDER_RIGHT		0x000008
#define MASK2_BORDERS			(MASK2_BORDER_TOP|MASK2_BORDER_BOTTOM|MASK2_BORDER_LEFT|MASK2_BORDER_RIGHT)
#define MASK2_CORNERS			(MASK2_CORNER_TL|MASK2_CORNER_TR|MASK2_CORNER_BL|MASK2_CORNER_BR)
#define MASK2_CORNER_TL			0x000010
#define MASK2_CORNER_TR			0x000020
#define MASK2_CORNER_BL			0x000040
#define MASK2_CORNER_BR			0x000080

#define PEN_WIDTH				5
#define CORNER_SIZE			7

#define PROP_COORDX				1
#define PROP_COORDY				2
#define PROP_WIDTH				3
#define PROP_HEIGHT				4
#define PROP_COMMENT			5
#define PROP_NAME				6
#define PROP_CONST				7
#define PROP_VALUE				8
#define PROP_FUNCNAME			9
#define PROP_FONT				10
#define PROP_PARAM				11
#define PROP_FORMAT				12
#define PROP_NETWORK_ID			13

#define PROPLIST_BLOCK			1
#define PROPLIST_PIN			2
#define PROPLIST_LINK			3
#define PROPLIST_COMMENT		4

#define BLOCK_FUNCTIONAL					1
#define BLOCK_FUNCTIONAL_PIN				2
#define BLOCK_COMMENT						3

#define BLOCK_COMPARATOR_UP					20
#define BLOCK_COMPARATOR_DOWN				21

#define BLOCK_LOGICAL_AND					50
#define BLOCK_LOGICAL_OR					51
#define BLOCK_LOGICAL_NOT					52
#define BLOCK_LOGICAL_XOR					53
#define BLOCK_LOGICAL_RISING_EDGE			54
#define BLOCK_LOGICAL_FALLING_EDGE			55
#define BLOCK_LOGICAL_TRIGGER_RS			56
#define BLOCK_LOGICAL_TRIGGER_SR			57
#define BLOCK_LOGICAL_TRIGGER_RS_RE			58
#define BLOCK_LOGICAL_FRONTS				59

#define BLOCK_COUNTER						80

#define BLOCK_MATH_INT_ADD					100
#define BLOCK_MATH_INT_SUB					101
#define BLOCK_MATH_INT_MUL					102
#define BLOCK_MATH_INT_DIV					103
#define BLOCK_MATH_INT_MOD					104
#define BLOCK_MATH_INT_ABS					105
#define BLOCK_MATH_INT_EQUAL				106
#define BLOCK_MATH_INT_GREAT				107
#define BLOCK_MATH_INT_GREATEQUAL			108
#define BLOCK_MATH_INT_LESS					109
#define BLOCK_MATH_INT_LESSEQUAL			110
#define BLOCK_MATH_INT_NOTEQUAL				111

#define BLOCK_MATH_FLOAT_ADD				150
#define BLOCK_MATH_FLOAT_SUB				151
#define BLOCK_MATH_FLOAT_MUL				152
#define BLOCK_MATH_FLOAT_DIV				153
#define BLOCK_MATH_FLOAT_GREAT				154
#define BLOCK_MATH_FLOAT_GREATEQUAL			155
#define BLOCK_MATH_FLOAT_LESS				156
#define BLOCK_MATH_FLOAT_LESSEQUAL			157
#define BLOCK_MATH_FLOAT_EQUAL				158
#define BLOCK_MATH_FLOAT_NOTEQUAL			159
#define BLOCK_MATH_FLOAT_ABS				160
#define BLOCK_MATH_FLOAT_FLOOR				161
#define BLOCK_MATH_FLOAT_ROUND				162

#define BLOCK_MATH_COS						170
#define BLOCK_MATH_SIN						171
#define BLOCK_MATH_TAN						172
#define BLOCK_MATH_SQRT						173
#define BLOCK_MATH_POW						174
#define BLOCK_MATH_LOG						175
#define BLOCK_MATH_LOG10					176
#define BLOCK_MATH_ACOS						177
#define BLOCK_MATH_ASIN						178
#define BLOCK_MATH_ATAN						179
#define BLOCK_MATH_EXP						180 

#define BLOCK_MATH_CAST_FLOAT_INT			200
#define BLOCK_MATH_CAST_INT_FLOAT			201

#define BLOCK_MATH_BITWISE_AND				250
#define BLOCK_MATH_BITWISE_OR				251
#define BLOCK_MATH_BITWISE_XOR				252
#define BLOCK_MATH_BITWISE_NOT				253
#define BLOCK_MATH_BITWISE_SHIFT_LEFT		254
#define BLOCK_MATH_BITWISE_SHIFT_RIGHT		255
#define BLOCK_MATH_BITWISE_PACK				256
#define BLOCK_MATH_BITWISE_UNPACK			257

#define BLOCK_ANTIBOUNCE					270
#define BLOCK_DELAY_ON						271
#define BLOCK_DELAY_OFF						272

#define BLOCK_CONTROLLER_NIMOD01			300
#define BLOCK_EXTENSION_NIMODA01			301

#define BLOCK_SENSOR_TRD_2W_PT100			400
#define BLOCK_SENSOR_TRD_2W_PT500			401
#define BLOCK_SENSOR_TRD_2W_PT1000			402
#define BLOCK_SENSOR_TRD_2W_M50				403
#define BLOCK_SENSOR_TRD_2W_M100			404
#define BLOCK_SENSOR_TRD_2W_P50				405
#define BLOCK_SENSOR_TRD_2W_P100			406
#define BLOCK_SENSOR_TRD_3W_PT100			407
#define BLOCK_SENSOR_TRD_3W_PT500			408
#define BLOCK_SENSOR_TRD_3W_PT1000			409
#define BLOCK_SENSOR_TRD_3W_M50				410
#define BLOCK_SENSOR_TRD_3W_M100			411
#define BLOCK_SENSOR_TRD_3W_P50				412
#define BLOCK_SENSOR_TRD_3W_P100			413
#define BLOCK_SENSOR_TRD_4W_PT100			414
#define BLOCK_SENSOR_TRD_4W_PT500			415
#define BLOCK_SENSOR_TRD_4W_PT1000			416
#define BLOCK_SENSOR_TRD_4W_M50				417
#define BLOCK_SENSOR_TRD_4W_M100			418
#define BLOCK_SENSOR_TRD_4W_P50				419
#define BLOCK_SENSOR_TRD_4W_P100			420

#define BLOCK_TRANSFORM_CURRENT				450
#define BLOCK_TRANSFORM_LINEAR				451
#define BLOCK_TRANSFORM_LINEAR_LIMITS		452

#define FXLINK								1001
#define FXPIN								2001
											
//#include "FXGraphView.h"		

class CFXGraphView;
class CPropertiesWnd;
class CFXBlock;
class CFXParam;
class CFXGraphDoc;

void Log(CFXMsgType type,CString str);
void WriteStr(CArchive&ar, LPCSTR fmt,...);

#define REGION_COORD			1
#define REGION_NAME				2
#define REGION_FUNCNAME			4
#define REGION_BLOCK			8
#define REGION_LEFT				16
#define REGION_RIGHT			32
#define REGION_VALUE			64
#define REGION_PIN				128
#define REGION_LINK				256

class CFXObject : public CObject
{
public:
	CFXObject(void);
	DECLARE_SERIAL(CFXObject);
	virtual void AfterSerialize(){}
	static CString GetClassDescriptor(int id){
		CString desc;
		switch(id){
		case BLOCK_FUNCTIONAL:
			desc = "CFXBlockFunctional";
			break;
		default:
			desc = "CFXObject";
		}
		return desc;
	}
protected:
	int m_X;
	int m_Y;
	CString m_Name;
public:
	virtual void SetName(CString name){
		m_Name = name;
	}
	CString GetName(){
		return m_Name;
	}
	virtual int GetNewID(){return 0;}
	virtual CFXObject* GetByID(int id){
		return NULL;
	}
	CFXObject(CFXObject* pObject,CString name){
		m_pBlock = pObject;
		if (m_pBlock)
			m_ID = m_pBlock->GetNewID();
		else
			m_ID = 0;
		m_Name = name;
		m_SaveX = 0;
		m_SaveY = 0;
		m_Style = 0;
		m_X = 0;
		m_Y = 0;
	}
	CFXObject(CFXBlock* pBlock,CString name){
		m_pBlock = (CFXObject*)pBlock;
		m_Name = name;
		if (m_pBlock)
			m_ID = m_pBlock->GetNewID();
		else
			m_ID = 1;
		m_SaveX = 0;
		m_SaveY = 0;
		m_Style = 0;
		m_X = 0;
		m_Y = 0;
	}
	~CFXObject(void);
	virtual int GetClassID(){
		return 0;
	}
	virtual const char* GetClassName(){
		const char *s = typeid(*this).name();
		const char *p = s+6;
		return p;
	}
	virtual void Serialize(CArchive& ar);
	virtual void SetX(int x){
		m_X = x;
	}
	virtual void SetY(int y){
		m_Y = y;
	}
	virtual void SetXY(int x, int y){
		m_X = x;
		m_Y = y;
	}
	virtual void SetXY(CPoint p){
		SetXY(p.x,p.y);
	}
	int GetX() const{
		return m_X;
	}
	int GetY() const{
		return m_Y;
	}
	CPoint GetXY() const{
		return CPoint(m_X,m_Y);
	}
	CFXObject* m_pBlock;
	int m_ID;
	int m_Style;
	int m_SaveX;
	int m_SaveY;
	virtual void Draw(CFXGraphView*pView){
	}
	void StartMoving(void);
	virtual void Move(int dx, int dy);
	virtual void FillProperties(CPropertiesWnd* pWnd);
	virtual int GetPropertyList(){
		return 0;
	}
	virtual bool Check(){
		return false;
	}
	CFXGraphDoc* GetActiveDocument(void);
	virtual void Invalidate(CFXGraphView* pView, int regions);
};

