//
// Created by chan on 2018/1/22.
//

#ifndef MMAPRECORD_LOG_H
#define MMAPRECORD_LOG_H

#include <android/log.h>

#define LOG_TAG "mmap_record"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#endif //MMAPRECORD_LOG_H
