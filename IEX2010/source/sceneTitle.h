#pragma once 
#include    "system\Scene.h"
#include    "system\Framework.h"

class sceneTitle : public Scene
{
public :
    ~sceneTitle();
    bool Initialize()override;
    void Update()override;
    void Render()override;

private :
    iexView* m_view;
};

extern Framework*	MainFrame;