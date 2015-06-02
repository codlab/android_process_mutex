Android Mutex across Processus
=========================

A simple mutex based system for Android to share mutex locking system across threads and even processus.


How it works ?
==============

Since Android does not provide standard Shared Memory APIs, the library is based on https://github.com/pelya/android-shmem
which provide everything you need to add support for such a feature.

pthread + mutex are used inside the library


How to use ?
============

```
compile 'eu.codlab:mutex_shared:0.9'
```

At first, create an instance of the object, prefereably in the Application instance
Then simply :
```
Mutex my_mutex = new Mutex("SomeKeyToMapTheMutex");

my_mutex.lock();
//enter the critical section

... stuff in critical section ...

//quit the critical section
my_mutex.unlock();
```

Example ? those lines in Threads, AsyncTask, AbstractThreadedSyncAdapter, ...

Compatibility & limitation
==========================

Compatible with every Android version, every architecture.

As state in the TODOs, the library lacks of some feature (!!). Any issue, comments? Feel free to comment, share, pull request


TODOs
=====

* create mutex on server id listener (hence, providing a path/id will attach the memory to the correct segment)

* enhance memory - check for leaks
