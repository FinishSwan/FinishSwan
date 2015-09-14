#include	"iextreme.h"
#include	"system/system.h"
#include	"Player.h"
#include	"camera.h"
#include	"Wave.h"
#include	"InputManager.h"

#include	"ScrConverter.h"
#include	"sceneMain.h"

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


	//	プレイヤー初期化
	player = new Player();
	player->Init("DATA\\CHR\\ECCMAN\\ECCMAN.IEM");
	player->SetPos(Vector3(0.0f, 0.0f, 0.0f));//位置決定
	player->SetScale(Vector3(0.05f, 0.05f, 0.05f));//スケール設定
	player->SetAngle(Vector3(0.05f, 0.05f, 0.05f));//向き

	//	敵初期化

	//波初期化
	wave = new Wave();


	return true;
}

sceneMain::~sceneMain()
{
	delete camera;
	delete player;
	delete stage;
	delete wave;

}

//*****************************************************************************************************************************
//
//		更新
//
//*****************************************************************************************************************************


void	sceneMain::Update()
{
	//	カメラ更新
	Vector3 p = player->GetPos() + Vector3(0,7,0);
	camera->SetTarget(p);
	camera->Update();

	//	プレイヤー更新
	Vector3 cp = camera->GetPos();
	Vector3 ct = camera->GetTarget();
	player->Move(cp,ct);
	player->Update();

	if (InputManager::GetMouseButton(0) == KEY_STATE_PRESSED)
	{
		//wave->Start_Wave(player->GetPos() + Vector3(0, 4, 0), Vector3(sinf(player->GetAngle().y), .0f, cosf(player->GetAngle().y)));
		wave->Start_Wave(camera->GetPos(), camera->GetForward());
	}
		
	
	//波更新
	wave->Update();
	//	敵更新

	InputManager::Update();

	SetCursorPos(100, 200);

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

	//	プレイヤー描画
	player->Render();


	//波描画
	wave->Render();
	//	敵描画

}



