/*
 * Copyright 2023 The Android Open Source Project
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
 */

#include <android_runtime/AndroidRuntime.h>
#include <android_runtime/Log.h>
#include <nativehelper/JNIHelp.h>
#include <perfetto/public/data_source.h>
#include <perfetto/public/producer.h>
#include <perfetto/public/protos/trace/test_event.pzc.h>
#include <perfetto/public/protos/trace/trace_packet.pzc.h>
#include <utils/Log.h>
#include <utils/RefBase.h>

#include <sstream>
#include <thread>

#include "core_jni_helpers.h"

namespace android {

class PerfettoDataSourceInstance {
public:
    PerfettoDataSourceInstance(JNIEnv* env, jobject javaDataSourceInstance,
                               PerfettoDsInstanceIndex inst_idx);
    ~PerfettoDataSourceInstance();

    void onStart(JNIEnv* env);
    void onFlush(JNIEnv* env);
    void onStop(JNIEnv* env);

    jobject GetJavaDataSourceInstance() {
        return mJavaDataSourceInstance;
    }

    PerfettoDsInstanceIndex getIndex() {
        return inst_idx;
    }

private:
    PerfettoDsInstanceIndex inst_idx;
    jobject mJavaDataSourceInstance;
};
} // namespace android