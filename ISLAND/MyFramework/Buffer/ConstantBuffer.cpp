#include "Framework.h"

ConstantBuffer::ConstantBuffer(void* data, UINT dataSize)
    : data(data), dataSize(dataSize)
{
    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.ByteWidth = dataSize;
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    V(DEVICE->CreateBuffer(&bd, nullptr, &buffer));
}

ConstantBuffer::~ConstantBuffer()
{
    buffer->Release();
}

void ConstantBuffer::MapData()
{
    D3D11_MAPPED_SUBRESOURCE subResource;

    DC->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
    memcpy(subResource.pData, data, dataSize);
    DC->Unmap(buffer, 0);
}

void ConstantBuffer::SetVSBuffer(UINT slot)
{
    MapData();
    DC->VSSetConstantBuffers(slot, 1, &buffer);
}

void ConstantBuffer::SetPSBuffer(UINT slot)
{
    MapData();
    DC->PSSetConstantBuffers(slot, 1, &buffer);
}
