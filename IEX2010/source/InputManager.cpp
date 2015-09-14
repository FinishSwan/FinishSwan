
#include	"iextreme.h"
#include	"system/system.h"

#include	"InputManager.h"
//************************************************************************************************************************************************
//
//		入力管理クラスの定義
//
//************************************************************************************************************************************************
	IDirectInput*						InputManager::m_pInput				=	NULL;
	IDirectInputDevice*					InputManager::m_pMouse				=	NULL;
	IDirectInputDevice*					InputManager::m_pKeyBoard			=	NULL;
	InputManager::MOUSE_INPUT_DATA		InputManager::m_MouseInputData		=	{	0	};
	InputManager::KEYBOARD_INPUT_DATA	InputManager::m_KeyBoardInputData	=	{	KEY_STATE_NON_PRESSED	};
	//********************************************************************************************************************************************
	//		初期化
	//********************************************************************************************************************************************
	bool	InputManager::Initialize( void )
	{
		HRESULT	hResult	=	S_OK;

		//	DirectInputインターフェイスを取得
		hResult	=	DirectInput8Create( GetModuleHandle( NULL ), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL );

		//	マウスデバイスの初期化
		if( SUCCEEDED( hResult ) ){
			//	デバイスを作成
			hResult	=	m_pInput->CreateDevice( GUID_SysMouse, &m_pMouse, NULL );

			//	データ形式を設定
			if( SUCCEEDED( hResult ) ){
				hResult	=	m_pMouse->SetDataFormat( &c_dfDIMouse2 );
			}

			//	強調レベルの設定
			if( SUCCEEDED( hResult ) ){
				//	非排他
				hResult	=	m_pMouse->SetCooperativeLevel( iexSystem::Window, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND );
				//	排他
				//hResult	=	m_pMouse->SetCooperativeLevel( iexSystem::Window, DISCL_EXCLUSIVE | DISCL_FOREGROUND );
			}

			//	バッファサイズの設定
			if( SUCCEEDED( hResult ) ){
				DIPROPDWORD	dipdw;
				//	ヘッダー
				dipdw.diph.dwSize		=	sizeof( DIPROPDWORD );
				dipdw.diph.dwHeaderSize	=	sizeof( DIPROPHEADER );
				dipdw.diph.dwObj		=	0;
				dipdw.diph.dwHow		=	DIPH_DEVICE;
				//	データ
				dipdw.dwData			=	sizeof( DIMOUSESTATE2 );

				//	セット
				hResult	=	m_pMouse->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );
			}
		}

		//	キーボードデバイスの初期化
		if( SUCCEEDED( hResult ) ){
			//	デバイスを作成
			hResult	=	m_pInput->CreateDevice( GUID_SysKeyboard, &m_pKeyBoard, NULL );

			//	データ形式を設定
			if( SUCCEEDED( hResult ) ){
				hResult	=	m_pKeyBoard->SetDataFormat( &c_dfDIKeyboard ); 
			}

			//	強調レベルの設定
			if( SUCCEEDED( hResult ) ){
				hResult	=	m_pKeyBoard->SetCooperativeLevel( iexSystem::Window, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND );
			}
		}

		//	結果を返す
		if( SUCCEEDED( hResult ) )	return	true;
		else						return	false;
	}
	//********************************************************************************************************************************************
	//		解放
	//********************************************************************************************************************************************
	void	InputManager::Release( void )
	{
		if( m_pMouse )		m_pMouse->Unacquire();
		if( m_pKeyBoard )	m_pKeyBoard->Unacquire();

		m_pMouse->Release();	m_pMouse	=	NULL;
		m_pKeyBoard->Release();	m_pKeyBoard	=	NULL;
		m_pInput->Release();	m_pInput	=	NULL;
	}
	//********************************************************************************************************************************************
	//		クリア
	//********************************************************************************************************************************************
	void	InputManager::Clear( void )
	{
		//	マウスの入力情報をクリア
		m_MouseInputData.axisX	=	0;
		m_MouseInputData.axisY	=	0;
		m_MouseInputData.axisZ	=	0;
		for( int i = 0; i < 8; i++ ){
			m_MouseInputData.buttonState[i]	=	KEY_STATE_NON_PRESSED;
		}

		//	キーボードの入力情報をクリア
		for( int i = 0; i < 256; i++ ){
			m_KeyBoardInputData.keyState[i]	=	KEY_STATE_NON_PRESSED;
		}
	}
	//********************************************************************************************************************************************
	//		更新
	//********************************************************************************************************************************************
	void	InputManager::Update( void )
	{
		//	マウスの入力情報を更新
		UpdateMouse();
		//	キーボードの入力情報を更新
		UpdateKeyBoard();
	}
	//********************************************************************************************************************************************
	//		その他
	//********************************************************************************************************************************************
	//	使用開始
	void		InputManager::Begin( void )
	{
		m_pMouse->Acquire();
		m_pKeyBoard->Acquire();
	}
	//	マウスを更新
	void		InputManager::UpdateMouse( void )
	{
		HRESULT	hResult	=	S_OK;

		//	マウスの状態を取得
		DIMOUSESTATE2	mouseState;
		hResult	=	m_pMouse->GetDeviceState( sizeof( DIMOUSESTATE2 ), &mouseState );
		if( FAILED( hResult ) ){
			m_pMouse->Acquire();
			hResult	=	m_pMouse->GetDeviceState( sizeof( DIMOUSESTATE2 ), &mouseState );
		}
		
		if( SUCCEEDED( hResult ) ){
			//	各軸の情報を更新
			m_MouseInputData.axisX	=	mouseState.lX;
			m_MouseInputData.axisY	=	mouseState.lY;
			m_MouseInputData.axisZ	=	mouseState.lZ;

			//	各ボタンの情報を更新
			for( int i = 0; i < 8; i++ ){
				m_MouseInputData.buttonState[i]	=	NextKeyState( m_MouseInputData.buttonState[i], ( mouseState.rgbButtons[i] & 0x80 )? true : false );
			}
		}
		//	入力情報の取得に失敗したので入力をクリア
		else{
			//	各軸の情報を更新
			m_MouseInputData.axisX	=	0;
			m_MouseInputData.axisY	=	0;
			m_MouseInputData.axisZ	=	0;

			//	各ボタンの情報を更新
			for( int i = 0; i < 8; i++ ){
				m_MouseInputData.buttonState[i]	=	NextKeyState( m_MouseInputData.buttonState[i], false );
			}
		}
	}
	//	キーボードを更新
	void		InputManager::UpdateKeyBoard( void )
	{
		HRESULT	hResult	=	S_OK;

		char	buffer[256];

		//	キーの状態を取得
		hResult	=	m_pKeyBoard->GetDeviceState( sizeof( buffer ), (LPVOID)&buffer );
		if( FAILED( hResult ) ){
			m_pKeyBoard->Acquire();
			hResult	=	m_pKeyBoard->GetDeviceState( sizeof( buffer ), (LPVOID)&buffer );
		}

		//	入力情報を更新
		if( SUCCEEDED( hResult ) ){
			for( int i = 0; i < 256; i++ ){
				m_KeyBoardInputData.keyState[i]	=	NextKeyState( m_KeyBoardInputData.keyState[i], ( buffer[i] & 0x80 )? true : false );
			}
		}
		//	入力情報の取得に失敗したのでデータをクリア
		else{
			for( int i = 0; i < 256; i++ ){
				m_KeyBoardInputData.keyState[i]	=	NextKeyState( m_KeyBoardInputData.keyState[i], false );
			}
		}
	}
	//	次のボタンの状態を取得
	KEY_STATE	InputManager::NextKeyState( KEY_STATE _Current, bool _Input )
	{
		switch( _Current ){
		//	押されていない
		case	KEY_STATE_NON_PRESSED:
			if( _Input )	return	KEY_STATE_PRESSED;
			else			return	KEY_STATE_NON_PRESSED;
		//	押され続けている
		case	KEY_STATE_CONTINUATION:
			if( _Input )	return	KEY_STATE_CONTINUATION;
			else			return	KEY_STATE_RELEASE;
		//	離された
		case	KEY_STATE_RELEASE:
			if( _Input )	return	KEY_STATE_PRESSED;
			else			return	KEY_STATE_NON_PRESSED;
			break;
		//	押された
		case	KEY_STATE_PRESSED:
			if( _Input )	return	KEY_STATE_CONTINUATION;
			else			return	KEY_STATE_RELEASE;
		}

		return	KEY_STATE_NON_PRESSED;
	}
	//	ウィンドウ内のマウスカーソル位置を取得
	POINT		InputManager::GetMouseCursorCoord( void )
	{
		POINT	cursorPos;

		//	マウスカーソルの絶対座標を取得
		GetCursorPos( &cursorPos );

		//	スクリーン座標系でのカーソル座標をクライアント座標系に変換
		ScreenToClient( iexSystem::Window, &cursorPos );

		//	スクリーンサイズ変動対策
		RECT	clientRect;
		GetClientRect( iexSystem::Window, &clientRect );
		cursorPos.x	=	( LONG )( ( float )cursorPos.x * ( ( float )iexSystem::ScreenWidth  / ( clientRect.right  - clientRect.left ) ) );
		cursorPos.y	=	( LONG )( ( float )cursorPos.y * ( ( float )iexSystem::ScreenHeight / ( clientRect.bottom - clientRect.top  ) ) );

		return	cursorPos;
	}
	//	マウスの協調レベルを設定
	void		InputManager::SetMouseExclusion( bool _Exclusion )
	{
		HRESULT	hResult;

		//	一時的にデバイスへのアクセス権を解放
		hResult	=	m_pMouse->Unacquire();

		//	排他
		if( _Exclusion )	hResult	=	m_pMouse->SetCooperativeLevel( iexSystem::Window, DISCL_EXCLUSIVE | DISCL_FOREGROUND );
		//	非排他
		else				hResult	=	m_pMouse->SetCooperativeLevel( iexSystem::Window, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND );

		//	アクセス権を再取得
		hResult	=	m_pMouse->Acquire();
	}
//************************************************************************************************************************************************
//
//		グローバル関数
//
//************************************************************************************************************************************************
	//	パッドによるカーソル座標更新
	BOOL	UpdateCursorCoordAtPadAxis( float _AxisThreshold, float _Sensitivity )
	{
		static	const	float	c_PadInputMax		=	1000.0f;

		BOOL	result	=	TRUE;

		POINT	beforeCursorCoord	=	{	0	};
		
		result	=	GetCursorPos( &beforeCursorCoord );

		if( result ){
			float	axisX				=	( float )KEY_GetAxisX() + KEY_GetAxisX2();
			float	axisY				=	( float )KEY_GetAxisY() + KEY_GetAxisY2();
			float	padAxisX			=	axisX * ( 1.0f / c_PadInputMax ) * _Sensitivity;
			float	padAxisY			=	axisY * ( 1.0f / c_PadInputMax ) * _Sensitivity;

			if( abs( axisX + FLT_MIN ) < c_PadInputMax * _AxisThreshold )		padAxisX	=	0.0f;
			if( abs( axisY + FLT_MIN ) < c_PadInputMax * _AxisThreshold )		padAxisY	=	0.0f;

			float	correctionRate		=	1.0f / ( 1.0f - _AxisThreshold );
			if( padAxisX )	padAxisX	=	( padAxisX > 0.0f )?	( padAxisX - _AxisThreshold ) * correctionRate	:	( padAxisX + _AxisThreshold ) * correctionRate;
			if( padAxisY )	padAxisY	=	( padAxisY > 0.0f )?	( padAxisY - _AxisThreshold ) * correctionRate	:	( padAxisY + _AxisThreshold ) * correctionRate;

			POINT	newCurosrCoord		=	{
				( LONG )( beforeCursorCoord.x + padAxisX ),
				( LONG )( beforeCursorCoord.y + padAxisY )
			};

			result	=	SetCursorPos( newCurosrCoord.x, newCurosrCoord.y );
		}

		return	result;
	}
	//	パッド入力によるトリガー
	bool	GetPadKeyDecision( bool _Moment )
	{
		if( _Moment )	return	KEY( KEY_B ) == 3	||	KEY( KEY_R2 ) == 3;
		else			return	KEY( KEY_B )		||	KEY( KEY_R2 );
	}
	bool	GetPadKeyCancell( void )
	{
		return	KEY( KEY_A ) == 3;
	}
