#include <jni.h>
#include <string>
#include "Client.h"

/**
 *
 * @param env
 * @param jStr
 * @return
 */
std::string jstringTostring(JNIEnv *env, jstring jStr) {
    if (!jStr)
        return "";

    const jclass stringClass = env->GetObjectClass(jStr);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));

    size_t length = (size_t) env->GetArrayLength(stringJbytes);
    jbyte *pBytes = env->GetByteArrayElements(stringJbytes, NULL);

    std::string ret = std::string((char *) pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);
    return ret;
}


extern "C" {
    /**
     *
     * @param env
     * @return
     */
JNIEXPORT jstring JNICALL
Java_com_example_nativeapplication_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

/**
 *
 * @param env
 * @param ip
 * @param port
 * @return
 */
JNIEXPORT jint JNICALL
Java_com_example_nativeapplication_MainActivity_connect(
        JNIEnv *env,
        jobject,
        jstring ip,
        jint port
) {

    Client client;
    string host = jstringTostring(env, ip);
    return client.connectToServer(host, (int) port);
}

/**
 *
 * @param env
 * @param thiz
 * @param port
 */
JNIEXPORT void JNICALL
Java_com_example_nativeapplication_MainActivity_disconnect(JNIEnv *env, jobject thiz, jint port) {
    Client client;
    client.disconnectFromServer((int) port);
}

/**
 *
 * @param env
 * @param thiz
 * @param port
 * @return
 */
JNIEXPORT jstring JNICALL
Java_com_example_nativeapplication_MainActivity_receivedData(JNIEnv *env, jobject thiz, jint port) {
    Client client;
    string data = client.receivedData((int) port);
    return env->NewStringUTF(data.c_str());
}

/**
 *
 * @param env
 * @param thiz
 * @param port
 * @param data
 */
JNIEXPORT void JNICALL
Java_com_example_nativeapplication_MainActivity_sendData(JNIEnv *env, jobject thiz, jint port,
                                                         jstring data) {
    Client client;
    string sData = jstringTostring(env, data);
    client.sendData((int) port, sData);
}

}

