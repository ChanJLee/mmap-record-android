
#include <string>
#include <sstream>
#include "mmap.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "mmaprecord.h"

#include "jstringholder.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

mmap_info *get_mmap_info(JNIEnv *env, jobject object) {
    jclass mmap_record_clazz = env->GetObjectClass(object);
    jfieldID reference_id = env->GetFieldID(mmap_record_clazz, "mBufferInfoReference", "J");
    return reinterpret_cast<mmap_info *>(env->GetLongField(object, reference_id));
}

void set_mmap_info(JNIEnv *env, jobject object, void *ref) {
    jclass mmap_record_clazz = env->GetObjectClass(object);
    jfieldID reference_id = env->GetFieldID(mmap_record_clazz, "mBufferInfoReference", "J");
    env->SetLongField(object, reference_id, (jlong) ref);
}

JNIEXPORT jint JNICALL
Java_com_chan_lib_MmapRecord_init(JNIEnv *env, jobject instance, jstring buffer, jstring log) {
    // open buffer
    JStringHolder buffer_path_string_holder(*env, buffer);
    const char *buffer_path = buffer_path_string_holder.getCString();

    // open log
    JStringHolder log_path_string_holder(*env, log);
    const char *log_path = log_path_string_holder.getCString();

    mmap_info *info = new mmap_info;
    open_buffer(buffer_path, log_path, info);
    set_mmap_info(env, instance, info);
    return 0;
}


JNIEXPORT void JNICALL
Java_com_chan_lib_MmapRecord_release(JNIEnv *env, jobject instance) {
    mmap_info *info = get_mmap_info(env, instance);
    if (info == nullptr) {
        return;
    }

    close(info->buffer_fd);
    close(info->path_fd);
}

JNIEXPORT void JNICALL
Java_com_chan_lib_MmapRecord_save(JNIEnv *env, jobject object, jstring json) {
    mmap_info *info = get_mmap_info(env, object);
    if (info == nullptr) {
        return;
    }

    JStringHolder json_holder(*env, json);
    const char *c_json = json_holder.getCString();
    size_t c_json_len = strlen(c_json);
    write_buffer(info, (const u1 *) c_json, c_json_len);
}

JNIEXPORT jstring JNICALL
Java_com_chan_lib_MmapRecord_read(JNIEnv *env, jobject instance) {
    mmap_info *info = get_mmap_info(env, instance);
    if (info == nullptr || info->used_size <= 0) {
        return nullptr;
    }

    return env->NewStringUTF((const char *) info->buffer);
}


#ifdef __cplusplus
}
#endif