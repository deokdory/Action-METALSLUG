#include "Framework.h"
#include "TextureRect.h"

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation,
                         std::wstring path)
    : position(position),
      size(size),
      rotation(rotation) {

  Texture2D* texture = new Texture2D(path);

  // vertices
  vertices.assign(4, VertexTexture());

  vertices[0].position = verticesLocalPosition[0] = Vector3(-0.5f, -0.5f, 0.0f);
  vertices[1].position = verticesLocalPosition[1] = Vector3(0.5f, 0.5f, 0.0f);
  vertices[2].position = verticesLocalPosition[2] = Vector3(0.5f, -0.5f, 0.0f);
  vertices[3].position = verticesLocalPosition[3] = Vector3(-0.5f, 0.5f, 0.0f);

  vertices[0].uv = Vector2(0, 1);
  vertices[1].uv = Vector2(1, 0);
  vertices[2].uv = Vector2(1, 1);
  vertices[3].uv = Vector2(0, 0);

  // vertex Buffer
  vertexBuffer = new VertexBuffer;
  vertexBuffer->Create(vertices, D3D11_USAGE_DYNAMIC);

  // index Buffer
  incides = {0, 1, 2, 0, 3, 1};
  indexBuffer = new IndexBuffer();
  indexBuffer->Create(incides, D3D11_USAGE_IMMUTABLE);

  // Texture Buffer
  textureBuffer = new TextureBuffer();

  // vertex Shader
  vertexShader = new VertexShader();
  vertexShader->Create(ShaderPath + L"VertexTexture.hlsl", "VS");

  // pixel Shader
  pixelShader = new PixelShader();
  pixelShader->Create(ShaderPath + L"VertexTexture.hlsl", "PS");

  // input Layout
  inputLayout = new InputLayout();
  inputLayout->Create(VertexTexture::descs, VertexTexture::count, vertexShader->GetBlob());

  // world Buffer
  worldBuffer = new WorldBuffer();

  // Shader Resource View
  {
    shaderResourceView = texture->GetSRV();
  }
  SAFE_DELETE(texture);
}

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation) 
: position(position), size(size), rotation(rotation) {
  // vertices
  vertices.assign(4, VertexTexture());

  vertices[0].position = verticesLocalPosition[0] = Vector3(-0.5f, -0.5f, 0.0f);
  vertices[1].position = verticesLocalPosition[1] = Vector3(0.5f, 0.5f, 0.0f);
  vertices[2].position = verticesLocalPosition[2] = Vector3(0.5f, -0.5f, 0.0f);
  vertices[3].position = verticesLocalPosition[3] = Vector3(-0.5f, 0.5f, 0.0f);

  vertices[0].uv = Vector2(0, 1);
  vertices[1].uv = Vector2(1, 0);
  vertices[2].uv = Vector2(1, 1);
  vertices[3].uv = Vector2(0, 0);

  // vertex Buffer
  vertexBuffer = new VertexBuffer;
  vertexBuffer->Create(vertices, D3D11_USAGE_DYNAMIC);

  // index Buffer
  incides = {0, 1, 2, 0, 3, 1};
  indexBuffer = new IndexBuffer();
  indexBuffer->Create(incides, D3D11_USAGE_IMMUTABLE);
  
  // Texture Buffer
  textureBuffer = new TextureBuffer();

  // vertex Shader
  vertexShader = new VertexShader();
  vertexShader->Create(ShaderPath + L"VertexTexture.hlsl", "VS");

  // pixel Shader
  pixelShader = new PixelShader();
  pixelShader->Create(ShaderPath + L"VertexTexture.hlsl", "PS");

  // input Layout
  inputLayout = new InputLayout();
  inputLayout->Create(VertexTexture::descs, VertexTexture::count, vertexShader->GetBlob());

  // world Buffer
  worldBuffer = new WorldBuffer();
}

TextureRect::~TextureRect() {
  SAFE_RELEASE(shaderResourceView);
  SAFE_DELETE(worldBuffer);
  SAFE_DELETE(inputLayout);
  SAFE_DELETE(pixelShader);
  SAFE_DELETE(vertexShader);
  SAFE_DELETE(indexBuffer);
  SAFE_DELETE(vertexBuffer);
}

void TextureRect::Move(Vector2 move) { 
  position += {move.x, move.y, 0.0f};
}

void TextureRect::MapVertexBuffer() {
  DC->Map(vertexBuffer->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
}

void TextureRect::UnmapVertexBuffer() {
  std::memcpy(subResource.pData, vertices.data(),
              sizeof(vertices[0]) * vertices.size());
  DC->Unmap(vertexBuffer->GetResource(), 0);
  
}

void TextureRect::SetShader(std::wstring shaderpath) {
  vertexShader->Clear();
  pixelShader->Clear();

  vertexShader->Create(shaderpath, "VS");
  pixelShader->Create(shaderpath, "PS");
}

void TextureRect::SetAnchorPoint(int point) {

  if (point < 0 || point > 8) return;

  {
    switch (point) {
      case 0: {
        MapVertexBuffer();
        vertices[0].position = verticesLocalPosition[0] =
            Vector3(-0.5f, -0.5f, 0.0f);
        vertices[1].position = verticesLocalPosition[1] =
            Vector3(0.5f, 0.5f, 0.0f);
        vertices[2].position = verticesLocalPosition[2] =
            Vector3(0.5f, -0.5f, 0.0f);
        vertices[3].position = verticesLocalPosition[3] =
            Vector3(-0.5f, 0.5f, 0.0f);
        UnmapVertexBuffer();
        return;
      }
      case 1: {
        MapVertexBuffer();
        vertices[0].position = verticesLocalPosition[0] =
            Vector3(0.0f, -1.0f, 0.0f);
        vertices[1].position = verticesLocalPosition[1] =
            Vector3(1.0f, 0.0f, 0.0f);
        vertices[2].position = verticesLocalPosition[2] =
            Vector3(1.0f, -1.0f, 0.0f);
        vertices[3].position = verticesLocalPosition[3] =
            Vector3(0.0f, 0.0f, 0.0f);
        UnmapVertexBuffer();
        return;
      }
      case 2: {
        MapVertexBuffer();
        vertices[0].position = verticesLocalPosition[0] =
            Vector3(-0.5f, -1.0f, 0.0f);
        vertices[1].position = verticesLocalPosition[1] =
            Vector3(0.5f, 0.0f, 0.0f);
        vertices[2].position = verticesLocalPosition[2] =
            Vector3(0.5f, -1.0f, 0.0f);
        vertices[3].position = verticesLocalPosition[3] =
            Vector3(-0.5f, 0.0f, 0.0f);
        UnmapVertexBuffer();
        return;
      }
      case 3: {
        MapVertexBuffer();
        vertices[0].position = verticesLocalPosition[0] =
            Vector3(-1.0f, -1.0f, 0.0f);
        vertices[1].position = verticesLocalPosition[1] =
            Vector3(0.0f, 0.0f, 0.0f);
        vertices[2].position = verticesLocalPosition[2] =
            Vector3(0.0f, -1.0f, 0.0f);
        vertices[3].position = verticesLocalPosition[3] =
            Vector3(-1.0f, 0.0f, 0.0f);
        UnmapVertexBuffer();
        return;
      }
      case 4: {
        MapVertexBuffer();
        vertices[0].position = verticesLocalPosition[0] =
            Vector3(0.0f, -0.5f, 0.0f);
        vertices[1].position = verticesLocalPosition[1] =
            Vector3(1.0f, 0.5f, 0.0f);
        vertices[2].position = verticesLocalPosition[2] =
            Vector3(1.0f, -0.5f, 0.0f);
        vertices[3].position = verticesLocalPosition[3] =
            Vector3(0.0f, 0.5f, 0.0f);
        UnmapVertexBuffer();
        return;
      }
      case 5: {
        MapVertexBuffer();
        vertices[0].position = verticesLocalPosition[0] =
            Vector3(-1.0f, -0.5f, 0.0f);
        vertices[1].position = verticesLocalPosition[1] =
            Vector3(0.0f, 0.5f, 0.0f);
        vertices[2].position = verticesLocalPosition[2] =
            Vector3(0.0f, -0.5f, 0.0f);
        vertices[3].position = verticesLocalPosition[3] =
            Vector3(-1.0f, 0.5f, 0.0f);
        UnmapVertexBuffer();
        return;
      }
      case 6: {
        MapVertexBuffer();
        vertices[0].position = verticesLocalPosition[0] =
            Vector3(0.0f, 0.0f, 0.0f);
        vertices[1].position = verticesLocalPosition[1] =
            Vector3(1.0f, 1.0f, 0.0f);
        vertices[2].position = verticesLocalPosition[2] =
            Vector3(1.0f, 0.0f, 0.0f);
        vertices[3].position = verticesLocalPosition[3] =
            Vector3(0.0f, 1.0f, 0.0f);
        UnmapVertexBuffer();
        return;
      }
      case 7: {
        MapVertexBuffer();
        vertices[0].position = verticesLocalPosition[0] =
            Vector3(-0.5f, 0.0f, 0.0f);
        vertices[1].position = verticesLocalPosition[1] =
            Vector3(0.5f, 1.0f, 0.0f);
        vertices[2].position = verticesLocalPosition[2] =
            Vector3(0.5f, 0.0f, 0.0f);
        vertices[3].position = verticesLocalPosition[3] =
            Vector3(-0.5f, 1.0f, 0.0f);
        UnmapVertexBuffer();
        return;
      }
      case 8: {
        MapVertexBuffer();
        vertices[0].position = verticesLocalPosition[0] =
            Vector3(-1.0f, 0.0f, 0.0f);
        vertices[1].position = verticesLocalPosition[1] =
            Vector3(0.0f, 1.0f, 0.0f);
        vertices[2].position = verticesLocalPosition[2] =
            Vector3(0.0f, 0.0f, 0.0f);
        vertices[3].position = verticesLocalPosition[3] =
            Vector3(-1.0f, 1.0f, 0.0f);
        UnmapVertexBuffer();
        return;
      }
      default: {
        return;
      }
    }
  }
}

void TextureRect::Update() {
  UpdateWorld();
}

void TextureRect::UpdateWorld() {
  D3DXMatrixTranslation(&transMatrix, position.x, position.y, position.z);
  D3DXMatrixScaling(&scaleMatrix, size.x, size.y, size.z);
  D3DXMatrixRotationZ(&rotationMatrix, (float)D3DXToRadian(rotation));

  worldMatrix = scaleMatrix * rotationMatrix * transMatrix;
  worldBuffer->SetWorld(worldMatrix);
}

void TextureRect::Render() {
  vertexBuffer->SetIA();
  indexBuffer->SetIA();
  inputLayout->SetIA();
  DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  vertexShader->SetShader();
  pixelShader->SetShader();
  worldBuffer->SetVSBuffer(0);

  textureBuffer->SetPSBuffer(2);
  DC->PSSetShaderResources(0, 1, &shaderResourceView);

  DC->DrawIndexed(indexBuffer->GetCount(), 0, 0);
}

void TextureRect::GUI() {}

void TextureRect::SetIsFliped(bool bFliped) {
  textureBuffer->Flip(bFliped);
  this->bFliped = bFliped;
}
