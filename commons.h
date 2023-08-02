#pragma once
using namespace std;
#include <stdint.h>
#include <string>

// /////////////////// //
// SPECIAL PARAM TYPES //
// /////////////////// //

#pragma pack(push, 1)
struct _s_point2d {
    int16_t A;
    int16_t B;
};
struct _s_rgb {
    char pad_A;
    char R;
    char G;
    char B;
};
struct _s_argb {
    char A;
    char R;
    char G;
    char B;
};
struct _s_doublefloat {
    float f1;
    float f2;
};
struct _s_triplefloat {
    float f1;
    float f2;
    float f3;
};
struct _s_quadfloat {
    float f1;
    float f2;
    float f3;
    float f4;
};
struct _s_rgbfloat {
    float r;
    float g;
    float b;
};
struct _s_argbfloat {
    float a;
    float r;
    float g;
    float b;
};
struct _s_shortrange {
    int16_t min;
    int16_t max;
};
struct _s_floatrange {
    float min;
    float max;
};

template <typename T>
struct _s_tagblock {
    T* content_ptr;
    int64_t structure_ptr;
    int32_t count;
    uint32_t unk1; // h5 exclusive
    uint32_t unk2; // h5 exclusive
    T* operator[] (uint32_t index) {
        if (index >= count) throw exception("attempted to access out of bounds _s_tagblock index");
        return content_ptr + index;
    }
};
struct _s_tagref {
    void* content_ptr; // ptr to the tag in question
    uint32_t nameLength; // h5 exclusive 
    uint32_t tagid;
    uint64_t assetid;
    uint32_t group;
    uint32_t runtime_tag_handle;
};
struct _s_data {
    char* content_ptr;
    int64_t structure_ptr;
    uint32_t compiled_unk1; 
    uint32_t compiled_unk2; // h5 exclusive 
    uint32_t data_size;
    char operator[] (uint32_t index) { // why did we put this here? i dont think we'd ever need to index the _s_data
        if (index >= data_size) throw exception("attempted to access out of bounds _s_data index");
        return *(content_ptr + index);
    }
};
template <typename T>
struct _s_resource {
    T* content_ptr;
    uint32_t runtime_resource_handle;
    uint32_t is_chunked_resource;
};

#pragma pack(pop)
