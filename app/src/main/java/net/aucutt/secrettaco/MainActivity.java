package net.aucutt.secrettaco;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Adapter;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.CheckBox;
import android.widget.ListAdapter;
import android.widget.ListView;
import android.widget.RadioButton;
import android.widget.TextView;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("nativelib");
    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
         final TextView textView = (TextView)findViewById(R.id.textView);
        peaceTaco();
        ListView listo = (ListView)findViewById(R.id.listView);
        String[] values = new String[] {"Secret1","Secret2","Secret3","Secret4","Secret5","Force Secret null","Force env null"};
        final ArrayList<String> list = new ArrayList<String>();
        for (int i = 0; i < values.length; ++i) {
            list.add(values[i]);
        }
        ArrayAdapter theAdapter = new ArrayAdapter<>(this,android.R.layout.simple_list_item_1, list);

        listo.setAdapter(theAdapter);
        listo.setOnItemClickListener( new AdapterView.OnItemClickListener() {
                                          @Override
                                          public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                                               String secret = (String)  parent.getItemAtPosition(position);
                                              //lookupKey(secret);
                                              CheckBox checkers = (CheckBox) findViewById(R.id.check1);
                                              String production = checkers.isChecked() ? "prod" : "someStupidEnvironment";
                                              if ( secret.equalsIgnoreCase("Force Secret null")) {
                                                  secret = null;
                                              } else  if ( secret.equalsIgnoreCase("Force env null")) {
                                                  production = null;
                                              }

                                              textView.setText(secret + " : "  + lookupKey(secret,production));
                                          }
                                      }


        );

    }

    public native String lookupKey(String key,String deployEnv);

    public native void peaceTaco();

}
