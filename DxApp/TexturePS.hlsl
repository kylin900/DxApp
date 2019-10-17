Texture2D tex;

SamplerState splr;

struct VSOut
{
    float2 tex : TexCoord;
    float4 pos : SV_Position;
};

float4 main(VSOut tc : TexCoord) : SV_Target
{
    return tex.Sample(splr, tc.tex);
}