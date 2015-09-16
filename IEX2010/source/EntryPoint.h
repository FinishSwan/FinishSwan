#pragma once

class EntryPoint
{
	struct Positioning
	{
		Vector3 pos;
		Vector3 angle;
		bool Isactive;
		Positioning():pos(Vector3(0,0,0)),angle(Vector3(0,0,0)),Isactive(false){}
	};
private:
	static Positioning container[15];
	static int numactive;

public:

	static void Initialize();
	static bool Register(const Vector3& pos, const Vector3& angle);
	static void GetPoint(Vector3* outpos, Vector3* outangle);
	static void Release();

};