struct VertexInput {
  float4 position : POSITION0;   
  float4 color : COLOR0;         

};

struct PixelInput {
  float4 position : SV_POSITION0; 
                                  
  float4 color : COLOR0;          
};




cbuffer WorldBuffer : register(b0) { matrix _world; }

cbuffer VPbuffer : register(b1) {
  matrix _view;
  matrix _projection;
}

cbuffer CollisionBuffer : register(b0)
{
    bool _isOn;
}

PixelInput VS(VertexInput input) { 
  PixelInput output;

  output.position = mul(input.position, _world);          
  output.position = mul(output.position, _view);          
  output.position = mul(output.position, _projection);    

  output.color = input.color;
  return output;
}

float4 PS(PixelInput input) : SV_Target { 
    return _isOn ? input.color: float4(0, 0, 0, 0);
}
































