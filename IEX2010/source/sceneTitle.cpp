#include    "iextreme.h"
#include    "sceneTitle.h"
#include    "sceneFind.h"
#include    "sceneMain.h"

#include	"Fade.h"


sceneTitle::~sceneTitle()
{
    delete m_view;
	delete m_title;
}

bool sceneTitle::Initialize()
{
    m_view = new iexView();
	m_title = new iex2DObj("DATA\\BG\\title.png");
	Pushed = false;
	m_view->Set(Vector3(0, 500, -500), Vector3(0, 0, 0));
	iexLight::DirLight(0, &Vector3(0,0,1), 1.0f, 1.0f, 1.0f);
	iexLight::SetFog(800, 1000, 0);
	FadeManager::FadeOut(1.0f);
    return true;
}

void sceneTitle::Update()
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
		MainFrame->ChangeScene(new sceneFind());
	}
}

void sceneTitle::Render()
{
	//m_view->Activate();
    //m_view->Clear(0xFFFFFFFF);
	
	m_title->Render(0, 0, 1280, 720, 0, 0, 1280, 720);
}

