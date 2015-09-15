#include    "iextreme.h"
#include    "Player.h"
#include    "CP11Rand.h"

void    Particle_AfterImage::Execute(const Vector3& position,Vector3 owner_velocity)
{
    if (owner_velocity.LengthSq() < 0.01f)
        return;
    Vector3 move(0, 0, 0);
    Vector3 power(0, 0, 0);
    Vector3 pos = position;
    Vector3 adjust(
        10.0f *  (float)(RandomEngine::Execute(0, 0xFFFF)) / 0xFFFF - 5.0f,
        10.0f *  (float)(RandomEngine::Execute(0, 0xFFFF)) / 0xFFFF - 5.0f,
        10.0f *  (float)(RandomEngine::Execute(0, 0xFFFF)) / 0xFFFF - 5.0f);

    pos += adjust;
    iexParticle::Set(
        6,                      //type
        0,                     //�o���t���[��
        0x00FFFFFF,  //�o�������_�J���[
        100,                  //���ł܂ł̃t���[��
        0x00FFFFFF, //���Ŏ��̒��_�J���[
        50,                 //���ԃt���[��
        0xAAFFFFFF,//���ԃt���[�����_�J���[
        &pos,
        &move,
        &power,
        .0f,                //�t���[�����Ƃ̉�]���
        0.9,                  //�t���[�����Ƃ̃X�P�[�����O(��Z  
        4,              //�����X�P�[��
        RS_COPY);
}
