package com.chan.lib;

/**
 * Created by chan on 2018/1/21.
 */

public class MmapRecord {
	private long mBufferInfoReference;

	static {
		System.loadLibrary("mmap-record");
	}

	public MmapRecord(String path, String log) {
		init(path, log);
	}

	private native int init(String path, String log);

	public native void release();

	public native void save(String json);

	public native String read();
}
