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


![image](img/img.jpg)
