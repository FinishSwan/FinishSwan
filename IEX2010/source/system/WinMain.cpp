#include	"iextreme.h"
#include	"Framework.h"
#include	"sceneMain.h"
#include    "..\sceneTitle.h"
#define _CRTDBG_MAP_ALLOC

#include	"Fade.h"
#include	"..\CP11Rand.h"

#include    "..\EntryPoint.h"
#include    "..\ScaleManager.h"

#include <crtdbg.h>
#include    "..\ObjectManager.h"

//*****************************************************************************************************************************
//
//
//
//*****************************************************************************************************************************

char*	AppTitle = "IEX2010";

BOOL	bFullScreen = FALSE;
DWORD	ScreenMode  = SCREEN720p;

Framework*	MainFrame = NULL;

//*****************************************************************************************************************************
//		アプリケーション初期化
//*****************************************************************************************************************************

BOOL	InitApp( HWND hWnd )
{
	//	IEXシステム初期化
	IEX_Initialize( hWnd, bFullScreen, ScreenMode );
	IEX_InitAudio();
	IEX_InitInput();

	//	システムの初期化
	SYSTEM_Initialize();
    obj_manager.Initialize();
	FadeManager::SetColor(Vector3(1.0f, 1.0f, 1.0f));
	FadeManager::FadeOut(5.0f);

    EntryPoint::Initialize();
    

    //オブジェクトの位置決定
    Vector3 pos[8] =
    {
		//Vector3(0, -5.6, 0),
		Vector3(10.0f , 0, -5.0f),
        Vector3(23.74, 0, 24.04),
        Vector3(-26.74, 0, 29.26),
        Vector3(-30.88, 0, -29.46),
        Vector3(29.85, 0, -29.35),
        Vector3(-1.02, 0, -9.32),
        Vector3(23.42, 0, 0.51),
        Vector3(0.66, 0, 25.31),
    };
    //向き決定
    Vector3 angle[8] =
    {
        Vector3(0, 0, 0),
        Vector3(0, 0, 0),
        Vector3(0, 0, 0),
        Vector3(0, 0, 0),
        Vector3(0, 0, 0),
        Vector3(0, 0, 0),
        Vector3(0, 0, 0),
        Vector3(0, 0, 0),
    };

    for (int i = 0; i < 9; i++)
    {
        EntryPoint::Register(pos[i], angle[i]);
    }
    //スケール設定
    char* filename[8] =
    {
        //"DATA\\IMO\\new_room.IMO",
        ("DATA\\IMO\\tana.IMO"),
        ("DATA\\IMO\\bed.IMO"),
        ("DATA\\IMO\\sofa.IMO"),
        ("DATA\\IMO\\table_kai.IMO"),
        ("DATA\\IMO\\tanataka.IMO"),
        ("DATA\\IMO\\terebi.IMO"),
        ("DATA\\IMO\\toire.IMO"),
        ("DATA\\IMO\\tukuetoisu.IMO"),
    };
    float scale[8] =
    {
      //  1.2f,
        0.08f,
        3.0f,
        0.85f,
        0.1f,
        0.2f,
        0.15f,
        0.1f,
        0.005f,
    };

    for (int i = 0; i < 9; i++)
    {
        ScaleManager::Register(filename[i], scale[i]);
    }

	RandomEngine::Initialize();
	//	メインフレームワーク生成
	MainFrame = new Framework();
	//	初期シーン登録
	//MainFrame->ChangeScene( new sceneMain() );
    MainFrame->ChangeScene(new sceneTitle());

	return TRUE;
}

//*****************************************************************************************************************************
//		ウィンドウプロシージャ
//*****************************************************************************************************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message){
	case WM_DESTROY: PostQuitMessage(0); return 0;
	case WM_KEYDOWN:
			switch (wParam){
			case VK_ESCAPE: PostMessage(hWnd, WM_CLOSE, 0, 0); return 0;
			case VK_F1:		iexSystem::OpenDebugWindow(); return 0;
			}
			break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

//*****************************************************************************************************************************
//		ウィンドウ作成
//*****************************************************************************************************************************
HWND InitWindow( HINSTANCE hInstance, int nCmdShow )
{
	HWND			hWnd;

	//	スクリーンサイズ取得
	RECT	WindowSize;
	iexSystem::GetScreenRect( ScreenMode, WindowSize );

	//	ウィンドウクラス設定
	WNDCLASS	wc;
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = WindowProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH )GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = "IEX2010";
	RegisterClass(&wc);

	//	ウィンドウ作成
	if( !bFullScreen ){
		AdjustWindowRect( &WindowSize, WS_OVERLAPPEDWINDOW, FALSE );
		hWnd = CreateWindow( "IEX2010", AppTitle, WS_OVERLAPPEDWINDOW, 
								0, 0, WindowSize.right-WindowSize.left, WindowSize.bottom-WindowSize.top,
								NULL, NULL, hInstance, NULL);
	} else {
		hWnd = CreateWindow( "IEX2010", AppTitle, WS_POPUP, 0, 0, WindowSize.right,WindowSize.bottom, NULL, NULL, hInstance, NULL);
		ShowCursor(FALSE);
	}
	if( !hWnd ) return NULL;
	
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

    return hWnd;
}

//*****************************************************************************************************************************
//		WinMain
//*****************************************************************************************************************************
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	MSG		msg;
	HWND	hWnd;

	if( GetAsyncKeyState(VK_CONTROL)&0x8000 ) bFullScreen = TRUE;

	//メモリリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	hWnd = InitWindow(hInstance, nCmdShow);

	InitApp(hWnd);


	//	メインループ
	for(;;){
		if( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) ){
			if( !GetMessage(&msg, NULL, 0, 0) ) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			if( MainFrame->Update() ) MainFrame->Render();
		}
	}

	//	全解放	
	delete	MainFrame;
	SYSTEM_Release();
    obj_manager.Release();
	iexSystem::CloseDebugWindow();
	IEX_ReleaseInput();
	IEX_Release();

	return 0;
}
