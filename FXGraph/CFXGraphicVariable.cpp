﻿#include "stdafx.h"
#include "CFXGraphicVariable.h"
#include "FXPin.h"
IMPLEMENT_SERIAL(CFXGraphicVariable, CObject, 1);

COLORREF colors[] = { RGB(0x00,0xff,0xff), // aqua
					RGB(0x00,0x00,0xff), // blue
					RGB(0x7f,0xff,0xd4), // aquamarine
					RGB(0x8a,0x2b,0xe2), // blueviolet
					RGB(0xa5,0x2a,0x2a), // brown
					RGB(0xde,0xb8,0x87), // burlywood
					RGB(0x5f,0x9e,0xa0), // cadetblue
					RGB(0x7f,0xff,0x00), // chartreuse
					RGB(0xd2,0x69,0x1e), // chocolate
					RGB(0xff,0x7f,0x50), // coral
					RGB(0x64,0x95,0xed), // cornflowerblue
					RGB(0xdc,0x14,0x3c), // crimson
					RGB(0x00,0xff,0xff), // cyan
					RGB(0x00,0x00,0x8b), // darkblue
					RGB(0x00,0x8b,0x8b), // darkcyan
					RGB(0xb8,0x86,0x0b), // darkgoldenrod	
					RGB(0x00,0x64,0x00), // darkgreen
					RGB(0xbd,0xb7,0x6b), // darkkhaki
					RGB(0x8b,0x00,0x8b), // darkmagenta
					RGB(0x55,0x6b,0x2f), // darkolivegreen
					RGB(0xff,0x8c,0x00), // darkorange
					RGB(0x99,0x32,0xcc), // darkochid
					RGB(0x8b,0x00,0x00), // darkred	
					RGB(0xe9,0x96,0x7a), // darksalmon
					RGB(0x8f,0xbc,0x8f), // darkseagreen
					RGB(0x48,0x3d,0x8b), // darkslateblue
					RGB(0x2f,0x4f,0x4f), // darkslategray 
					RGB(0x00,0xce,0xd1), // darkturquoise
					RGB(0x94,0x00,0xd3), // darkviolet
					RGB(0xff,0x14,0x93), // deeppink
					RGB(0x00,0xBF,0xFF), // deepskyblue
					RGB(0x69,0x69,0x69), //  dimgray
					RGB(0x1E,0x90,0xFF), //  dodgerblue
					RGB(0xFF,0xFA,0xF0), //  floralwhite
					RGB(0x22,0x8B,0x22), //  forestgreen
					RGB(0xFF,0x00,0xFF), //  fushsia
					RGB(0xDC,0xDC,0xDC), //  gainsboro
					RGB(0xFF,0xD7,0x00), //  gold
					RGB(0xDA,0xA5,0x20), //  goldenrod
					RGB(0x80,0x80,0x80), //  gray
					RGB(0x00,0x80,0x00), //  green
					RGB(0xAD,0xFF,0x2F), //  greenyellow
					RGB(0xFF,0x69,0xB4), //  hotpink
					RGB(0xCD,0x5C,0x5C), //  indiandred
					RGB(0x4B,0x00,0x82), //  indigo
					RGB(0xF0,0xE6,0x8C), //  khaki
					RGB(0xE6,0xE6,0xFA), //  lavender
					RGB(0xFF,0xF0,0xF5), //  lavenderblush
					RGB(0x7C,0xFC,0x00), //  lawngreen
					RGB(0xFF,0xFA,0xCD), //  lemonchiffon
					RGB(0xAD,0xD8,0xE6), //  ligtblue
					RGB(0xF0,0x80,0x80), //  lightcoral
					RGB(0xE0,0xFF,0xFF), //  lightcyan
					RGB(0xFA,0xFA,0xD2), //  lightgoldenrodyellow
					RGB(0x90,0xEE,0x90), //  lightgreen
					RGB(0xD3,0xD3,0xD3), //  lightgrey
					RGB(0xFF,0xB6,0xC1), //  lightpink
					RGB(0xFF,0xA0,0x7A), //  lightsalmon
					RGB(0x20,0xB2,0xAA), //  lightseagreen
					RGB(0x87,0xCE,0xFA), //  lightscyblue
					RGB(0x77,0x88,0x99), //  lightslategray
					RGB(0xB0,0xC4,0xDE), //  lightsteelblue
					RGB(0x00,0xFF,0x00), //  lime
					RGB(0x32,0xCD,0x32), //  limegreen
					RGB(0xFA,0xF0,0xE6), //  linen
					RGB(0xFF,0x00,0xFF), //  magenta
					RGB(0x80,0x00,0x00), //  maroon
					RGB(0x66,0xCD,0xAA), //  mediumaquamarine
					RGB(0x00,0x00,0xCD), //  mediumblue
					RGB(0xBA,0x55,0xD3), //  mediumorchid
					RGB(0x93,0x70,0xDB), //  mediumpurple
					RGB(0x3C,0xB3,0x71), //  mediumseagreen
					RGB(0x7B,0x68,0xEE), //  mediumslateblue
					RGB(0x00,0xFA,0x9A), //  mediumspringgreen
					RGB(0x48,0xD1,0xCC), //  mediumturquoise
					RGB(0xC7,0x15,0x85), //  medium violetred
					RGB(0x19,0x19,0x70), //  midnightblue
					RGB(0xFF,0xE4,0xE1), //  mistyrose
					RGB(0xFF,0xE4,0xB5), //  moccasin
					RGB(0xFF,0xDE,0xAD), //  navajowhite
					RGB(0x00,0x00,0x80), //  navy
					RGB(0xFD,0xF5,0xE6), //  oldlace
					RGB(0x80,0x80,0x00), //  olive
					RGB(0x6B,0x8E,0x23), //  olivedrab
					RGB(0xFF,0xA5,0x00), //  orange
					RGB(0xFF,0x45,0x00), //  orengered
					RGB(0xDA,0x70,0xD6), //  orchid
					RGB(0xEE,0xE8,0xAA), //  palegoldenrod
					RGB(0x98,0xFB,0x98), //  palegreen
					RGB(0xAF,0xEE,0xEE), //  paleturquose
					RGB(0xDB,0x70,0x93), //  palevioletred
					RGB(0xFF,0xEF,0xD5), //  papayawhop
					RGB(0xFF,0xDA,0xB9), //  peachpuff
					RGB(0xCD,0x85,0x3F), //  peru
					RGB(0xFF,0xC0,0xCB), //  pink
					RGB(0xDD,0xA0,0xDD), //  plum
					RGB(0xB0,0xE0,0xE6), //  powderblue
					RGB(0x80,0x00,0x80), //  purple
					RGB(0xBC,0x8F,0x8F), //  rosybrown
					RGB(0x41,0x69,0xE1), //  royalblue
					RGB(0x8B,0x45,0x13), //  saddlebrown
					RGB(0xFA,0x80,0x72), //  salmon
					RGB(0xF4,0xA4,0x60), //  sandybrown
					RGB(0x2E,0x8B,0x57), //  seagreen
					RGB(0xFF,0xF5,0xEE), //  seashell
					RGB(0xA0,0x52,0x2D), //  sienna
					RGB(0xC0,0xC0,0xC0), //  silver
					RGB(0x87,0xCE,0xEB), //  skyblue
					RGB(0x6A,0x5A,0xCD), //  slateblue
					RGB(0x70,0x80,0x80), //  slategray
					RGB(0x00,0xFF,0x7F), //  springgreen
					RGB(0x46,0x82,0xB4), //  steelblue
					RGB(0xD2,0xB4,0x8C), //  tan
					RGB(0x00,0x80,0x80), //  teal
					RGB(0xD8,0xBF,0xD8), //  thistle
					RGB(0xFF,0x63,0x47), //  tomato
					RGB(0x40,0xE0,0xD0), //  turquose
					RGB(0xEE,0x82,0xEE), //  violet
					RGB(0xF5,0xDE,0xB3), //  wheat
					RGB(0xFF,0xFF,0xFF), //  white
					RGB(0xF5,0xF5,0xF5), //  whitesmoke
					RGB(0xFF,0xFF,0x00), //  yellow
					RGB(0x9A, 0xCD, 0x32) }; //  yellowgreen


CFXGraphicVariable::CFXGraphicVariable()
{
	m_ID = 0;
	m_Color = RGB(0, 0, 0);
	m_Type = Logical;
	m_Name = _T("");
}

CFXGraphicVariable::CFXGraphicVariable(int id, CString name, CFXPinType type)
{
	if (name.IsEmpty())
		name.Format(_T("pin #%d"), id);
	m_ID = id;
	m_Name = name;
	m_Type = type;
	m_Color = colors[rand() % NCOLORS];
}

void CFXGraphicVariable::Serialize(CArchive& ar)
{
	if (ar.IsStoring()) {
		ar << m_ID;
		ar << m_Color;
		ar << m_Type;
		ar << m_Name;
	}
	else {
		ar >> m_ID;
		ar >> m_Color;
		ar >> m_Type;
		ar >> m_Name;
	}
}
