#include    "iextreme.h"
#include    "sceneSuccess.h"
#include    "sceneMain.h"
#include    "sceneTitle.h"

#include	"Fade.h"


sceneSuccess::~sceneSuccess()
{
    delete m_view;
	delete m_img;
}

bool sceneSuccess::Initialize()
{
    m_view = new iexView();
	m_img = new iex2DObj("DATA\\BG\\success.png");
	Pushed = false;
	m_view->Set(Vector3(0, 500, -500), Vector3(0, 0, 0));
	iexLight::DirLight(0, &Vector3(0,0,1), 1.0f, 1.0f, 1.0f);
	iexLight::SetFog(800, 1000, 0);
	FadeManager::FadeOut(1.0f);
    return true;
}

void sceneSuccess::Update()
{
	if (!Pushed)
	{
		if (KEY_Get(KEY_SPACE) == 3)
		{
			Pushed = true;
			FadeManager::FadeIn(1.5f);
		}
	}

	if (Pushed && FadeManager::IsFadeEnd())
	{
		MainFrame->ChangeScene(new sceneTitle());
	}
}

void sceneSuccess::Render()
{
	//m_view->Activate();
	m_view->Clear();
	
	m_img->Render(0, 0, 1280, 720, 0, 0, 1280, 720);
}

