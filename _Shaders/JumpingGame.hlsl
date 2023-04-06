struct VertexInput {
  float4 position : POSITION0;   // ���� ��ġ "position"�̶�� ������ "POSITION0" ��Ʈ���� ��ġ�� ���� ������ �����Ѵ�
  float2 uv : TEXCOORD0;         // ���� ����
};

struct PixelInput {
  float4 position : SV_POSITION0;  // �ȼ� ��ġ  �ȼ��� ��ġ�� ��Ÿ���� �ý���
                                   // ���� �ǹ� ( SV = System Value )
  float2 uv : TEXCOORD0;  // �ȼ� ����
};

// cbuffer : constance buffer ��� ���� ��������
// ��� ���� �������� b0�� �Ҵ�� ���� ����� �����ϴ� ��� ����
// 0 ~ 127
cbuffer WorldBuffer : register(b0) { matrix _world; }

// ��� ���� �������� b1�� �Ҵ�� ��, �������� ����� �����ϴ� ��� ����
cbuffer VPbuffer : register(b1) {
  matrix _view;
  matrix _projection;
}

cbuffer JumpingGameBuffer : register(b3)
{
    float2 _xyPosition;
    int _transitionCount;
}

// ���� ���̴� �Լ�
// �Է����� VertexInput�� �ް� PixelInput ����ü�� ��ȯ
// VS�� EntryName
PixelInput VS(VertexInput input) { 
  PixelInput output;

  output.position = mul(input.position, _world);           // ���� ��ġ�� ���� ����� ����
  output.position = mul(output.position, _view);           // ����� �� ����� ����
  output.position = mul(output.position, _projection);     // ����� �������� ����� ����

  output.uv = input.uv;
  return output;
}

Texture2D _sourceTex : register(t0);  // �ؽ��� �����͸� ����
SamplerState _samp : register(s0);    // ���ø��ϴ� ��� ����

// �ȼ� ���̴� �Լ�
// �Է����� PixelInput ����ü�� �ް� float4 ������ �ȼ� ������ ��ȯ
float4 PS(PixelInput input) : SV_Target
{
    float4 color = _sourceTex.Sample(_samp, (float2) input.uv);
    
    float3 temp;
    float4 resultColor;
    
    float xPos = _xyPosition.x / 2560.f;
    float yPos = (1440 - _xyPosition.y) / 1440.f;
    float xTransition = _transitionCount / 2560.f;
    float yTransition = _transitionCount / 1440.f;
    
    if ((input.uv.x >= xPos - xTransition && input.uv.x <= xPos + xTransition) &&
        (input.uv.y >= yPos - yTransition && input.uv.y <= yPos + yTransition))
    {
        temp = dot(color.rgb, float3(0.299f, 0.587f, 0.114f));
        resultColor = float4(temp, color.a);
    }
    else
    {
        resultColor = color;
    }
    return resultColor;
}
/*
Semantic ����ƽ
- HLSL ���̴����� �������� �ǹ̸� �����ϴµ� ���
- ���̴��� �Է� �����Ϳ� ��� �����͸� �ùٸ��� �ؼ��ϰ� ó���� �� �ֵ��� ����
- ���� �̸� �ڿ� ':' ��ȣ�� �Բ� ����
- �ý��� �� ����ƽ�� 'SV_' ���λ�� �����ϸ� Direct3D���� ���ǵ� Ư���� �ǹ̸� ����
- �ý��� �� ����ƽ�� ���̴� �������� ���� �����͸� �����ϴµ� ���

slot
- GPU ���� ����ϴ� ��� ����, �ؽ���, ���÷� ���� �ڿ����� �ĺ��ϴ� �ε���
- �� ������ ������ ��ȣ�� ������, �ش� �ڿ��� ������ ���ҿ� ���� �ٸ��� �Ҵ��
- register��� Ű���带 ����Ͽ� ����
- �� �ڿ��� � ���Կ� �Ҵ�� ������ ��������� ������ �� ����

- �ֿ� ����
  1) ��� ���� ����
  - ��� �����͸� �����ϴµ� ���, VS�� PS���� ������ �� �ִ�
  - ��� ���� ������ register(b#)�� ����Ͽ� ����

  2) �ؽ��� ����
  - �̹��� �����͸� �����ϴµ� ���
  - �ؽ��� ���� ������ register(t#)�� ����Ͽ� ����

  3) ���÷� ����
  - �ؽ��ĸ� ���ø��ϴ� �� ���
  - ���÷� ������ register(s#)�� ����Ͽ� ����

cbuffer = Constance Buffer : ��� ����
- ���̴����� ����ϴ� ���� ������ �����ϴµ� ���
- �� ��� ���� �������Ϳ��� �� ���� ��� ���۸� �Ҵ��� �� ����
- ��� ���� ���ο��� ���� ���� ������ ������ �� �ִ�.

Sampler : ���÷�
- �ؽ��Ŀ��� �ȼ� ���� �������� ����� �����ϴ� ��ü
- �ؽ��� ���ø��� �ؽ��� �̹����� ���� �ؼ� ���� ����ϴ� �۾�
(�ؼ� : �ؽ����� �ȼ� ��)
*/