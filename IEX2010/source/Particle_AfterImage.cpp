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
        0,                     //�o���t���[��
		0xFF888888,  //�o�������_�J���[
        100,                  //���ł܂ł̃t���[��
		0xFF888888, //���Ŏ��̒��_�J���[
        50,                 //���ԃt���[��
        0xFF888888,//���ԃt���[�����_�J���[
        &pos,
        &move,
        &power,
        .0f,                //�t���[�����Ƃ̉�]���
        0.98,                  //�t���[�����Ƃ̃X�P�[�����O(��Z  
        0.25,              //�����X�P�[��
        RS_COPY);
}
