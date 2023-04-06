struct VertexInput {
  float4 position : POSITION0;   
  float2 uv : TEXCOORD0;         
};

struct PixelInput {
  float4 position : SV_POSITION0;  
  float2 uv : TEXCOORD0;  
};

cbuffer WorldBuffer : register(b0) { matrix _world; }

// ��� ���� �������� b1�� �Ҵ�� ��, �������� ����� �����ϴ� ��� ����
cbuffer VPbuffer : register(b1) {
  matrix _view;
  matrix _projection;
}

cbuffer BlurBuffer : register(b1) {
  float2 _imageSize;
  int _blurCount;
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
float4 PS(PixelInput input) : SV_Target {
  float4 color = _sourceTex.Sample(_samp, (float2)input.uv);

  // �ֺ� �ȼ��� ����
  float2 arr[8] = {float2(-1, +1), float2(+0, +1), float2(+1, +1),
                   float2(-1, +0), float2(+1, +0), float2(-1, -1),
                   float2(+0, -1), float2(+1, -1)};

    // �� ī��Ʈ��ŭ �ݺ�
  for (int blur = 1; blur < _blurCount; blur++) {
    // �ֺ� �ȼ��鿡 ���� �ݺ�
    for (int i = 0; i < 8; i++) {
      // �Է� �ؽ��Ŀ��� ���ø��� �ֺ� �ȼ����� ����� ��ġ ���
      float x = arr[i].x * (float)blur / _imageSize.x;
      float y = arr[i].y * (float)blur / _imageSize.y;

      // ���ο� uv ��ǥ ���
      float2 uv = input.uv + float2(x, y);

      // �Է� �ؽ��Ŀ� ������ �߰��� ���ø��Ͽ� ����
      color += _sourceTex.Sample(_samp, uv);
    }
  }
  // �� �ݺ� Ƚ��
  int blurInterations = _blurCount - 1;

  // ������ ����
  int offsetCount = 8;

  // ��ü ���ø� ����
  int totalSamples = blurInterations * offsetCount + 1;
    
  return color /= totalSamples;
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