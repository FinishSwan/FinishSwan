#pragma once 
#include    "system\Scene.h"
#include    "system\Framework.h"

class sceneTitle : public Scene
{
public :
    ~sceneTitle();
    bool Initialize();
    void Update();
    void Render();

private :
	bool Pushed;
    iexView* m_view;
	iex2DObj* m_title;
};

extern Framework*	MainFrame;