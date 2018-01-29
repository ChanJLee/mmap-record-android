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

typedef struct {
    u1 *buffer;
    size_t size;
} mem_info;

typedef struct {
    int buffer_fd;
    int path_fd;
    u4 buffer_size;
    u1 *buffer;
    u4 used_size = 0;
} mmap_info;

#define ERROR_INVALID_ARGUMENT -1
#define ERROR_OPEN_BUFFER -2
#define ERROR_OPEN_PATH -3
#define RESIZE(a) ((((a) / PAGE_SIZE) + 1) * PAGE_SIZE)


int open_buffer(const char *buffer_path, const char *path, mmap_info *info);

void write_buffer(mmap_info* info, const u1 *data, size_t data_size);

#ifdef __cplusplus
}
#endif


#endif //MMAPRECORD_MMAP_H
