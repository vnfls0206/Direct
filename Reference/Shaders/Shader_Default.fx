matrix		g_matWorld, g_matView, g_matProj;
texture		g_texture;

sampler BaseSampler = sampler_state
{
	texture = g_texture;
	MAGFILTER = LINEAR;
	MIPFILTER = LINEAR;
	MINFILTER = LINEAR;
};

struct VS_IN
{
	float3 vPosition : POSITION;	
	float2 vTexUV : TEXCOORD;
};
struct VS_OUT
{
	vector vPosition : POSITION; // * ¿ùµå * ºä * Åõ¿µ
	float2 vTexUV : TEXCOORD;
};

VS_OUT VS_MAIN(VS_IN In)
{
	VS_OUT			Out = (VS_OUT)0;

	matrix		matWV, matWVP;

	matWV = mul(g_matWorld, g_matView);
	matWVP = mul(matWV, g_matProj);

	Out.vPosition = mul(vector(In.vPosition, 1.f), matWVP);
	Out.vTexUV = In.vTexUV;

	return Out;
}

struct PS_IN
{
	vector vPosition : POSITION;
	float2 vTexUV : TEXCOORD;
};
struct PS_OUT
{
	vector vColor : COLOR;
};

PS_OUT PS_MAIN(PS_IN In)
{
	PS_OUT			Out = (PS_OUT)0;

	Out.vColor = tex2D(BaseSampler, In.vTexUV);

	return Out;
}

technique Default_Device
{
	pass AlphaBlend
	{
		ZWriteEnable = false;

		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;

		vertexShader = compile vs_3_0 VS_MAIN();
		pixelShader = compile ps_3_0 PS_MAIN();
	}
	pass NoneAlpha
	{
		ZWriteEnable = false;

		AlphaBlendEnable = false;

		vertexShader = compile vs_3_0 VS_MAIN();
		pixelShader = compile ps_3_0 PS_MAIN();
	}

}