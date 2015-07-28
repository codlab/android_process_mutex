package eu.codlab.sharedmutex;

/**
 * Created by kevinleperf on 31/05/15.
 */
public class Mutex {
    private static boolean _static_init = false;

    public Mutex() {

    }

    {
        System.loadLibrary("mutex_shared");
    }

    public static void initAll() {
        Mutex mutex = new Mutex();
        mutex.configureInstances("initAll");
        _static_init = true;
    }

    public void init() {
        if (_static_init) {
            configure("init");
        } else {
            throw new IllegalStateException("static initAll method must be called first");
        }
    }

    private native void configureInstances(String string);

    private native void configure(String string);

    public native void lock();

    public native void unlock();

    public native void release();
}
