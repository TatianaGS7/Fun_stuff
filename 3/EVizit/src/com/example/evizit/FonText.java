package com.example.evizit;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.Button;
import android.widget.TextView;
import java.util.List;  //BD
import com.example.evizit.DataBase;
import com.example.evizit.R;//



public class FonText extends Activity {
	private TextView Rc, mLabel;
	private DataBase dh; //БД
	private EditText numberviz, Editj, Saitj, editemailj, numphonej;

	
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.fontext);
		final RadioButton radio1 = (RadioButton)findViewById(R.id.radio1);
		final RadioButton radio2 = (RadioButton)findViewById(R.id.radio2);
		final RadioButton radio3 = (RadioButton)findViewById(R.id.radio3);
		final RadioButton radio4 = (RadioButton)findViewById(R.id.radio4);
		final RadioButton radio5 = (RadioButton)findViewById(R.id.radio5);
		
		 numberviz = (EditText) findViewById(R.id.num);
		 Editj = (EditText) findViewById(R.id.Edit);
		 Saitj = (EditText) findViewById(R.id.Sait);
		 editemailj = (EditText) findViewById(R.id.editemail);
		 numphonej = (EditText) findViewById(R.id.numphone);
		 mLabel = (TextView)findViewById(R.id.textf);

		 
		
		 
		
		Rc = (TextView)findViewById(R.id.Records);  //БД
        Button ButIns = (Button)findViewById(R.id.Insert);//БД
        Button ButDel= (Button)findViewById(R.id.Del);//БД
        ButIns.setOnClickListener(insert_action);//БД
        ButDel.setOnClickListener(delete_all_action);//БД
		
		//БазаДанных
	 
        dh = DataBase();
        dh.deleteAll();
        
        List<String> notes = this.dh.selectAll();
        StringBuilder sb = new StringBuilder();
        sb.append("");
        
        for (String note : notes) {
        	sb.append(note + "\n");
        }
       Rc.setText(sb); 

       
       //
    		
		radio1.setOnClickListener(radioButtonClick);
		radio2.setOnClickListener(radioButtonClick);
		radio3.setOnClickListener(radioButtonClick);
		radio4.setOnClickListener(radioButtonClick);
		radio5.setOnClickListener(radioButtonClick);
		
		final Button button1 = (Button)findViewById(R.id.Back);
		button1.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View arg0) {
				Intent intent = new Intent();
				intent.setClass(getApplicationContext(), MainActivity.class);
				startActivity(intent);				
			}
		});
		

		final Button button2 = (Button)findViewById(R.id.OK);
		button2.setOnClickListener(sent);  
	}

        OnClickListener radioButtonClick = new OnClickListener() {
        public void onClick(View v) {
        RadioButton rb = (RadioButton)v;
        mLabel.setText("Выбран " + rb.getText());	
        switch (v.getId()) {
        case R.id.radio1:
        Rc.setBackgroundResource(R.drawable.f1);
        break;
        case R.id.radio2: 	
        Rc.setBackgroundResource(R.drawable.f2);
        break;   
        case R.id.radio3: 
        Rc.setBackgroundResource(R.drawable.f3);
        break;
        case R.id.radio4:
        Rc.setBackgroundResource(R.drawable.f4);
        break;
        case R.id.radio5: 	
        Rc.setBackgroundResource(R.drawable.f5);
        break;      
        }
      }
	};
	
	
	//БД
    public DataBase DataBase(){
	   return new DataBase(this);
 }
    
    private OnClickListener delete_all_action = new OnClickListener() {
 	   public void onClick(View v) {
 		  numberviz.getText().clear();
 		   Editj.getText().clear();
 		   Saitj.getText().clear();
 		   editemailj.getText().clear();
 		   numphonej.getText().clear();
 		   dh = DataBase();
 		   dh.deleteAll();
 		   refresh ();
 	   }
    };
    private OnClickListener insert_action = new OnClickListener() {
 	   public void onClick(View v) {
 		   
	 	    
 		   dh = DataBase();
 		   EditText memo1 = (EditText)findViewById(R.id.Edit);
 		   EditText memo2 = (EditText)findViewById(R.id.Sait);
 		   EditText memo3 = (EditText)findViewById(R.id.editemail);
 		   EditText memo4 = (EditText)findViewById(R.id.numphone);
 		   dh.insert(memo1.getText().toString());
 		   dh.insert(memo2.getText().toString());
 		   dh.insert(memo3.getText().toString());
 		   dh.insert(memo4.getText().toString());
 		   refresh();
 	   }
    };
    
    public void refresh () {
 	   dh = DataBase();
 	   TextView Rc = (TextView)findViewById(R.id.Records); 
 	   List<String> notes = dh.selectAll();
 	   StringBuilder sb  = new StringBuilder();
 	   for (String note : notes) {
 		   sb.append(note + "\n" + "\n" );
 	   }
 	   Rc.setText(sb);
    }
    
    private OnClickListener sent = new OnClickListener() {

	public void onClick(View v) {

             final Intent emailIntent = new Intent(android.content.Intent.ACTION_SEND);
             emailIntent.setType("plain/text");
             
             emailIntent.putExtra(android.content.Intent.EXTRA_EMAIL,
            		    new String[]{"spenelopes@rambler.ru"});
             
             emailIntent.putExtra(Intent.EXTRA_SUBJECT, "Заказ визитки");
            
 

             String message = "";
             message += "ФИО: "+ Editj.getText(); 
             message += "\n" + "Сайт: " + Saitj.getText(); 
             message += "\n" + "Эл. почта: "+ editemailj.getText(); 
             message += "\n" + "Телефон: "+ numphonej.getText();   
            // message += Rc.getText(); 
             message +=  "\n" + "Количество визиток: "+ numberviz.getText();
             message += "\n" + mLabel.getText();
             emailIntent.putExtra(Intent.EXTRA_TEXT, message); 
  
             FonText.this.startActivity(Intent.createChooser(emailIntent,
                 "Отправка письма..."));
           }

     };


}
