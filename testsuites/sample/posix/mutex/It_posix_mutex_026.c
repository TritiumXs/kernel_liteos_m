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

#include "It_posix_mutex.h"

/* pthread_mutex_trylock 3-1.c
 * Test that pthread_mutex_trylock()
 * Upon successful completion, it shall return a 0
 *
 */

static UINT32 Testcase(VOID)
{
    int rc;
    pthread_mutex_t mutex = TEST_MUTEX_INIT;

    /* Initialize a mutex object with the default mutex attributes */
    rc = pthread_mutex_init(&mutex, NULL);
    ICUNIT_ASSERT_EQUAL(rc, 0, rc);

    /* Try to lock the mutex using pthread_mutex_trylock() */
    rc = pthread_mutex_trylock(&mutex);
    ICUNIT_GOTO_EQUAL(rc, 0, rc, EXIT);

    rc = pthread_mutex_unlock(&mutex);
    ICUNIT_ASSERT_EQUAL(rc, 0, rc);

    rc = pthread_mutex_destroy(&mutex);
    ICUNIT_ASSERT_EQUAL(rc, 0, rc);

    return LOS_OK;

EXIT:
    (void)pthread_mutex_destroy(&mutex);

    return LOS_NOK;
}

/**
 * @tc.name: ItPosixMux026
 * @tc.desc: Test interface pthread_mutex_unlock
 * @tc.type: FUNC
 * @tc.require: issueI5WZI6
 */

VOID ItPosixMux026(void)
{
    TEST_ADD_CASE("ItPosixMux026", Testcase, TEST_POSIX, TEST_MUX, TEST_LEVEL2, TEST_FUNCTION);
}
