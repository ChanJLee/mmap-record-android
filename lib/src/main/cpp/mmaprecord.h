//
// Created by chan on 2018/1/22.
//

#ifndef MMAPRECORD_MMAPRECORD_H
#define MMAPRECORD_MMAPRECORD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <jni.h>
#include "mmap.h"

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