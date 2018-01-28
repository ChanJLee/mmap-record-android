//
// Created by chan on 2018/1/28.
//

#ifndef MMAPRECORD_SCOPEBYTEARRAY_H
#define MMAPRECORD_SCOPEBYTEARRAY_H

#include <jni.h>

class ScopeByteArray {
private:
    JNIEnv *mEnv;
    const jbyteArray mArray;
    jbyte *mBytes;
public:
    ScopeByteArray(JNIEnv *mEnv, const jbyteArray array) : mEnv(mEnv), mArray(array) {
        mBytes = mEnv->GetByteArrayElements(mArray, NULL);
    }

    ~ScopeByteArray() {
        mEnv->ReleaseByteArrayElements(mArray, mBytes, 0);
    }

    jbyte *getBytes() {
        return mBytes;
    }
};

#endif //MMAPRECORD_SCOPEBYTEARRAY_H
