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
#include	"ScaleManager.h"



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
Fileobject* lpstage = nullptr;
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
	iexLight::SetFog(800, 1000, 0);

	//	����
	Vector3	 dir(-2.0f, -0.5f, 1.0f);
	iexLight::DirLight(0, &dir, 1.0f, 1.0f, 1.0f);
	iexLight::SetAmbient(0x808080);


	//	���s��

	obj_manager.Initialize();

	//	�X�e�[�W�ǂݍ���z
	iexMesh* stage = new iexMesh("DATA\\IMO\\new_room.IMO");
	//�v���C���[�ǂݍ���
	iex3DObj* insert = new iex3DObj("DATA\\CHR\\ECCMAN\\ECCMAN.IEM");
		lpstage = new Fileobject(1,
		0.3,
		Vector3(0, -6, 0),
		Vector3(0, 0, 0),
		Vector3(1, 1, 1),
		Vector3(1.5, 1.5, 1.5),
		BaseObjct::TYPE::judge,
		stage);

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
	obj_manager.InsertObject(player);
	obj_manager.InsertObject(ball);
	//	�J�����ݒ�
	//view = new iexView();
	camera = new Camera();
	camera->SetAngle(Vector3(0.05f, 0.05f, 0.05f));

	FadeManager::FadeOut(1.0f);

	EntryPoint::Initialize();

	//�I�u�W�F�N�g�̈ʒu����
	Vector3 pos[7] =
	{
		Vector3(23.74, 0, 24.04),
		Vector3(-26.74, 0, 29.26),
		Vector3(-30.88, 0, -29.46),
		Vector3(29.85, 0, -29.35),
		Vector3(-1.02, 0, -9.32),
		Vector3(23.42, 0, 0.51),
		Vector3(0.66, 0, 25.31),
	};
	//��������
	Vector3 angle[7] =
	{
		Vector3(0, 0, 0),
		Vector3(0, 0, 0),
		Vector3(0, 0, 0),
		Vector3(0, 0, 0),
		Vector3(0, 0, 0),
		Vector3(0, 0, 0),
		Vector3(0, 0, 0),
	};

	for (int i = 0; i < 7; i++)
	{
		EntryPoint::Register(pos[i], angle[i]);
	}



	//�X�P�[���ݒ�
	char* filename[8] =
	{
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
		0.08f,
		3.0f,
		0.85f,
		0.1f,
		0.2f,
		0.15f,
		0.1f,
		0.005f,
	};
	for (int i  = 0; i < 8; i++)
	{
		ScaleManager::Register(filename[i], scale[i]);
	}
	for (int i = 0; i < 8; i++)
	{
		ScaleManager::GetScale(filename[i]);
	}

	//�I�u�W�F�N�g�ǂݍ���
	for (int i = 0; i < 7; i++)
	{
		Vector3 p, s;
		EntryPoint::GetPoint(&p, &s);
		iexMesh* insert_mesh = new iexMesh(filename[i]);
		Fileobject* insert_obj = new Fileobject(1, 0.3,
			p,
			angle[i],
			scale[i],
			Vector3(1, 1, 1),
			BaseObjct::judge,
			insert_mesh);

		obj_manager.InsertObject(insert_obj);

	}





	//�{�[���ǂݍ���
	iexMesh* insert_ball = new iexMesh("DATA\\IMO\\Ball.IMO");

	//�I�u�W�F�N�g�ǂݍ���
	//	//iexMesh* insert_mesh = new iexMesh("DATA\\IMO\\desk.IMO");
	//    iexMesh* insert_mesh = new iexMesh("DATA\\BG\\stage\\stage01.x");
	//	iexMesh* insert_mesh2 = new iexMesh("DATA\\IMO\\tana.IMO");
	////	iexMesh* insert_mesh3= new iexMesh("DATA\\IMO\\notePC.IMO");



	//�I�u�W�F�N�g������
	/*desk = new Fileobject(1,
		0.3,
		Vector3(5, 0, 0),
		Vector3(0, 0, 0),
		Vector3(1, 1, 1),
		Vector3(1, 1, 1),
		BaseObjct::TYPE::judge,1
		insert_mesh);*/

	//�X�e�[�W


	ball = new Ball(1,
		0.3,
		Vector3(0, 0, 0),
		Vector3(0, 0, 0),
		Vector3(0.05f, 0.05f, 0.05f),
		Vector3(1, 1, 1), BaseObjct::TYPE::judge,
		insert_ball);


	//�g������
	wave = new Wave();

	//	�G������





	//obj_manager.InsertObject(desk);
	obj_manager.InsertObject(lpstage);
	//obj_manager.InsertObject(notePC);


	//EntryPoint::Initialize();

	//EntryPoint::Register(desk->GetPos(),desk->GetAngle());
	//Vector3 desk_pos(0,0,0);
	//Vector3 desk_angle(0,0,0);
	//EntryPoint::GetPoint(&desk_pos,&desk_angle);


	iexParticle::Initialize("DATA\\particle2.png", 1000);

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
	Vector3 p = obj_manager.GetPlayer()->GetPos() + Vector3(0, 5, 0);
	camera->SetTarget(p);
	camera->Update();

	//desk->Update();

	//	�v���C���[�X�V
	Vector3 forward(sinf(player->GetAngle().y), .0f, cosf(player->GetAngle().y));
	if (KEY_Get(KEY_B) == 3)
		ball->Ball_Start(player->GetPos() + Vector3(0, 7, 0), forward * 3.0f);

	obj_manager.Update();

	Vector3 out;
	Vector3 pos = obj_manager.GetPlayer()->GetPos();
	pos.y += 0.5;
	Vector3 angle = obj_manager.GetPlayer()->GetAngle();
	Vector3 vec = Vector3(sinf(angle.y), 0, cosf(angle.y));
	vec.Normalize();
	float out_d = 100;



	//������
	//obj_manager.Collision_of_Sphere(obj_manager.GetPlayer(),&out_d,&out);

	//RayPick
	Vector3 m(0, 0, 0);
	BaseObjct* test = obj_manager.Collision_of_RayPick(&out, &pos, &vec, &out_d, obj_manager.GetPlayer());

	/*if (InputManager::GetMouseButton(0) == KEY_STATE_PRESSED)
	{
	wave->Start_Wave(camera->GetPos(), camera->GetForward());
	}*/



	//�g�X�V
	wave->Update();
	//	�G�X�V

	InputManager::Update();

	//SetCursorPos(100, 200);
	iexParticle::Update();

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
	camera->Clear(/*0xFFFFFFFF*/);
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

	iexParticle::Render(shader2D, "copy");

	Vector3 p = obj_manager.GetPlayer()->GetPos();


	/*char	str[128];
	sprintf(str, "x %03f : y %03f : z %03f", p.x, p.y, p.z);
	IEX_DrawText(str, 10, 10, 400, 20, 0xFF000000);*/
}