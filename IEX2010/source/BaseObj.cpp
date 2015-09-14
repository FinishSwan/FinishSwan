#include	"iextreme.h"
#include	"BaseObj.h"

BaseObjct::BaseObjct(const float radius, const float adjust_h,
		const Vector3& pos, 
		const Vector3& angle,
		const Vector3& scale,
		const Vector3& color) :
		pos(pos), scale(scale), angle(angle),
		color(color), radius(radius), adjust_height(adjust_h), velocity(Vector3(0,0,0))
		
{

}

BaseObjct::~BaseObjct()
{
	
}