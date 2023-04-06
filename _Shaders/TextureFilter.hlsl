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

cbuffer ShadedBuffer : register(b0) { int Selection; }

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
float4 PS(PixelInput input) : SV_Target {
  float4 color = _sourceTex.Sample(_samp, (float2)input.uv);
  float4 resultColor = 0;

  if (Selection == 1) {
    return color;
  } else if (Selection == 2) {
    // AM
    float3 temp;
    temp = dot(color.rgb, float3(0.299f, 0.587f, 0.114f));
    resultColor = float4(temp, color.a);
  } else if (Selection == 3) {
    // Sepia
    float3 gray = float3(0.393f, 0.769f, 0.189f);
    float3 temp = dot(color.rgb, gray);
    temp.r += 0.2f;
    temp.g += 0.1f;
    resultColor = float4(temp, color.a);
  } else if (Selection == 4) {
    // Negative
    float3 negative = 1 - abs(color.rgb);
    resultColor = float4(negative, color.a);
  } else if (Selection == 5) {
    // Posterize
    float3 value = float3(1.0f, 1.0f, 4.0f);
    float3 posterize = round(color.rgb * value) / value;
    resultColor = float4(posterize, color.a);
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