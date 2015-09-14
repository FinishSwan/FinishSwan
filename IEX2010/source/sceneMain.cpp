#include	"iextreme.h"
#include	"system/system.h"
#include	"Player.h"
#include	"camera.h"
#include	"Wave.h"
#include	"InputManager.h"
#include   "Fieldobject.h"

#include	"ScrConverter.h"
#include	"sceneMain.h"

#include	"ObjectManager.h"

//*****************************************************************************************************************************
//
//	グローバル変数
//
//*****************************************************************************************************************************
//	カメラ用
iexView*	view;
Camera*		camera;

//	ステージ用
iexMesh* stage = NULL;

//　プレイヤー用
Player*		player = NULL;
Fileobject*  desk = nullptr;
Fileobject*  hondana = nullptr;
Fileobject*  notePC = nullptr;


Wave*		wave = NULL;


//*****************************************************************************************************************************
//
//	初期化
//
//*****************************************************************************************************************************


bool sceneMain::Initialize()
{
	//	環境設定
	//iexLight::SetFog( 1500, 2000, 0xff0080ff );
	iexLight::SetFog( 800, 1000, 0 );

	//	環境光
	Vector3	 dir(-2.0f, -0.5f, 1.0f);
	iexLight::DirLight(0, &dir, 1.0f, 1.0f, 1.0f);
	iexLight::SetAmbient(0x808080);
	

	//	平行光


	//	カメラ設定
	//view = new iexView();
	camera = new Camera();
	camera->SetAngle(Vector3(0.05f, 0.05f, 0.05f));

	//	ステージ読み込み
	stage = new iexMesh("DATA\\BG\\STAGE\\STAGE01.X");
	iex3DObj* insert = new iex3DObj("DATA\\CHR\\ECCMAN\\ECCMAN.IEM");

	//オブジェクト読み込み
	iexMesh* insert_mesh = new iexMesh("DATA\\IMO\\desk.IMO");
	iexMesh* insert_mesh2 = new iexMesh("DATA\\IMO\\hondana.IMO");
	iexMesh* insert_mesh3= new iexMesh("DATA\\IMO\\notePC.IMO");
	

	//オブジェクト初期化
	

	desk = new Fileobject(1,
		0.3,
		Vector3(5, 10, 1),
		Vector3(8, 0, 0),
		Vector3(1, 1, 1),
		Vector3(1, 1, 1),
		insert_mesh);

	hondana = new Fileobject(1,
		0.3,
		Vector3(20, 10, 30),
		Vector3(70, 0, 0),
		Vector3(1, 1, 1),
		Vector3(1, 1, 1),
		insert_mesh2);

	notePC = new Fileobject(1,
		0.3,
		Vector3(-20, 10, 0),
		Vector3(0, 0, 0),
		Vector3(1, 1, 1),
		Vector3(1, 1, 1),
		insert_mesh3);

	//	プレイヤー初期化
	player = new Player(1,
		0.3,
		Vector3(90.1783905, 0, 0),
		Vector3(0, 0, 0),
		Vector3(0.05f, 0.05f, 0.05f),
		Vector3(1, 1, 1),
		insert);
	
	//波初期化
	wave = new Wave();

	//	敵初期化

	obj_manager.Initialize();


	
	obj_manager.InsertObject(player);
	obj_manager.InsertObject(desk);
	obj_manager.InsertObject(hondana);
	obj_manager.InsertObject(notePC);
	
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

}

//*****************************************************************************************************************************
//
//		更新
//
//*****************************************************************************************************************************


void	sceneMain::Update()
{
	//	カメラ更新
	Vector3 p =obj_manager.GetPlayer()->GetPos() + Vector3(0,7,0);
	camera->SetTarget(p);
	camera->Update();

	//desk->Update();

	//	プレイヤー更新
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

	//球判定
	//obj_manager.Collision_of_Sphere(obj_manager.GetPlayer(),&out_d,&out);

	//RayPick
	Vector3 m(0, 0, 0);
	BaseObjct* test = obj_manager.Collision_of_RayPick(&out, &pos, &vec, &out_d, obj_manager.GetPlayer());


	if (InputManager::GetMouseButton(0) == KEY_STATE_PRESSED)
	{
		//wave->Start_Wave(player->GetPos() + Vector3(0, 4, 0), Vector3(sinf(player->GetAngle().y), .0f, cosf(player->GetAngle().y)));
		wave->Start_Wave(camera->GetPos(), camera->GetForward());
	}
		
	
	//波更新
	wave->Update();
	//	敵更新

	InputManager::Update();
	
	//SetCursorPos(100, 200);

}

//*****************************************************************************************************************************
//
//		描画関連
//
//*****************************************************************************************************************************

void	sceneMain::Render()
{
	//	画面クリア
	camera->Activate();
	camera->Clear(0xFFFFFFFF);
	shader->SetValue("ViewPos", camera->GetPos());

	//	ステージ描画
	if (!wave->IsRender(stage))
		stage->Render(shader, "white");

	//オブジェクト描画
	//desk->Render();

	//	プレイヤー描画
	/*player->Render();*/

	obj_manager.Render();
	//波描画
	wave->Render();

}