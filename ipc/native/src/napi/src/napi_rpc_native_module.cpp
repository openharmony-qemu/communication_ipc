/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "napi_ashmem.h"
#include "napi_message_parcel.h"
#include "napi_message_sequence.h"
#include "napi/native_api.h"
#include "napi/native_node_api.h"
#include "napi_remote_object.h"

namespace OHOS {
extern napi_value NAPI_RemoteProxy_queryLocalInterface(napi_env env, napi_callback_info info);
extern napi_value NAPI_RemoteProxy_getLocalInterface(napi_env env, napi_callback_info info);
extern napi_value NAPI_RemoteProxy_sendRequest(napi_env env, napi_callback_info info);
extern napi_value NAPI_RemoteProxy_sendMessageRequest(napi_env env, napi_callback_info info);
extern napi_value NAPI_RemoteProxy_addDeathRecipient(napi_env env, napi_callback_info info);
extern napi_value NAPI_RemoteProxy_registerDeathRecipient(napi_env env, napi_callback_info info);
extern napi_value NAPI_RemoteProxy_removeDeathRecipient(napi_env env, napi_callback_info info);
extern napi_value NAPI_RemoteProxy_unregisterDeathRecipient(napi_env env, napi_callback_info info);
extern napi_value NAPI_RemoteProxy_getInterfaceDescriptor(napi_env env, napi_callback_info info);
extern napi_value NAPI_RemoteProxy_getDescriptor(napi_env env, napi_callback_info info);
extern napi_value NAPI_RemoteProxy_isObjectDead(napi_env env, napi_callback_info info);

EXTERN_C_START
extern napi_value NAPIIPCSkeletonExport(napi_env env, napi_value exports);
extern napi_value NAPIRemoteProxyExport(napi_env env, napi_value exports);
extern napi_value NAPIRemoteInterfaceExport(napi_env env, napi_value exports,
    const napi_callback *proxyMethods, size_t proxyCount);
extern napi_value NAPIMessageOptionExport(napi_env env, napi_value exports);
extern napi_value NAPICallingInfoExport(napi_env env, napi_value exports);

static napi_value RpcExport(napi_env env, napi_value exports)
{
    NAPI_MessageParcel::Export(env, exports);
    NAPI_MessageSequence::Export(env, exports);
    NAPIAshmem::AshmemExport(env, exports);
    NAPIIPCSkeletonExport(env, exports);
    NAPIRemoteObjectExport(env, exports);
    NAPIRemoteProxyExport(env, exports);
    static constexpr napi_callback proxyMethods[] = {
        NAPI_RemoteProxy_queryLocalInterface,
        NAPI_RemoteProxy_getLocalInterface,
        NAPI_RemoteProxy_sendRequest,
        NAPI_RemoteProxy_sendMessageRequest,
        NAPI_RemoteProxy_addDeathRecipient,
        NAPI_RemoteProxy_registerDeathRecipient,
        NAPI_RemoteProxy_removeDeathRecipient,
        NAPI_RemoteProxy_unregisterDeathRecipient,
        NAPI_RemoteProxy_getInterfaceDescriptor,
        NAPI_RemoteProxy_getDescriptor,
        NAPI_RemoteProxy_isObjectDead,
    };
    NAPIRemoteInterfaceExport(env, exports, proxyMethods, sizeof(proxyMethods) / sizeof(proxyMethods[0]));
    NAPIMessageOptionExport(env, exports);
    NapiError::NAPIRpcErrorEnumExport(env, exports);
    NAPICallingInfoExport(env, exports);
    return exports;
}
EXTERN_C_END

/*
 * Module register function
 */
NAPI_MODULE(rpc, RpcExport)
} // namespace OHOS