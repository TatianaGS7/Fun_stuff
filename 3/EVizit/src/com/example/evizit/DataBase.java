package com.example.evizit;


import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.database.sqlite.SQLiteStatement;
import java.util.ArrayList;
import java.util.List;

public class DataBase {
	private static final String DATABASE_NAME = "mydatabase.db";
	private static final String TABLE_NAME = "table1";
	private static final String COL_NAME = "name";
	private static final int DATABASE_VERSION = 1;
	
	
	private Context context;
	private SQLiteDatabase db;
	private static final String INSERT = "insert into "  +  TABLE_NAME  +  "(name) values (?)";
	private SQLiteStatement insertStmt;
	
	public DataBase(Context context) {
		this.context = context;
		OpenHelper openHelper = new OpenHelper(this.context);
		this.db = openHelper.getWritableDatabase();
		this.insertStmt = this.db.compileStatement(INSERT);
		
	}
	
	public long insert(String name) {
		this.insertStmt.bindString(1, name);
		return this.insertStmt.executeInsert();
	}
	
	public void deleteAll() {
		this.db.delete(TABLE_NAME, null, null);
		
	}
	
	
	public List<String> selectAll() {
		List<String> list = new ArrayList<String>();
		Cursor cursor = this.db.query(TABLE_NAME, new String[] { COL_NAME }, null, null, null, null, null);
		if (cursor.moveToFirst()){
			do{
				list.add(cursor.getString(0));
			} while (cursor.moveToNext());
		}
		if (cursor != null && !cursor.isClosed()) {
			cursor.close();
		}
		return list;
		}
	
	private static class OpenHelper extends SQLiteOpenHelper {
		OpenHelper(Context context) {
			super(context, DATABASE_NAME, null, DATABASE_VERSION);
		}
		
		 @Override
		    public void onCreate(SQLiteDatabase db) {
		        db.execSQL("CREATE TABLE "  +  TABLE_NAME  +  "(_id INTEGER PRIMARY KEY AUTOINCREMENT, " + COL_NAME + " TEXT)");
		    }
		 
		 @Override
		    public void onUpgrade(SQLiteDatabase db, int oldVersion, int NewVersion) {
		        db.execSQL("DROP TABLE IF EXIST "  +  TABLE_NAME);
		        onCreate(db);
		 }
	}
	
}
