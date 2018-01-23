//
// Created by chan on 2018/1/22.
//

#ifndef MMAPRECORD_JSTRINGHOLDER_H
#define MMAPRECORD_JSTRINGHOLDER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <jni.h>

class JStringHolder {
private:
    JNIEnv &mEnv;
    jstring mJString;
    const char *mCString;

public:
    JStringHolder(JNIEnv &env, jstring jstr) : mEnv(env), mJString(jstr) {
        mCString = mEnv.GetStringUTFChars(mJString, 0);
    }

    virtual ~JStringHolder() {
        mEnv.ReleaseStringUTFChars(mJString, mCString);
    }

    const char *getCString() const {
        return mCString;
    }
};

#ifdef __cplusplus
}
#endif


#endif //MMAPRECORD_JSTRINGHOLDER_H
