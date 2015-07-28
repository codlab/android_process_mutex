package eu.codlab.app_test;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;

import eu.codlab.sharedmutex.Mutex;

public class MainActivity extends AppCompatActivity {
    private final static int LOOP = 100000;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Mutex.initAll();
        final Mutex mutex_1 = new Mutex();
        final Mutex mutex_2 = new Mutex();
        final boolean[] bool = new boolean[]{true};

        Thread thread = new Thread() {
            public void run() {
                for (int i = 0; i < LOOP; i++) {
                    mutex_1.lock();
                    try {
                        Thread.sleep(60);
                    } catch (Exception e) {

                    }
                    if (!bool[0]) {
                        throw new RuntimeException("Exception Mutex during tests !");
                    }else{
                        Log.d("MainActivity", "ok");
                    }
                    mutex_2.unlock();
                    try {
                        Thread.sleep(60);
                    } catch (Exception e) {

                    }

                }
            }
        };
        Thread thread2 = new Thread() {
            public void run() {
                for (int i = 0; i < LOOP; i++) {
                    mutex_2.lock();
                    bool[0] = false;
                    Log.d("MainActivity", "enter - set to false");
                    try {
                        Thread.sleep(100);
                    } catch (Exception e) {

                    }
                    Log.d("MainActivity", "enter - set to true");
                    bool[0] = true;
                    mutex_2.unlock();
                    try {
                        Thread.sleep(60);
                    } catch (Exception e) {

                    }
                }
            }
        };
        thread.start();
        thread2.start();

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
