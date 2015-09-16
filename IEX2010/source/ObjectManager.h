#pragma once
#include	"Singleton.h"
#include	"BaseObj.h"
class BaseObjct;

#define MAX_OBJECT 10
enum BaseObjct::TYPE;

class ObjectManager : public Singleton<ObjectManager>
{
private :
	BaseObjct* m_object_array[MAX_OBJECT];	//この配列ですべてのオブジェクトのインスタンスを管理する
    BaseObjct* m_answer_object;
    int                m_num_register;

    bool DecisionAnswerObject();

public :
	ObjectManager(){}
	~ObjectManager();
	void Initialize();
	void Release();
	
	void Update();
	void Render();

	bool InsertObject(BaseObjct* insert);
	BaseObjct* GetPlayer(){ return m_object_array[0]; }
	
	BaseObjct* Collision_of_RayPick(Vector3* out, Vector3* pos, Vector3* vec, float *Dist3,
		BaseObjct* owner_object,BaseObjct::TYPE check_type = BaseObjct::TYPE::judge);

	BaseObjct* Collision_of_Sphere(BaseObjct* owner_object,float* ret_merikomi,Vector3* ret_merikomi_vec);

	void AllPaint(BaseObjct* owner_object);

    bool    PlacementAllObject();
    bool    Is_AnswerObject(const BaseObjct* object);
	BaseObjct* GetAnswerObject(){ return m_answer_object; }

};

#define obj_manager (ObjectManager::GetInstance())
