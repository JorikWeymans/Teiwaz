Texture2D gTexture;

SamplerState samPoint
{
    Filter = MIN_MAG_MIP_POINT;
    AddressU = Mirror;
    AddressV = Mirror;
};


DepthStencilState depthStencilState
{
	DepthEnable = TRUE;
};
RasterizerState BackCulling
{
	CullMode = BACK;
};

//IN/OUT STRUCTS
//--------------
struct VS_INPUT
{
    float3 Position : POSITION;
	float2 TexCoord : TEXCOORD0;

};

struct PS_INPUT
{
    float4 Position : SV_POSITION;
	float2 TexCoord : TEXCOORD1;
};


//VERTEX SHADER
//-------------
PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;
	// Set the Position1
	output.Position = float4(input.Position, 1.f);

	// Set the TexCoord
	output.TexCoord = input.TexCoord;
	return output;
}

float maxi(float3 fl)
{
    float rf = max(fl.x, fl.y);
    rf = max(rf, fl.z);
	
    return rf;
}
float mini(float3 fl)
{
    float rf = min(fl.x, fl.y);
    rf = min(rf, fl.z);
	
    return rf;
}
//PIXEL SHADER
//------------
float4 PS(PS_INPUT input): SV_Target
{
	float3 color = gTexture.Sample(samPoint, input.TexCoord);
	
    float grayscale = 0.0f;
	
	
	//https://www.johndcook.com/blog/2009/08/24/algorithms-convert-color-grayscale/ (lightness, average, Luminosity)
	//Lightness
    //grayscale = (maxi(color) + mini(color)) / 2;
	
	//average
    //grayscale = (color.x + color.y + color.z) / 3;
	
	//Luminosity
    grayscale = grayscale = (0.21 * color.x) + (0.72 * color.y) + (0.07 * color.z);

	return float4( grayscale, grayscale, grayscale, 1.0f );
	
	//sepia
    return float4( grayscale * 1.02, grayscale * .56, grayscale * .1f, 1.0f );
}


//TECHNIQUE
//---------
technique11 Grayscale
{
    pass P0
    {          
        // Set states...
		SetDepthStencilState(depthStencilState, 0);
		SetVertexShader( CompileShader( vs_4_0, VS() ) );
		SetRasterizerState(BackCulling);    
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }
}

