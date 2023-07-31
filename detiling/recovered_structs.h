
#include <wtypes.h>
#include <DirectXTex.h>

#pragma once


#pragma pack(push,1)
typedef enum XG_FORMAT {
	XG_FORMAT_UNKNOWN = 0,
	XG_FORMAT_R32G32B32A32_TYPELESS = 1,
	XG_FORMAT_R32G32B32A32_FLOAT = 2,
	XG_FORMAT_R32G32B32A32_UINT = 3,
	XG_FORMAT_R32G32B32A32_SINT = 4,
	XG_FORMAT_R32G32B32_TYPELESS = 5,
	XG_FORMAT_R32G32B32_FLOAT = 6,
	XG_FORMAT_R32G32B32_UINT = 7,
	XG_FORMAT_R32G32B32_SINT = 8,
	XG_FORMAT_R16G16B16A16_TYPELESS = 9,
	XG_FORMAT_R16G16B16A16_FLOAT = 10,
	XG_FORMAT_R16G16B16A16_UNORM = 11,
	XG_FORMAT_R16G16B16A16_UINT = 12,
	XG_FORMAT_R16G16B16A16_SNORM = 13,
	XG_FORMAT_R16G16B16A16_SINT = 14,
	XG_FORMAT_R32G32_TYPELESS = 15,
	XG_FORMAT_R32G32_FLOAT = 16,
	XG_FORMAT_R32G32_UINT = 17,
	XG_FORMAT_R32G32_SINT = 18,
	XG_FORMAT_R32G8X24_TYPELESS = 19,
	XG_FORMAT_D32_FLOAT_S8X24_UINT = 20,
	XG_FORMAT_R32_FLOAT_X8X24_TYPELESS = 21,
	XG_FORMAT_X32_TYPELESS_G8X24_UINT = 22,
	XG_FORMAT_R10G10B10A2_TYPELESS = 23,
	XG_FORMAT_R10G10B10A2_UNORM = 24,
	XG_FORMAT_R10G10B10A2_UINT = 25,
	XG_FORMAT_R11G11B10_FLOAT = 26,
	XG_FORMAT_R8G8B8A8_TYPELESS = 27,
	XG_FORMAT_R8G8B8A8_UNORM = 28,
	XG_FORMAT_R8G8B8A8_UNORM_SRGB = 29,
	XG_FORMAT_R8G8B8A8_UINT = 30,
	XG_FORMAT_R8G8B8A8_SNORM = 31,
	XG_FORMAT_R8G8B8A8_SINT = 32,
	XG_FORMAT_R16G16_TYPELESS = 33,
	XG_FORMAT_R16G16_FLOAT = 34,
	XG_FORMAT_R16G16_UNORM = 35,
	XG_FORMAT_R16G16_UINT = 36,
	XG_FORMAT_R16G16_SNORM = 37,
	XG_FORMAT_R16G16_SINT = 38,
	XG_FORMAT_R32_TYPELESS = 39,
	XG_FORMAT_D32_FLOAT = 40,
	XG_FORMAT_R32_FLOAT = 41,
	XG_FORMAT_R32_UINT = 42,
	XG_FORMAT_R32_SINT = 43,
	XG_FORMAT_R24G8_TYPELESS = 44,
	XG_FORMAT_D24_UNORM_S8_UINT = 45,
	XG_FORMAT_R24_UNORM_X8_TYPELESS = 46,
	XG_FORMAT_X24_TYPELESS_G8_UINT = 47,
	XG_FORMAT_R8G8_TYPELESS = 48,
	XG_FORMAT_R8G8_UNORM = 49,
	XG_FORMAT_R8G8_UINT = 50,
	XG_FORMAT_R8G8_SNORM = 51,
	XG_FORMAT_R8G8_SINT = 52,
	XG_FORMAT_R16_TYPELESS = 53,
	XG_FORMAT_R16_FLOAT = 54,
	XG_FORMAT_D16_UNORM = 55,
	XG_FORMAT_R16_UNORM = 56,
	XG_FORMAT_R16_UINT = 57,
	XG_FORMAT_R16_SNORM = 58,
	XG_FORMAT_R16_SINT = 59,
	XG_FORMAT_R8_TYPELESS = 60,
	XG_FORMAT_R8_UNORM = 61,
	XG_FORMAT_R8_UINT = 62,
	XG_FORMAT_R8_SNORM = 63,
	XG_FORMAT_R8_SINT = 64,
	XG_FORMAT_A8_UNORM = 65,
	XG_FORMAT_R1_UNORM = 66,
	XG_FORMAT_R9G9B9E5_SHAREDEXP = 67,
	XG_FORMAT_R8G8_B8G8_UNORM = 68,
	XG_FORMAT_G8R8_G8B8_UNORM = 69,
	XG_FORMAT_BC1_TYPELESS = 70,
	XG_FORMAT_BC1_UNORM = 71,
	XG_FORMAT_BC1_UNORM_SRGB = 72,
	XG_FORMAT_BC2_TYPELESS = 73,
	XG_FORMAT_BC2_UNORM = 74,
	XG_FORMAT_BC2_UNORM_SRGB = 75,
	XG_FORMAT_BC3_TYPELESS = 76,
	XG_FORMAT_BC3_UNORM = 77,
	XG_FORMAT_BC3_UNORM_SRGB = 78,
	XG_FORMAT_BC4_TYPELESS = 79,
	XG_FORMAT_BC4_UNORM = 80,
	XG_FORMAT_BC4_SNORM = 81,
	XG_FORMAT_BC5_TYPELESS = 82,
	XG_FORMAT_BC5_UNORM = 83,
	XG_FORMAT_BC5_SNORM = 84,
	XG_FORMAT_B5G6R5_UNORM = 85,
	XG_FORMAT_B5G5R5A1_UNORM = 86,
	XG_FORMAT_B8G8R8A8_UNORM = 87,
	XG_FORMAT_B8G8R8X8_UNORM = 88,
	XG_FORMAT_R10G10B10_XR_BIAS_A2_UNORM = 89,
	XG_FORMAT_B8G8R8A8_TYPELESS = 90,
	XG_FORMAT_B8G8R8A8_UNORM_SRGB = 91,
	XG_FORMAT_B8G8R8X8_TYPELESS = 92,
	XG_FORMAT_B8G8R8X8_UNORM_SRGB = 93,
	XG_FORMAT_BC6H_TYPELESS = 94,
	XG_FORMAT_BC6H_UF16 = 95,
	XG_FORMAT_BC6H_SF16 = 96,
	XG_FORMAT_BC7_TYPELESS = 97,
	XG_FORMAT_BC7_UNORM = 98,
	XG_FORMAT_BC7_UNORM_SRGB = 99,
	XG_FORMAT_AYUV = 100,
	XG_FORMAT_Y410 = 101,
	XG_FORMAT_Y416 = 102,
	XG_FORMAT_NV12 = 103,
	XG_FORMAT_P010 = 104,
	XG_FORMAT_P016 = 105,
	XG_FORMAT_420_OPAQUE = 106,
	XG_FORMAT_YUY2 = 107,
	XG_FORMAT_Y210 = 108,
	XG_FORMAT_Y216 = 109,
	XG_FORMAT_NV11 = 110,
	XG_FORMAT_AI44 = 111,
	XG_FORMAT_IA44 = 112,
	XG_FORMAT_P8 = 113,
	XG_FORMAT_A8P8 = 114,
	XG_FORMAT_B4G4R4A4_UNORM = 115,
	XG_FORMAT_P208 = 130,
	XG_FORMAT_V208 = 131,
	XG_FORMAT_V408 = 132,
	XG_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE,
	XG_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE,
	XG_FORMAT_FORCE_UINT = 0xffffffff
};


// source: https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_bind_flag
// chance this doesn't match exactly
typedef enum XG_BIND_FLAG : UINT {
	XG_BIND_VERTEX_BUFFER = 0x1L,
	XG_BIND_INDEX_BUFFER = 0x2L,
	XG_BIND_CONSTANT_BUFFER = 0x4L,
	XG_BIND_SHADER_RESOURCE = 0x8L,
	XG_BIND_STREAM_OUTPUT = 0x10L,
	XG_BIND_RENDER_TARGET = 0x20L, // CONFIRMED
	XG_BIND_DEPTH_STENCIL = 0x40L, // CONFIRMED
	XG_BIND_UNORDERED_ACCESS = 0x80L,
	XG_BIND_DECODER = 0x200L,
	XG_BIND_VIDEO_ENCODER = 0x400L
};
// source: https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_resource_misc_flag
// potentially incorrect
typedef enum XG_RESOURCE_MISC_FLAG : UINT {
	XG_RESOURCE_MISC_GENERATE_MIPS = 0x1L,
	XG_RESOURCE_MISC_SHARED = 0x2L,
	XG_RESOURCE_MISC_TEXTURECUBE = 0x4L,
	XG_RESOURCE_MISC_DRAWINDIRECT_ARGS = 0x10L,
	XG_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS = 0x20L,
	XG_RESOURCE_MISC_BUFFER_STRUCTURED = 0x40L,
	XG_RESOURCE_MISC_RESOURCE_CLAMP = 0x80L,
	XG_RESOURCE_MISC_SHARED_KEYEDMUTEX = 0x100L,
	XG_RESOURCE_MISC_GDI_COMPATIBLE = 0x200L,
	XG_RESOURCE_MISC_SHARED_NTHANDLE = 0x800L,
	XG_RESOURCE_MISC_RESTRICTED_CONTENT = 0x1000L,
	XG_RESOURCE_MISC_RESTRICT_SHARED_RESOURCE = 0x2000L,
	XG_RESOURCE_MISC_RESTRICT_SHARED_RESOURCE_DRIVER = 0x4000L,
	XG_RESOURCE_MISC_GUARDED = 0x8000L,
	XG_RESOURCE_MISC_TILE_POOL = 0x20000L,
	XG_RESOURCE_MISC_TILED = 0x40000L,
	XG_RESOURCE_MISC_HW_PROTECTED = 0x80000L,
	XG_RESOURCE_MISC_SHARED_DISPLAYABLE,
	XG_RESOURCE_MISC_SHARED_EXCLUSIVE_WRITER
};
// source: https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_cpu_access_flag
typedef enum XG_CPU_ACCESS_FLAG {
	XG_CPU_ACCESS_WRITE = 0x10000L,
	XG_CPU_ACCESS_READ = 0x20000L
};
// source: DirectXTex.h : LINE 134 (it confirms these match elsewhere)
enum XG_RESOURCE_DIMENSION
{	// "Subset here matches D3D10_RESOURCE_DIMENSION and D3D11_RESOURCE_DIMENSION"
	XG_RESOURCE_DIMENSION_TEXTURE1D = 2,
	XG_RESOURCE_DIMENSION_TEXTURE2D = 3,
	XG_RESOURCE_DIMENSION_TEXTURE3D = 4,
};
enum XG_TILE_MODE : UINT {
	// unknown // placeholder
	XG_TILE_MODE_INVALID = 0,
	XG_TILE_MODE_LINEAR = 1,
};
typedef enum XG_USAGE {
	XG_USAGE_DEFAULT = 0,
	XG_USAGE_IMMUTABLE = 1,
	XG_USAGE_DYNAMIC = 2,
	XG_USAGE_STAGING = 3
};
typedef enum XG_TEXTURE_LAYOUT {
	XG_TEXTURE_LAYOUT_UNKNOWN = 0,
	XG_TEXTURE_LAYOUT_ROW_MAJOR = 1,
	XG_TEXTURE_LAYOUT_64KB_UNDEFINED_SWIZZLE = 2,
	XG_TEXTURE_LAYOUT_64KB_STANDARD_SWIZZLE = 3
};
typedef enum XG12_RESOURCE_MISC_FLAGS {
	XG12_RESOURCE_FLAG_NONE = 0,
	XG12_RESOURCE_FLAG_ALLOW_RENDER_TARGET = 0x1,
	XG12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL = 0x2,
	XG12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS = 0x4,
	XG12_RESOURCE_FLAG_DENY_SHADER_RESOURCE = 0x8,
	XG12_RESOURCE_FLAG_ALLOW_CROSS_ADAPTER = 0x10,
	XG12_RESOURCE_FLAG_ALLOW_SIMULTANEOUS_ACCESS = 0x20,
	XG12_RESOURCE_FLAG_VIDEO_DECODE_REFERENCE_ONLY = 0x40,
	XG12_RESOURCE_FLAG_VIDEO_ENCODE_REFERENCE_ONLY = 0x80,
	XG12_RESOURCE_FLAG_RAYTRACING_ACCELERATION_STRUCTURE = 0x100
};

// basis source: https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_texture1d_desc
// accurate source: DirectXTexXboxTile.cpp : LINE 842, 202
typedef struct XG_TEXTURE1D_DESC{
	UINT Width;
	UINT MipLevels;
	UINT ArraySize;
	XG_FORMAT Format;
	XG_USAGE Usage;
	XG_BIND_FLAG BindFlags;
	XG_RESOURCE_MISC_FLAG MiscFlags;
	XG_TILE_MODE TileMode;
	UINT Pitch;
};

// source: SimpleESRAM.cpp : LINE 304
typedef struct XG_SAMPLE_DESC{
	UINT Count;
	UINT Qualtiy;
};

// basis source: https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_texture2d_desc
// accurate source: SimpleESRAM.cpp : LINE 297
typedef struct XG_TEXTURE2D_DESC{
	UINT Width;
	UINT Height;
	UINT MipLevels;
	UINT ArraySize;
	XG_FORMAT Format;
	XG_SAMPLE_DESC SampleDesc;
	XG_USAGE Usage;
	XG_BIND_FLAG BindFlags;
	XG_CPU_ACCESS_FLAG CPUAccessFlags;
	XG_RESOURCE_MISC_FLAG MiscFlags;
	//UINT ESRAMOffsetBytes; // im pretty sure these are only for the ESRAM example
	//UINT ESRAMUsageBytes;
	XG_TILE_MODE TileMode;
	UINT Pitch;
};
// basis source: https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_texture3d_desc
// accurate source: SimpleESRAM.cpp : LINE 297
typedef struct XG_TEXTURE3D_DESC {
	UINT Width;
	UINT Height;
	UINT Depth;
	UINT MipLevels;
	XG_FORMAT Format;
	XG_USAGE Usage;
	XG_BIND_FLAG BindFlags;
	XG_CPU_ACCESS_FLAG CPUAccessFlags;
	XG_RESOURCE_MISC_FLAG MiscFlags;
	XG_TILE_MODE TileMode;
	UINT Pitch;
};

typedef struct XG_RESOURCE_DESC{
	XG_RESOURCE_DIMENSION Dimension;
	UINT64 Alignment;
	UINT Width;
	UINT Height;
	UINT ArraySize;
	UINT MipLevels;
	XG_FORMAT Format;
	XG_SAMPLE_DESC SampleDesc;
	XG_TEXTURE_LAYOUT Layout;
	XG12_RESOURCE_MISC_FLAGS MiscFlags;
	// possibly pitch in here too
};

// NOT REAL STRUCT // USED TO GET THIS TO COMPILE //
typedef struct XG_mipmap{
	UINT WidthElements;
	UINT HeightElements;
	UINT PitchPixels;
	UINT PaddedDepthOrArraySize;
	UINT SizeBytes;
	UINT OffsetBytes;
	UINT PaddedHeightElements;
	UINT PaddedWidthElements;
	UINT PitchBytes;
	UINT Slice2DSizeBytes;
};
// NOT REAL STRUCT // USED TO GET THIS TO COMPILE //
typedef struct XG_plane{
	XG_mipmap* MipLayout;
	size_t BytesPerElement;
};

// size should be 1720 bytes (?) sourced from the decompiled 'GetResourceLayout' function
typedef struct XG_RESOURCE_LAYOUT {
	UINT SizeBytes; // im pretty sure this is right, judging by the decompiled code of the xg.dll
	// these are just to remove the errors aka incorrect mappings
	UINT Planes;
	XG_plane* Plane;
	UINT Dimension;
	UINT MipLevels;
	UINT BaseAlignmentBytes;

};

class XGTextureAddressComputer
{
public:
	size_t GetTexelElementOffsetBytes(UINT s, UINT level, UINT x, UINT y, UINT arrayorslice, UINT sample) { return 0L; } // REMAP THE INPUTS
	HRESULT GetResourceLayout(XG_RESOURCE_LAYOUT* layout) { return S_OK; }
	unsigned long Release() { return 0L; }
};
namespace XG_DLL{
	bool LoadScanline(DirectX::XMVECTOR* pDestination, size_t count, const void* pSource, size_t size, DXGI_FORMAT format) noexcept; // { return true; }
	typedef bool __stdcall externLoadScanline(DirectX::XMVECTOR* pDestination, size_t count, const void* pSource, size_t size, DXGI_FORMAT format) noexcept; // { return true; }
	externLoadScanline* ref_LoadScanline;

	bool _LoadScanline(DirectX::XMVECTOR* pDestination, size_t count, const void* pSource, size_t size, DXGI_FORMAT format) noexcept;
	typedef bool __stdcall extern_LoadScanline(DirectX::XMVECTOR* pDestination, size_t count, const void* pSource, size_t size, DXGI_FORMAT format) noexcept;
	extern_LoadScanline* ref__LoadScanline;


	bool StoreScanline(void* pDestination, size_t size, DXGI_FORMAT format, const DirectX::XMVECTOR* pSource, size_t count, float threshold = 0) noexcept; // { return true; }
	typedef bool __stdcall externStoreScanline(void* pDestination, size_t size, DXGI_FORMAT format, const DirectX::XMVECTOR* pSource, size_t count, float threshold) noexcept; // { return true; }
	externStoreScanline* ref_StoreScanline;

	bool _StoreScanline(void* pDestination, size_t size, DXGI_FORMAT format, const DirectX::XMVECTOR* pSource, size_t count, float threshold = 0) noexcept;
	typedef bool __stdcall extern_StoreScanline(void* pDestination, size_t size, DXGI_FORMAT format, const DirectX::XMVECTOR* pSource, size_t count, float threshold) noexcept;
	extern_StoreScanline* ref__StoreScanline;


	HRESULT XGCreateTexture1DComputer(XG_TEXTURE1D_DESC* texdata, XGTextureAddressComputer** computer); // { return S_OK; }
	typedef HRESULT __stdcall externXGCreateTexture1DComputer(XG_TEXTURE1D_DESC* texdata, XGTextureAddressComputer** computer); // { return S_OK; }
	externXGCreateTexture1DComputer* ref_XGCreateTexture1DComputer;

	HRESULT XGCreateTexture2DComputer(XG_TEXTURE2D_DESC* texdata, XGTextureAddressComputer** computer); // { return S_OK; }
	typedef HRESULT __stdcall externXGCreateTexture2DComputer(XG_TEXTURE2D_DESC* texdata, XGTextureAddressComputer** computer); // { return S_OK; }
	externXGCreateTexture2DComputer* ref_XGCreateTexture2DComputer;

	HRESULT XGCreateTexture3DComputer(XG_TEXTURE3D_DESC* texdata, XGTextureAddressComputer** computer); // { return S_OK; }
	typedef HRESULT __stdcall externXGCreateTexture3DComputer(XG_TEXTURE3D_DESC* texdata, XGTextureAddressComputer** computer); // { return S_OK; }
	externXGCreateTexture3DComputer* ref_XGCreateTexture3DComputer;

	XG_TILE_MODE XGComputeOptimalTileMode(XG_RESOURCE_DIMENSION dimension, XG_FORMAT format, UINT width, UINT height, UINT depth__, UINT something, XG_BIND_FLAG bind_flag); // { return (XG_TILE_MODE)0; }
	typedef XG_TILE_MODE __stdcall externXGComputeOptimalTileMode(XG_RESOURCE_DIMENSION dimension, XG_FORMAT format, UINT width, UINT height, UINT depth__, UINT something, XG_BIND_FLAG bind_flag); // { return (XG_TILE_MODE)0; }
	externXGComputeOptimalTileMode* ref_XGComputeOptimalTileMode;



	// management stuff
	HINSTANCE mod;

	bool IsDllLoaded = false;
	void VerifyDll();
};

struct DDS_HEADER_XBOX_p{ // Must match structure in XboxDDSTextureLoader module
	DXGI_FORMAT dxgiFormat;
	uint32_t    resourceDimension;
	uint32_t    miscFlag; // see DDS_RESOURCE_MISC_FLAG
	uint32_t    arraySize;
	uint32_t    miscFlags2; // see DDS_MISC_FLAGS2
	uint32_t    tileMode; // see XG_TILE_MODE / XG_SWIZZLE_MODE
	uint32_t    baseAlignment;
	uint32_t    dataSize;
	uint32_t    xdkVer; // matching _XDK_VER / _GXDK_VER
};
/* // for RE reference
struct DDS_HEADER_DXT10{
	DXGI_FORMAT     dxgiFormat;
	uint32_t        resourceDimension;
	uint32_t        miscFlag; // see D3D11_RESOURCE_MISC_FLAG
	uint32_t        arraySize;
	uint32_t        miscFlags2; // see DDS_MISC_FLAGS2
};*/

// we aren't given direct access to these through the xbox header reference


struct DDS_PIXELFORMAT_p{
	uint32_t    size;
	uint32_t    flags;
	uint32_t    fourCC;
	uint32_t    RGBBitCount;
	uint32_t    RBitMask;
	uint32_t    GBitMask;
	uint32_t    BBitMask;
	uint32_t    ABitMask;
};
struct DDS_HEADER_p{
	uint32_t        size;
	uint32_t        flags;
	uint32_t        height;
	uint32_t        width;
	uint32_t        pitchOrLinearSize;
	uint32_t        depth; // only if DDS_HEADER_FLAGS_VOLUME is set in flags
	uint32_t        mipMapCount;
	uint32_t        reserved1[11];
	DDS_PIXELFORMAT_p ddspf;
	uint32_t        caps;
	uint32_t        caps2;
	uint32_t        caps3;
	uint32_t        caps4;
	uint32_t        reserved2;
};


#pragma pack(pop)
/*
if (layout.Planes != 1)
return HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED);

if (layout.SizeBytes != xbox.GetSize()
	|| layout.BaseAlignmentBytes != xbox.GetAlignment())
	return E_UNEXPECTED; */