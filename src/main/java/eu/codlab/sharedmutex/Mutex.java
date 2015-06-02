package eu.codlab.sharedmutex;

/**
 * Created by kevinleperf on 31/05/15.
 */
public class Mutex {
    private Mutex() {

    }

    public Mutex(String path) {
        configure(path);
    }

    public Mutex(String path, boolean configure_instances) {
        if (configure_instances) {
            configureInstances(path);
        } else {
            configure(path);
        }
    }

    {
        System.loadLibrary("mutex_shared");
    }

    private native void configureInstances(String string);

    private native void configure(String string);

    public native void lock();

    public native void unlock();

    public native void release();
}
