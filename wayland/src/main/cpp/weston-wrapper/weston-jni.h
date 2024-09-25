#ifndef WESTON_JNI_H
#define WESTON_JNI_H

#include <jni.h>
#include <pixman.h>
#include <libweston/backend-android.h>
#include <android/native_window_jni.h>
#include "input_ops.h"

#define RENDERER_PIXMAN 0
#define RENDERER_GL 1

struct WestonConfig {
    int rendererType;
    int renderRefreshRate;
    ARect screenRect;
    ARect displayRect;
    ARect renderRect;
    char socketPath[64];

    float outputScaleX;
    float outputScaleY;
    int outputStartX;
    int outputStartY;
    int displayWidth;
    int displayHeight;
    bool isScaled;
    pixman_image_t* compositeImg;
};

struct WestonJni {
    jobject javaObject;
    ANativeWindow* window;
    ANativeWindow_Buffer buffer;
    struct WestonConfig config;

    struct wl_display* display;
    struct weston_log_context* logCtx;
    struct weston_compositor* compositor;
    struct weston_android_backend_config* backendConfig;
    struct weston_backend* backend;
    struct weston_head* head;
    struct weston_output* output;
    struct wl_shell* shell;
    bool display_running;

    void (*output_create)();
    void (*output_destroy)();
    void (*output_set_size)(int, int);
    void (*repaint_output_pixman)(pixman_image_t*);
    void (*destroy)();

    android_touch func_android_touch;
};

#endif //WESTON_JNI_H