#include	"iextreme.h"
#include	"system/system.h"
#include	"Player.h"
#include	"camera.h"
#include	"Wave.h"
#include	"BallObj.h"
#include	"InputManager.h"

#include	"ScrConverter.h"
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

Ball*		ball = NULL;

Wave*		wave = NULL;


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

	iexMesh* insert_ball = new iexMesh("DATA\\IMO\\Ball.IMO");

	//	�v���C���[������
	player = new Player(1,
		0.3,
		Vector3(0, 0, 0),
		Vector3(0, 0, 0),
		Vector3(0.05f, 0.05f, 0.05f),
		Vector3(1, 1, 1),
		insert);

	ball = new Ball(1,
		0.3,
		Vector3(0, 0, 0),
		Vector3(0, 0, 0),
		Vector3(0.05f, 0.05f, 0.05f),
		Vector3(1, 1, 1),
		insert_ball);
	//player->Init("DATA\\CHR\\ECCMAN\\ECCMAN.IEM");
	//player->SetPos(Vector3(10.0f, 0.0f, 0.0f));//�ʒu����
	//player->SetScale(Vector3(0.05f, 0.05f, 0.05f));//�X�P�[���ݒ�
	//player->SetAngle(Vector3(0.05f, 0.05f, 0.05f));//����

	//�g������
	wave = new Wave();

	//	�G������

	obj_manager.Initialize();


	
	obj_manager.InsertObject(player);
	obj_manager.InsertObject(ball);

	return true;
}

sceneMain::~sceneMain()
{
	obj_manager.Release();
	delete camera;
	//delete player;
	delete stage;
	delete wave;

}

//*****************************************************************************************************************************
//
//		�X�V
//
//*****************************************************************************************************************************


void	sceneMain::Update()
{
	//	�J�����X�V
	Vector3 p =obj_manager.GetPlayer()->GetPos() + Vector3(0,7,0);
	camera->SetTarget(p);
	camera->Update();

	//	�v���C���[�X�V
	Vector3 cp = camera->GetPos();
	Vector3 ct = camera->GetTarget();
	player->Move(cp,ct);

	Vector3 forward(sinf(player->GetAngle().y), .0f, cosf(player->GetAngle().y));
	if (KEY_Get(KEY_B)==3)
		ball->Ball_Start(player->GetPos() + Vector3(0, 7, 0), forward * 3.0f);

	obj_manager.Update();

	if (InputManager::GetMouseButton(0) == KEY_STATE_PRESSED)
	{
		//wave->Start_Wave(player->GetPos() + Vector3(0, 4, 0), Vector3(sinf(player->GetAngle().y), .0f, cosf(player->GetAngle().y)));
		wave->Start_Wave(camera->GetPos(), camera->GetForward());
	}
		


	//�g�X�V
	wave->Update();
	//	�G�X�V

	InputManager::Update();

	SetCursorPos(100, 200);

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
	camera->Clear(0xFFFFFFFF);
	shader->SetValue("ViewPos", camera->GetPos());

	//	�X�e�[�W�`��
	if (!wave->IsRender(stage))
		stage->Render(shader, "white");

	//	�v���C���[�`��
	/*player->Render();*/

	obj_manager.Render();
	//�g�`��
	wave->Render();
	//	�G�`��

}



