#ifndef INJECTDEMO_LOGGER_H
#define INJECTDEMO_LOGGER_H

#include <android/log.h>

#define TAG "INJECT"
#define LOGD(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__)
#define LOGF(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__)

#endif //INJECTDEMO_LOGGER_H
