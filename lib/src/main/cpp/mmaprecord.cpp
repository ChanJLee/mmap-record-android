#include "mmaprecord.h"
#include "jstringholder.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/stat.h>
#include <fcntl.h>
#include <sstream>
#include <sys/mman.h>
#include "log.h"


JNIEXPORT jint JNICALL
Java_com_chan_lib_MmapRecord_init(JNIEnv *env, jobject instance, jstring buffer, jstring log) {
    // open buffer
    JStringHolder buffer_path_string_holder(*env, buffer);
    const char *buffer_path = buffer_path_string_holder.getCString();
    int buffer_fd = open(buffer_path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (buffer_fd < 0) {
        jclass exception = env->FindClass("java/lang/IllegalArgumentException");
        std::ostringstream oss;
        oss << "open " << buffer << " failed.";
        env->ThrowNew(exception, oss.str().c_str());
        return -1;
    }

    // open log
    JStringHolder log_path_string_holder(*env, log);
    const char *log_path = log_path_string_holder.getCString();
    int log_fd = open(log_path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (log_fd < 0) {
        jclass exception = env->FindClass("java/lang/IllegalArgumentException");
        std::ostringstream oss;
        oss << "open " << log << " failed.";
        env->ThrowNew(exception, oss.str().c_str());
        return -1;
    }

    // read dirty data
    stat buffer_file_stat;
    if (fstat(buffer_fd, &buffer_file_stat) >= 0) {
        size_t buffer_file_size = (size_t) buffer_file_stat.st_size;
        if (buffer_file_size > 0) {
            char *buffered_data = (char *) mmap(0, buffer_file_size, PROT_WRITE | PROT_READ,
                                                MAP_SHARED, buffer_fd, 0);
            LOGD(buffered_data);
        }
    }

    // write data
    const int buffer_size = 1000;
    // 1000 is buffer size
    ftruncate(buffer_fd, buffer_size);
    lseek(buffer_fd, 0, SEEK_SET);
    char *map_ptr = (char *) mmap(0, buffer_size, PROT_WRITE | PROT_READ, MAP_SHARED, buffer_fd, 0);
    if (map_ptr == MAP_FAILED) {
        return -2;
    }

    mmap_info *info = new mmap_info;
    info->buffer = map_ptr;
    info->buffer_fd = buffer_fd;
    info->log_fd = log_fd;
    info->buffer_size = buffer_size;

    jclass mmap_record_clazz = env->GetObjectClass(instance);
    jfieldID reference_id = env->GetFieldID(mmap_record_clazz, "mBufferInfoReference", "L");
    env->SetLongField(instance, reference_id, (jlong) info);

    return 0;
}


JNIEXPORT void JNICALL
Java_com_chan_lib_MmapRecord_void(JNIEnv *env, jobject instance, jlong mmap_info_reference) {
    mmap_info *info = static_cast<mmap_info *>(mmap_info_reference);
    if (info == nullptr) {
        return;
    }

    close(info->buffer_fd);
    close(info->log_fd);
}

#ifdef __cplusplus
}
#endif