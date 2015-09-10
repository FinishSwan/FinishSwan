#include	"iextreme.h"
#include	"system/system.h"
#include	"Player.h"
#include	"camera.h"

#include	"sceneMain.h"

#include	"ObjectManager.h"

//*****************************************************************************************************************************
//
//	�O���[�o���ϐ�
//
//*****************************************************************************************************************************
//	�J�����p
iexView*	view;
Camera*		camera;

//	�X�e�[�W�p
iexMesh* stage = NULL;

//�@�v���C���[�p
Player*		player = NULL;


//*****************************************************************************************************************************
//
//	������
//
//*****************************************************************************************************************************

bool sceneMain::Initialize()
{
	//	���ݒ�
	//iexLight::SetFog( 1500, 2000, 0xff0080ff );
	iexLight::SetFog( 800, 1000, 0 );

	//	����
	Vector3	 dir(-2.0f, -0.5f, 1.0f);
	iexLight::DirLight(0, &dir, 1.0f, 1.0f, 1.0f);
	iexLight::SetAmbient(0x808080);
	

	//	���s��


	//	�J�����ݒ�
	//view = new iexView();
	camera = new Camera();
	camera->SetAngle(Vector3(0.05f, 0.05f, 0.05f));

	//	�X�e�[�W�ǂݍ���
	stage = new iexMesh("DATA\\BG\\STAGE\\STAGE01.X");

	iex3DObj* insert = new iex3DObj("DATA\\CHR\\ECCMAN\\ECCMAN.IEM");

	//	�v���C���[������
	player = new Player(1,
		0.3,
		Vector3(0, 0, 0),
		Vector3(0, 0, 0),
		Vector3(1, 1, 1),
		Vector3(1, 1, 1),
		insert);
	//player->Init("DATA\\CHR\\ECCMAN\\ECCMAN.IEM");
	//player->SetPos(Vector3(10.0f, 0.0f, 0.0f));//�ʒu����
	//player->SetScale(Vector3(0.05f, 0.05f, 0.05f));//�X�P�[���ݒ�
	//player->SetAngle(Vector3(0.05f, 0.05f, 0.05f));//����

	//	�G������

	obj_manager.Initialize();

	return true;
}

sceneMain::~sceneMain()
{
	delete camera;
	delete player;
	delete stage;

}

//*****************************************************************************************************************************
//
//		�X�V
//
//*****************************************************************************************************************************


void	sceneMain::Update()
{
	//	�J�����X�V
	Vector3 p = player->GetPos();
	camera->SetTarget(p);
	camera->Update();

	//	�v���C���[�X�V
	Vector3 cp = camera->GetPos();
	Vector3 ct = camera->GetTarget();
	player->Move(cp,ct);
	player->Update();

	

	//	�G�X�V
}

//*****************************************************************************************************************************
//
//		�`��֘A
//
//*****************************************************************************************************************************

void	sceneMain::Render()
{
	//	��ʃN���A
	camera->Activate();
	camera->Clear();

	//	�X�e�[�W�`��
	stage->Render();

	//	�v���C���[�`��
	player->Render();

	//	�G�`��

}



