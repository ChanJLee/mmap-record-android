//
// Created by chan on 2018/1/24.
//

#ifndef MMAPRECORD_MMAP_H
#define MMAPRECORD_MMAP_H

#include <cwchar>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef NEED_FREE
#undef NEED_FREE
#define NEED_FREE
#else
#define NEED_FREE
#endif

typedef unsigned char u1;
typedef unsigned short u2;
typedef unsigned int u4;

const u1 MAGIC_HEADER[] = {'w', 'j', 's', 'j', 'h', 'a', 'p', 'y'};

typedef struct {
    u1 magic[sizeof(MAGIC_HEADER)];
    u4 size;
    u2 type;
    u2 padding;
} mmap_header;

typedef struct {
    u1 *buffer;
    size_t size;
} mem_info;

u1 *mmap_alloc(int fd, size_t size);

mem_info read_dirty_data(int fd);

NEED_FREE u1 *read_data(const u1 *buffer, size_t size);

void write_data(u1 *buffer, size_t buffer_size, const u1 *data, size_t data_size);

#ifdef __cplusplus
}
#endif


#endif //MMAPRECORD_MMAP_H
