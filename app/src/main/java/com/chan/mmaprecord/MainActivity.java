package com.chan.mmaprecord;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import com.chan.lib.MmapRecord;

import java.io.File;

public class MainActivity extends AppCompatActivity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		TextView textView = findViewById(R.id.sample_text);
		File dir = getDir("sd", MODE_PRIVATE);
		if (!dir.exists()) {
			dir.mkdirs();
		}
		MmapRecord mmapRecord = new MmapRecord(new File(dir, "x.log").getAbsolutePath());
	}
}
