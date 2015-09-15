class FadeManager
{
private:
	static float FadeStartVal;
	static float FadeEndVal;
	static float FadeMaxTime;
	static float FadeTime;
	static float FadeVal;

	static void Fade_Start(float StartVal,float EndVal, float Time);
public:

	static void FadeIn(float Time);
	static void FadeOut(float Time);

	static bool IsFadeEnd(){ return FadeTime == FadeMaxTime; }

	static void Update();
	static void Render();
};