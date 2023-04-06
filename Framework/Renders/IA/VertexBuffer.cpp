#include "Framework.h"
#include "VertexBuffer.h"

VertexBuffer::~VertexBuffer() { SAFE_RELEASE(buffer); }

// Input Assembler
void VertexBuffer::SetIA() {
  // �Է� ������� ���� ���۸� �Է��ϴ� �Լ�
  DC->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
}
