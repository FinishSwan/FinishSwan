//**************************************************************************************************
//																									
//		��{�V�F�[�_�[		
//
//**************************************************************************************************

//------------------------------------------------------
//		���֘A
//------------------------------------------------------
float4x4 TransMatrix;	//	�ϊ��s��
float4x4 matView;		//	�ϊ��s��
float4x4 Projection;	//	�ϊ��s��

float3	ViewPos;

float3	WorldViewPos;
float3 WavePos = { 0, 5, 0 };
float WaveLangth = 15.0f;
float WaveOffSet = 1.21;
float WaveSpeed = .0f;
float WaveLossTime = .0f;
float WaveMaxTime = 1.0f;
float WaveTime = .0f;

float4 Color;

float PowerSlerpBegin = -3.8f;
float PowerSlerpEnd = 20.8f;


float3	PaintPos;
float		PaintRange;

float WavePower = .8f;
float3 WaveColor = { .0f, .0f, .0f };
float WaveMul = 1.3f;

//------------------------------------------------------
//		�e�N�X�`���T���v���[	
//------------------------------------------------------
texture Texture;	//	�f�J�[���e�N�X�`��
sampler DecaleSamp = sampler_state
{
    Texture = <Texture>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = Wrap;
    AddressV = Wrap;
};

texture NormalMap;	//	�@���}�b�v�e�N�X�`��
sampler NormalSamp = sampler_state
{
    Texture = <NormalMap>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = Wrap;
    AddressV = Wrap;
};

texture SpecularMap;	//	�X�y�L�����}�b�v�e�N�X�`��
sampler SpecularSamp = sampler_state
{
    Texture = <SpecularMap>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = Wrap;
    AddressV = Wrap;
};

texture HeightMap;		//	�����}�b�v�e�N�X�`��
sampler HeightSamp = sampler_state
{
    Texture = <HeightMap>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = Wrap;
    AddressV = Wrap;
};

//**************************************************************************************************
//		���_�t�H�[�}�b�g
//**************************************************************************************************
struct VS_BASIC
{
    float4 Pos    : POSITION;
    float4 Color  : COLOR0;
    float2 Tex	  : TEXCOORD0;
};

struct VS_OUTPUT
{
    float4 Pos		: POSITION;
    float4 Color	: COLOR0;
    float2 Tex		: TEXCOORD0;
    float3 Normal	: TEXCOORD1;

    float4 Ambient	: COLOR1;
	float4 light	: COLOR2;
	float3 vLight	: TEXCOORD2;
	float3 vE		: TEXCOORD3;
	float  specular	: TEXCOORD4;
};

struct VS_INPUTL
{
    float4 Pos    : POSITION;
    float3 Normal : NORMAL;
    float4 Color  : COLOR0;
    float2 Tex	  : TEXCOORD0;
};

struct VS_INPUT_BUMP
{
	float4 Pos		:POSITION;
	float3 Normal	:NORMAL;
	float2 Tex		:TEXCOORD0;

	float4 Color	: COLOR0;
};

struct VS_OUTPUT_WAVE
{
	float4 Pos		:POSITION;
	float3 Normal	:NORMAL;
	float4 Color	:COLOR0;

	float2 Tex		:TEXCOORD0;
	float3 vPos		:TEXCOORD1;
	float3 vE	:TEXCOORD2;
};

struct VS_OUTPUT_PAINT
{
	float4 Pos		:POSITION;
	float2 Tex		:TEXCOORD0;
	float3 vPos		:TEXCOORD1;

};



//**************************************************************************************************
//
//		���C�e�B���O
//
//**************************************************************************************************

//**************************************************************************************************
//	�������C�e�B���O
//**************************************************************************************************
float3 SkyColor = { 0.48f, 0.5f, 0.5f };
float3 GroundColor = { 0.4f, 0.4f, 0.4f };

inline float4 HemiLight( float3 normal )
{
	float4 color;
	float rate = (normal.y*0.5f) + 0.5f;
	color.rgb = SkyColor * rate;
	color.rgb += GroundColor * (1-rate);
	color.a = 1.0f;

	return color;
}

//**************************************************************************************************
//	���s��
//**************************************************************************************************
float3 LightDir = { 1.0f, -1.0f, 0.0f };
float3 DirLightColor = { 0.6f, 0.6f, 0.6f };

inline float3 DirLight( float3 dir, float3 normal )
{
	float3 light;
	float rate = max( 0.0f, dot( -dir, normal ) );
	light = DirLightColor * rate;
	
	return light;
}

//**************************************************************************************************
//	�X�y�L����
//**************************************************************************************************
inline float Specular(float3 pos, float3 normal)
{
    float   sp;

    float3	H = normalize(ViewPos - pos);
    H = normalize(H - LightDir);
    
	sp = dot(normal, H);
	sp = max( 0, sp );
	sp = pow(sp, 10);

    return sp;
}

//------------------------------------------------------
//		�t�H�O�֘A
//------------------------------------------------------
float	FogNear	= 60.0f;
float	FogFar  = 80.0f;
float3	FogColor = { 0.7f, 0.7f, 0.7f };


//**************************************************************************************************
//	���}�b�v�p
//**************************************************************************************************
texture EnvMap;		//	���e�N�X�`��
sampler EnvSamp = sampler_state
{
    Texture = <EnvMap>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = Wrap;
    AddressV = Wrap;
};

inline float4 Environment( float3 normal )
{
	float4	color;
	
	float2	uv;
	uv.x = normal.x*0.5f + 0.5f;
	uv.y = normal.y*0.5f + 0.5f;

	color = tex2D( EnvSamp, uv );
	return color;
}

float4 VS_White(float4 Pos:POSITION):POSITION
{
	return mul(Pos, Projection);

}

float4 PS_White(float4 Pos:POSITION) :COLOR
{
	return float4(1,1,1,1);
}

float4 PS_Black(float4 Pos:POSITION) : COLOR
{
	return float4(0, 0, 0, 1);
}
float4 PS_Color(float4 Pos:POSITION) : COLOR
{
	return Color;
}


VS_OUTPUT_WAVE VS_Wave(VS_INPUT_BUMP In)
{
	VS_OUTPUT_WAVE Out = (VS_OUTPUT_WAVE)0;


	Out.Pos = mul(In.Pos, Projection);

	Out.Tex = In.Tex;
	Out.Color = In.Color;

	float4 P = mul(In.Pos, TransMatrix);
		float3x3	  mat = TransMatrix;
		float3 N = mul(In.Normal, mat);

		Out.vPos = P;

	//���_���[�J�����W�n�Z�o
	float3 vx;
	float3 vy = { 0, 1, 0.001f };
		vx = cross(vy, N);
	vx = -normalize(vx);
	vy = cross(N, vx);
	vy = normalize(vy);
	N = normalize(N);

	float3 vP = P.xyz;
		vP -= ViewPos;
	vP = normalize(vP);

	Out.vE.x = dot(vx, vP);
	Out.vE.y = dot(vy, vP);
	Out.vE.z = dot(N, vP);


	Out.vE = N;
	return Out;

}

VS_OUTPUT_PAINT VS_Paint(VS_BASIC In)
{
	VS_OUTPUT_PAINT Out = (VS_OUTPUT_PAINT)0;


	Out.Pos = mul(In.Pos, Projection);

	Out.Tex = In.Tex;

	float4 P = mul(In.Pos, TransMatrix);

	Out.vPos = P.xyz;

	return Out;
}

float4 PS_Paint(VS_OUTPUT_PAINT In) : COLOR
{
	float dist = length(PaintPos - In.vPos);
	if (dist < PaintRange)
		return tex2D(DecaleSamp, In.Tex);
	return Color;
}

float WaveHeight(float Length)
{
	float EmitTime = WaveTime - (Length / WaveSpeed);
	if (EmitTime < -.00f)
		return .0f;
	float WaveCycle = sin(EmitTime * WaveMul + WaveOffSet) * -0.5f - 0.5f;
	float WorkWavePower = WavePower;


	//���Ԍ���
	WorkWavePower *= 1.0f - (EmitTime / WaveMaxTime);

		float PowerLostDist = WorkWavePower / (WaveLossTime / WaveSpeed);
		float PowerSlerpBeginPos = PowerLostDist + PowerSlerpBegin;
		float PowerSlerpEndPos = PowerLostDist + PowerSlerpEnd;
		float PowerSlerpBeginValue = WorkWavePower - WaveLossTime * (PowerSlerpBeginPos / WaveSpeed);

		float rate = max(.0f, 1.0f - (Length - PowerSlerpBeginPos) / (PowerSlerpEnd - PowerSlerpBegin));

		if (rate > 1.0f)
		{
			//��������
			WorkWavePower -= WaveLossTime * (Length / WaveSpeed);
		}
		else
		{
			WorkWavePower = PowerSlerpBeginValue * rate * rate;
		}


	////��������
	//WorkWavePower -= WaveLossTime * (Length / WaveSpeed);

	WorkWavePower = max(WorkWavePower, .0f);

	return WaveCycle * WorkWavePower;

}

float4 PS_Wave(VS_OUTPUT_WAVE In) : COLOR
{
	float4 OUT;
	// �s�N�Z���F����
	OUT.a = 1;

	//float4 screen;
	//screen.xy = In.vPos.xy * 2 - 1;
	//screen.y = -screen.y;
	//screen.z = In.vPos.z;
	//screen.w = 1;

	//float4 pos = mul(screen, InvProj);
	//	pos.xyz /= pos.w;

	float3 pos = In.vPos;


	float dist = length(pos.xyz - WavePos.xyz);

	//float h = (sin((dist + WaveOffSet) * WaveMul) + 1.0f) * 0.5f *WavePower;
	//h *= max(0, 1.0 - dist / WaveLangth);

	float h = WaveHeight(dist);

	float3 E = normalize(In.vE);
		float3 D = normalize(pos - ViewPos);

		//�@���擾

		float3 Dot = dot(D, E);

		D -= Dot * E;

	pos.xyz += D * h * 2.0f;

	dist = length(pos.xyz - WavePos.xyz);

	float adjust = 0.001f;

	//h = (sin((dist + WaveOffSet) * WaveMul) + 1.0f) * 0.5f *WavePower;
	//h *= max(0, 1.0 - dist / WaveLangth);

	h = WaveHeight(dist);
	//h = dist/100.0f;

	//float h2 = (sin((dist + WaveOffSet) * WaveMul + adjust) + 1.0f) * 0.5f *WavePower;
	//h2 *= max(0, 1.0 - dist / WaveLangth);

	float h2 = WaveHeight(dist + adjust);

	float2 vec;
	//TODO �T�C���g��Y�����擾
	vec.y = abs(h2 - h) / adjust;
	vec.x = 1.0f;
	vec = normalize(vec);

	float rate = abs(vec.x);
	OUT.rgb = rate + (1 - rate) * WaveColor;
	//OUT.rgb = h;



	return OUT;
}


//**************************************************************************************************
//
//		��{�V�F�[�_�[
//
//**************************************************************************************************

//------------------------------------------------------
//	���_�V�F�[�_�[
//------------------------------------------------------
VS_BASIC VS_Basic( VS_INPUTL In )
{
	VS_BASIC Out = (VS_BASIC)0;

	float3 P = mul(In.Pos, TransMatrix);

	float3x3	mat = TransMatrix;
	float3 N = mul(In.Normal, mat);
	N = normalize(N);

	Out.Pos   = mul(In.Pos, Projection);
	Out.Color.rgb = DirLight( LightDir, N ) + HemiLight( N );
	Out.Color.a = 1.0f;
	Out.Tex   = In.Tex;

	return Out;
}

//------------------------------------------------------
//	���_�J���[�t�V�F�[�_�[
//------------------------------------------------------
VS_BASIC VS_Basic2( VS_INPUTL In )
{
    VS_BASIC Out = (VS_BASIC)0;
	
	float3 P = mul( In.Pos, TransMatrix );

	float3x3	mat = TransMatrix;
	float3 N = mul(In.Normal, mat);
	N = normalize(N);

	Out.Pos   = mul(In.Pos, Projection);
	Out.Color.rgb = (DirLight( LightDir, N ) + HemiLight( N ));
	Out.Color.a = In.Color.a;
	Out.Tex   = In.Tex;

    return Out;
}

//------------------------------------------------------
//	�s�N�Z���V�F�[�_�[	
//------------------------------------------------------
float4 PS_Basic( VS_BASIC In) : COLOR
{   
	float4	OUT;
	//	�s�N�Z���F����
	OUT = In.Color * tex2D( DecaleSamp, In.Tex );

	return OUT;
}

//------------------------------------------------------
//	�e�N�j�b�N
//------------------------------------------------------
technique copy
{
    pass P0
    {
		AlphaBlendEnable = true;
		BlendOp          = Add;
		SrcBlend         = SrcAlpha;
		DestBlend        = InvSrcAlpha;
		ZWriteEnable     = true;

		VertexShader = compile vs_3_0 VS_Basic();
		PixelShader  = compile ps_3_0 PS_Basic();
    }
}

technique lcopy
{
    pass P0
    {
		AlphaBlendEnable = true;
		BlendOp          = Add;
		SrcBlend         = SrcAlpha;
		DestBlend        = InvSrcAlpha;
		ZWriteEnable     = true;

		VertexShader = compile vs_2_0 VS_Basic2();
		PixelShader  = compile ps_2_0 PS_Basic();
    }
}

technique add
{
    pass P0
    {
		AlphaBlendEnable = true;
		BlendOp          = Add;
		SrcBlend         = SrcAlpha;
		DestBlend        = One;
		ZWriteEnable     = false;

		VertexShader = compile vs_3_0 VS_Basic();
		PixelShader  = compile ps_3_0 PS_Basic();
    }
}

//**************************************************************************************************
//
//		�t���G�t�F�N�g
//
//**************************************************************************************************
//------------------------------------------------------
//	���_�V�F�[�_
//------------------------------------------------------
VS_OUTPUT VS_FullFX( VS_INPUTL In )
{
    VS_OUTPUT Out = (VS_OUTPUT)0;
	
	float4 P = mul(In.Pos,    TransMatrix);

	float3x3	mat = TransMatrix;
	float3 N = mul(In.Normal, mat);
	N = normalize(N);
	Out.Normal = N;
	Out.Ambient.rgb = HemiLight(N);

	Out.Pos   = mul(In.Pos, Projection);
	Out.Color = 1.0f;
	Out.Tex   = In.Tex;

	//	���C�g�x�N�g���␳
	float3	vx;
	float3	vy = { 0.0f, -1, 0.01f };

	vx = cross( N, vy );
	vx = normalize( vx );
	
	vy = cross( vx, N );
	vy = normalize( vy );

	//	���C�g�x�N�g���␳
	Out.vLight.x = dot(vx, LightDir);
	Out.vLight.y = dot(vy, LightDir);
	Out.vLight.z = dot(N, LightDir);
	Out.vLight = normalize( Out.vLight );

	// �����x�N�g���␳
	float3 E = (P - ViewPos);   // �����x�N�g��
	Out.vE.x = -dot(vx, E);
	Out.vE.y = dot(vy, E);
	Out.vE.z = dot(N, E);
	Out.vE = normalize( Out.vE );

	Out.light = 0;//PointLight( P, N );

	//	�t�H�O�v�Z
	Out.Ambient.a = (FogFar-Out.Pos.z) / (FogFar-FogNear);
	Out.Ambient.a = saturate(Out.Ambient.a);

	return Out;
}

//------------------------------------------------------
//	���_�J���[�t�V�F�[�_
//------------------------------------------------------
VS_OUTPUT VS_FullFX2( VS_INPUTL In )
{
	VS_OUTPUT Out = (VS_OUTPUT)0;

	float4 P = mul(In.Pos, TransMatrix);

	float3x3	mat = TransMatrix;
	float3 N = mul(In.Normal, mat);
	N = normalize(N);
	Out.Normal = N;

	Out.Ambient.rgb = HemiLight(N);

	Out.Pos   = mul(In.Pos, Projection);
	Out.Color = In.Color;
	Out.Tex   = In.Tex;

	//	���C�g�x�N�g���␳
	float3	vx;
	float3	vy = { 0, 1, 0.01f };

	vx = cross( N, vy );
	vx = normalize( vx );

	vy = cross( N, vx );
	vy = normalize( vy );

	//	���C�g�x�N�g���␳
	Out.vLight.x = dot(vx, LightDir);
	Out.vLight.y = dot(vy, LightDir);
	Out.vLight.z = dot(N, LightDir);

	// �����x�N�g���␳
	float3 E = (P - ViewPos);   // �����x�N�g��
	Out.vE.x = dot(vx, E);
	Out.vE.y = dot(vy, E);
	Out.vE.z = dot(N, E);

	Out.light = 0;//PointLight( P, N );

	//	�t�H�O�v�Z
	Out.Ambient.a = (FogFar-Out.Pos.z) / (FogFar-FogNear);
	Out.Ambient.a = saturate(Out.Ambient.a);

	return Out;
}

//------------------------------------------------------
//		�s�N�Z���V�F�[�_�[	
//------------------------------------------------------
float4 PS_FullFX( VS_OUTPUT In) : COLOR
{   
	float4	OUT;
	float2 Tex = In.Tex;

	//	�p�����b�N�X�f�B�X�v���[�X�����g
	float h = tex2D( HeightSamp, Tex ).r-0.5f;// �����}�b�v�̃T���v�����O
	float3 E = normalize(In.vE);
	In.vLight = normalize(In.vLight);
	
	Tex -= 0.05f * h * E.xy;
	float3 N = tex2D( NormalSamp, Tex ).xyz * 2.0f - 1.0f;

	//	���C�g�v�Z
	float3 light = DirLight(In.vLight, N);
	//	�s�N�Z���F����
	OUT = In.Color * tex2D( DecaleSamp, Tex );
	OUT.rgb = (OUT.rgb*(light+In.Ambient.rgb));


	//	�X�y�L����
	float3  R = normalize( reflect( E, N ) );
	OUT.rgb += pow( max( 0, dot(R, -In.vLight) ), 10 ) * tex2D( SpecularSamp, Tex );
	//	�t�H�O�̗p
	OUT.rgb = (OUT.rgb * In.Ambient.a) + (FogColor * (1-In.Ambient.a));

	return OUT;
}

//------------------------------------------------------
//		�s�N�Z���V�F�[�_�[	
//------------------------------------------------------
float4 PS_FullFX2( VS_OUTPUT In) : COLOR
{   
	float4	OUT;
	float2 Tex = In.Tex;

	//	�p�����b�N�X�f�B�X�v���[�X�����g
	float h = tex2D( HeightSamp, Tex ).r-0.5f;// �����}�b�v�̃T���v�����O
	float3 E = normalize(In.vE);
	In.vLight = normalize(In.vLight);
	
	float3 N = tex2D( NormalSamp, Tex ).xyz * 2.0f - 1.0f;

	//	���C�g�v�Z
	float3 light = DirLight(In.vLight, N);
	//	�s�N�Z���F����
	OUT = In.Color * tex2D( DecaleSamp, Tex );
	OUT.rgb = (OUT.rgb*(light+In.Ambient.rgb));


	//	�X�y�L����
	float3  R = normalize( reflect( E, N ) );
	OUT.rgb += pow( max( 0, dot(R, -In.vLight) ), 10 ) * tex2D( SpecularSamp, Tex );
	//	�t�H�O�̗p
	OUT.rgb = (OUT.rgb * In.Ambient.a) + (FogColor * (1-In.Ambient.a));

	return OUT;
}

//------------------------------------------------------
//		�����Ȃ�	
//------------------------------------------------------
technique copy_fx
{
    pass P0
    {
		AlphaBlendEnable = true;
		BlendOp          = Add;
		SrcBlend         = SrcAlpha;
		DestBlend        = InvSrcAlpha;
		ZWriteEnable     = true;

		VertexShader = compile vs_3_0 VS_FullFX();
		PixelShader  = compile ps_3_0 PS_FullFX();
    }
}

technique lcopy_fx
{
    pass P0
    {
		AlphaBlendEnable = true;
		BlendOp          = Add;
		SrcBlend         = SrcAlpha;
		DestBlend        = InvSrcAlpha;
		ZWriteEnable     = true;
		VertexShader = compile vs_3_0 VS_FullFX2();
		PixelShader  = compile ps_3_0 PS_FullFX();
    }
}

technique copy_fx2
{
    pass P0
    {
		AlphaBlendEnable = true;
		BlendOp          = Add;
		SrcBlend         = SrcAlpha;
		DestBlend        = InvSrcAlpha;
		ZWriteEnable     = true;

		VertexShader = compile vs_3_0 VS_FullFX();
		PixelShader  = compile ps_3_0 PS_FullFX2();
    }
}

technique lcopy_fx2
{
    pass P0
    {
		AlphaBlendEnable = true;
		BlendOp          = Add;
		SrcBlend         = SrcAlpha;
		DestBlend        = InvSrcAlpha;
		ZWriteEnable     = true;
		VertexShader = compile vs_3_0 VS_FullFX2();
		PixelShader  = compile ps_3_0 PS_FullFX2();
    }
}

technique	wave
{
	pass P0
	{
		AlphaBlendEnable = true;
		BlendOp = Add;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
		ZWriteEnable = true;
		CullMode = CCW;
		ZEnable = true;

		VertexShader = compile vs_3_0 VS_Wave();
		PixelShader = compile ps_3_0 PS_Wave();
	}
}

technique	white
{
	pass P0
	{
		AlphaBlendEnable = true;
		BlendOp = Add;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
		ZWriteEnable = true;
		CullMode = CCW;
		ZEnable = true;

		VertexShader = compile vs_2_0 VS_White();
		PixelShader = compile ps_2_0 PS_White();
	}
}

technique	black
{
	pass P0
	{
		AlphaBlendEnable = true;
		BlendOp = Add;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
		ZWriteEnable = true;
		CullMode = CCW;
		ZEnable = true;

		VertexShader = compile vs_2_0 VS_White();
		PixelShader = compile ps_2_0 PS_Black();
	}
}

technique	color
{
	pass P0
	{
		AlphaBlendEnable = true;
		BlendOp = Add;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
		ZWriteEnable = true;
		CullMode = CCW;
		ZEnable = true;

		VertexShader = compile vs_2_0 VS_White();
		PixelShader = compile ps_2_0 PS_Color();
	}
}


technique	paint
{
	pass P0
	{
		AlphaBlendEnable = true;
		BlendOp = Add;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
		ZWriteEnable = true;
		CullMode = CCW;
		ZEnable = true;

		VertexShader = compile vs_2_0 VS_Paint();
		PixelShader = compile ps_2_0 PS_Paint();
	}
}


