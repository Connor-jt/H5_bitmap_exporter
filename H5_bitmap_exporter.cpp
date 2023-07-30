// H5_bitmap_exporter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <DirectXTex.h>
#include "tagprocessing/TagFramework.h"
#include "Bitm.h"


#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <algorithm>



struct Tag{
    char* data_ptr;
    char* cleanup_ptr;

};
struct resource_handle {
    resource_handle(uint64_t _size, ifstream* _read_handle, char* _content, bool _is_chunk) {
        size = _size;
        read_handle = _read_handle;
        content = _content;
        is_chunk = _is_chunk;
    }
    uint64_t size;
    ifstream* read_handle;
    char* content;
    bool is_chunk;
};

bool is_short_header(DXGI_FORMAT format) {
    switch (format) {
    case DXGI_FORMAT_R8G8B8A8_UNORM:
    case DXGI_FORMAT_R16G16_UNORM:
    case DXGI_FORMAT_R8G8_UNORM:
    case DXGI_FORMAT_R16_UNORM:
    case DXGI_FORMAT_R8_UNORM:
    case DXGI_FORMAT_A8_UNORM:
    case DXGI_FORMAT_R8G8_B8G8_UNORM:
    case DXGI_FORMAT_G8R8_G8B8_UNORM:
    case DXGI_FORMAT_BC1_UNORM:
    case DXGI_FORMAT_BC2_UNORM:
    case DXGI_FORMAT_BC3_UNORM:
    case DXGI_FORMAT_BC4_SNORM:
    case DXGI_FORMAT_BC5_SNORM:
    case DXGI_FORMAT_B5G6R5_UNORM:
    case DXGI_FORMAT_B5G5R5A1_UNORM:
    case DXGI_FORMAT_R8G8_SNORM:
    case DXGI_FORMAT_R8G8B8A8_SNORM:
    case DXGI_FORMAT_R16G16_SNORM:
    case DXGI_FORMAT_B8G8R8A8_UNORM:
    case DXGI_FORMAT_B8G8R8X8_UNORM:
    case DXGI_FORMAT_B4G4R4A4_UNORM:
    case DXGI_FORMAT_YUY2:
    case DXGI_FORMAT_R32G32B32A32_FLOAT:
    case DXGI_FORMAT_R16G16B16A16_FLOAT:
    case DXGI_FORMAT_R16G16B16A16_UNORM:
    case DXGI_FORMAT_R16G16B16A16_SNORM:
    case DXGI_FORMAT_R32G32_FLOAT:
    case DXGI_FORMAT_R16G16_FLOAT:
    case DXGI_FORMAT_R32_FLOAT:
    case DXGI_FORMAT_R16_FLOAT:
    /*  // only short header if conversion flag 'DDS_FLAGS_FORCE_DX9_LEGACY'
    case DXGI_FORMAT_R10G10B10A2_UNORM:
    case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
    case DXGI_FORMAT_BC1_UNORM_SRGB:
    case DXGI_FORMAT_BC2_UNORM_SRGB:
    case DXGI_FORMAT_BC3_UNORM_SRGB:
    case DXGI_FORMAT_BC4_UNORM:
    case DXGI_FORMAT_BC5_UNORM:
    case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
    case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB: */
        return true;
    }
    return false;
}

// function from 'https://github.com/Lord-Zedd/H5Bitmap/' //
int32_t GetFormat(uint16_t tagformat){
    switch (tagformat){
    case  0x0: return 65;
    case  0x1:
    case  0x2: return 61;
    case  0x3: return 49;
  //case  0x4:
  //case  0x5: throw new exception("unsupported image format");
    case  0x6: return 85;
  //case  0x7: throw new exception("unsupported image format");
    case  0x8: return 86;
    case  0x9: return 115;
    case  0xA: return 88;
    case  0xB: return 87;
  //case  0xC: throw new exception("unsupported image format");
    case  0xE: return 71;
    case  0xF: return 74;
    case 0x10: return 77;
  //case 0x11:
  //case 0x12:
  //case 0x13:
  //case 0x14:
  //case 0x15: throw new exception("unsupported image format");
    case 0x16: return 51;
  //case 0x17: throw new exception("unsupported image format");
    case 0x18: return 2;
    case 0x19: return 10;
    case 0x1A: 
    case 0x1B: return 54;
    case 0x1C: return 31;
    case 0x1D: return 24;
    case 0x1E: return 11;
    case 0x1F: return 37;
    case 0x20: return 56;
    case 0x21: return 35;
    case 0x22: return 13;
  //case 0x23: throw new exception("unsupported image format");
    case 0x24: return 80;
    case 0x25: return 81;
  //case 0x26: throw new exception("unsupported image format");
    case 0x27: return 84;
    case 0x28: return 107; // "This is a guess, tag defs claim this format is deprecated, yet it is still used. gg"
  //case 0x29: 
  //case 0x2A: throw new exception("unsupported image format");
    case 0x2B:
    case 0x2C: return 80;
    case 0x2D: return 83;
    case 0x2E: return 84;
    case 0x2F: return 95;
    case 0x30: return 96;
    case 0x31: return 97;
    case 0x32: return 45;
    case 0x33: return 26;
    default: return -1;
    }

}



// regular mapping
uint32_t bitmapping_size = 96;
/*uint64_t* bit_array = new uint64_t[bitmapping_size]{
0b0000000000000000000000000000000000000000000000000000000000000001,
0b0000000000000000000000000000000000000000000000000000000000000010,
0b0000000000000000000000000000000000000000000000000000000000000100,
0b0000000000000000000000000000000000000000000000000000000000001000,
0b0000000000000000000000000000000000000000000000000000000000010000,
0b0000000000000000000000000000000000000000000000000000000000100000,
0b0000000000000000000000000000000000000000000000000000000001000000,
0b0000000000000000000000000000000000000000000000000000000010000000,
0b0000000000000000000000000000000000000000000000000000000100000000,
0b0000000000000000000000000000000000000000000000000000001000000000,
0b0000000000000000000000000000000000000000000000000000010000000000,
0b0000000000000000000000000000000000000000000000000000100000000000,
0b0000000000000000000000000000000000000000000000000001000000000000,
0b0000000000000000000000000000000000000000000000000010000000000000,
0b0000000000000000000000000000000000000000000000000100000000000000,
0b0000000000000000000000000000000000000000000000001000000000000000,
0b0000000000000000000000000000000000000000000000010000000000000000,
0b0000000000000000000000000000000000000000000000100000000000000000,
0b0000000000000000000000000000000000000000000001000000000000000000,
0b0000000000000000000000000000000000000000000010000000000000000000,
0b0000000000000000000000000000000000000000000100000000000000000000,
0b0000000000000000000000000000000000000000001000000000000000000000,
0b0000000000000000000000000000000000000000010000000000000000000000,
0b0000000000000000000000000000000000000000100000000000000000000000,
0b0000000000000000000000000000000000000001000000000000000000000000,
0b0000000000000000000000000000000000000010000000000000000000000000,
0b0000000000000000000000000000000000000100000000000000000000000000,
0b0000000000000000000000000000000000001000000000000000000000000000,
0b0000000000000000000000000000000000010000000000000000000000000000,
0b0000000000000000000000000000000000100000000000000000000000000000,
0b0000000000000000000000000000000001000000000000000000000000000000,
0b0000000000000000000000000000000010000000000000000000000000000000, }; */


// mountains macro control & plain white pattern
/*
4096 x 4096
bc7_unorm__dxt5_blue_ (49)
mip count 12
tilemode 13 format 2
*//*
uint64_t* bit_array = new uint64_t[bitmapping_size]{
0b1000000000000000000, 0b1000000000000000000, 0b1000000000000000000,
0b100000000000000000, 0b100000000000000000, 0b100000000000000000,
0b10000000000000000, 0b10000000000000000, 0b10000000000000000,
0b1000000000000000, 0b1000000000000000, 0b1000000000000000,
0b100000000000000, 0b100000000000000, 0b100000000000000,
0b10000000000000, 0b10000000000000, 0b10000000000000,
0b1000000000000, 0b1000000000000, 0b1000000000000,
0b100000000, 0b100000000000, 0b100000000000,
0b10000000, 0b10000000000, 0b10000000000,
0b1000000, 0b1000000000, 0b1000000000,
0b100000, 0b100000000, 0b100000000,
0b10000, 0b10000000, 0b10000000,
0b1000, 0b1000000, 0b1000000,
0b100, 0b100000, 0b100000,
0b100000000000, 0b10000, 0b10000,
0b10, 0b1000, 0b1000,
0b10000000000, 0b100, 0b100,
0b1, 0b10, 0b10,
0b1000000000, 0b1, 0b1,
0b10000000000000000000, 0b0, 0b0,
0b100000000000000000000, 0b0, 0b0,
0b1000000000000000000000, 0b0, 0b0,
0b10000000000000000000000, 0b0, 0b0,
0b100000000000000000000000, 0b0, 0b0,
0b1000000000000000000000000, 0b0, 0b0,
0b10000000000000000000000000, 0b0, 0b0,
0b100000000000000000000000000, 0b0, 0b0,
0b1000000000000000000000000000, 0b0, 0b0,
0b10000000000000000000000000000, 0b0, 0b0,
0b100000000000000000000000000000, 0b0, 0b0,
0b1000000000000000000000000000000, 0b0, 0b0,
0b10000000000000000000000000000000, 0b0, 0b0, }; // */


/*
2048 x 4096
bc3_unorm__dxt5__dxt5_ (16)
tileMode 14 format 2
*/
uint64_t* bit_array = new uint64_t[bitmapping_size]{
0b100000000000000000,   0b100000000000000000, 0b100000000000000000,
0b10000000000000000,    0b10000000000000000, 0b10000000000000000,
0b1000000000000000,     0b1000000000000000, 0b1000000000000000,
0b100000000000000,      0b100000001100000, 0b100000000000000,
0b100000000,            0b10000000000000, 0b10000000000000,
0b10000000,             0b1000000000000, 0b1000000000000,
0b1000000,              0b100010000000, 0b100000000000,
0b100000,               0b10001000000, 0b10000000000,
0b100000000000,         0b1000000000, 0b1000000000,
0b10,                   0b100000000, 0b100000000,
0b1000000000000,        0b10001000, 0b10000000,
0b10000000000000,       0b1010000, 0b1000000,
0b10000,                0b100000, 0b100000,
0b1000,                 0b11000, 0b10000,
0b100,                  0b1000, 0b1000,
0b10000000000,          0b100, 0b100,
0b1,                    0b10, 0b10,
0b1000000000,           0b1, 0b1,
0b1000000000000000000, 0b0, 0b0,
0b10000000000000000000, 0b0, 0b0,
0b100000000000000000000, 0b0, 0b0,
0b1000000000000000000000, 0b0, 0b0,
0b10000000000000000000000, 0b0, 0b0,
0b100000000000000000000000, 0b0, 0b0,
0b1000000000000000000000000, 0b0, 0b0,
0b10000000000000000000000000, 0b0, 0b0,
0b100000000000000000000000000, 0b0, 0b0,
0b1000000000000000000000000000, 0b0, 0b0,
0b10000000000000000000000000000, 0b0, 0b0,
0b100000000000000000000000000000, 0b0, 0b0,
0b1000000000000000000000000000000, 0b0, 0b0,
0b10000000000000000000000000000000, 0b0, 0b0, }; // */

void UnSwizzle(char* pixel_buffer, uint64_t buffer_size, uint32_t pixel_stride){
    // create a new buffer to unswizzle to
    char* reference_buffer = new char[buffer_size];
    memcpy(reference_buffer, pixel_buffer, buffer_size); // this is not optimized at all
    std::fill_n(pixel_buffer, buffer_size, 0);
    // unswizzle
    uint64_t pixel_count = buffer_size / pixel_stride;
    for (uint64_t pixel_index = 0; pixel_index < pixel_count; pixel_index++){
        uint64_t active_pixel_address = pixel_index;
        uint64_t address = 0;
        for (int32_t i = 0; i < bitmapping_size; i+=3)

            if (bit_array[i+1] != 0) // no point in processing the empty plots

                // hmm, we have to ensure that at the first bit is active, second bit doesn't matter but still has to be xor'd

                if ((active_pixel_address & bit_array[i+1]) >= bit_array[i+2]){
                    active_pixel_address ^= bit_array[i+1]; // this is so when we XOR, it will affect the later bits
                    address |= bit_array[i];
                }

        if (active_pixel_address != 0)
            throw new exception("unaccounted bits");
        // im sure this not a very optimized moment here too
        memcpy(pixel_buffer + (address*pixel_stride), reference_buffer + (pixel_index * pixel_stride), pixel_stride);
    }
    // transfer the unswizzled data over
    delete[] reference_buffer;
}

void BITM_GetTexture(std::string filepath, bool deswizzle) {

    // /////////////////////////// //
    // READ BITMAP FILE & PROCESS //
    // ///////////////////////// //

    ifstream file_stream(filepath, ios::binary | ios::ate);
    if (!file_stream.is_open())
        throw new exception("failed to open bitmap tag");
    
    std::streamsize file_size = file_stream.tellg();
    if (file_size < tag_header_size)
        throw new exception("bitmap is too small to contain tag data");
    
    // read the whole file
    char* tag_bytes = new char[file_size]; // this gets cleaned up in open_ready_tag;
    file_stream.seekg(0, ios::beg);
    file_stream.read(tag_bytes, file_size);
    file_stream.close();

    // process file into runtime tag
    char* tagdata = nullptr;
    char* cleanup_ptr = nullptr;
    TAG_OBJ_TYPE tag_type = TagProcessing::Open_ready_tag(tag_bytes, file_size, tagdata, cleanup_ptr);
    if (tag_type != TAG_OBJ_TYPE::bitmap)
        throw new exception("not a bitmap file?"); // NOTE: this will fail, we will have to map the new value for bitmap struct hash things // apparently not

    // /////////////////// //
    // READ ALL RESOURCES //
    // ///////////////// //

    // we now need to look for resource files, if its a chunk, add it to the out array
    // if its a tag struct file, add it to the inputs
    vector<resource_handle>* file_resources = new vector<resource_handle>();

    // convert path into parent directory
    const size_t last_slash_idx = filepath.rfind('\\');
    if (std::string::npos == last_slash_idx)
        throw new exception("faile to calculate file directory (theres virtually no way this happens)");
    string filefolder = filepath.substr(0, last_slash_idx);


    for (const auto& entry : std::filesystem::directory_iterator(filefolder)) {
        string current_file = entry.path().string();
        if (current_file.length() > filepath.length() && filepath == current_file.substr(0, filepath.length()) && current_file[filepath.length()] == '[') {
            ifstream resource_stream(current_file, ios::binary | ios::ate);
            if (!resource_stream.is_open()) {
                continue;
            }
            std::streamsize resource_size = resource_stream.tellg();
            if (resource_size == 0) {
                continue;
            }
            // read the whole file
            char* resource_bytes = new char[resource_size];
            resource_stream.seekg(0, ios::beg);
            resource_stream.read(resource_bytes, resource_size);
            resource_stream.close(); // might as well, seeing as we're reading everything right now, needs to be changed in an optimization pass

            bool ischunked = (current_file.substr(0, current_file.length()).find(".chunk") != std::string::npos);
            resource_handle* new_resource = new resource_handle(resource_size, &resource_stream, resource_bytes, ischunked);
            file_resources->push_back(*new_resource);
        }
    }







    // //////////////////////////////////////////// //
    // BUILD IMAGE HEADER AND VERIFY COMPATIBILITY //
    // ////////////////////////////////////////// //
    // TODO: we need to output ALL of these, as they are probably different images

    bitm* bitm_tag = (bitm*)(tagdata);
    bitm::__bitmaps_* selected_bitmap = bitm_tag->bitmaps_[0];

    if (selected_bitmap->type__DO_NOT_CHANGE != bitm::__bitmaps_::__type__DO_NOT_CHANGE::_2D_texture)
        throw new exception("unsupported image type");

    if (selected_bitmap->bitmap_resource_handle_.content_ptr == 0 || selected_bitmap->bitmap_resource_handle_.content_ptr == (BitmapDataResource*)0xbcbcbcbcbcbcbcbc){
        // then we need to fetch this resource
        resource_handle* mid_resource = nullptr;
        for (int i = 0; i < file_resources->size(); i++){
            if ((*file_resources)[i].is_chunk == false) {
                mid_resource = &(*file_resources)[i];
                break;
        }}
        if (mid_resource == nullptr)
            throw new exception("no intermediate resource found");

        char* res_tagdata = nullptr;
        char* res_cleanup_ptr = nullptr;
        TagProcessing::Open_ready_tag(mid_resource->content, mid_resource->size, res_tagdata, res_cleanup_ptr);

        selected_bitmap->bitmap_resource_handle_.content_ptr = (BitmapDataResource*)res_tagdata;
    }


    BitmapDataResource* bitmap_details = selected_bitmap->bitmap_resource_handle_.content_ptr;

    DirectX::TexMetadata* meta = new DirectX::TexMetadata();

    // configure meta data

    meta->depth = selected_bitmap->depth__pixels_DO_NOT_CHANGE;
    meta->arraySize = 1; // no support for array types yet
    meta->mipLevels = 0; // it seems this does not apply for all versions // selected_bitmap->mipmap_count;
    meta->miscFlags = 0; // the only flag seems to be TEX_MISC_TEXTURECUBE = 0x4
    meta->miscFlags2 = 0;
    meta->dimension = (DirectX::TEX_DIMENSION)3; // TEX_DIMENSION_TEXTURE2D

    // test format
    uint32_t bitm_format = GetFormat(selected_bitmap->format__DO_NOT_CHANGE);
    if (bitm_format == -1)
        throw new exception("unsupported bitmap format");
    meta->format = (DXGI_FORMAT)bitm_format;


    size_t header_size = sizeof(uint32_t) + 124; // sizeof(DirectX::DDS_HEADER);
    if (!is_short_header(meta->format)) header_size += 20; // sizeof(DirectX::DDS_HEADER_DXT10);

    size_t image_data_size = 0;
    meta->width = selected_bitmap->width__pixels_DO_NOT_CHANGE;
    meta->height = selected_bitmap->height__pixels_DO_NOT_CHANGE;
    // figure out if this texture is using internal data, or resource data


    /* leftover for if reading streaming data is ever needed
    if (bitmap_details->streamingData.count == 0)
        throw new exception("no streaming data or pixel data");

    uint32_t index = 0; // probably the lowest quality // select the image that we want to be using
    if (index >= bitmap_details->streamingData.count)
        throw new exception("out of bounds index for streaming texture array");

    // we do not actually use streamingdata, because it contains virtually nothing useful
    // the only thing it really tells us anything is MAYBE the chunkinfo
    // it looks like that just tells us how many blocks of 256 our image contains
    // so to calculate the dimensions (assuming the image is square), we would use this formula
    // dimensions = Math.sqrt(chunkinfo) * 256 // idk what that is in c++
    */


    // instead of doing any of that, lets just pick the largest resource file
    int largest_resource_index = -1;
    for (int i = 0; i < file_resources->size(); i++) {
        if ((*file_resources)[i].size > image_data_size){
            largest_resource_index = i;
            image_data_size = (*file_resources)[i].size;
    }}

    bool is_using_pixel_data = false;
    if (largest_resource_index == -1){ // resort to internal pixel buffer (the lowest resolution by the looks of it)
        is_using_pixel_data = true;
        image_data_size = bitmap_details->pixels.data_size;
    }

    if (image_data_size == 0)
        throw new exception("no pixels to export from this image, possible read logic failure");

    // ///////////////////////////////////// //
    // CONVERT BITMAP TO DIRECTXTEX TEXTURE //
    // /////////////////////////////////// //

    //
    // NOTE: most of this process is entirely unnecessary
    // its only used because the original code was doing this to debug each step
    //

    std::cout << "eoncoding bitmap header\n";
    char* DDSheader_dest = new char[header_size + image_data_size];
    size_t output_size = 0;
    HRESULT hr = EncodeDDSHeader(*meta, DirectX::DDS_FLAGS_NONE, (void*)DDSheader_dest, header_size, output_size);
    if (!SUCCEEDED(hr))
        throw new exception("image failed to generate DDS header");
    if (header_size != output_size)
        // DXGI_FORMAT_BC1_UNORM_SRGB (72) is actually long header? // TODO??
        throw new exception("header size was incorrectly assumed! must investigate this image format!!!");

    std::cout << "copying bitmap data\n";
    // then write the bitmap data
    if (is_using_pixel_data)  // non-resource pixel array
        memcpy(DDSheader_dest + header_size, bitmap_details->pixels.content_ptr, image_data_size);
    else // chunked resource 
        memcpy(DDSheader_dest + header_size, (*file_resources)[largest_resource_index].content, image_data_size);
        //OpenTagResource(tag, resource_index, DDSheader_dest + header_size, image_data_size);

    // ////////////////// //
    // UNSWIZZLE TEXTURE //
    // //////////////// //
    if (deswizzle){
        std::cout << "Unswizzling DDS\n";
        UnSwizzle(DDSheader_dest + header_size, image_data_size, 16L); // not sure on the stride yet
    }


    std::cout << "loading bitmap as DDS\n";
    // and then we should have a fully loaded dds image in mem, which we should beable to now export for testing purposes
    DirectX::ScratchImage* DDS_image = new DirectX::ScratchImage();
    hr = DirectX::LoadFromDDSMemory(DDSheader_dest, header_size + image_data_size, (DirectX::DDS_FLAGS)0, nullptr, *DDS_image);
    if (FAILED(hr))
        throw new exception("failed to load DDS from memory");
    // we need to export via WIC file, so no extra tool is required to actually finish the conversion

    // if BC, then we need to decompress the image to convert it
    DirectX::ScratchImage* decompressedImage = new DirectX::ScratchImage();
    bool is_BC = false;
    if (DirectX::IsCompressed(meta->format)) {
        std::cout << "decompressing BC format\n";
        is_BC = true;
        hr = DirectX::Decompress(DDS_image->GetImages(), DDS_image->GetImageCount(), DDS_image->GetMetadata(), DXGI_FORMAT_R8G8B8A8_UNORM, *decompressedImage);
        if (FAILED(hr))
            throw new exception("could not decompress BC bitmap");

    }
    else decompressedImage = DDS_image;

    // then convert it
    //DirectX::ScratchImage WICImage;
    //hr = DirectX::Convert(decompressedImage->GetImages(), decompressedImage->GetImageCount(), decompressedImage->GetMetadata(), DXGI_FORMAT_R8G8B8A8_UNORM, DirectX::TEX_FILTER_DEFAULT, DirectX::TEX_THRESHOLD_DEFAULT, WICImage);
    //if (FAILED(hr))
    //    throw new exception("could not convert image to exportable format");

    std::cout << "saving DDS file\n";

    const wchar_t* dds_export_file_path = L"C:\\Users\\Joe bingle\\Downloads\\H5 images\\test.dds";
    hr = DirectX::SaveToDDSFile(*decompressedImage->GetImage(0, 0, 0), (DirectX::DDS_FLAGS)0, dds_export_file_path);
    if (FAILED(hr))
        throw new exception("failed to save DDS to local file");


    std::cout << "saving WIC file\n";


    const wchar_t* png_export_file_path = L"C:\\Users\\Joe bingle\\Downloads\\H5 images\\test.png";
    hr = DirectX::SaveToWICFile(*decompressedImage->GetImage(0, 0, 0), DirectX::WIC_FLAGS_NONE, DirectX::GetWICCodec(DirectX::WIC_CODEC_JPEG), png_export_file_path);
    if (FAILED(hr))
        throw new exception("failed to save DDS to local file");

    return;
}




int main(){
    HRESULT hr = CoInitialize(NULL); // used for the WIC file exporting? i think
    if (FAILED(hr))
        throw new exception("Failed to coInitialize");

    std::cout << "exporting image test!\n";

    bool deswizzle = true;

    // the mountain control? image 
    //BITM_GetTexture("C:\\Users\\Joe bingle\\Downloads\\H5 bitm\\Fo05 Desert Macromask 4k PC\\fo05_desert_macromask_control{pc}.bitmap", deswizzle);
    //BITM_GetTexture("C:\\Users\\Joe bingle\\Downloads\\H5 bitm\\Fo05 Desert Macromask 4k Xbox\\fo05_desert_macromask_control{x1}.bitmap", deswizzle);
    // the mountain white image 
    //BITM_GetTexture("C:\\Users\\Joe bingle\\Downloads\\H5 bitm\\Fo05 Desert Terrainmacro Color 4k PC\\fo05_desert_terrainmacro_color{pc}.bitmap", deswizzle);
    //BITM_GetTexture("C:\\Users\\Joe bingle\\Downloads\\H5 bitm\\Fo05 Desert Terrainmacro Color 4k Xbox\\fo05_desert_terrainmacro_color{x1}.bitmap", deswizzle);
    // forerunner thing // NO VALID PATTERN
    //BITM_GetTexture("C:\\Users\\Joe bingle\\Downloads\\H5 bitm\\Forerunner mp coliseum PC\\fr_mp_coliseum_techbits_b_control{pc}.bitmap", deswizzle);
    //BITM_GetTexture("C:\\Users\\Joe bingle\\Downloads\\H5 bitm\\Forerunner Mp Coliseum Xbox\\fr_mp_coliseum_techbits_b_control{x1}.bitmap", deswizzle);


    //BITM_GetTexture("C:\\Users\\Joe bingle\\Downloads\\H5 bitm\\Ghost PC\\ghost_hull_default_color{pc}.bitmap", deswizzle);
    BITM_GetTexture("C:\\Users\\Joe bingle\\Downloads\\H5 bitm\\Ghost Xbox\\ghost_hull_default_color{x1}.bitmap", deswizzle);



    std::cout << "exporting completed!\n";
}