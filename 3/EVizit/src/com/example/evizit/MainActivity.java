package com.example.evizit;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.view.View;
import android.widget.Button;

public class MainActivity extends Activity {


	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		
		final Button button1 = (Button)findViewById(R.id.button1);
		button1.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View arg0) {
				Intent intent = new Intent();
				intent.setClass(getApplicationContext(), FonText.class);
				startActivity(intent);				
			}
		});
		
		final Button button2 = (Button)findViewById(R.id.button2);
		button2.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View arg0) {
				Intent intent = new Intent();
				intent.setClass(getApplicationContext(), Company_viz.class);
				startActivity(intent);				
			}
		});
		

	}
}
