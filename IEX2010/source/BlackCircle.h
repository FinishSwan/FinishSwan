class BlackCircle
{
private:
	float time;
	float maxtime;
	bool enable;
	iex2DObj* obj;
public:
	BlackCircle();

	void Start(float time);
	void Render();
	void Update();
	bool IsBlacked(){ return maxtime < time; }
	bool IsEnable(){ return enable; };
};

extern BlackCircle* blackcircle;