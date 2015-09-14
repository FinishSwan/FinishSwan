
//********************************************************************************************************************
//		定数リストの定義	
//********************************************************************************************************************
	//	入力状態
	enum	KEY_STATE{
		KEY_STATE_NON_PRESSED,		//	押されていない
		KEY_STATE_CONTINUATION,		//	押され続けている
		KEY_STATE_RELEASE,			//	離された
		KEY_STATE_PRESSED,			//	押された
	};
//********************************************************************************************************************
//
//		クラスの宣言
//
//********************************************************************************************************************
	//		入力管理クラス
	//****************************************************************************************************************
	class	InputManager
	{
	public:
		//	マウスの入力データ
		struct	MOUSE_INPUT_DATA{
			LONG		axisX,	axisY,	axisZ;	//	各軸の変化量（Ｚ軸はホイール）
			KEY_STATE	buttonState[8];			//	各ボタンの状態
		};
		//	キーボードの入力データ
		struct	KEYBOARD_INPUT_DATA{
			KEY_STATE	keyState[256];			//	各キーの状態
		};
	private:
		static	IDirectInput*			m_pInput;
		static	IDirectInputDevice*		m_pMouse;
		static	IDirectInputDevice*		m_pKeyBoard;

		static	MOUSE_INPUT_DATA		m_MouseInputData;
		static	KEYBOARD_INPUT_DATA		m_KeyBoardInputData;
	private:
		//	次のキー状態を取得
		static	KEY_STATE	NextKeyState( KEY_STATE _Current, bool _Input );
		//	マウスを更新
		static	void		UpdateMouse( void );
		//	キーボードを更新
		static	void		UpdateKeyBoard( void );
	public:
		//	初期化
		static	bool	Initialize( void );
		//	解放
		static	void	Release( void );

		//	使用開始
		static	void	Begin( void );
		//	入力情報のクリア
		static	void	Clear( void );
		//	更新
		static	void	Update( void );
		
		//	ウィンドウ内でのマウスカーソル位置を取得
		static	POINT	GetMouseCursorCoord( void );

		//	優先レベルの設定
		static	void	SetMouseExclusion( bool _Exclusion );

		//	情報の取得
		static	KEY_STATE	GetMouseButton( int _ButtonNum ){	return	m_MouseInputData.buttonState[_ButtonNum];	}
		static	LONG		GetMouseAxisX( void ){				return	m_MouseInputData.axisX;						}
		static	LONG		GetMouseAxisY( void ){				return	m_MouseInputData.axisY;						}
		static	LONG		GetMouseAxisZ( void ){				return	m_MouseInputData.axisZ;						}
		static	KEY_STATE	GetKeyState( int _DIKeyCode ){		return	m_KeyBoardInputData.keyState[_DIKeyCode];	}
	};

//********************************************************************************************************************
//		グローバル関数
//********************************************************************************************************************
	//	パッドによるカーソル座標更新
	BOOL	UpdateCursorCoordAtPadAxis( float _AxisThreshold, float _Sensitivity );
	//	パッド入力による決定トリガー
	bool	GetPadKeyDecision( bool _Moment = true );
	bool	GetPadKeyCancell( void );