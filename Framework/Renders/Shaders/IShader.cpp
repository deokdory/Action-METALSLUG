#include "Framework.h"
#include "IShader.h"


void IShader::CompileShader(std::wstring path, std::string entryName,
                            std::string profile, ID3DBlob** blob) {
  ID3DBlob* error = nullptr;  // �����Ϸ� ���� �޼����� ������ blob ������ ����
  // ���̴��� ������, ����� blob �����ͷ� ���� ����
  HRESULT hr = D3DCompileFromFile(
      path.c_str(),  // �������� ���̴� ���
      nullptr,       // ���̴� ������ ����� ��Ÿ���� ������
      nullptr,       // ��� �� ��
      entryName.c_str(),  // �������� ���̴� ���Ͽ��� ����
                          // ���������� ����� �Լ� �̸�
      profile.c_str(),  // �������� ���̴� ���Ͽ��� ����� ������ �̸�
      D3DCOMPILE_ENABLE_STRICTNESS,  // ������ ������ �ɼ� / ��� �޼����� ����
                                     // 1�� ����
      0,  // ����� ������ ���Ե� ������ ����� �����ϱ� ���� �ɼ�
      blob,  // ������ ����� ������ blob ������ �ּҰ�
      &error  // �����Ϸ� ���� �޼����� ������ blob ������ �ּҰ�
  );
  CheckShaderError(hr, error);
  SAFE_RELEASE(error);
}

void IShader::CheckShaderError(HRESULT hr, ID3DBlob* error) {
  if (FAILED(hr)) {
    if (error) {
      std::string str = (const char*)error->GetBufferPointer();
      MessageBoxA(handle, str.c_str(), "Shader Error", MB_OK);
    }
    // ���α׷� �ߴ�
    CHECK(false);
  }
}
