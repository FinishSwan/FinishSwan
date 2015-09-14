#include    "iextreme.h"
#include    "sceneTitle.h"
#include    "sceneMain.h"

sceneTitle::~sceneTitle()
{
    delete m_view;
}

bool sceneTitle::Initialize()
{
    m_view = new iexView();
    return true;
}

void sceneTitle::Update()
{

    if (KEY_Get(KEY_SPACE) == 3)
    {
        MainFrame->ChangeScene(new sceneMain());
    }
}

void sceneTitle::Render()
{
    m_view->Clear(0xFFFFF000);
}

