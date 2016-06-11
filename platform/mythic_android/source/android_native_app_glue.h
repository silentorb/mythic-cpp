#pragma once

/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <poll.h>
#include <pthread.h>
#include <sched.h>

#include <android/looper.h>
#include <glm/vec2.hpp>
#include "Android_App.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The native activity interface provided by <android/native_activity.h>
 * is based on a set of application-provided callbacks that will be called
 * by the Activity's main thread when certain events occur.
 *
 * This means that each one of this callbacks _should_ _not_ block, or they
 * risk having the system force-close the application. This programming
 * model is direct, lightweight, but constraining.
 *
 * The 'android_native_app_glue' static library is used to provide a different
 * execution model where the application can implement its own main event
 * loop in a different thread instead. Here's how it works:
 *
 * 1/ The application must provide a function named "android_main()" that
 *    will be called when the activity is created, in a new thread that is
 *    distinct from the activity's main thread.
 *
 * 2/ android_main() receives a pointer to a valid "android_app" structure
 *    that contains references to other important objects, e.g. the
 *    ANativeActivity obejct instance the application is running in.
 *
 * 3/ the "android_app" object holds an ALooper instance that already
 *    listens to two important things:
 *
 *      - activity lifecycle events (e.g. "pause", "resume"). See APP_CMD_XXX
 *        declarations below.
 *
 *      - input events coming from the AInputQueue attached to the activity.
 *
 *    Each of these correspond to an ALooper identifier returned by
 *    ALooper_pollOnce with values of LOOPER_ID_MAIN and LOOPER_ID_INPUT,
 *    respectively.
 *
 *    Your application can use the same ALooper to listen to additional
 *    file-descriptors.  They can either be callback based, or with return
 *    identifiers starting with LOOPER_ID_USER.
 *
 * 4/ Whenever you receive a LOOPER_ID_MAIN or LOOPER_ID_INPUT event,
 *    the returned data will point to an android_poll_source structure.  You
 *    can call the process() function on it, and fill in android_app->onAppCmd
 *    and android_app->onInputEvent to be called for your own processing
 *    of the event.
 *
 *    Alternatively, you can call the low-level functions to read and process
 *    the data directly...  look at the process_cmd() and process_input()
 *    implementations in the glue to see how to do this.
 *
 * See the sample named "native-activity" that comes with the NDK with a
 * full usage example.  Also look at the JavaDoc of NativeActivity.
 */

enum {
    /**
     * Looper data ID of commands coming from the app's main thread, which
     * is returned as an identifier from ALooper_pollOnce().  The data for this
     * identifier is a pointer to an android_poll_source structure.
     * These can be retrieved and processed with android_app_read_cmd()
     * and android_app_exec_cmd().
     */
    LOOPER_ID_MAIN = 1,

    /**
     * Looper data ID of events coming from the AInputQueue of the
     * application's window, which is returned as an identifier from
     * ALooper_pollOnce().  The data for this identifier is a pointer to an
     * android_poll_source structure.  These can be read via the inputQueue
     * object of android_app.
     */
    LOOPER_ID_INPUT = 2,

    /**
     * Start of user-defined ALooper identifiers.
     */
    LOOPER_ID_USER = 3,
};

enum {
    /**
     * Command from main thread: the AInputQueue has changed.  Upon processing
     * this command, android_app->inputQueue will be updated to the new queue
     * (or NULL).
     */
    APP_CMD_INPUT_CHANGED,

    /**
     * Command from main thread: a new ANativeWindow is ready for use.  Upon
     * receiving this command, android_app->window will contain the new window
     * surface.
     */
    APP_CMD_INIT_WINDOW,

    /**
     * Command from main thread: the existing ANativeWindow needs to be
     * terminated.  Upon receiving this command, android_app->window still
     * contains the existing window; after calling android_app_exec_cmd
     * it will be set to NULL.
     */
    APP_CMD_TERM_WINDOW,

    /**
     * Command from main thread: the current ANativeWindow has been resized.
     * Please redraw with its new size.
     */
    APP_CMD_WINDOW_RESIZED,

    /**
     * Command from main thread: the system needs that the current ANativeWindow
     * be redrawn.  You should redraw the window before handing this to
     * android_app_exec_cmd() in order to avoid transient drawing glitches.
     */
    APP_CMD_WINDOW_REDRAW_NEEDED,

    /**
     * Command from main thread: the content area of the window has changed,
     * such as from the soft input window being shown or hidden.  You can
     * find the new content rect in android_app::contentRect.
     */
    APP_CMD_CONTENT_RECT_CHANGED,

    /**
     * Command from main thread: the app's activity window has gained
     * input focus.
     */
    APP_CMD_GAINED_FOCUS,

    /**
     * Command from main thread: the app's activity window has lost
     * input focus.
     */
    APP_CMD_LOST_FOCUS,

    /**
     * Command from main thread: the current device configuration has changed.
     */
    APP_CMD_CONFIG_CHANGED,

    /**
     * Command from main thread: the system is running low on memory.
     * Try to reduce your memory use.
     */
    APP_CMD_LOW_MEMORY,

    /**
     * Command from main thread: the app's activity has been started.
     */
    APP_CMD_START,

    /**
     * Command from main thread: the app's activity has been resumed.
     */
    APP_CMD_RESUME,

    /**
     * Command from main thread: the app should generate a new saved state
     * for itself, to restore from later if needed.  If you have saved state,
     * allocate it with malloc and place it in android_app.savedState with
     * the size in android_app.savedStateSize.  The will be freed for you
     * later.
     */
    APP_CMD_SAVE_STATE,

    /**
     * Command from main thread: the app's activity has been paused.
     */
    APP_CMD_PAUSE,

    /**
     * Command from main thread: the app's activity has been stopped.
     */
    APP_CMD_STOP,

    /**
     * Command from main thread: the app's activity is being destroyed,
     * and waiting for the app thread to clean up and exit before proceeding.
     */
    APP_CMD_DESTROY,
};

/**
 * Call when ALooper_pollAll() returns LOOPER_ID_MAIN, reading the next
 * app command message.
 */
int8_t android_app_read_cmd(struct Android_App* android_app);

/**
 * Call with the command returned by android_app_read_cmd() to do the
 * initial pre-processing of the given command.  You can perform your own
 * actions for the command after calling this function.
 */
void android_app_pre_exec_cmd(struct Android_App* android_app, int8_t cmd);

/**
 * Call with the command returned by android_app_read_cmd() to do the
 * final post-processing of the given command.  You must have done your own
 * actions for the command before calling this function.
 */
void android_app_post_exec_cmd(struct Android_App* android_app, int8_t cmd);


#ifdef __cplusplus
}
#endif

glm::vec2 android_get_dpi();