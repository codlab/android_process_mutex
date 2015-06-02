#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <android/log.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <jni.h>
#include <semaphore.h>
#include "sys/shm.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MUTEX "/mutex_lock"
int des_cond, des_msg, des_mutex;
int mode = S_IRWXU | S_IRWXG;

pthread_mutexattr_t mutexAttr;
pthread_mutex_t * semaphor;

JNIEXPORT void JNICALL Java_eu_codlab_sharedmutex_Mutex_configureInstances(JNIEnv* env, jclass clazz, jstring string) {
    const char *nativeString = (*env)->GetStringUTFChars(env, string, 0);

    des_mutex = shmget(IPC_PRIVATE, sizeof(*semaphor), mode);
    semaphor = shmat(des_mutex, NULL, 0);

    pthread_mutex_lock(semaphor);

    pthread_mutexattr_init(&mutexAttr);
    pthread_mutexattr_setpshared(&mutexAttr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(semaphor, &mutexAttr);

    pthread_mutex_unlock(semaphor);

    (*env)->ReleaseStringUTFChars(env, string, nativeString);
}

JNIEXPORT void JNICALL Java_eu_codlab_sharedmutex_Mutex_configure(JNIEnv* env, jclass clazz, jstring string) {
    const char *nativeString = (*env)->GetStringUTFChars(env, string, 0);

    des_mutex = shmget(IPC_PRIVATE, sizeof(*semaphor), mode);
    semaphor = shmat(des_mutex, NULL, 0);

    sleep(1);

    (*env)->ReleaseStringUTFChars(env, string, nativeString);
}

JNIEXPORT void JNICALL Java_eu_codlab_sharedmutex_Mutex_lock(JNIEnv* env, jclass clazz) {
    pthread_mutex_lock(semaphor);
}

JNIEXPORT void JNICALL Java_eu_codlab_sharedmutex_Mutex_unlock(JNIEnv* env, jclass clazz) {
    pthread_mutex_unlock(semaphor);
}

JNIEXPORT void JNICALL Java_eu_codlab_sharedmutex_Mutex_release(JNIEnv* env, jclass clazz) {
    pthread_mutexattr_destroy(&mutexAttr);
    pthread_mutex_destroy(semaphor);
}



static JNINativeMethod method_table[] = {
    { "configure", "(Ljava/lang/String;)V", (void *) Java_eu_codlab_sharedmutex_Mutex_configure },
    { "lock",      "()V", (void *) Java_eu_codlab_sharedmutex_Mutex_lock },
    { "unlock",    "()V", (void *) Java_eu_codlab_sharedmutex_Mutex_unlock },
    { "release",   "()V", (void *) Java_eu_codlab_sharedmutex_Mutex_release }
};

static int method_table_size = sizeof(method_table) / sizeof(method_table[0]);

jint JNI_OnLoad(JavaVM* vm, void* reserved) {
  JNIEnv* env;
  if ((*vm)->GetEnv(vm, (void **) &env, JNI_VERSION_1_6) != JNI_OK) {
    return JNI_ERR;
  } else {
    jclass clazz = (*env)->FindClass(env, "eu/codlab/sharedmutex/Mutex");
    if (clazz) {
      jint ret = (*env)->RegisterNatives(env, clazz, method_table, method_table_size);
      (*env)->DeleteLocalRef(env, clazz);
      return ret == 0 ? JNI_VERSION_1_6 : JNI_ERR;
    } else {
      return JNI_ERR;
    }
  }
}

#ifdef __cplusplus
}
#endif