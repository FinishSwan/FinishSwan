#include	"iextreme.h"
#include	"system/system.h"
#include	"Player.h"
#include	"camera.h"
#include	"Wave.h"
#include	"BallObj.h"
#include	"InputManager.h"
#include   "Fieldobject.h"
#include	"Fade.h"

#include	"ScrConverter.h"
#include	"sceneMain.h"

#include	"ObjectManager.h"

#include	"EntryPoint.h"

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
Fileobject*  desk = nullptr;
Fileobject*  hondana = nullptr;
Fileobject*  notePC = nullptr;

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

	FadeManager::FadeOut(1.0f);

	//	�X�e�[�W�ǂݍ���
	stage = new iexMesh("DATA\\BG\\STAGE\\STAGE01.X");
	iex3DObj* insert = new iex3DObj("DATA\\CHR\\ECCMAN\\ECCMAN.IEM");

	iexMesh* insert_ball = new iexMesh("DATA\\IMO\\Ball.IMO");

	//�I�u�W�F�N�g�ǂݍ���
	//iexMesh* insert_mesh = new iexMesh("DATA\\IMO\\desk.IMO");
    iexMesh* insert_mesh = new iexMesh("DATA\\BG\\stage\\stage01.x");
	iexMesh* insert_mesh2 = new iexMesh("DATA\\IMO\\table_kai.IMO");
//	iexMesh* insert_mesh3= new iexMesh("DATA\\IMO\\notePC.IMO");
	

	//�I�u�W�F�N�g������
	

	desk = new Fileobject(1,
		0.3,
		Vector3(5, 0, 0),
		Vector3(0, 0, 0),
		Vector3(1, 1, 1),
		Vector3(1, 1, 1),
		BaseObjct::TYPE::judge,
		insert_mesh);


	hondana = new Fileobject(1,
		0.3,
		Vector3(2, 1, 3),
		Vector3(0, 0, 0),
		Vector3(1, 1, 1),
		Vector3(1, 1, 1),
		BaseObjct::TYPE::judge,
		stage);

	//notePC = new Fileobject(1,
	//	0.3,
	//	Vector3(-20, 10, 0),
	//	Vector3(0, 0, 0),
	//	Vector3(1, 1, 1),
	//	Vector3(1, 1, 1),
	//	insert_mesh3);

	//	�v���C���[������
	player = new Player(1,
		0.3,
		//Vector3(90.1783905, 0, 0)
		Vector3(0, 0, 0),
		Vector3(0, 0, 0),
		Vector3(0.05f, 0.05f, 0.05f),
		Vector3(1, 1, 1),
		BaseObjct::TYPE::player,
		insert);

	ball = new Ball(1,
		0.3,
		Vector3(0, 0, 0),
		Vector3(0, 0, 0),
		Vector3(0.05f, 0.05f, 0.05f),
		Vector3(1, 1, 1),BaseObjct::TYPE::judge,
		insert_ball);
	
	
	EntryPoint::Initialize();

	Vector3 pos[10] =
	{
		Vector3(0, 0, 0),
		Vector3(1, 0, 0),
		Vector3(2, 0, 0),
		Vector3(3, 0, 0),
		Vector3(4, 0, 0),
		Vector3(5, 0, 0),
		Vector3(6, 0, 0),
		Vector3(7, 0, 0),
		Vector3(8, 0, 0),
		Vector3(9, 0, 0),
	};

		Vector3 angle[10] =
	{
		Vector3(0, 0, 0),
		Vector3(1, 0, 0),
		Vector3(2, 0, 0),
		Vector3(3, 0, 0),
		Vector3(4, 0, 0),
		Vector3(5, 0, 0),
		Vector3(6, 0, 0),
		Vector3(7, 0, 0),
		Vector3(8, 0, 0),
		Vector3(9, 0, 0),
	};

		for (int i = 0; i < 10; i++)
		{
			EntryPoint::Register(pos[i], angle[i]);
		}


		
		for (int i = 0; i < 10; i++)
		{
			Vector3 p, a;
			EntryPoint::GetPoint(&p, &a);
			Vector3 temp;
			temp = p;
			temp = a;

		}

	//�g������
	wave = new Wave();

	//	�G������

	obj_manager.Initialize();

	obj_manager.InsertObject(player);
	obj_manager.InsertObject(ball);

	//obj_manager.InsertObject(desk);
	obj_manager.InsertObject(hondana);
	//obj_manager.InsertObject(notePC);


	EntryPoint::Initialize();

	//EntryPoint::Register(desk->GetPos(),desk->GetAngle());
	//Vector3 desk_pos(0,0,0);
	//Vector3 desk_angle(0,0,0);
	//EntryPoint::GetPoint(&desk_pos,&desk_angle);
	

	iexParticle::Initialize("DATA\\particle.png", 1000);

	return true;
}

sceneMain::~sceneMain()
{
	obj_manager.Release();
	delete camera;
	delete stage;
	delete wave;
	iexParticle::Release();
	EntryPoint::Release();

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

	//desk->Update();

	//	�v���C���[�X�V
	Vector3 forward(sinf(player->GetAngle().y), .0f, cosf(player->GetAngle().y));
	if (KEY_Get(KEY_B)==3)
		ball->Ball_Start(player->GetPos() + Vector3(0, 7, 0), forward * 3.0f);

	obj_manager.Update();

	Vector3 out;
	Vector3 pos = obj_manager.GetPlayer()->GetPos();
	pos.y += 0.5;
	Vector3 angle = obj_manager.GetPlayer()->GetAngle();
	Vector3 vec = Vector3(sinf(angle.y), 0, cosf(angle.y));
	vec.Normalize();
	float out_d=100;

	if (KEY_Get(KEY_A))
		iexParticle::Update();

	//������
	//obj_manager.Collision_of_Sphere(obj_manager.GetPlayer(),&out_d,&out);

	//RayPick
	Vector3 m(0, 0, 0);
	BaseObjct* test = obj_manager.Collision_of_RayPick(&out, &pos, &vec, &out_d, obj_manager.GetPlayer());

	//if (InputManager::GetMouseButton(0) == KEY_STATE_PRESSED)
	//{
		//wave->Start_Wave(camera->GetPos(), camera->GetForward());
	//}
		


	//�g�X�V
	wave->Update();
	//	�G�X�V

	InputManager::Update();
	
	//SetCursorPos(100, 200);

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
	//if (!wave->IsRender(stage))
	//	stage->Render(shader, "white");

	//�I�u�W�F�N�g�`��
	//desk->Render();

	//	�v���C���[�`��
	/*player->Render();*/

	obj_manager.Render();
	//�g�`��
	wave->Render();

}