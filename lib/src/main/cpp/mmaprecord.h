//
// Created by chan on 2018/1/22.
//

#ifndef MMAPRECORD_MMAPRECORD_H
#define MMAPRECORD_MMAPRECORD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <jni.h>

typedef char byte;

typedef struct {
    int buffer_fd;
    int log_fd;
    int buffer_size;
    int used_size = 0;
    byte *buffer;
} mmap_info;

JNIEXPORT jint JNICALL
Java_com_chan_lib_MmapRecord_init(JNIEnv *env, jobject instance, jstring path, jstring log_path);

JNIEXPORT void JNICALL
Java_com_chan_lib_MmapRecord_release(JNIEnv *env, jobject instance);

JNIEXPORT void JNICALL
Java_com_chan_lib_MmapRecord_save(JNIEnv *env, jobject instance, jstring json);

JNIEXPORT jstring JNICALL
Java_com_chan_lib_MmapRecord_read(JNIEnv *env, jobject instance);

#ifdef __cplusplus
}
#endif

#endif //MMAPRECORD_MMAPRECORD_H