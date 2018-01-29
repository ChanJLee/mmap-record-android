//
// Created by chan on 2018/1/24.
//

#include <sys/mman.h>
#include <sys/stat.h>
#include "mmap.h"
#include "log.h"
#include <fcntl.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

void read_dirty_data(int fd, mem_info *info);

u1 *mmap_alloc(int fd, size_t size);

int open_buffer(const char *buffer_path, const char *path, mmap_info *info) {
    if (strlen(buffer_path) == 0 || strlen(path) == 0 || info == nullptr) {
        return ERROR_INVALID_ARGUMENT;
    }

    int buffer_fd = ::open(buffer_path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (buffer_fd < 0) {
        return ERROR_OPEN_BUFFER;
    }

    int path_fd = ::open(path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (path_fd < 0) {
        close(buffer_fd);
        return ERROR_OPEN_PATH;
    }

    mem_info mem_info;
    read_dirty_data(buffer_fd, &mem_info);
    if (mem_info.size != 0 && mem_info.buffer != nullptr) {
        // write data to path
        write(path_fd, mem_info.buffer, mem_info.size);
    }

    info->buffer_size = RESIZE(128);
    info->buffer_fd = buffer_fd;
    info->path_fd = path_fd;
    info->used_size = 0;
    info->buffer = mmap_alloc(buffer_fd, info->buffer_size);

    return 0;
}

u1 *mmap_alloc(int fd, size_t size) {
    ftruncate(fd, (off_t) size);
    lseek(fd, 0, SEEK_SET);
    size_t alloc_size = size;
    u1 *map_ptr = (u1 *) mmap(0, alloc_size, PROT_WRITE | PROT_READ, MAP_PRIVATE, fd, 0);
    return map_ptr == MAP_FAILED ? nullptr : map_ptr;
}

void read_dirty_data(int fd, mem_info *info) {
    info->size = 0;
    info->buffer = nullptr;

    // read dirty data
    struct stat buffer_file_stat;
    if (fstat(fd, &buffer_file_stat) < 0) {
        return;
    }

    size_t buffer_file_size = (size_t) buffer_file_stat.st_size;
    if (buffer_file_size <= 0) {
        return;
    }

    info->buffer = (u1 *) mmap(0, buffer_file_size, PROT_WRITE | PROT_READ, MAP_PRIVATE, fd, 0);
    info->size = buffer_file_size;
}

void write_buffer(mmap_info *info, const u1 *data, size_t data_size) {
    // need to allocate more buffer
    if (info->buffer_size <= data_size) {
        u4 resize_size = RESIZE(info->buffer_size * 2);
        u1 *pre_buffer = info->buffer;
        LOG_D("size %d, address %x", info->buffer_size, (u4) pre_buffer);
        info->buffer = (u1 *) mremap(pre_buffer, info->buffer_size, resize_size, 0);
        info->buffer_size = resize_size;
        LOG_D("resize buffer %d, address %x", info->buffer_size, (u4) info->buffer);
    }

    if (info->buffer == MAP_FAILED) {
        LOG_D("ignore write buffer");
        return;
    }

    info->used_size = data_size;
    // copy data
    memcpy(info->buffer, data, data_size);
}

#ifdef __cplusplus
}
#endif