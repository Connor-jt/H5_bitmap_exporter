
#include "recovered_structs.h"

HINSTANCE mod;
bool IsDllLoaded = false;

typedef bool __stdcall externLoadScanline(DirectX::XMVECTOR* pDestination, size_t count, const void* pSource, size_t size, DXGI_FORMAT format) noexcept; // { return true; }
externLoadScanline* ref_LoadScanline;

typedef bool __stdcall extern_LoadScanline(DirectX::XMVECTOR* pDestination, size_t count, const void* pSource, size_t size, DXGI_FORMAT format) noexcept;
extern_LoadScanline* ref__LoadScanline;


typedef bool __stdcall externStoreScanline(void* pDestination, size_t size, DXGI_FORMAT format, const DirectX::XMVECTOR* pSource, size_t count, float threshold) noexcept; // { return true; }
externStoreScanline* ref_StoreScanline;

typedef bool __stdcall extern_StoreScanline(void* pDestination, size_t size, DXGI_FORMAT format, const DirectX::XMVECTOR* pSource, size_t count, float threshold) noexcept;
extern_StoreScanline* ref__StoreScanline;


typedef HRESULT __stdcall externXGCreateTexture1DComputer(XG_TEXTURE1D_DESC* texdata, XGTextureAddressComputer** computer); // { return S_OK; }
externXGCreateTexture1DComputer* ref_XGCreateTexture1DComputer;

typedef HRESULT __stdcall externXGCreateTexture2DComputer(XG_TEXTURE2D_DESC* texdata, XGTextureAddressComputer** computer); // { return S_OK; }
externXGCreateTexture2DComputer* ref_XGCreateTexture2DComputer;

typedef HRESULT __stdcall externXGCreateTexture3DComputer(XG_TEXTURE3D_DESC* texdata, XGTextureAddressComputer** computer); // { return S_OK; }
externXGCreateTexture3DComputer* ref_XGCreateTexture3DComputer;

typedef XG_TILE_MODE __stdcall externXGComputeOptimalTileMode(XG_RESOURCE_DIMENSION dimension, XG_FORMAT format, UINT width, UINT height, UINT depth__, UINT something, XG_BIND_FLAG bind_flag); // { return (XG_TILE_MODE)0; }
externXGComputeOptimalTileMode* ref_XGComputeOptimalTileMode;

#include <strsafe.h>
void VerifyDll() {
    if (IsDllLoaded) return;

    HINSTANCE mod = LoadLibrary(L"xg.dll");
    if (!mod){
        LPVOID lpMsgBuf;
        DWORD dw = GetLastError();
        std::string result = "[DLL ERROR] : xg.dll failed to load, process cannot continue, code: " + dw;
        throw std::exception(result.c_str());
    }
    ref_XGCreateTexture1DComputer = (externXGCreateTexture1DComputer*)GetProcAddress(mod, "XGCreateTexture1DComputer");
    if (!ref_XGCreateTexture1DComputer) throw std::exception("[DLL ERROR] : function 'XGCreateTexture1DComputer' could not be loaded, non-critical but process will not continue");
    ref_XGCreateTexture2DComputer = (externXGCreateTexture2DComputer*)GetProcAddress(mod, "XGCreateTexture2DComputer");
    if (!ref_XGCreateTexture2DComputer) throw std::exception("[DLL ERROR] : function 'XGCreateTexture2DComputer' could not be loaded, critical error, the process cannot continue");
    ref_XGCreateTexture3DComputer = (externXGCreateTexture3DComputer*)GetProcAddress(mod, "XGCreateTexture3DComputer");
    if (!ref_XGCreateTexture3DComputer) throw std::exception("[DLL ERROR] : function 'XGCreateTexture3DComputer' could not be loaded, non-critical but process will not continue");

    ref_XGComputeOptimalTileMode =  (externXGComputeOptimalTileMode*)GetProcAddress(mod, "XGComputeOptimalTileMode");
    if (!ref_XGComputeOptimalTileMode) throw std::exception("[DLL ERROR] : function 'XGComputeOptimalTileMode' could not be loaded, non-critical but process will not continue");

    IsDllLoaded = true;
}
bool verifyTextureComputer(XGTextureAddressComputer** computer) {
    // no code for this yet
    // but we do need to validate that the classes functions actually exist
    // although with the two different versions of the dll's that might be hard to achieve
    return true;
}

HRESULT XG_DLL::XGCreateTexture1DComputer(XG_TEXTURE1D_DESC* texdata, XGTextureAddressComputer** computer) {
    VerifyDll();
    HRESULT result = ref_XGCreateTexture1DComputer(texdata, computer);
    verifyTextureComputer(computer);
    return result;
}

HRESULT XG_DLL::XGCreateTexture2DComputer(XG_TEXTURE2D_DESC* texdata, XGTextureAddressComputer** computer) {
    VerifyDll();
    HRESULT result = ref_XGCreateTexture2DComputer(texdata, computer);
    verifyTextureComputer(computer);
    return result;
}

HRESULT XG_DLL::XGCreateTexture3DComputer(XG_TEXTURE3D_DESC* texdata, XGTextureAddressComputer** computer){
    VerifyDll();
    HRESULT result = ref_XGCreateTexture3DComputer(texdata, computer);
    verifyTextureComputer(computer);
    return result;
}

XG_TILE_MODE XG_DLL::XGComputeOptimalTileMode(XG_RESOURCE_DIMENSION dimension, XG_FORMAT format, UINT width, UINT height, UINT depth__, UINT something, XG_BIND_FLAG bind_flag){
    VerifyDll();
    return ref_XGComputeOptimalTileMode(dimension, format, width, height, depth__, something, bind_flag);
}

