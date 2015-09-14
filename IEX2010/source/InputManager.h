
//********************************************************************************************************************
//		�萔���X�g�̒�`	
//********************************************************************************************************************
	//	���͏��
	enum	KEY_STATE{
		KEY_STATE_NON_PRESSED,		//	������Ă��Ȃ�
		KEY_STATE_CONTINUATION,		//	�����ꑱ���Ă���
		KEY_STATE_RELEASE,			//	�����ꂽ
		KEY_STATE_PRESSED,			//	�����ꂽ
	};
//********************************************************************************************************************
//
//		�N���X�̐錾
//
//********************************************************************************************************************
	//		���͊Ǘ��N���X
	//****************************************************************************************************************
	class	InputManager
	{
	public:
		//	�}�E�X�̓��̓f�[�^
		struct	MOUSE_INPUT_DATA{
			LONG		axisX,	axisY,	axisZ;	//	�e���̕ω��ʁi�y���̓z�C�[���j
			KEY_STATE	buttonState[8];			//	�e�{�^���̏��
		};
		//	�L�[�{�[�h�̓��̓f�[�^
		struct	KEYBOARD_INPUT_DATA{
			KEY_STATE	keyState[256];			//	�e�L�[�̏��
		};
	private:
		static	IDirectInput*			m_pInput;
		static	IDirectInputDevice*		m_pMouse;
		static	IDirectInputDevice*		m_pKeyBoard;

		static	MOUSE_INPUT_DATA		m_MouseInputData;
		static	KEYBOARD_INPUT_DATA		m_KeyBoardInputData;
	private:
		//	���̃L�[��Ԃ��擾
		static	KEY_STATE	NextKeyState( KEY_STATE _Current, bool _Input );
		//	�}�E�X���X�V
		static	void		UpdateMouse( void );
		//	�L�[�{�[�h���X�V
		static	void		UpdateKeyBoard( void );
	public:
		//	������
		static	bool	Initialize( void );
		//	���
		static	void	Release( void );

		//	�g�p�J�n
		static	void	Begin( void );
		//	���͏��̃N���A
		static	void	Clear( void );
		//	�X�V
		static	void	Update( void );
		
		//	�E�B���h�E���ł̃}�E�X�J�[�\���ʒu���擾
		static	POINT	GetMouseCursorCoord( void );

		//	�D�惌�x���̐ݒ�
		static	void	SetMouseExclusion( bool _Exclusion );

		//	���̎擾
		static	KEY_STATE	GetMouseButton( int _ButtonNum ){	return	m_MouseInputData.buttonState[_ButtonNum];	}
		static	LONG		GetMouseAxisX( void ){				return	m_MouseInputData.axisX;						}
		static	LONG		GetMouseAxisY( void ){				return	m_MouseInputData.axisY;						}
		static	LONG		GetMouseAxisZ( void ){				return	m_MouseInputData.axisZ;						}
		static	KEY_STATE	GetKeyState( int _DIKeyCode ){		return	m_KeyBoardInputData.keyState[_DIKeyCode];	}
	};

//********************************************************************************************************************
//		�O���[�o���֐�
//********************************************************************************************************************
	//	�p�b�h�ɂ��J�[�\�����W�X�V
	BOOL	UpdateCursorCoordAtPadAxis( float _AxisThreshold, float _Sensitivity );
	//	�p�b�h���͂ɂ�錈��g���K�[
	bool	GetPadKeyDecision( bool _Moment = true );
	bool	GetPadKeyCancell( void );