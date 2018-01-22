//
// Created by chan on 2018/1/22.
//

#ifndef MMAPRECORD_JSTRINGHOLDER_H
#define MMAPRECORD_JSTRINGHOLDER_H

#include <jni.h>

class JStringHolder {
private:
    JNIEnv &mEnv;
    jstring &mJString;
    const char *mCString;

public:
    JStringHolder(JNIEnv &mEnv, jstring mJString) : mEnv(mEnv), mJString(mJString) {
        mCString = mEnv.GetStringUTFChars(mJString, 0);
    }

    virtual ~JStringHolder() {
        mEnv.ReleaseStringUTFChars(mJString, mCString);
    }

    const char *getCString() const {
        return mCString;
    }
};

#endif //MMAPRECORD_JSTRINGHOLDER_H
