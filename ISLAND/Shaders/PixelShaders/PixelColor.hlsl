struct PixelInput
{
    float4 pos : SV_Position;
    float4 color : Color;
};

//                          ��ȯ���� �ø�ƽ ����(SV : system value)
float4 main(PixelInput input) : SV_Target
{
    return input.color;
}