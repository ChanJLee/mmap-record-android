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
    byte *buffer;
} mmap_info;

JNIEXPORT jint JNICALL
Java_com_chan_lib_MmapRecord_init(JNIEnv *env, jobject instance, jstring path, jstring log_path);

JNIEXPORT void JNICALL
Java_com_chan_lib_MmapRecord_void(JNIEnv *env, jobject instance, jlong mmap_info_reference);

#ifdef __cplusplus
}
#endif


#endif //MMAPRECORD_MMAPRECORD_H
