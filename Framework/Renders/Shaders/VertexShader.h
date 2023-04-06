// �������� ��ġ, ����, UV��ǥ ���� �Ӽ��� ���

#pragma once
#include "IShader.h"

class VertexShader : public IShader {
 public:
  ~VertexShader();

  virtual void Create(const std::wstring path,
                      const std::string entryName) override;
  virtual void Clear() override;
  virtual void SetShader() override;

  ID3DBlob* GetBlob() { return blob; }
  ID3D11VertexShader* GetResource() { return shader; }

 private:
  ID3D11VertexShader* shader = nullptr;
  ID3DBlob* blob = nullptr;
};