package com.chan.lib;

/**
 * Created by chan on 2018/1/21.
 */

public class MmapRecord {
	static {
		System.loadLibrary("mmap-record");
	}

	public MmapRecord(String path) {
		init(path);
	}

	private native int init(String path);
}
