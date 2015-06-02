Android Mutex across Processus
=========================

A simple mutex based system for Android to share mutex locking system across threads and even processus.


How it works ?
==============

Since Android does not provide standard Shared Memory APIs, the library is based on https://github.com/pelya/android-shmem
which provide everything you need to add support for such a feature.

pthread + mutex are used inside the library

TODOs
=====

* create mutex on server id listener (hence, providing a path/id will attach the memory to the correct segment)

* enhance memory - check for leaks
