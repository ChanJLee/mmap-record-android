package com.chan.lib;

import android.support.annotation.Keep;

/**
 * Created by chan on 2018/1/21.
 */
@Keep
public class MmapRecord {
	private long mBufferInfoReference;

	static {
		System.loadLibrary("mmap-record");
	}

	public MmapRecord(String bufferPath, String path) {
		init(bufferPath, path);
	}

	private native int init(String bufferPath, String path);

	public native void release();

	public native void save(byte[] data);

	public native byte[] read();

	public native void recycle(byte[] data);
}
