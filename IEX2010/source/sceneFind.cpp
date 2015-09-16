#include    "iextreme.h"
#include    "sceneFind.h"
#include    "sceneMain.h"

#include	"system/system.h"

#include	"ObjectManager.h"

#include	"Fade.h"

iexMesh* mesh;

sceneFind::~sceneFind()
{
    delete m_view;
	delete m_img;
}

bool sceneFind::Initialize()
{
    m_view = new iexView();
	m_img = new iex2DObj("DATA\\BG\\find.png");
	mesh = new iexMesh("DATA\\BG\\stage\\stage01.x");
	Pushed = false;
	iexLight::DirLight(0, &Vector3(0,0,1), 1.0f, 1.0f, 1.0f);
	iexLight::SetFog(800, 1000, 0);
	FadeManager::FadeOut(1.0f);
    return true;
}

void sceneFind::Update()
{	

	if (!Pushed)
	{
		if (KEY_Get(KEY_SPACE) == 3)
		{
			Pushed = true;
			FadeManager::FadeIn(1.5f);
		}
	}
	m_view->Set(Vector3(10, 30, -20), Vector3(0, 10, 0));

	if (Pushed && FadeManager::IsFadeEnd())
	{
		MainFrame->ChangeScene(new sceneMain());
	}

}

void sceneFind::Render()
{
	m_view->Activate();
    m_view->Clear();
	
	iexMesh* mesh = obj_manager.GetAnswerObject()->getMesh();

	mesh->SetPos(0, 0, 0);

	mesh->SetScale(obj_manager.GetAnswerObject()->GetScale());

	mesh->Update();
	
	m_img->Render(0, 0, 1280, 720, 0, 0, 1280, 720);

	m_view->ClearZ();


	shader->SetValue("Color", Vector3(0.5f, 0.5f, 0.5f));
	mesh->Render();
}

