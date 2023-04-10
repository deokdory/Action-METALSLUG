#include "Framework.h"
#include "VertexTypes.h"

/* 
	D3D11_INPUT_ELEMENT_DESC

	SementicName			: ���� ������ �̸�
	SementicIndex			: �� �̸� �ߺ� �� ���� ���� �ε��� ��
	Format					: ������ ����
	nputSlot				: �Է� ������ �ε���
	AlignedByteOffset		: ���� �������� ����Ʈ ���� ������ ( 0 = �ڵ����)
	InputSlotClass			: ���Ǵ� ������ ������ ����
	InstanceDataStepRate	: �ν��Ͻ����� ������ �о���̴µ� ����� ���� ����Ʈ ��
*/



D3D11_INPUT_ELEMENT_DESC VertexColor::descs[]
{
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,							  D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
};

D3D11_INPUT_ELEMENT_DESC VertexTexture::descs[]
{
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,							  D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,	 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
};
