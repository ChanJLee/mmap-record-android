//
// Created by chan on 2018/1/24.
//

#include <sys/mman.h>
#include "mmap.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

u1 *mmap_alloc(int fd, size_t size) {
    u1 *map_ptr = (u1 *) mmap(0, size, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    return map_ptr == MAP_FAILED ? nullptr : map_ptr;
}

bool has_dirty_data(const u1 *buffer, size_t size) {
    if (size < sizeof(mmap_header)) {
        return false;
    }

    return memcmp(buffer, MAGIC_HEADER, sizeof(MAGIC_HEADER)) == 0;
}

NEED_FREE u1 *read_data(const u1 *buffer, size_t size) {
    if (!has_dirty_data(buffer, size)) {
        return nullptr;
    }

    mmap_header header;
    memcpy(&header, buffer, sizeof(mmap_header));
    if (header.size == 0) {
        return nullptr;
    }

    u1 *result = new u1[header.size];
    memcpy(result, buffer + sizeof(mmap_header), header.size);
    return result;
}

void write_data(u1 *buffer, size_t buffer_size, const u1 *data, size_t data_size) {
    // need to allocate more buffer
    if (buffer_size <= data_size + sizeof(mmap_header)) {
        return;
    }

    mmap_header header;
    memcpy(header.magic, MAGIC_HEADER, sizeof(MAGIC_HEADER));
    header.size = data_size;
    memcpy(buffer, &header, sizeof(mmap_header));
    memcpy(buffer + sizeof(mmap_header), data, data_size);
}

#ifdef __cplusplus
}
#endif