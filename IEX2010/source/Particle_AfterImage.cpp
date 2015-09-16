#include    "iextreme.h"
#include    "Player.h"
#include    "CP11Rand.h"

void    Particle_AfterImage::Execute(const Vector3& position,Vector3 owner_velocity)
{
    if (owner_velocity.LengthSq() < 0.01f)
        return;
    Vector3 move(0, 0.03, 0);
    Vector3 power(0, 0, 0);
    Vector3 pos = position;
    Vector3 adjust(
        3.0f *  (float)(RandomEngine::Execute(0, 0xFFFF)) / 0xFFFF - 2.5f,
		8.0f *  (float)(RandomEngine::Execute(0, 0xFFFF)) / 0xFFFF - 8.0f,
		3.0f *  (float)(RandomEngine::Execute(0, 0xFFFF)) / 0xFFFF - 2.5f);

    pos += adjust;
    iexParticle::Set(
        10,                      //type
        0,                     //出現フレーム
		0xFF888888,  //出現時頂点カラー
        100,                  //消滅までのフレーム
		0xFF888888, //消滅時の頂点カラー
        50,                 //中間フレーム
        0xFF888888,//中間フレーム頂点カラー
        &pos,
        &move,
        &power,
        .0f,                //フレームごとの回転情報
        0.98,                  //フレームごとのスケーリング(乗算  
        0.25,              //初期スケール
        RS_COPY);
}
