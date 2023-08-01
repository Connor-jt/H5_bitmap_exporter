// TagFramework.h - Contains the logic for reading tag files into renderable objects
#pragma once
#include <string>
#include <stdint.h>
#include <vector>
#include "TagStructs.h"
using namespace TagStructs;
using namespace std;

// this defines the possible data type output from reading a tag file
// if its none of these, then the data will be discarded as we have no use for it
// thus returning a nullptr

enum TAG_OBJ_TYPE{
	NONE = 0,
	UNKNOWN = 1,
	bitmap,
	render_model,
	physics_model,
	collision_model,
	bsp,
	runtime_geo,
	terrain,
	level
};
/*
struct size_pointer {
public:
	size_pointer(char* ptr, unsigned int _size){
		content_ptr = ptr;
		size = _size;
	}
	~size_pointer() {
		if (content_ptr != 0)
			delete[] content_ptr;
	}
	char* content_ptr;
	unsigned int size;
};
class runtime_tag{
public:
    void* tag_data; // to use this, you must cast it to the specific tag's structure, these structures can be generated via the plugins_to_cpp_convertor;
    vector<size_pointer>* streaming_chunks;
	runtime_tag(void* _tag_data, vector<size_pointer>* chunk_resources, vector<size_pointer>* struct_resources, char* _cleanup_ptr) {
		tag_data = _tag_data;
		streaming_chunks = chunk_resources;
		resource_structs_cleanup_ptrs = struct_resources;
		cleanup_ptr = _cleanup_ptr;
	}
	~runtime_tag(){ // cleanup all allocated structs/resources
		delete[] cleanup_ptr;
		// these should be handled automatically now
		//for (int c = 0; c < streaming_chunks->size(); c++) delete (*streaming_chunks)[c];
		//for (int c = 0; c < resource_structs_cleanup_ptrs->size(); c++) delete (*resource_structs_cleanup_ptrs)[c];
	}
private:
	char* cleanup_ptr; // call 'delete' on this to clean up the tag
	vector<size_pointer>* resource_structs_cleanup_ptrs; // used to clean up, each item's size will be listed as 0 when loaded
};
*/


static class TagProcessing {
public:
	static TAG_OBJ_TYPE Open_ready_tag(char* tag_bytes, uint64_t tag_size, char*& _Out_tag, char*& _Out_cleanup_ptr);
private:
	static struct tag_loading_offsets {
		uint64_t tag_dependencies_offset;
		uint64_t data_blocks_offset;
		uint64_t tag_structs_offset;
		uint64_t data_references_offset;
		uint64_t tag_fixup_references_offset;
		uint64_t string_IDs_offset;
		uint64_t string_table_offset;
		uint64_t zoneset_info_offset;
		// these three are offsets into the headerless array (so -= header.size)
		uint64_t header_size;
		uint64_t data_1_offset; // tag data
		uint64_t data_2_offset; // resource data
		uint64_t data_3_offset; // alt resource data
	};
    static uint64_t resolve_datablock_offset(TagStructs::data_block* datar, tag_loading_offsets* offsets);
    static TAG_OBJ_TYPE Processtag(char* tag_bytes, uint64_t file_size, char*& _Out_data, char*& _Out_cleanup_ptr);
};
