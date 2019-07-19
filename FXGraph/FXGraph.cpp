
// FXGraph.cpp : Определяет поведение классов для приложения.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "FXGraph.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "FXGraphDoc.h"
#include "FXGraphView.h"
#include "FXObject.h"
#include "GridDlg.h"
#include <locale.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define TRACE_LEVEL TRACE_LEVEL_1

void FXGRaphTerminate(){

}

void TracePrint(int level, const char* format,...){
	if (level & TRACE_LEVEL){
		va_list args;
		va_start(args,format);
		char str[1024];
		char eol[10];
		eol[0]='\n';
		eol[1]=0;
		vsprintf(str,format,args);
		va_end(args);
		strcat(str,eol);
		TRACE(str);
	}		
}
// CFXGraphApp

BEGIN_MESSAGE_MAP(CFXGraphApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CFXGraphApp::OnAppAbout)
	// Стандартные команды по работе с файлами документов
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// Стандартная команда настройки печати
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_GRID, &CFXGraphApp::OnGrid)
//	ON_COMMAND(ID_CLASSVIEWMENU_WEBHELP, &CFXGraphApp::OnClassviewmenuWebhelp)
END_MESSAGE_MAP()


// создание CFXGraphApp

CFXGraphApp::CFXGraphApp()
	: m_GridStep(0)
	, m_GridState(false)
	, m_GridStyle(0)
{
	m_bHiColorIcons = TRUE;

	// поддержка диспетчера перезагрузки
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// Если приложение построено с поддержкой среды Common Language Runtime (/clr):
	//     1) Этот дополнительный параметр требуется для правильной поддержки работы диспетчера перезагрузки.
	//     2) В своем проекте для построения необходимо добавить ссылку на System.Windows.Forms.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: замените ниже строку идентификатора приложения строкой уникального идентификатора; рекомендуемый
	// формат для строки: ИмяКомпании.ИмяПродукта.СубПродукт.СведенияОВерсии
	SetAppID(_T("FXGraph.AppID"));

}

// Единственный объект CFXGraphApp

CFXGraphApp theApp;


// инициализация CFXGraphApp

BOOL CFXGraphApp::InitInstance()
{
	// InitCommonControlsEx() требуются для Windows XP, если манифест
	// приложения использует ComCtl32.dll версии 6 или более поздней версии для включения
	// стилей отображения. В противном случае будет возникать сбой при создании любого окна.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Выберите этот параметр для включения всех общих классов управления, которые необходимо использовать
	// в вашем приложении.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();
	setlocale(LC_ALL, "rus"); // Для того, чтобы функции для работы со строками понимали русские буквы

	// Инициализация библиотек OLE
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// Для использования элемента управления RichEdit требуется метод AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// Стандартная инициализация
	// Если эти возможности не используются и необходимо уменьшить размер
	// конечного исполняемого файла, необходимо удалить из следующего
	// конкретные процедуры инициализации, которые не требуются
	// Измените раздел реестра, в котором хранятся параметры
	// TODO: следует изменить эту строку на что-нибудь подходящее,
	// например на название организации
	SetRegistryKey(_T("FXGraph"));
	m_GridState = (bool)GetProfileInt(_T("Settings"),_T("GridState"),0);
	m_GridStep = GetProfileInt(_T("Settings"),_T("GridStep"),5);
	m_GridStyle = GetProfileInt(_T("Settings"),_T("GridStyle"),0);
	m_GridBind = (bool)GetProfileInt(_T("Settings"),_T("GridBind"),0);
	int r = GetProfileInt(_T("Settings"),_T("GridColorR"),0);
	int g = GetProfileInt(_T("Settings"),_T("GridColorG"),0);
	int b = GetProfileInt(_T("Settings"),_T("GridColorB"),0);
	m_GridColor = RGB(r,g,b);
	LoadStdProfileSettings(4);  // Загрузите стандартные параметры INI-файла (включая MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Зарегистрируйте шаблоны документов приложения. Шаблоны документов
	//  выступают в роли посредника между документами, окнами рамок и представлениями
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_FXGraphTYPE,
		RUNTIME_CLASS(CFXGraphDoc),
		RUNTIME_CLASS(CChildFrame), // настраиваемая дочерняя рамка MDI
		RUNTIME_CLASS(CFXGraphView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	//pDocTemplate = new CMultiDocTemplate(IDR_FXGraphTYPE,
	//	RUNTIME_CLASS(CFXGraphDoc),
	//	RUNTIME_CLASS(CChildFrame),
	//	RUNTIME_CLASS(CFXGraphViewScenario));
	//AddDocTemplate(pDocTemplate);
	// создайте главное окно рамки MDI

	FillObjectDescriptors();
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// вызов DragAcceptFiles только при наличии суффикса
	//  В приложении MDI это должно произойти сразу после задания m_pMainWnd
	// Включить открытие перетаскивания
	m_pMainWnd->DragAcceptFiles();

	// Синтаксический разбор командной строки на стандартные команды оболочки, DDE, открытие файлов
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Включить открытие выполнения DDE
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// Команды диспетчеризации, указанные в командной строке. Значение FALSE будет возвращено, если
	// приложение было запущено с параметром /RegServer, /Register, /Unregserver или /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// Главное окно было инициализировано, поэтому отобразите и обновите его
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

		return TRUE;
}

int CFXGraphApp::ExitInstance()
{
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// обработчики сообщений CFXGraphApp


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// Команда приложения для запуска диалога
void CFXGraphApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CFXGraphApp настройка методов загрузки и сохранения

void CFXGraphApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
	bNameValid = strName.LoadString(IDS_MENU_BLOCK);
	GetContextMenuManager()->AddMenu(strName, IDR_BLOCK);
	bNameValid = strName.LoadStringW(IDS_MENU_PIN);
	GetContextMenuManager()->AddMenu(strName, IDR_PIN);
	bNameValid = strName.LoadStringW(IDS_MENU_LINK);
	GetContextMenuManager()->AddMenu(strName, IDR_LINK);

	
}

void CFXGraphApp::LoadCustomState()
{
}

void CFXGraphApp::SaveCustomState()
{
}

// обработчики сообщений CFXGraphApp


void CFXGraphApp::OnGrid()
{
	CGridDlg dlg;
	dlg.m_Step = m_GridStep;
	dlg.m_Grid_On = m_GridState;
	dlg.m_GridStyle = m_GridStyle;
	dlg.m_GridBind = m_GridBind;
	dlg.m_GridColor.SetColor(m_GridColor);
	if (dlg.DoModal() == IDOK){
		m_GridStep = dlg.m_Step;
		m_GridState = dlg.m_Grid_On;
		m_GridStyle = dlg.m_GridStyle;
		m_GridBind = dlg.m_GridBind;
		m_GridColor = dlg.m_GridColor.GetColor();
		WriteProfileInt(_T("Settings"),_T("GridState"),m_GridState);
		WriteProfileInt(_T("Settings"),_T("GridStyle"),m_GridStyle);
		WriteProfileInt(_T("Settings"),_T("GridStep"),m_GridStep);
		WriteProfileInt(_T("Settings"),_T("GridBind"),m_GridBind);
		WriteProfileInt(_T("Settings"),_T("GridColorR"),GetRValue(m_GridColor));
		WriteProfileInt(_T("Settings"),_T("GridColorG"),GetGValue(m_GridColor));
		WriteProfileInt(_T("Settings"),_T("GridColorB"),GetBValue(m_GridColor));
		CMainFrame* pMainFrame = (CMainFrame*)m_pMainWnd;
		CView* pView = pMainFrame->GetActiveFrame()->GetActiveView();
		if (pView != NULL)
			pView->Invalidate(0);
	}
}



int CFXGraphApp::Run()
{
	TracePrint(TRACE_LEVEL_1,"CFXGraphApp:Run");
	try{
		return CWinAppEx::Run();
	}
	catch(CFXException &ex){
		TracePrint(TRACE_LEVEL_1,"CFXGraphApp:Run: Exception");
	}
	catch(CException &ex){
		TracePrint(TRACE_LEVEL_1,"CFXGraphApp:Run: Exception");
	}
	catch(CException* pEx){
		TracePrint(TRACE_LEVEL_1,"CFXGraphApp:Run: Exception");
	}
	catch(...){
		TracePrint(TRACE_LEVEL_1,"Unknown exception");
	}
	return CWinApp::Run();
}

void CFXGraphApp::FillObjectDescriptors()
{
	auto ods = &CFXObject::m_ObjectDescriptors;
	//CFXObjectDescriptor(int Id = 0, CString ClassName = L"", CString Name = L"", int ParentId = 0, bool IsGroup = false, int Version = 0)
	// Разное
	ods->Add({ GROUP_MISC, _T(""), _T("Разное"), 0, true });
	ods->Add({ BLOCK_COMMENT,  _T("CFXBlockComment"), _T("Комментарий"), GROUP_MISC });

	// Функциональные блоки
	ods->Add({ GROUP_FUNCBLOCKS, _T(""), _T("Функциональные блоки"), 0, true });
	ods->Add({ BLOCK_FUNCTIONAL,  _T("CFXBlockFunctional"), _T("Функциональный блок"), GROUP_FUNCBLOCKS });

	// Уставка
	ods->Add({ GROUP_SETUP,_T(""),_T("Уставка"),0,true });
	ods->Add({ BLOCK_SETUP_FLOAT,_T("CFXBlockSetupFloat"),_T("Уставка вещественного"),GROUP_SETUP });
	ods->Add({ BLOCK_SETUP_INT,_T("CFXBlockSetupInt"),_T("Уставка целого"),GROUP_SETUP });
	ods->Add({ BLOCK_SETUP_LOGICAL,_T("CFXBlockSetupLogical"),_T("Уставка логического"),GROUP_SETUP });
	// Математика
	ods->Add({ GROUP_MATH, _T(""), _T("Математика"), 0, true });
	// Математика-целочисленная
	ods->Add({ GROUP_MATH_INT, _T(""), _T("Целочисленная"), GROUP_MATH, true });
	ods->Add({ BLOCK_MATH_INT_ADD,  _T("CFXBlockMathIntAdd"), _T("Сложение"), GROUP_MATH_INT });
	ods->Add({ BLOCK_MATH_INT_SUB,  _T("CFXBlockMathIntSub"), _T("Вычитание"), GROUP_MATH_INT });
	ods->Add({ BLOCK_MATH_INT_MUL,  _T("CFXBlockMathIntMul"), _T("Умножение"), GROUP_MATH_INT });
	ods->Add({ BLOCK_MATH_INT_DIV,  _T("CFXBlockMathIntDiv"), _T("Деление"), GROUP_MATH_INT });
	ods->Add({ BLOCK_MATH_INT_MOD,  _T("CFXBlockMathIntMod"), _T("Остаток от деления"), GROUP_MATH_INT });
	ods->Add({ BLOCK_MATH_INT_EQUAL,  _T("CFXBlockMathIntEqual"), _T("Равно"), GROUP_MATH_INT });
	ods->Add({ BLOCK_MATH_INT_GREAT,  _T("CFXBlockMathIntGreat"), _T("Больше"), GROUP_MATH_INT });
	ods->Add({ BLOCK_MATH_INT_GREATEQUAL,  _T("CFXBlockMathIntGreatEqual"), _T("Больше равно"), GROUP_MATH_INT });
	ods->Add({ BLOCK_MATH_INT_LESS,  _T("CFXBlockMathIntLess"), _T("Меньше"), GROUP_MATH_INT });
	ods->Add({ BLOCK_MATH_INT_LESSEQUAL,  _T("CFXBlockMathIntLessEqual"), _T("Меньше равно"), GROUP_MATH_INT });
	ods->Add({ BLOCK_MATH_INT_NOTEQUAL,  _T("CFXBlockMathIntNotEqual"), _T("Не равно"), GROUP_MATH_INT });
	ods->Add({ BLOCK_MATH_INT_ABS,  _T("CFXBlockMathIntAbs"), _T("Модуль числа"), GROUP_MATH_INT });

	// Математика-вещественная
	ods->Add({ GROUP_MATH_FLOAT, _T(""), _T("Вещественная"), GROUP_MATH, true });
	ods->Add({ BLOCK_MATH_FLOAT_ADD,  _T("CFXBlockMathFloatAdd"), _T("Сложение"), GROUP_MATH_FLOAT });
	ods->Add({ BLOCK_MATH_FLOAT_SUB,  _T("CFXBlockMathFloatSub"), _T("Вычитание"), GROUP_MATH_FLOAT });
	ods->Add({ BLOCK_MATH_FLOAT_MUL,  _T("CFXBlockMathFloatMul"), _T("Умножение"), GROUP_MATH_FLOAT });
	ods->Add({ BLOCK_MATH_FLOAT_DIV,  _T("CFXBlockMathFloatDiv"), _T("Деление"), GROUP_MATH_FLOAT });
	ods->Add({ BLOCK_MATH_FLOAT_GREAT,  _T("CFXBlockMathFloatGreat"), _T("Больше"), GROUP_MATH_FLOAT });
	ods->Add({ BLOCK_MATH_FLOAT_GREATEQUAL,  _T("CFXBlockMathFloatGreatEqual"), _T("Больше равно"), GROUP_MATH_FLOAT });
	ods->Add({ BLOCK_MATH_FLOAT_LESS,  _T("CFXBlockMathFloatLess"), _T("Меньше"), GROUP_MATH_FLOAT });
	ods->Add({ BLOCK_MATH_FLOAT_LESSEQUAL,  _T("CFXBlockMathFloatLessEqual"), _T("Меньше равно"), GROUP_MATH_FLOAT });
	ods->Add({ BLOCK_MATH_FLOAT_EQUAL,  _T("CFXBlockMathFloatEqual"), _T("Равно"), GROUP_MATH_FLOAT });
	ods->Add({ BLOCK_MATH_FLOAT_NOTEQUAL,  _T("CFXBlockMathFloatNotEqual"), _T("Не равно"), GROUP_MATH_FLOAT });
	ods->Add({ BLOCK_MATH_FLOAT_ABS,  _T("CFXBlockMathFloatAbs"), _T("Модуль числа"), GROUP_MATH_FLOAT });
	ods->Add({ BLOCK_MATH_FLOAT_FLOOR,  _T("CFXBlockMathFloatFloor"), _T("Floor"), GROUP_MATH_FLOAT });
	ods->Add({ BLOCK_MATH_FLOAT_ROUND,  _T("CFXBlockMathFloatRound"), _T("Round"), GROUP_MATH_FLOAT });
	ods->Add({ BLOCK_MATH_FLOAT_MIN,  _T("CFXBlockMathFloatMin"), _T("Min"), GROUP_MATH_FLOAT });
	ods->Add({ BLOCK_MATH_FLOAT_MAX,  _T("CFXBlockMathFloatMax"), _T("Max"), GROUP_MATH_FLOAT });
	ods->Add({ BLOCK_MATH_FLOAT_LIMITS,_T("CFXBlockMathFloatLimits"),_T("Ограничения"),GROUP_MATH_FLOAT });
	ods->Add({ BLOCK_MATH_COS,  _T("CFXBlockMathCos"), _T("Cos"), GROUP_MATH_FLOAT });
	ods->Add({ BLOCK_MATH_SIN,  _T("CFXBlockMathSin"), _T("Sin"), GROUP_MATH_FLOAT });
	ods->Add({ BLOCK_MATH_TAN,  _T("CFXBlockMathTan"), _T("Tan"), GROUP_MATH_FLOAT });
	ods->Add({ BLOCK_MATH_SQRT,  _T("CFXBlockMathSqrt"), _T("Sqrt"), GROUP_MATH_FLOAT });
	ods->Add({ BLOCK_MATH_POW,  _T("CFXBlockMathPow"), _T("Pow"), GROUP_MATH_FLOAT });
	ods->Add({ BLOCK_MATH_LOG,  _T("CFXBlockMathLog"), _T("Log"), GROUP_MATH_FLOAT });
	ods->Add({ BLOCK_MATH_LOG10,  _T("CFXBlockMathLog10"), _T("Log10"), GROUP_MATH_FLOAT });
	ods->Add({ BLOCK_MATH_ACOS,  _T("CFXBlockMathAcos"), _T("Acos"), GROUP_MATH_FLOAT });
	ods->Add({ BLOCK_MATH_ASIN,  _T("CFXBlockMathAsin"), _T("Asin"), GROUP_MATH_FLOAT });
	ods->Add({ BLOCK_MATH_ATAN,  _T("CFXBlockMathAtan"), _T("Atan"), GROUP_MATH_FLOAT });
	ods->Add({ BLOCK_MATH_EXP,  _T("CFXBlockMathExp"), _T("Exp"), GROUP_MATH_FLOAT });
	// Математика-битовая
	ods->Add({ GROUP_MATH_BITWISE, _T(""), _T("Битовая"), GROUP_MATH, true });
	ods->Add({ BLOCK_MATH_BITWISE_AND,  _T("CFXBlockMathBitwiseAnd"), _T("Битовое И"), GROUP_MATH_BITWISE });
	ods->Add({ BLOCK_MATH_BITWISE_OR,  _T("CFXBlockMathBitwiseOr"), _T("Битовое ИЛИ"), GROUP_MATH_BITWISE });
	ods->Add({ BLOCK_MATH_BITWISE_XOR,  _T("CFXBlockMathBitwiseXor"), _T("Битовое XOR"), GROUP_MATH_BITWISE });
	ods->Add({ BLOCK_MATH_BITWISE_NOT,  _T("CFXBlockMathBitwiseNot"), _T("Битовое НЕ"), GROUP_MATH_BITWISE });
	ods->Add({ BLOCK_MATH_BITWISE_SHIFT_LEFT,  _T("CFXBlockMathBitwiseShiftLeft"), _T("Сдвиг влево"), GROUP_MATH_BITWISE });
	ods->Add({ BLOCK_MATH_BITWISE_SHIFT_RIGHT,  _T("CFXBlockMathBitwiseShiftRight"), _T("Сдвиг впрао"), GROUP_MATH_BITWISE });
	ods->Add({ BLOCK_MATH_BITWISE_PACK,  _T("CFXBlockMathBitwisePack"), _T("Кодирование"), GROUP_MATH_BITWISE });
	ods->Add({ BLOCK_MATH_BITWISE_UNPACK,  _T("CFXBlockMathBitwiseUnpack"), _T("Декодирование"), GROUP_MATH_BITWISE });

	// Математика-преобразование типов
	ods->Add({ GROUP_MATH_CAST, _T(""), _T("Преобразование типов"), GROUP_MATH, true });
	ods->Add({ BLOCK_MATH_CAST_FLOAT_INT,  _T("CFXBlockMathCastFloatInt"), _T("Вещественное к целому"), GROUP_MATH_CAST });
	ods->Add({ BLOCK_MATH_CAST_INT_FLOAT,  _T("CFXBlockMathCastIntFloat"), _T("Целое к вещественному"), GROUP_MATH_CAST });

	// Компараторы
	ods->Add({ GROUP_COMPARATOR, _T(""), _T("Компараторы"), 0, true });
	ods->Add({ BLOCK_COMPARATOR_DOWN,  _T("CFXBlockComparatorDown"), _T("Компаратор нижнего уровня"), GROUP_COMPARATOR });
	ods->Add({ BLOCK_COMPARATOR_UP,  _T("CFXBlockComparatorUp"), _T("Компаратор верхнего уровня"), GROUP_COMPARATOR });

	// Логика
	ods->Add({ GROUP_LOGICAL, _T(""), _T("Логика"), 0, true });
	ods->Add({ BLOCK_LOGICAL_AND,  _T("CFXBlockLogicalAnd"), _T("Логическое И"), GROUP_LOGICAL });
	ods->Add({ BLOCK_LOGICAL_OR,  _T("CFXBlockLogicalOr"), _T("Логическое ИЛИ"), GROUP_LOGICAL });
	ods->Add({ BLOCK_LOGICAL_NOT,  _T("CFXBlockLogicalNot"), _T("Логическое НЕ"), GROUP_LOGICAL });
	ods->Add({ BLOCK_LOGICAL_XOR,  _T("CFXBlockLogicalXor"), _T("Логическое XOR"), GROUP_LOGICAL });
	ods->Add({ BLOCK_LOGICAL_RISING_EDGE,  _T("CFXBlockLogicalRisingEdge"), _T("Восходящий фронт"), GROUP_LOGICAL });
	ods->Add({ BLOCK_LOGICAL_FALLING_EDGE,  _T("CFXBlockLogicalFallingEdge"), _T("Нисходящий фронт"), GROUP_LOGICAL });
	ods->Add({ BLOCK_LOGICAL_FRONTS,  _T("CFXBlockLogicalFronts"), _T("Фронты"), GROUP_LOGICAL });

	// Задержки
	ods->Add({ GROUP_DELAY, _T(""), _T("Задержки"), 0, true });
	ods->Add({ BLOCK_ANTIBOUNCE,  _T("CFXBlockAntiBounce"), _T("Дребезг"), GROUP_DELAY });
	ods->Add({ BLOCK_DELAY_ON,  _T("CFXBlockDelayOn"), _T("Задержка включения"), GROUP_DELAY });
	ods->Add({ BLOCK_DELAY_OFF,  _T("CFXBlockDelayOff"), _T("Задержка выключения"), GROUP_DELAY });
	
	// Счетчики, триггеры, память
	ods->Add({ GROUP_COUNTERS_TRIGGERS, _T(""), _T("Счетчики, триггеры"), 0, true });
	ods->Add({ BLOCK_COUNTER,  _T("CFXBlockCounter"), _T("Счетчик"), GROUP_COUNTERS_TRIGGERS });

	// Триггеры
	ods->Add({ GROUP_TRIGGERS, _T(""), _T("Триггеры"), GROUP_COUNTERS_TRIGGERS, true });
	ods->Add({ BLOCK_LOGICAL_TRIGGER_RS,  _T("CFXBlockLogicalTriggerRS"), _T("RS-триггер"), GROUP_TRIGGERS });
	ods->Add({ BLOCK_LOGICAL_TRIGGER_SR,  _T("CFXBlockLogicalTriggerSR"), _T("SR-триггер"), GROUP_TRIGGERS });
	ods->Add({ BLOCK_LOGICAL_TRIGGER_RS_RE,  _T("CFXBlockLogicalTriggerRSRisingEdge"), _T("RS-триггер по передним фронтам"), GROUP_TRIGGERS });
	
	ods->Add({ GROUP_MEMORY, _T(""), _T("Память"), GROUP_COUNTERS_TRIGGERS,true });
	ods->Add({ BLOCK_MEMORY_FLOAT, _T("CFXBlockMemoryFloat"), _T("Память (вещ)"),GROUP_MEMORY });
	ods->Add({ BLOCK_MEMORY_INT, _T("CFXBlockMemoryInt"), _T("Память (цел)"),GROUP_MEMORY });
	ods->Add({ BLOCK_MEMORY_LOGICAL, _T("CFXBlockMemoryLogical"), _T("Память (лог)"),GROUP_MEMORY });

	// Контроллеры
	ods->Add({ GROUP_CONTROLLERS, _T(""), _T("Триггеры"), 0, true });
	ods->Add({ BLOCK_CONTROLLER_NIMOD01,  _T("CFXBlockControllerNiMod01"), _T("Контроллер NiMod-A01"), GROUP_CONTROLLERS });
	ods->Add({ BLOCK_EXTENSION_NIMODA01,  _T("CFXBlockExtensionA01"), _T("Модуль расширения NiMod-A01"), GROUP_CONTROLLERS });
		
	// Контроллеры
	ods->Add({ GROUP_SENSORS, _T(""), _T("Датчики"), 0, true });

	// Контроллеры-термосопротивления 2-проводные
	ods->Add({ GROUP_SENSORS_TRD_2W, _T(""), _T("Термосопротивления 2-проводные"), GROUP_SENSORS, true });
	ods->Add({ BLOCK_SENSOR_TRD_2W_M50,  _T("CFXBlockSensorTRD2WM50"), _T("M50"), GROUP_SENSORS_TRD_2W });
	ods->Add({ BLOCK_SENSOR_TRD_2W_M100,  _T("CFXBlockSensorTRD2WM100"), _T("M100"), GROUP_SENSORS_TRD_2W });
	ods->Add({ BLOCK_SENSOR_TRD_2W_P50,  _T("CFXBlockSensorTRD2WP50"), _T("P50"), GROUP_SENSORS_TRD_2W });
	ods->Add({ BLOCK_SENSOR_TRD_2W_P100,  _T("CFXBlockSensorTRD2WP100"), _T("P100"), GROUP_SENSORS_TRD_2W });
	ods->Add({ BLOCK_SENSOR_TRD_2W_PT100,  _T("CFXBlockSensorTRD2WPt100"), _T("Pt100"), GROUP_SENSORS_TRD_2W });
	ods->Add({ BLOCK_SENSOR_TRD_2W_PT500,  _T("CFXBlockSensorTRD2WPt500"), _T("Pt500"), GROUP_SENSORS_TRD_2W });
	ods->Add({ BLOCK_SENSOR_TRD_2W_PT1000,  _T("CFXBlockSensorTRD2WPt1000"), _T("Pt1000"), GROUP_SENSORS_TRD_2W });
	
	// Контроллеры-термосопротивления 3-проводные
	ods->Add({ GROUP_SENSORS_TRD_3W, _T(""), _T("Термосопротивления 3-проводные"), GROUP_SENSORS, true });
	ods->Add({ BLOCK_SENSOR_TRD_3W_M50,  _T("CFXBlockSensorTRD3WM50"), _T("M50"), GROUP_SENSORS_TRD_3W });
	ods->Add({ BLOCK_SENSOR_TRD_3W_M100,  _T("CFXBlockSensorTRD3WM100"), _T("M100"), GROUP_SENSORS_TRD_3W });
	ods->Add({ BLOCK_SENSOR_TRD_3W_P50,  _T("CFXBlockSensorTRD3WP50"), _T("P50"), GROUP_SENSORS_TRD_3W });
	ods->Add({ BLOCK_SENSOR_TRD_3W_P100,  _T("CFXBlockSensorTRD3WP100"), _T("P100"), GROUP_SENSORS_TRD_3W });
	ods->Add({ BLOCK_SENSOR_TRD_3W_PT100,  _T("CFXBlockSensorTRD3WPt100"), _T("Pt100"), GROUP_SENSORS_TRD_3W });
	ods->Add({ BLOCK_SENSOR_TRD_3W_PT500,  _T("CFXBlockSensorTRD3WPt500"), _T("Pt500"), GROUP_SENSORS_TRD_3W });
	ods->Add({ BLOCK_SENSOR_TRD_3W_PT1000,  _T("CFXBlockSensorTRD3WPt1000"), _T("Pt1000"), GROUP_SENSORS_TRD_3W });

	// Контроллеры-термосопротивления 4-проводные
	ods->Add({ GROUP_SENSORS_TRD_4W, _T(""), _T("Термосопротивления 4-проводные"), GROUP_SENSORS, true });
	ods->Add({ BLOCK_SENSOR_TRD_4W_M50,  _T("CFXBlockSensorTRD4WM50"), _T("M50"), GROUP_SENSORS_TRD_4W });
	ods->Add({ BLOCK_SENSOR_TRD_4W_M100,  _T("CFXBlockSensorTRD4WM100"), _T("M100"), GROUP_SENSORS_TRD_4W });
	ods->Add({ BLOCK_SENSOR_TRD_4W_P50,  _T("CFXBlockSensorTRD4WP50"), _T("P50"), GROUP_SENSORS_TRD_4W });
	ods->Add({ BLOCK_SENSOR_TRD_4W_P100,  _T("CFXBlockSensorTRD4WP100"), _T("P100"), GROUP_SENSORS_TRD_4W });
	ods->Add({ BLOCK_SENSOR_TRD_4W_PT100,  _T("CFXBlockSensorTRD4WPt100"), _T("Pt100"), GROUP_SENSORS_TRD_4W });
	ods->Add({ BLOCK_SENSOR_TRD_4W_PT500,  _T("CFXBlockSensorTRD4WPt500"), _T("Pt500"), GROUP_SENSORS_TRD_4W });
	ods->Add({ BLOCK_SENSOR_TRD_4W_PT1000,  _T("CFXBlockSensorTRD4WPt1000"), _T("Pt1000"), GROUP_SENSORS_TRD_4W });
	ods->Add({ GROUP_SIMULATION, _T(""),_T("Симуляция"),0,true });
	ods->Add({ GROUP_SIMULATION_VISUAL,_T(""),_T("Отображение, ввод"),GROUP_SIMULATION,true });
	ods->Add({ BLOCK_SIMULATION_VISUAL_SHOW_FLOAT,_T("CFXBlockVisualShowFloat"),_T("Отображение вещественное"),GROUP_SIMULATION_VISUAL});
	ods->Add({ BLOCK_SIMULATION_VISUAL_SHOW_INT,_T("CFXBlockVisualShowInt"),_T("Отображение целое"),GROUP_SIMULATION_VISUAL });
	ods->Add({ BLOCK_SIMULATION_VISUAL_SHOW_LOGICAL,_T("CFXBlockVisualShowLogical"),_T("Отображение логическое"),GROUP_SIMULATION_VISUAL });

	// Прочие
	ods->Add({ GROUP_OTHER, _T(""), _T("Прочие"), 0, true });
	ods->Add({ BLOCK_TRANSFORM_CURRENT,  _T("CFXBlockTransformCurrent"), _T("Токовый 0-20мА, 4-20мА"), GROUP_OTHER });
	ods->Add({ BLOCK_TRANSFORM_LINEAR,  _T("CFXBlockTransformLinear"), _T("Линейное преобразование"), GROUP_OTHER });
	ods->Add({ BLOCK_TRANSFORM_LINEAR_LIMITS,  _T("CFXBlockTransformLinearLimits"), _T("Линейное преобразование с ограничением"), GROUP_OTHER });
	
	ods->Add({ BLOCK_PID, _T("CFXBlockPID"),_T("ПИД-Регулятор"), GROUP_OTHER });
	
	ods->Add({ GROUP_DEMO,_T(""), _T("Демонстрация"), 0, true });
	ods->Add({ BLOCK_DEMO_TU154, _T("CFXBlockDemoTu154"),_T("Ту-154"),GROUP_DEMO });
	//ods->Add({ FXLINK,  _T("CFXLink"),
	//ods->Add({ FXPIN,  _T("CFXPin"),
	//ods->Add({ BLOCK_FUNCTIONAL_PIN,  _T("CFXBlockFunctionalPin"),
}
