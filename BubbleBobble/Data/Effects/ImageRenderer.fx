float4x4 gTransform : WorldViewProjection;
Texture2D gTexture;
float2 gTextureSize;
float4 gSrcRect;

SamplerState samPoint
{
    Filter = MIN_MAG_MIP_POINT;
    AddressU = WRAP;
    AddressV = WRAP;
};

BlendState EnableBlending 
{     
	BlendEnable[0] = TRUE;
	SrcBlend = SRC_ALPHA;
    DestBlend = INV_SRC_ALPHA;
};

DepthStencilState NoDepth
{
	DepthEnable = FALSE;
};

RasterizerState BackCulling 
{ 
	CullMode = NONE; 
};

struct VS_DATA
{
	uint TextureId: TEXCOORD0;
	float4 TransformData : POSITION; //PosX, PosY, Depth (PosZ), Rotation
	float4 TransformData2 : POSITION1; //PivotX, PivotY, ScaleX, ScaleY
	float4 Color: COLOR;	
};

struct GS_DATA
{
	float4 Position : SV_POSITION;
	float4 Color: COLOR;
	float2 TexCoord: TEXCOORD0;
};


VS_DATA MainVS(VS_DATA input)
{
	return input;
}

//GEOMETRY SHADER
//***************
void CreateVertex(inout TriangleStream<GS_DATA> triStream, float3 pos, float4 col, float2 texCoord, float rotation, float2 rotCosSin, float2 offset, float2 pivotOffset)
{
	if (rotation != 0)
	{

		pos.xy -= (offset + pivotOffset);
		float2 newPos = float2((pos.x * rotCosSin.x) - (pos.y * rotCosSin.y), (pos.x * rotCosSin.y) + (pos.y * rotCosSin.x));
		pos.xy = newPos;
		//Retransform to initial position
		pos.xy += offset;
	}
	else
	{
		pos.xy -= pivotOffset;
	}
	//Geometry Vertex Output
	GS_DATA geomData = (GS_DATA) 0;
	geomData.Position = mul(float4(pos, 1.0f),gTransform);
	geomData.Color = col;
	geomData.TexCoord = texCoord;
	triStream.Append(geomData);

}

[maxvertexcount(4)]
void MainGS(point VS_DATA vertex[1], inout TriangleStream<GS_DATA> triStream)
{
	//Given Data (Vertex Data)
	float3 position = vertex[0].TransformData.xyz; //Extract the position data from the VS_DATA vertex struct
	float2 offset = vertex[0].TransformData.xy;//Extract the offset data from the VS_DATA vertex struct (initial X and Y position)
	float rotation = vertex[0].TransformData.w; //Extract the rotation data from the VS_DATA vertex struct
	float2 pivot = vertex[0].TransformData2.xy; //Extract the pivot data from the VS_DATA vertex struct
	float2 scale = vertex[0].TransformData2.zw; //Extract the scale data from the VS_DATA vertex struct
	float2 texCoord = float2(0, 0); //Initial Texture Coordinate

    pivot.x *= gSrcRect.z * scale.x;
    pivot.y *= gSrcRect.w * scale.y;

	float2 rotCosSin = float2(0, 0);
	if (rotation != 0)
	{
		rotCosSin.x = cos(rotation);
		rotCosSin.y = sin(rotation);
	}
	// LT----------RT //TringleStrip (LT > RT > LB, LB > RB > RT)
	// |          / |
	// |       /    |
	// |    /       |
	// | /          |
	// LB----------RB
	
    //gSrcRect.xy = position.xy;
    //gSrcRect.wz = gTextureSize.xy;
	//VERTEX 1 [LT]
    float4 drawRect = gSrcRect;
    drawRect.x /= gTextureSize.x;
    drawRect.y /= gTextureSize.y;
    drawRect.z /= gTextureSize.x;
    drawRect.w /= gTextureSize.y;
	
    position += float3(0, 0.0f, 0.0f);
    texCoord = float2(drawRect.x, drawRect.y);
	CreateVertex(triStream, position, vertex[0].Color, texCoord, rotation, rotCosSin, offset, pivot); 

	//VERTEX 2 [RT]
    position += float3(gSrcRect.z * scale.x , 0.0f, 0.0f);
    texCoord = float2(drawRect.x + drawRect.z, drawRect.y);
	CreateVertex(triStream, position, vertex[0].Color, texCoord, rotation, rotCosSin, offset, pivot);

	//VERTEX 3 [LB]
    position += float3(-gSrcRect.z * scale.x, gSrcRect.w * scale.y, 0.f);
    texCoord = float2(drawRect.x, drawRect.y + drawRect.w);
	CreateVertex(triStream, position, vertex[0].Color, texCoord, rotation, rotCosSin, offset, pivot); 

	//VERTEX 4 [RB]
    position += float3(gSrcRect.z * scale.x, 0.f, 0.f);
    texCoord = float2(drawRect.x + drawRect.z, drawRect.y + drawRect.w);
	CreateVertex(triStream, position, vertex[0].Color, texCoord, rotation, rotCosSin, offset, pivot); 
}

float4 MainPS(GS_DATA input) : SV_TARGET
{
	float4 sprite = gTexture.Sample(samPoint, input.TexCoord) * input.Color;	
	sprite.xyz += .04f;
	return sprite;
	
}

technique11 Default {

	pass p0 {
		SetRasterizerState(BackCulling);
		SetBlendState(EnableBlending,float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
		SetDepthStencilState(NoDepth,0);
		SetVertexShader(CompileShader(vs_4_0, MainVS()));
		SetGeometryShader(CompileShader(gs_4_0, MainGS()));
		SetPixelShader(CompileShader(ps_4_0, MainPS()));
	}
}
