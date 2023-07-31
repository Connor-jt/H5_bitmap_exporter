
#include "recovered_structs.h"


bool XG_DLL::LoadScanline(DirectX::XMVECTOR* pDestination, size_t count, const void* pSource, size_t size, DXGI_FORMAT format) noexcept {
    VerifyDll();
    return ref_LoadScanline(pDestination, count, pSource, size, format);
}

bool XG_DLL::_LoadScanline(DirectX::XMVECTOR* pDestination, size_t count, const void* pSource, size_t size, DXGI_FORMAT format) noexcept {
    VerifyDll();
    return ref__LoadScanline(pDestination, count, pSource, size, format);
}

bool XG_DLL::StoreScanline(void* pDestination, size_t size, DXGI_FORMAT format, const DirectX::XMVECTOR* pSource, size_t count, float threshold) noexcept {
    VerifyDll();
    return ref_StoreScanline(pDestination, size, format, pSource, count, threshold);
}

bool XG_DLL::_StoreScanline(void* pDestination, size_t size, DXGI_FORMAT format, const DirectX::XMVECTOR* pSource, size_t count, float threshold) noexcept {
    VerifyDll();
    return ref__StoreScanline(pDestination, size, format, pSource, count, threshold);
}

HRESULT XG_DLL::XGCreateTexture1DComputer(XG_TEXTURE1D_DESC* texdata, XGTextureAddressComputer** computer) {
    VerifyDll();
    return ref_XGCreateTexture1DComputer(texdata, computer);
}

HRESULT XG_DLL::XGCreateTexture2DComputer(XG_TEXTURE2D_DESC* texdata, XGTextureAddressComputer** computer) {
    VerifyDll();
    return ref_XGCreateTexture2DComputer(texdata, computer);
}

HRESULT XG_DLL::XGCreateTexture3DComputer(XG_TEXTURE3D_DESC* texdata, XGTextureAddressComputer** computer)
{
    return ref_XGCreateTexture3DComputer(texdata, computer);
}

XG_TILE_MODE XG_DLL::XGComputeOptimalTileMode(XG_RESOURCE_DIMENSION dimension, XG_FORMAT format, UINT width, UINT height, UINT depth__, UINT something, XG_BIND_FLAG bind_flag){
    VerifyDll();
    return ref_XGComputeOptimalTileMode(dimension, format, width, height, depth__, something, bind_flag);
}

void XG_DLL::VerifyDll(){
    if (IsDllLoaded) return;

    HINSTANCE mod = LoadLibrary(L"xg.dll");
    if (!mod) throw new std::exception("xg module failed to load");

    ref_LoadScanline = (externLoadScanline*)GetProcAddress(mod, "LoadScanline");
    //ref__LoadScanline = (extern_LoadScanline*)GetProcAddress(mod, "_LoadScanline");
    ref_StoreScanline = (externStoreScanline*)GetProcAddress(mod, "StoreScanline");
    //ref__StoreScanline = (extern_StoreScanline*)GetProcAddress(mod, "_StoreScanline");
    ref_XGCreateTexture1DComputer = (externXGCreateTexture1DComputer*)GetProcAddress(mod, "XGCreateTexture1DComputer");
    ref_XGCreateTexture2DComputer = (externXGCreateTexture2DComputer*)GetProcAddress(mod, "XGCreateTexture2DComputer");
    ref_XGCreateTexture3DComputer = (externXGCreateTexture3DComputer*)GetProcAddress(mod, "XGCreateTexture3DComputer");
    ref_XGComputeOptimalTileMode = (externXGComputeOptimalTileMode*)GetProcAddress(mod, "XGComputeOptimalTileMode");

    IsDllLoaded = true;
}
