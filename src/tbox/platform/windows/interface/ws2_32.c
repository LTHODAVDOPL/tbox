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
 * @file        ws2_32.c
 *
 */

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "ws2_32.h"
#include "../../atomic.h"
#include "../../../utils/utils.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * pragma
 */
#ifndef TB_COMPILER_IS_MINGW
#   pragma comment(lib, "Ws2_32.lib")
#endif

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementation
 */
static tb_bool_t tb_ws2_32_instance_init(tb_ws2_32_ref_t ws2_32)
{
    // check
    tb_assert_and_check_return_val(ws2_32, tb_false);

    // the ws2_32 module
    HANDLE module = GetModuleHandleA("ws2_32.dll");
    if (!module) module = (HANDLE)tb_dynamic_init("ws2_32.dll");
    tb_assert_and_check_return_val(module, tb_false);

    // init interfaces
    TB_INTERFACE_LOAD(ws2_32, WSAStartup);
    TB_INTERFACE_LOAD(ws2_32, WSACleanup);
    TB_INTERFACE_LOAD(ws2_32, WSASocketA);
    TB_INTERFACE_LOAD(ws2_32, WSAIoctl);
    TB_INTERFACE_LOAD(ws2_32, WSAGetLastError);
    TB_INTERFACE_LOAD(ws2_32, WSAEnumProtocolsW);
    TB_INTERFACE_LOAD(ws2_32, WSASend);
    TB_INTERFACE_LOAD(ws2_32, WSARecv);
    TB_INTERFACE_LOAD(ws2_32, WSASendTo);
    TB_INTERFACE_LOAD(ws2_32, WSARecvFrom);
    TB_INTERFACE_LOAD(ws2_32, bind);
    TB_INTERFACE_LOAD(ws2_32, send);
    TB_INTERFACE_LOAD(ws2_32, recv);
    TB_INTERFACE_LOAD(ws2_32, sendto);
    TB_INTERFACE_LOAD(ws2_32, recvfrom);
    TB_INTERFACE_LOAD(ws2_32, accept);
    TB_INTERFACE_LOAD(ws2_32, listen);
    TB_INTERFACE_LOAD(ws2_32, select);
    TB_INTERFACE_LOAD(ws2_32, connect);
    TB_INTERFACE_LOAD(ws2_32, shutdown);
    TB_INTERFACE_LOAD(ws2_32, getsockname);
    TB_INTERFACE_LOAD(ws2_32, getsockopt);
    TB_INTERFACE_LOAD(ws2_32, setsockopt);
    TB_INTERFACE_LOAD(ws2_32, ioctlsocket);
    TB_INTERFACE_LOAD(ws2_32, closesocket);
    TB_INTERFACE_LOAD(ws2_32, gethostname);
    TB_INTERFACE_LOAD(ws2_32, getaddrinfo);
    TB_INTERFACE_LOAD(ws2_32, freeaddrinfo);
    TB_INTERFACE_LOAD(ws2_32, getnameinfo);
    TB_INTERFACE_LOAD(ws2_32, gethostbyname);
    TB_INTERFACE_LOAD(ws2_32, gethostbyaddr);
    TB_INTERFACE_LOAD(ws2_32, __WSAFDIsSet);

    // ok
    return tb_true;
}

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */
tb_ws2_32_ref_t tb_ws2_32()
{
    // we will pre-initialize it in tb_platform_init()
    static tb_bool_t      s_binited = tb_false;
    static tb_ws2_32_t    s_ws2_32 = {0};
    if (!s_binited)
        s_binited = tb_ws2_32_instance_init(&s_ws2_32);
    return s_binited? &s_ws2_32 : tb_null;
}
