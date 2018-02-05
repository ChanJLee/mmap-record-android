package com.chan.mmaprecord;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.chan.lib.MmapRecord;

import java.io.File;

public class MainActivity extends AppCompatActivity {

	private MmapRecord mMmapRecord;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		File dir = getDir("sd", MODE_PRIVATE);
		if (!dir.exists()) {
			dir.mkdirs();
		}

		String bufferPath = new File(dir, "temp_log.log").getAbsolutePath();
		String targetPath = new File(dir, "log.log").getAbsolutePath();
		final MmapRecord mmapRecord = mMmapRecord = new MmapRecord(bufferPath, targetPath);
		final TextView textView = findViewById(R.id.sample_text);
		Button button = findViewById(R.id.button);
		button.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				byte[] array = mmapRecord.read();
				String json = array == null || array.length == 0 ? "" : new String(array);
				if (array != null) {
					mmapRecord.recycle(array);
				}
				String time = System.currentTimeMillis() + "";
				String content = (time + "|" + json);
				Log.d("mmap_record", content);
				Log.d("size", content.getBytes().length + "");
				mmapRecord.save(content.getBytes());
				textView.setText(time);
			}
		});

		findViewById(R.id.kill).setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				finish();
			}
		});

		findViewById(R.id.release).setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				mMmapRecord.release();
			}
		});

		findViewById(R.id.flush).setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				mMmapRecord.flush();
			}
		});
	}
}
