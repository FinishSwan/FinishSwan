#include	"iextreme.h"
#include	"BaseObj.h"
#include	"ObjectManager.h"

#include	<vector>
#include	<list>

void	ObjectManager::Initialize()
{
	ZeroMemory(m_object_array, sizeof(BaseObjct)* MAX_OBJECT);
}

void	ObjectManager::Release()
{

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
	BaseObjct* owner_object)
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
		
		Vector3 start_pos = *pos;
		Vector3 ray_vec = *vec;
		float dist = *Dist3;
		
		if (current_obj->RayPick(out, &start_pos, &ray_vec, &dist) != -1)
		{
			if (most_near < dist)
			{
				ret_object = current_obj;
				most_near = dist;
				ret_position = *out;
				ret_noraml = ray_vec;
				ret_dist = dist;
			}
		}
	}
	ret_object->Collision(ret_position, owner_object);
	*out = ret_position;
	*vec = ret_noraml;
	*Dist3 = ret_dist;

	return ret_object;

}

BaseObjct* ObjectManager::Collision_of_Sphere(BaseObjct* owner_object, float* ret_merikomi,
	Vector3* ret_merikomi_vec)
{
	Vector3 owner_object_pos = owner_object->GetPos();
	
	
	


	return nullptr;
}
