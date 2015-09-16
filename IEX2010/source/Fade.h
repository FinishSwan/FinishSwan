class FadeManager
{
private:
	static float FadeStartVal;
	static float FadeEndVal;
	static float FadeMaxTime;
	static float FadeTime;
	static float FadeVal;

	static Vector3 color;

	static void Fade_Start(float StartVal,float EndVal, float Time);
public:

	static void FadeIn(float Time);
	static void FadeOut(float Time);

	static bool IsFadeEnd(){ return FadeTime == FadeMaxTime; }

	static void SetColor(Vector3 color_val)
	{
		color = color_val;
	};
	static void Update();
	static void Render();
};