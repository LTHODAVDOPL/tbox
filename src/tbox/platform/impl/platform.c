/*!The Treasure Box Library
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * Copyright (C) 2009-2020, TBOOX Open Source Group.
 *
 * @author      ruki
 * @file        platform.c
 * @ingroup     platform
 *
 */

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "platform.h"
#include "impl.h"
#include "../cpu.h"
#include "../exception.h"
#include "../cache_time.h"
#include "../../network/network.h"
#if defined(TB_CONFIG_OS_ANDROID)
#   include "../android/android.h"
#elif defined(TB_CONFIG_OS_WINDOWS)
#   include "../windows/windows.h"
#endif

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementation
 */

tb_bool_t tb_platform_init_env(tb_handle_t priv)
{
    // init the current platform envirnoment
#if defined(TB_CONFIG_OS_ANDROID)
    if (!tb_android_init_env(priv)) return tb_false;
#elif defined(TB_CONFIG_OS_WINDOWS)
    if (!tb_windows_init_env()) return tb_false;
#endif

    // init socket envirnoment
    if (!tb_socket_init_env()) return tb_false;

    // init dns envirnoment
#ifndef TB_CONFIG_MICRO_ENABLE
    if (!tb_dns_init_env()) return tb_false;
#endif

    // init thread local envirnoment
#ifndef TB_CONFIG_MICRO_ENABLE
    if (!tb_thread_local_init_env()) return tb_false;
#endif

    // init exception envirnoment
#ifdef TB_CONFIG_EXCEPTION_ENABLE
    if (!tb_exception_init_env()) return tb_false;
#endif

    // init cpu count/cache
#ifndef TB_CONFIG_MICRO_ENABLE
    (tb_void_t)tb_cpu_count();
#endif

    // ok
    return tb_true;
}
tb_void_t tb_platform_exit_env()
{
    // exit exception envirnoment
#ifdef TB_CONFIG_EXCEPTION_ENABLE
    tb_exception_exit_env();
#endif

    // exit thread local envirnoment
#ifndef TB_CONFIG_MICRO_ENABLE
    tb_thread_local_exit_env();
#endif

    // exit dns envirnoment
#ifndef TB_CONFIG_MICRO_ENABLE
    tb_dns_exit_env();
#endif

    // exit socket envirnoment
    tb_socket_exit_env();

    // exit the current platform envirnoment
#if defined(TB_CONFIG_OS_ANDROID)
    tb_android_exit_env();
#elif defined(TB_CONFIG_OS_WINDOWS)
    tb_windows_exit_env();
#endif
}

