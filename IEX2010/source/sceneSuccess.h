#pragma once 
#include    "system\Scene.h"
#include    "system\Framework.h"

class sceneSuccess : public Scene
{
public :
	~sceneSuccess();
    bool Initialize();
    void Update();
    void Render();

private :
	bool Pushed;
    iexView* m_view;
	iex2DObj* m_img;
};

extern Framework*	MainFrame;