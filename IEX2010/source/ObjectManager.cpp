#include	"iextreme.h"
#include	"BaseObj.h"
#include	"ObjectManager.h"
#include	"Wave.h"

#include	<vector>
#include	<list>

void	ObjectManager::Initialize()
{
	ZeroMemory(m_object_array, sizeof(BaseObjct*)* MAX_OBJECT);
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
	float radius = owner_object->GetRadius();//‚ ‚½‚è”»’è‚Ì”¼Œa‚ÌƒQƒbƒ^[
	Vector3 owner_object_pos = owner_object->GetPos();//obj‚ÌƒQƒbƒ^[
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

		//XYZ‚ÌŒvŽZ
		Vector3 d;
		d.x = cullent_object_pos.x - owner_object_pos.x;
		d.y = cullent_object_pos.y - owner_object_pos.y;
		d.z = cullent_object_pos.z - owner_object_pos.z;

		//”¼Œa‚ÌŒvŽZ
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