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

#include <stdio.h>
#include <sys/types.h>
//#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

#include <locale>  
#include <codecvt>

#include "detiling/DirectXTexXbox.h"

#include <set>

struct Tag{
    char* data_ptr;
    char* cleanup_ptr;

};
struct resource_handle {
    resource_handle(uint64_t _size, char* _content, bool _is_chunk, string _filename) {
        size = _size;
        content = _content;
        is_chunk = _is_chunk;
        filename = _filename;
    }
    uint64_t size;
    char* content;
    bool is_chunk;
    string filename;
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
  //case  0x5: throw exception("unsupported image format");
    case  0x6: return 85;
  //case  0x7: throw exception("unsupported image format");
    case  0x8: return 86;
    case  0x9: return 115;
    case  0xA: return 88;
    case  0xB: return 87;
  //case  0xC: throw exception("unsupported image format");
    case  0xE: return 71;
    case  0xF: return 74;
    case 0x10: return 77;
  //case 0x11:
  //case 0x12:
  //case 0x13:
  //case 0x14:
  //case 0x15: throw exception("unsupported image format");
    case 0x16: return 51;
  //case 0x17: throw exception("unsupported image format");
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
  //case 0x23: throw exception("unsupported image format");
    case 0x24: return 80;
    case 0x25: return 81;
  //case 0x26: throw exception("unsupported image format");
    case 0x27: return 84;
    case 0x28: return 107; // "This is a guess, tag defs claim this format is deprecated, yet it is still used. gg"
  //case 0x29: 
  //case 0x2A: throw exception("unsupported image format");
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
bool is_exportable_format(DXGI_FORMAT format) {
    switch (format){
        case DXGI_FORMAT_R32G32B32A32_FLOAT:
        case DXGI_FORMAT_R16G16B16A16_FLOAT:
        case DXGI_FORMAT_R16G16B16A16_UNORM:
        case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:
        case DXGI_FORMAT_R10G10B10A2_UNORM:
        case DXGI_FORMAT_B5G5R5A1_UNORM:
        case DXGI_FORMAT_B5G6R5_UNORM:
        case DXGI_FORMAT_R32_FLOAT:
        case DXGI_FORMAT_R16_FLOAT:
        case DXGI_FORMAT_R16_UNORM:
        case DXGI_FORMAT_R8_UNORM:
        case DXGI_FORMAT_A8_UNORM:
        case DXGI_FORMAT_R8G8B8A8_UNORM:
        case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
        case DXGI_FORMAT_B8G8R8A8_UNORM:
        case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
        case DXGI_FORMAT_B8G8R8X8_UNORM:
        case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
            return true;
    }
    return false;
}


DirectX::WICCodecs output_type = DirectX::WIC_CODEC_JPEG;

void cleanup_resources(vector<resource_handle*>& file_resources) {
    for (int i = 0; i < file_resources.size(); i++) {
        auto var1 = file_resources[i]->content;
        if (var1 != 0) delete[] var1;
        delete file_resources[i];
}}

int read_number_from_string(string source, string search_string) {
    int offset = source.find(search_string);
    if (offset == -1) throw exception("failed to find resource index from resource filename");
    offset += search_string.length();

    // iterate through all following characters to see if they're digits or not
    int number_length = 0;
    while (true) {
        if (!std::isdigit(source[offset + number_length])) break;
        number_length++;}
    if (number_length == 0) throw exception("couldn't read index from resource filename");
    // substring and convert to int
    return std::stoi(source.substr(offset, number_length));
}
void OpenTag(std::string filepath, char*& tagdata, char*& cleanup_ptr, vector<resource_handle*>& file_resources) {
    // READ BITMAP FILE & PROCESS
    ifstream file_stream(filepath, ios::binary | ios::ate);
    if (!file_stream.is_open()) throw exception("failed to open bitmap tag");
    std::streamsize file_size = file_stream.tellg();
    if (file_size < tag_header_size) throw exception("bitmap is too small to contain tag data");
    // read the whole file
    char* tag_bytes = new char[file_size]; // this gets cleaned up in open_ready_tag;
    file_stream.seekg(0, ios::beg);
    file_stream.read(tag_bytes, file_size);
    file_stream.close();
    // process file into runtime tag
    TAG_OBJ_TYPE tag_type = TagProcessing::Open_ready_tag(tag_bytes, file_size, tagdata, cleanup_ptr);
    if (tag_type != TAG_OBJ_TYPE::bitmap)
        if (tag_type == TAG_OBJ_TYPE::NONE) throw exception("not a bitmap file");
        else throw exception("valid tag file, not a bitmap tag");
    // READ ALL RESOURCES
    // we now need to look for resource files, if its a chunk, add it to the out array
    // if its a tag struct file, add it to the inputs
    // convert path into parent directory
    const size_t last_slash_idx = filepath.rfind('\\');
    if (std::string::npos == last_slash_idx) throw exception("failed to calculate file directory (theres virtually no way this happens)");
    string filefolder = filepath.substr(0, last_slash_idx);

    int non_chunks = 0;
    int chunks = 0;
    // then created properly sorted set
    vector<resource_handle*> unsorted_files = {};
    for (const auto& file : std::filesystem::directory_iterator(filefolder)) {
        string current_file = file.path().string();
        if (current_file.length() > filepath.length() && filepath == current_file.substr(0, filepath.length()) && current_file[filepath.length()] == '[') {
            ifstream resource_stream(current_file, ios::binary | ios::ate);
            if (!resource_stream.is_open()) continue;
            std::streamsize resource_size = resource_stream.tellg();
            if (resource_size == 0) continue;
            // read the whole file
            char* resource_bytes = new char[resource_size];
            resource_stream.seekg(0, ios::beg);
            resource_stream.read(resource_bytes, resource_size);
            resource_stream.close(); // might as well, seeing as we're reading everything right now, needs to be changed in an optimization pass

            bool ischunked = (current_file.substr(0, current_file.length()).find(".chunk") != std::string::npos);
            non_chunks += !ischunked;
            chunks += ischunked;
            resource_handle* new_resource = new resource_handle(resource_size, resource_bytes, ischunked, current_file);
            unsorted_files.push_back(new_resource);
    }}

    // pad array with nullptrs
    for (int i = 0; i < unsorted_files.size(); i++) file_resources.push_back(nullptr);

    // then sort the things
    if (chunks > 0) { // then theres a single resource handle with multiple chunks
        if (non_chunks != 1) throw exception("bitmap with chunks can only have 1 intermediate resource file");
        for (auto resource : unsorted_files) {
            // non chunk goes first
            if (!resource->is_chunk) file_resources[0] = resource;
            // then chunks are inserted by their index+1
            else file_resources[read_number_from_string(resource->filename, ".chunk") +1] = resource;
    }} 
    // else sort just non-chunk resources
    else for (auto resource : unsorted_files) file_resources[read_number_from_string(resource->filename, ".bitmap[")] = resource;
}

void BITM_Export(std::string filepath, char*& DDSheader_dest, bitm* bitm_tag, bitm::__bitmaps_* selected_bitmap, size_t image_data_size, char* image_data) {

    BitmapDataResource* bitmap_details = selected_bitmap->bitmap_resource_handle_.content_ptr;
    


    size_t header_size = sizeof(uint32_t) + 124; // sizeof(DirectX::DDS_HEADER);
    
    // configure meta data
    DirectX::TexMetadata meta = {};
    meta.depth = selected_bitmap->depth__pixels_DO_NOT_CHANGE;
    meta.arraySize = 1; // no support for array types yet
    meta.mipLevels = 0; // it seems this does not apply for all versions // selected_bitmap->mipmap_count;
    meta.miscFlags = 8000000; // i think this enables tile mode // the only flag seems to be TEX_MISC_TEXTURECUBE = 0x4
    meta.miscFlags2 = 0;
    meta.dimension = (DirectX::TEX_DIMENSION)3; // TEX_DIMENSION_TEXTURE2D

    // test format
    uint32_t bitm_format = GetFormat(selected_bitmap->format__DO_NOT_CHANGE);
    if (bitm_format == -1) throw exception("DXGI format specified by the tag was either unsupported or invalid");
    meta.format = (DXGI_FORMAT)bitm_format;


    meta.width = selected_bitmap->width__pixels_DO_NOT_CHANGE;
    meta.height = selected_bitmap->height__pixels_DO_NOT_CHANGE;

    // i *believe* that no PC tags have these fields, as they are probably all for tiling related data
    bool is_xbox = (bitmap_details->tileMode != 0 || bitmap_details->format != 0 || bitmap_details->bitmap_data_resource_flags.content != 0);
    // to convert our metadata to xbox, we're just going to pretend we're writing the regular DDS header
    // we encode so it fixes up all of the data, and then we just change stuff that we need to, to convert it to the xbox version
    if (is_xbox){
        std::cout << "[XBOX]\n";
        header_size += sizeof(DDS_HEADER_XBOX_p);
        // warn user if type is likely unsupported
        if (!DirectX::IsTypeless(meta.format) && !DirectX::IsCompressed(meta.format) && !DirectX::IsPacked(meta.format))
            std::cout << "this image type may not be supported\n";
    } else {
        std::cout << "[PC]\n";
        if (!is_short_header(meta.format)) header_size += 20; // sizeof(DirectX::DDS_HEADER_DXT10);
    }
    // ///////////////////////////////////// //
    // CONVERT BITMAP TO DIRECTXTEX TEXTURE //
    // /////////////////////////////////// //

    std::cout << "eoncoding bitmap header\n";
    DDSheader_dest = new char[header_size + image_data_size];
    size_t output_size = 0;
    HRESULT hr = EncodeDDSHeader(meta, DirectX::DDS_FLAGS_NONE, (void*)DDSheader_dest, header_size, output_size);
    if (!SUCCEEDED(hr)) throw exception("image failed to generate DDS header");
    if (!is_xbox && header_size != output_size) // if its xbox, then we're going to get an output size smaller than our header everytime
        // DXGI_FORMAT_BC1_UNORM_SRGB (72) is actually long header? // TODO??
        throw exception("header size was incorrectly assumed! must investigate this image format!!!");

    std::cout << "copying bitmap data\n";
    // then write the bitmap data into our dds 
    memcpy(DDSheader_dest + header_size, image_data, image_data_size);

    DirectX::ScratchImage DDS_image = {};
    // ////////////////// //
    // UNSWIZZLE TEXTURE //
    // //////////////// //
    if (is_xbox){
        std::cout << "Processing DDS as xbox DDS\n";

        DDS_HEADER_p* encoded_header = (DDS_HEADER_p*)(DDSheader_dest + sizeof(uint32_t));
        encoded_header->ddspf.flags |= 4; // DDS_FOURCC
        encoded_header->ddspf.fourCC = 0x584F4258; // 'XBOX' backwards

        DDS_HEADER_XBOX_p* encoded_xbox_header = (DDS_HEADER_XBOX_p*)(DDSheader_dest + sizeof(uint32_t) + 124); // sizeof(DirectX::DDS_HEADER);
        // luckily, if the original format was the DX10 header, then it encodes the first 5 parameters for this header: dxgiFormat, resourceDimension, miscFlag, arraySize & miscFlags2
        // thats because we just pretend its a regular DDS header, and are converting it in place (which works because the xbox version is larger than the regular one)
        // ok apparently theres a few textures that do NOT use the DX10 extension, so we have to write that data anyway !!!!
        if (is_short_header(meta.format)){
            encoded_xbox_header->dxgiFormat = meta.format;
            encoded_xbox_header->resourceDimension = meta.dimension;
            encoded_xbox_header->miscFlag = meta.miscFlags & ~4; // TEX_MISC_TEXTURECUBE; // this is just what is done in the regular encode
            // something something array count | TEX_MISC_TEXTURECUBE flag
            encoded_xbox_header->arraySize = meta.arraySize;
            encoded_xbox_header->miscFlags2 = meta.miscFlags2;}
        encoded_xbox_header->tileMode = bitmap_details->tileMode; // bitmap_details->tileMode; // Xbox::c_XboxTileModeLinear;
        encoded_xbox_header->baseAlignment = 32768; // this is the value that the Xbox layout is saying it should be?? // can be anything other than 0??
        encoded_xbox_header->dataSize = image_data_size;
        encoded_xbox_header->xdkVer = 0;

        // ok, now our image should be good for loading
        Xbox::XboxImage xbox_image = {};
        HRESULT hr = Xbox::LoadFromDDSMemory(DDSheader_dest, header_size + image_data_size, nullptr, xbox_image);
        if (!SUCCEEDED(hr)) throw exception("failed to load xbox encoded image");

        hr = Xbox::Detile(xbox_image, DDS_image);
        if (!SUCCEEDED(hr)) throw exception("failed to detile xbox image");
    }else{
        std::cout << "loading bitmap as DDS\n";
        // and then we should have a fully loaded dds image in mem, which we should beable to now export for testing purposes
        hr = DirectX::LoadFromDDSMemory(DDSheader_dest, header_size + image_data_size, (DirectX::DDS_FLAGS)0, nullptr, DDS_image);
        if (FAILED(hr)) throw exception("failed to load DDS from memory");
    }

    // we need to export via WIC file, so no extra tool is required to actually finish the conversion

    // if BC, then we need to decompress the image to convert it
    DirectX::ScratchImage decompressedImage = {};
    const DirectX::Image* final_img = nullptr;
    if (DirectX::IsCompressed(meta.format)) {
        std::cout << "decompressing BC format\n";
        hr = DirectX::Decompress(DDS_image.GetImages(), DDS_image.GetImageCount(), DDS_image.GetMetadata(), DXGI_FORMAT_R8G8B8A8_UNORM, decompressedImage);
        if (FAILED(hr)) throw exception("could not decompress BC bitmap");
        final_img = decompressedImage.GetImage(0, 0, 0);
    }else if (!is_exportable_format(meta.format)){ // BC bitmaps should always convert to that format anyway, so they shouldn't need to convert
        std::cout << "converting image format\n";
        hr = DirectX::Convert(DDS_image.GetImages(), DDS_image.GetImageCount(), DDS_image.GetMetadata(), DXGI_FORMAT_R8G8B8A8_UNORM, DirectX::TEX_FILTER_DEFAULT, DirectX::TEX_THRESHOLD_DEFAULT, decompressedImage);
        if (FAILED(hr)) throw exception("failed to save DDS to local file");
        final_img = decompressedImage.GetImage(0, 0, 0);
    }else final_img = DDS_image.GetImage(0, 0, 0);

    std::cout << "saving WIC file\n";
    string export_file_path = filepath;
    switch (output_type) {
    case DirectX::WIC_CODEC_JPEG: export_file_path += string(".jpeg"); break;
    case DirectX::WIC_CODEC_PNG:  export_file_path += string(".png" ); break;
    case DirectX::WIC_CODEC_TIFF: export_file_path += string(".tiff"); break;
    case DirectX::WIC_CODEC_GIF:  export_file_path += string(".gif" ); break;
    default:                      export_file_path += string(".file"); break;}

    wstring wide_export_path (export_file_path.begin(), export_file_path.end());
    hr = DirectX::SaveToWICFile(*final_img, DirectX::WIC_FLAGS_NONE, DirectX::GetWICCodec(output_type), wide_export_path.c_str());
    if (FAILED(hr)) throw exception("could not convert image to another format");
}

void BITM_Process(std::string filepath, char* tagdata, vector<resource_handle*> file_resources) {
    // BUILD IMAGE HEADER AND VERIFY COMPATIBILITY
    bitm* bitm_tag = (bitm*)(tagdata);
    int highest_used_resource = -1;
    for (int bitmap_index = 0; bitmap_index < bitm_tag->bitmaps_.count; bitmap_index++) {
        if (bitm_tag->bitmaps_.count > 1) cout << "\nprocessing image " << bitmap_index+1 << "/" << bitm_tag->bitmaps_.count << "\n";
        bitm::__bitmaps_* selected_bitmap = bitm_tag->bitmaps_[bitmap_index];

        if (selected_bitmap->type__DO_NOT_CHANGE != bitm::__bitmaps_::__type__DO_NOT_CHANGE::_2D_texture && selected_bitmap->type__DO_NOT_CHANGE != bitm::__bitmaps_::__type__DO_NOT_CHANGE::array)
            throw exception("this tool does not currently support texture formats other than 2D images & array types");

        if (selected_bitmap->bitmap_resource_handle_.content_ptr == 0 || selected_bitmap->bitmap_resource_handle_.content_ptr == (BitmapDataResource*)0xbcbcbcbcbcbcbcbc) {
            // then we need to fetch this resource
            resource_handle* mid_resource = nullptr;
            for (int i = highest_used_resource+1; i < file_resources.size(); i++) {
                if (file_resources[i]->is_chunk == false) {
                    mid_resource = file_resources[i];
                    highest_used_resource = i;
                    break;
            }}
            if (mid_resource == nullptr) throw exception("no bitmap resource header resource-file found");

            char* res_tagdata = nullptr;
            char* res_cleanup_ptr = nullptr;
            TagProcessing::Open_ready_tag(mid_resource->content, mid_resource->size, res_tagdata, res_cleanup_ptr);
            if (res_tagdata == nullptr || res_cleanup_ptr == nullptr) throw exception("failed to open tag resource file");
            mid_resource->content = res_cleanup_ptr; // pointer for mr cleanup
            selected_bitmap->bitmap_resource_handle_.content_ptr = (BitmapDataResource*)res_tagdata;
        }
        BitmapDataResource* bitmap_details = selected_bitmap->bitmap_resource_handle_.content_ptr;

        char* DDSheader_dest = nullptr;
        size_t image_data_size = 0;
        char* image_data_ptr = nullptr;
        // instead of doing any of that, lets just pick the largest resource file
        int largest_resource_index = -1;

        if (bitm_tag->bitmaps_.count == 1) { // we only look for mips when theres only 1 bitmap, otherwise its not possible to have mips?
            for (int i = 0; i < file_resources.size(); i++) {
                if (file_resources[i]->is_chunk && file_resources[i]->size > image_data_size) {
                    largest_resource_index = i;
                    image_data_size = file_resources[i]->size;
                    image_data_ptr = file_resources[i]->content;
        }}}
        if (largest_resource_index == -1) { // resort to internal pixel buffer (the lowest resolution by the looks of it)
            cout << "using internal pixel buffer\n";
            image_data_size = bitmap_details->pixels.data_size;
            image_data_ptr = bitmap_details->pixels.content_ptr;
        }

        if (image_data_size == 0 || image_data_ptr == nullptr) throw exception("no pixels to export from this image, possible read logic failure");
    
        try{BITM_Export(filepath + std::to_string(bitmap_index), DDSheader_dest, bitm_tag, selected_bitmap, image_data_size, image_data_ptr);
        }catch (exception ex) {
            if (DDSheader_dest) delete[] DDSheader_dest;
            throw ex;}
        delete[] DDSheader_dest;
    }
}


void ProcessTagfile(std::string filepath) {
    // load the tag file
    char* tagdata = nullptr;
    char* cleanup_ptr = nullptr; 
    vector<resource_handle*> file_resources = {};
    try{
        OpenTag(filepath, tagdata, cleanup_ptr, file_resources);
        cout << "found " << file_resources.size() << " resources\n";
        BITM_Process(filepath, tagdata, file_resources);}
    catch (exception ex) {
        if (cleanup_ptr) delete[] cleanup_ptr;
        cleanup_resources(file_resources);
        throw ex;}
    // cleanup junk
    if (cleanup_ptr) delete[] cleanup_ptr;
    cleanup_resources(file_resources);
}

std::vector<std::string> bitmap_files;
// sourced from: https://stackoverflow.com/a/25640066/22277207
void FindBitmaps(const std::wstring& directory){
    std::wstring tmp = directory + L"\\*";
    std::string dir (directory.begin(), directory.end());
    WIN32_FIND_DATAW file;
    HANDLE search_handle = FindFirstFileW(tmp.c_str(), &file);
    if (search_handle != INVALID_HANDLE_VALUE){
        std::vector<std::wstring> directories;

        do{
            if (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
                if ((!lstrcmpW(file.cFileName, L".")) || (!lstrcmpW(file.cFileName, L"..")))
                    continue;
                directories.push_back(directory + L"\\" + std::wstring(file.cFileName));
                continue;
            }
            wstring wide_filename = std::wstring(file.cFileName);
            string filename(wide_filename.begin(), wide_filename.end());
            if (filename.substr(filename.find_last_of(".") + 1) == "bitmap") 
                bitmap_files.push_back(dir + "\\" + filename);

        } while (FindNextFileW(search_handle, &file));

        FindClose(search_handle);

        for (std::vector<std::wstring>::iterator iter = directories.begin(), end = directories.end(); iter != end; ++iter)
            FindBitmaps(*iter);
    }
}


std::string version = "0.2.3";
int main(int argc, char* argv[]){
    try{
        HRESULT hr = CoInitialize(NULL); // used for the WIC file exporting? i think
        if (FAILED(hr)) {
            std::cout << "failed to coInitialize Application (idk what this means), aborting process";
            system("pause");
            return 0;
        }
        std::cout << "bitm exporter Version: " << version << "\n";

        // ////////////////////////////// //
        // MANUAL CONFIGURATIONS CONSOLE //
        // //////////////////////////// //

        if (argc <= 1) {
            std::cout << "enter the directory containing bitmaps (dont put a \\ at the end)\nAll sub directories will also be searched (recursive search)\n";

            //string directory;
            //std::cin >> directory;

            std::string directory;
            std::getline(std::cin, directory);
            std::cout << "finding bitmaps...\n";

            // fallback so the findbitmaps function doesn't break when i hit enter twice or something
            struct stat s;
            int err = stat(directory.c_str(), &s);
            if (-1 == err) {
                std::cout << "failed to find directory, process aborted\n";
                system("pause");
                return 0;
            }

            wstring wide_directory(directory.begin(), directory.end());
            FindBitmaps(wide_directory);
            std::cout << bitmap_files.size() << " bitmaps found\n\n";
            if (bitmap_files.size() == 0) {
                std::cout << "it looks like you didn't find any bitmaps, did you input the path correctly? process aborted\n";
                system("pause");
                return 0;
            }


            std::cout << "enter the output file format (by entering the corresponding index)\n";
            std::cout << "[0]: jpeg\n";
            std::cout << "[1]: png\n";
            std::cout << "[2]: tiff\n";
            std::cout << "[3]: gif\n\n";

            int file_format;
            std::cin >> file_format;

            switch (file_format)
            {
            case 0:
                output_type = DirectX::WIC_CODEC_JPEG;
                std::cout << "\n[jpeg]\n\n";
                break;
            case 1:
                output_type = DirectX::WIC_CODEC_PNG;
                std::cout << "\n[png]\n\n";
                break;
            case 2:
                output_type = DirectX::WIC_CODEC_TIFF;
                std::cout << "\n[tiff]\n\n";
                break;
            case 3:
                output_type = DirectX::WIC_CODEC_GIF;
                std::cout << "\n[gif]\n\n";
                break;
            default:
                std::cout << "Invalid index provided, process aborted\n";
                system("pause");
                return 0;
            }
        }else {
            string path = string(argv[1]);
            bitmap_files.push_back(path);
            
            if (argc == 2) { // we didn't specify which format
                output_type = DirectX::WIC_CODEC_PNG;
                std::cout << "\n[png]\n\n";
            } else{ // then we also specified the file format
                string type = string(argv[2]);
                
                if (type == "jpeg")output_type = DirectX::WIC_CODEC_JPEG;
                else if (type == "png") output_type = DirectX::WIC_CODEC_PNG;
                else if (type == "tiff") output_type = DirectX::WIC_CODEC_TIFF;
                else if (type == "tiff") output_type = DirectX::WIC_CODEC_GIF;
                else {
                    std::cout << "Invalid image format provided, process aborted\n";
                    system("pause");
                    return 0;
                }
                std::cout << "\n[" + type + "]\n\n";
                
            }
        }




        for (int i = 0; i < bitmap_files.size(); i++) {
            string filename = bitmap_files[i];
            std::cout << "\nexporting [" << i << "]: " << filename << "\n";
            try{ProcessTagfile(filename);
            }catch (exception ex) {std::cout << "error extracting: " << ex.what() << "\n\n"; }
        }
        
        std::cout << "exporting completed!\n";
        if (argc <= 1) system("pause"); // dont pause if this was called by a script or something
        return 0;

    }catch (exception ex){
        std::cout << "complete process failure\n";
        system("pause");
        return 0;
    }
}

// this one indicates that we need to figure out how to get different sizes per image slot
// // wait do arrays even need us to fetch all the images?????
// C:\Users\Joe bingle\Downloads\misc\pelican_booster_core{x1}.bitmap