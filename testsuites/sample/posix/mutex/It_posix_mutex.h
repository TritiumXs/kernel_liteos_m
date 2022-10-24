/*
 * Copyright (c) 2022 Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _IT_POSIX_MUTEX_H
#define _IT_POSIX_MUTEX_H

#include "osTest.h"
#include "pthread.h"
#include "errno.h"
#include "sched.h"
#include "semaphore.h"
#include "unistd.h"

#ifdef LOSCFG_DEBUG_DEADLOCK
#define TEST_MUTEX_INIT              \
    {                                \
        { 0, 0, 0, 0 },              \
        {                            \
            { 0, 0 }, { 0, 0 }, 0, 0 \
        }                            \
    }
#else
#define TEST_MUTEX_INIT    \
    {                      \
        { 0, 0, 0, 0 },    \
        {                  \
            { 0, 0 }, 0, 0 \
        }                  \
    }
#endif

UINT32 PosixPthreadDestroy(pthread_attr_t *attr, pthread_t thread);
UINT32 PosixPthreadInit(pthread_attr_t *attr, int pri);
void TestExtraTaskDelay(UINT32 tick);

VOID ItPosixMux001(void);
VOID ItPosixMux002(void);
VOID ItPosixMux003(void);
VOID ItPosixMux004(void);
VOID ItPosixMux005(void);
VOID ItPosixMux006(void);
VOID ItPosixMux007(void);
VOID ItPosixMux008(void);
VOID ItPosixMux009(void);

VOID ItSuitePosixMutex(void);

#endif
