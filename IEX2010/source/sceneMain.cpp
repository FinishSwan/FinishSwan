#include	"iextreme.h"
#include	"system/system.h"
#include	"Player.h"
#include	"camera.h"

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
//		更新
//
//*****************************************************************************************************************************


void	sceneMain::Update()
{
	//	カメラ更新
	Vector3 p = player->GetPos();
	camera->SetTarget(p);
	camera->Update();

	//	プレイヤー更新
	Vector3 cp = camera->GetPos();
	Vector3 ct = camera->GetTarget();
	player->Move(cp,ct);
	player->Update();

	

	//	敵更新
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
	camera->Clear();

	//	ステージ描画
	stage->Render();

	//	プレイヤー描画
	player->Render();

	//	敵描画

}



