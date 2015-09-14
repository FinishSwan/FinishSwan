#pragma once
#include    "iextreme.h"

class BaseObject
{
public: 
    
    virtual bool Update() = 0;
    virtual void Render() = 0;

    inline Vector3 GetPos(){ return pos; }
    inline Vector3 GetAngle(){ return angle; }
    inline Vector3 GetScale(){ return scale; }
    inline Vector3 GetColor(){ return color; }
    inline Vector3 GetVelocity(){ return velocity; }

protected :
    Vector3 pos;
    Vector3 scale;
    Vector3 angle;
    Vector3 color;          //G‚ê‚½‚ÌF
    Vector3 velocity;     //ˆÚ“®î•ñ

};

