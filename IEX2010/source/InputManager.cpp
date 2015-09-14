
#include	"iextreme.h"
#include	"system/system.h"

#include	"InputManager.h"
//************************************************************************************************************************************************
//
//		���͊Ǘ��N���X�̒�`
//
//************************************************************************************************************************************************
	IDirectInput*						InputManager::m_pInput				=	NULL;
	IDirectInputDevice*					InputManager::m_pMouse				=	NULL;
	IDirectInputDevice*					InputManager::m_pKeyBoard			=	NULL;
	InputManager::MOUSE_INPUT_DATA		InputManager::m_MouseInputData		=	{	0	};
	InputManager::KEYBOARD_INPUT_DATA	InputManager::m_KeyBoardInputData	=	{	KEY_STATE_NON_PRESSED	};
	//********************************************************************************************************************************************
	//		������
	//********************************************************************************************************************************************
	bool	InputManager::Initialize( void )
	{
		HRESULT	hResult	=	S_OK;

		//	DirectInput�C���^�[�t�F�C�X���擾
		hResult	=	DirectInput8Create( GetModuleHandle( NULL ), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL );

		//	�}�E�X�f�o�C�X�̏�����
		if( SUCCEEDED( hResult ) ){
			//	�f�o�C�X���쐬
			hResult	=	m_pInput->CreateDevice( GUID_SysMouse, &m_pMouse, NULL );

			//	�f�[�^�`����ݒ�
			if( SUCCEEDED( hResult ) ){
				hResult	=	m_pMouse->SetDataFormat( &c_dfDIMouse2 );
			}

			//	�������x���̐ݒ�
			if( SUCCEEDED( hResult ) ){
				//	��r��
				hResult	=	m_pMouse->SetCooperativeLevel( iexSystem::Window, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND );
				//	�r��
				//hResult	=	m_pMouse->SetCooperativeLevel( iexSystem::Window, DISCL_EXCLUSIVE | DISCL_FOREGROUND );
			}

			//	�o�b�t�@�T�C�Y�̐ݒ�
			if( SUCCEEDED( hResult ) ){
				DIPROPDWORD	dipdw;
				//	�w�b�_�[
				dipdw.diph.dwSize		=	sizeof( DIPROPDWORD );
				dipdw.diph.dwHeaderSize	=	sizeof( DIPROPHEADER );
				dipdw.diph.dwObj		=	0;
				dipdw.diph.dwHow		=	DIPH_DEVICE;
				//	�f�[�^
				dipdw.dwData			=	sizeof( DIMOUSESTATE2 );

				//	�Z�b�g
				hResult	=	m_pMouse->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );
			}
		}

		//	�L�[�{�[�h�f�o�C�X�̏�����
		if( SUCCEEDED( hResult ) ){
			//	�f�o�C�X���쐬
			hResult	=	m_pInput->CreateDevice( GUID_SysKeyboard, &m_pKeyBoard, NULL );

			//	�f�[�^�`����ݒ�
			if( SUCCEEDED( hResult ) ){
				hResult	=	m_pKeyBoard->SetDataFormat( &c_dfDIKeyboard ); 
			}

			//	�������x���̐ݒ�
			if( SUCCEEDED( hResult ) ){
				hResult	=	m_pKeyBoard->SetCooperativeLevel( iexSystem::Window, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND );
			}
		}

		//	���ʂ�Ԃ�
		if( SUCCEEDED( hResult ) )	return	true;
		else						return	false;
	}
	//********************************************************************************************************************************************
	//		���
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
	//		�N���A
	//********************************************************************************************************************************************
	void	InputManager::Clear( void )
	{
		//	�}�E�X�̓��͏����N���A
		m_MouseInputData.axisX	=	0;
		m_MouseInputData.axisY	=	0;
		m_MouseInputData.axisZ	=	0;
		for( int i = 0; i < 8; i++ ){
			m_MouseInputData.buttonState[i]	=	KEY_STATE_NON_PRESSED;
		}

		//	�L�[�{�[�h�̓��͏����N���A
		for( int i = 0; i < 256; i++ ){
			m_KeyBoardInputData.keyState[i]	=	KEY_STATE_NON_PRESSED;
		}
	}
	//********************************************************************************************************************************************
	//		�X�V
	//********************************************************************************************************************************************
	void	InputManager::Update( void )
	{
		//	�}�E�X�̓��͏����X�V
		UpdateMouse();
		//	�L�[�{�[�h�̓��͏����X�V
		UpdateKeyBoard();
	}
	//********************************************************************************************************************************************
	//		���̑�
	//********************************************************************************************************************************************
	//	�g�p�J�n
	void		InputManager::Begin( void )
	{
		m_pMouse->Acquire();
		m_pKeyBoard->Acquire();
	}
	//	�}�E�X���X�V
	void		InputManager::UpdateMouse( void )
	{
		HRESULT	hResult	=	S_OK;

		//	�}�E�X�̏�Ԃ��擾
		DIMOUSESTATE2	mouseState;
		hResult	=	m_pMouse->GetDeviceState( sizeof( DIMOUSESTATE2 ), &mouseState );
		if( FAILED( hResult ) ){
			m_pMouse->Acquire();
			hResult	=	m_pMouse->GetDeviceState( sizeof( DIMOUSESTATE2 ), &mouseState );
		}
		
		if( SUCCEEDED( hResult ) ){
			//	�e���̏����X�V
			m_MouseInputData.axisX	=	mouseState.lX;
			m_MouseInputData.axisY	=	mouseState.lY;
			m_MouseInputData.axisZ	=	mouseState.lZ;

			//	�e�{�^���̏����X�V
			for( int i = 0; i < 8; i++ ){
				m_MouseInputData.buttonState[i]	=	NextKeyState( m_MouseInputData.buttonState[i], ( mouseState.rgbButtons[i] & 0x80 )? true : false );
			}
		}
		//	���͏��̎擾�Ɏ��s�����̂œ��͂��N���A
		else{
			//	�e���̏����X�V
			m_MouseInputData.axisX	=	0;
			m_MouseInputData.axisY	=	0;
			m_MouseInputData.axisZ	=	0;

			//	�e�{�^���̏����X�V
			for( int i = 0; i < 8; i++ ){
				m_MouseInputData.buttonState[i]	=	NextKeyState( m_MouseInputData.buttonState[i], false );
			}
		}
	}
	//	�L�[�{�[�h���X�V
	void		InputManager::UpdateKeyBoard( void )
	{
		HRESULT	hResult	=	S_OK;

		char	buffer[256];

		//	�L�[�̏�Ԃ��擾
		hResult	=	m_pKeyBoard->GetDeviceState( sizeof( buffer ), (LPVOID)&buffer );
		if( FAILED( hResult ) ){
			m_pKeyBoard->Acquire();
			hResult	=	m_pKeyBoard->GetDeviceState( sizeof( buffer ), (LPVOID)&buffer );
		}

		//	���͏����X�V
		if( SUCCEEDED( hResult ) ){
			for( int i = 0; i < 256; i++ ){
				m_KeyBoardInputData.keyState[i]	=	NextKeyState( m_KeyBoardInputData.keyState[i], ( buffer[i] & 0x80 )? true : false );
			}
		}
		//	���͏��̎擾�Ɏ��s�����̂Ńf�[�^���N���A
		else{
			for( int i = 0; i < 256; i++ ){
				m_KeyBoardInputData.keyState[i]	=	NextKeyState( m_KeyBoardInputData.keyState[i], false );
			}
		}
	}
	//	���̃{�^���̏�Ԃ��擾
	KEY_STATE	InputManager::NextKeyState( KEY_STATE _Current, bool _Input )
	{
		switch( _Current ){
		//	������Ă��Ȃ�
		case	KEY_STATE_NON_PRESSED:
			if( _Input )	return	KEY_STATE_PRESSED;
			else			return	KEY_STATE_NON_PRESSED;
		//	�����ꑱ���Ă���
		case	KEY_STATE_CONTINUATION:
			if( _Input )	return	KEY_STATE_CONTINUATION;
			else			return	KEY_STATE_RELEASE;
		//	�����ꂽ
		case	KEY_STATE_RELEASE:
			if( _Input )	return	KEY_STATE_PRESSED;
			else			return	KEY_STATE_NON_PRESSED;
			break;
		//	�����ꂽ
		case	KEY_STATE_PRESSED:
			if( _Input )	return	KEY_STATE_CONTINUATION;
			else			return	KEY_STATE_RELEASE;
		}

		return	KEY_STATE_NON_PRESSED;
	}
	//	�E�B���h�E���̃}�E�X�J�[�\���ʒu���擾
	POINT		InputManager::GetMouseCursorCoord( void )
	{
		POINT	cursorPos;

		//	�}�E�X�J�[�\���̐�΍��W���擾
		GetCursorPos( &cursorPos );

		//	�X�N���[�����W�n�ł̃J�[�\�����W���N���C�A���g���W�n�ɕϊ�
		ScreenToClient( iexSystem::Window, &cursorPos );

		//	�X�N���[���T�C�Y�ϓ��΍�
		RECT	clientRect;
		GetClientRect( iexSystem::Window, &clientRect );
		cursorPos.x	=	( LONG )( ( float )cursorPos.x * ( ( float )iexSystem::ScreenWidth  / ( clientRect.right  - clientRect.left ) ) );
		cursorPos.y	=	( LONG )( ( float )cursorPos.y * ( ( float )iexSystem::ScreenHeight / ( clientRect.bottom - clientRect.top  ) ) );

		return	cursorPos;
	}
	//	�}�E�X�̋������x����ݒ�
	void		InputManager::SetMouseExclusion( bool _Exclusion )
	{
		HRESULT	hResult;

		//	�ꎞ�I�Ƀf�o�C�X�ւ̃A�N�Z�X�������
		hResult	=	m_pMouse->Unacquire();

		//	�r��
		if( _Exclusion )	hResult	=	m_pMouse->SetCooperativeLevel( iexSystem::Window, DISCL_EXCLUSIVE | DISCL_FOREGROUND );
		//	��r��
		else				hResult	=	m_pMouse->SetCooperativeLevel( iexSystem::Window, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND );

		//	�A�N�Z�X�����Ď擾
		hResult	=	m_pMouse->Acquire();
	}
//************************************************************************************************************************************************
//
//		�O���[�o���֐�
//
//************************************************************************************************************************************************
	//	�p�b�h�ɂ��J�[�\�����W�X�V
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
	//	�p�b�h���͂ɂ��g���K�[
	bool	GetPadKeyDecision( bool _Moment )
	{
		if( _Moment )	return	KEY( KEY_B ) == 3	||	KEY( KEY_R2 ) == 3;
		else			return	KEY( KEY_B )		||	KEY( KEY_R2 );
	}
	bool	GetPadKeyCancell( void )
	{
		return	KEY( KEY_A ) == 3;
	}
