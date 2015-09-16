#include	"iextreme.h"
#include	"BaseObj.h"
#include	"ObjectManager.h"
#include	"Wave.h"
#include	"EntryPoint.h"
#include    "Fieldobject.h"
#include	<vector>
#include	<list>
#include    "ScaleManager.h"
#include    "CP11Rand.h"
#include    <assert.h>
#include    "Player.h"

void	ObjectManager::Initialize()
{
	ZeroMemory(m_object_array, sizeof(BaseObjct*)* MAX_OBJECT);
    m_num_register = 0;
	m_answer_object = nullptr;
}

void	ObjectManager::Release()
{
    for (auto it : m_object_array)
    {
        if (it)
        {
            delete it;
            it = nullptr;
        }
    }

}


bool	ObjectManager::InsertObject(BaseObjct* insert)
{

	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (!m_object_array[i])
		{
			m_object_array[i] = insert;
            m_num_register++;
			return true;
		}
	}

	return false;

}

BaseObjct* ObjectManager::Collision_of_RayPick(Vector3* out, Vector3* pos, Vector3* vec, float *Dist3,
	BaseObjct* owner_object,BaseObjct::TYPE check_type)
{

	float most_near = FLT_MAX;
	BaseObjct* ret_object = nullptr;
	Vector3 ret_position;
	Vector3 ret_noraml;
	float ret_dist;
	for (auto& current_obj : m_object_array)
	{

		if (current_obj == nullptr)
			continue;

		if (current_obj == owner_object)
			continue;

		if (!current_obj->IsType(check_type))
			continue;

		Vector3 start_pos = *pos;
		Vector3 ray_vec = *vec;
		float dist = *Dist3;

		if (current_obj->RayPick(out, &start_pos, &ray_vec, &dist) != -1)
		{
			if (most_near > dist)
			{
				ret_object = current_obj;
				most_near = dist;
				ret_position = *out;
				ret_noraml = ray_vec;
				ret_dist = dist;
			}
		}
	}
	if (ret_object)
		ret_object->Collision(ret_position, owner_object);
	*out = ret_position;
	*vec = ret_noraml;
	*Dist3 = ret_dist;

	return ret_object;

}

BaseObjct* ObjectManager::Collision_of_Sphere(BaseObjct* owner_object, float* ret_merikomi,
	Vector3* ret_merikomi_vec)
{
	BaseObjct* ret_obj = nullptr;
	//float merikomi = *ret_merikomi;
	float radius = owner_object->GetRadius();//あたり判定の半径のゲッター
	Vector3 owner_object_pos = owner_object->GetPos();//objのゲッター
	owner_object_pos.y += owner_object->GetAdjust_height();//
	Vector3 merikomi_vec = *ret_merikomi_vec;

	for (auto& cullent_object : m_object_array)
	{
		if (cullent_object == nullptr)
			continue;

		if (cullent_object == owner_object)
			continue;

		Vector3 cullent_object_pos = owner_object->GetPos();
		cullent_object_pos.y += owner_object->GetAdjust_height();

		//XYZの計算
		Vector3 d;
		d.x = cullent_object_pos.x - owner_object_pos.x;
		d.y = cullent_object_pos.y - owner_object_pos.y;
		d.z = cullent_object_pos.z - owner_object_pos.z;

		//半径の計算
		float r = cullent_object->GetRadius();
	 	float dist = d.Length();
		float r1;
		r1 = radius + r;
		float two_radius = sqrtf(r1 * r1);
		if(dist <= two_radius)
		{
			ret_obj = cullent_object;
			*ret_merikomi = two_radius - dist;
			d.Normalize();
			*ret_merikomi_vec = d;
		}

	}
	return ret_obj;
}

void	ObjectManager::Update()
{
	for (auto& it : m_object_array)
	{
		if (!it)
			continue;
		it->Base_Update();
	}
}

void	ObjectManager::Render()
{
	
	for (auto& it : m_object_array)
	{
		if (!it)
			continue;
		if(!wave->IsRender(it))
			it->Render();
	}

}

void	ObjectManager::AllPaint(BaseObjct* owner_object)
{
	for (auto& it : m_object_array)
	{
		if (it == nullptr)
			continue;
	
		if (it == owner_object)
			continue;

		if (it->IsPainted())
			continue;

		it->Paint_Start(owner_object->GetPos());

	}

	
}

#define SAFE_DELETE(x)if(x) delete x; x = nullptr;

bool ObjectManager::PlacementAllObject()
{
    if (m_num_register >0)
    {
        for (int i = 0; i < m_num_register; i++)
        {
            SAFE_DELETE(m_object_array[i]);
        }
    }

    //オブジェクトの位置決定
    Vector3 pos[8] =
    {
        //Vector3(0, -5.6, 0),
        Vector3(10.0f, 0, -5.0f),
        Vector3(23.74, 0, 24.04),
        Vector3(-26.74, 0, 29.26),
        Vector3(-30.88, 0, -29.46),
        Vector3(29.85, 0, -29.35),
        Vector3(-1.02, 0, -9.32),
        Vector3(23.42, 0, 0.51),
        Vector3(0.66, 0, 25.31),
    };
    //向き決定
    Vector3 angle[8] =
    {
        Vector3(0, 0, 0),
        Vector3(0, 0, 0),
        Vector3(0, 0, 0),
        Vector3(0, 0, 0),
        Vector3(0, 0, 0),
        Vector3(0, 0, 0),
        Vector3(0, 0, 0),
        Vector3(0, 0, 0),
    };

    for (int i = 0; i < 8; i++)
    {
        EntryPoint::Register(pos[i], angle[i]);
    }

    m_num_register = 0;
    iex3DObj* insert = new iex3DObj("DATA\\CHR\\human\\human Find_Me.IEM");
    player = new Player(
        1,
        0.3,
        Vector3(0, 0, 0),
        Vector3(0, 0, 0),
        Vector3(0.05f, 0.05f, 0.05f),
        Vector3(1, 1, 1),
        BaseObjct::TYPE::player,
        insert);
    InsertObject(player);

	iexMesh* insert_mesh = new iexMesh("DATA\\IMO\\new_room.IMO");
	Fileobject* insert_obj = new Fileobject(1, 0.3,
		Vector3(0, -5.6, 0),
		Vector3(0,0,0),
		Vector3(1.2, 1.2, 1.2),
		Vector3(1, 1, 1),
		BaseObjct::judge,
		insert_mesh);
	InsertObject(insert_obj);

    char* filename[8] =
    {
        /*"DATA\\IMO\\new_room.IMO",*/
        ("DATA\\IMO\\tana.IMO"),
        ("DATA\\IMO\\bed.IMO"),
        ("DATA\\IMO\\sofa.IMO"),
        ("DATA\\IMO\\table_kai.IMO"),
        ("DATA\\IMO\\tanataka.IMO"),
        ("DATA\\IMO\\terebi.IMO"),
        ("DATA\\IMO\\toire.IMO"),
        ("DATA\\IMO\\tukuetoisu.IMO"),
    };

    //オブジェクト読み込み
    for (int i = 0; i < 8; i++)
    {
        Vector3 p, a;
        EntryPoint::GetPoint(&p, &a);
        iexMesh* insert_mesh = new iexMesh(filename[i]);
        Vector3 scale = ScaleManager::GetScale(filename[i]);
        Fileobject* insert_obj = new Fileobject(1, 0.3,
            p,
            a,
            scale,
            Vector3(1, 1, 1),
            BaseObjct::judge,
            insert_mesh);
        InsertObject(insert_obj);
    }
   assert( DecisionAnswerObject());
    return true;
}

bool ObjectManager::DecisionAnswerObject()
{
    if (m_answer_object)
        m_answer_object = nullptr;
    
    int answer_index = RandomEngine::Execute(2, 8);
    assert(m_object_array[answer_index]);
    m_answer_object = m_object_array[answer_index];
    return true;
}

bool ObjectManager::Is_AnswerObject(const BaseObjct* object)
{
    if (m_answer_object == object)
        return true;

    return false;
}
