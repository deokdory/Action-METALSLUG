#include "Framework.h"
#include "RenderTexture.h"

RenderTexture::RenderTexture() {
  D3D11_TEXTURE2D_DESC textureDesc;
  ZeroMemory(&textureDesc, sizeof(D3D11_TEXTURE2D_DESC));
  // Fill Texture2D Desc
  // �׷���ī�忡�� ����ϴ� �ؽ��� ������
  {
    textureDesc.Width = WinMaxWidth;
    textureDesc.Height = WinMaxHeight;
    textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    textureDesc.Usage = D3D11_USAGE_DEFAULT;
    textureDesc.BindFlags =
        D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.SampleDesc.Quality = 0;
    textureDesc.MipLevels = 1;
    textureDesc.ArraySize = 1;
    textureDesc.MiscFlags = 0;

    HRESULT hr = DEVICE->CreateTexture2D(&textureDesc, nullptr, &mTexture);
    CHECK(hr);
  }

  D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
  ZERO_MEMORY(rtvDesc);
  {
    rtvDesc.Format = textureDesc.Format;
    rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
    rtvDesc.Texture2D.MipSlice = 0;

    HRESULT hr = DEVICE->CreateRenderTargetView(mTexture, &rtvDesc, &mRtv);
    CHECK(hr);
  }

  D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
  ZERO_MEMORY(srvDesc);
  {
    srvDesc.Format = textureDesc.Format;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = 1;

    HRESULT hr = DEVICE->CreateShaderResourceView(mTexture, &srvDesc, &shaderResourceView);
    CHECK(hr);
  }
}

RenderTexture::~RenderTexture() {
  SAFE_RELEASE(shaderResourceView);
  SAFE_RELEASE(mRtv);
  SAFE_RELEASE(mTexture);
}

void RenderTexture::RenderToTexture() {
  // OM �ܰ迡�� ����� RTV �� ����-���ٽ� �� ����
  DC->OMSetRenderTargets(1, &mRtv, nullptr);
  DC->ClearRenderTargetView(mRtv, Values::ClearColor);
}

/*
Texture2D
- �׷���ī�忡�� ����ϴ� �ؽ��� �����͸� �����ϴ� ��ü
- �ַ� �̹���, ����, ������, ����Ʈ�� ���� ����
- ũ��, ����, �Ӹ�, ��Ƽ���ø� �� �پ��� �Ӽ��� ���� �� �ִ�

Shader Resource View
- �ؽ��ĸ� ���̴����� �б� ���� ��
- ���̴��� �ؽ��ĸ� �о �ȼ��� ���� ���
- SRV�� ����Ͽ� ���̴��� �ؽ��� �����Ϳ� �������� �� �ִ�

Render Target View
- ���� Ÿ�ٿ� ���� ��
- ���̴� ����� �����ϴ� ����
- �ش� ���ۿ� ���� �ϱ�/���� �׼����� ����
- ���̴� ����� ���� Ÿ�ٿ� ������ �� �ִ�

(View : ���ҽ��� Ư�� �κ��̳� Ư�� ������� �ؼ��� �����͸� �����ϴ� ��ü)

MipMap
- DirectX���� �Ʒ��� ������ ���� �ؽ����� ���� �ػ� ������ �����ϴ� �̹��� �÷���
- ������ �ػ� ������ �迭�� ����
  - 3D �������� ��ü�� ȭ�鿡 ����� ���� ũ�� ���̰�, �ָ� ���� ���� �۰� ���δ�
  - ����� ��ü���� ���� �ػ��� �ؽ��ĸ� �����ϰ�, �ָ� �ִ� ��ü���� ���� �ؽ��ĸ� �����Ѵ�
    -> �ڿ� ��뷮�� �پ��� ������ �ӵ��� ������
*/
