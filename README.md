# Android_hook_sf_draw_arm64
hook surfaceflinger进程的eglSwapBuffers方式实现绘制,适用arm64 root下的安卓真机

该版本仅适用于arm64版本.

# 使用方法
```
cd jni
ndk-build
```

```
cd libs/arm64-v8a
adb push inject /data/local/tmp
adb push libhello.so /data/local/tmp
adb shell
cd /data/local/tmp
chmod 777 inject
./inject
```


参考了这篇文章

https://github.com/MelonWXD/ELFHooker

https://github.com/android/ndk-samples/tree/main/hello-gl2


![image](img/img.jpg)

## Android 12
该方法并不适用高版本安卓,
高版本请参考:
[Magisk注入app并嵌入imgui](https://pshocker.github.io/2022/03/21/Magisk%E6%B3%A8%E5%85%A5app%E5%B9%B6%E5%B5%8C%E5%85%A5imgui/).