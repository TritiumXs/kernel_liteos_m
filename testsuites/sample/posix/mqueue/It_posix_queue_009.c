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
#include "It_posix_queue.h"

static UINT32 Testcase(VOID)
{
    INT32 ret;
    CHAR mqname[MQUEUE_STANDARD_NAME_LENGTH] = "";
    mqd_t mqueue;
    struct mq_attr attr = {0};
    struct mq_attr attrget;

    ret = snprintf_s(mqname, MQUEUE_STANDARD_NAME_LENGTH, MQUEUE_STANDARD_NAME_LENGTH - 1,
                     "/mq009_%d", LOS_CurTaskIDGet());
    ICUNIT_GOTO_NOT_EQUAL(ret, -1, ret, EXIT2);

    attr.mq_maxmsg = MQUEUE_SHORT_ARRAY_LENGTH;
    attr.mq_msgsize = 5; // 5, queue message size.
    mqueue = mq_open(mqname, O_CREAT | O_RDWR | O_NONBLOCK, S_IRUSR | S_IWUSR, &attr);
    ICUNIT_GOTO_NOT_EQUAL(mqueue, (mqd_t)-1, mqueue, EXIT1);

    ret = mq_getattr(mqueue, &attrget);
    ICUNIT_GOTO_EQUAL(ret, 0, ret, EXIT1);
    ICUNIT_GOTO_EQUAL(attrget.mq_curmsgs, 0, attrget.mq_curmsgs, EXIT1);
    ICUNIT_GOTO_EQUAL(attrget.mq_flags, O_CREAT | O_RDWR | O_NONBLOCK, attrget.mq_flags, EXIT1);
    ICUNIT_GOTO_EQUAL(attrget.mq_maxmsg, attr.mq_maxmsg, attrget.mq_maxmsg, EXIT1);
    ICUNIT_GOTO_EQUAL(attrget.mq_msgsize, attr.mq_msgsize, attrget.mq_msgsize, EXIT1);

    if (!(attrget.mq_flags & O_NONBLOCK)) {
        goto EXIT1;
    }

    ret = mq_close(mqueue);
    ICUNIT_GOTO_EQUAL(ret, 0, ret, EXIT1);

    ret = mq_unlink(mqname);
    ICUNIT_GOTO_EQUAL(ret, 0, ret, EXIT);

    return LOS_OK;
EXIT1:
    mq_close(mqueue);
EXIT:
    mq_unlink(mqname);
EXIT2:
    return LOS_OK;
}

/**
* @tc.name: ItPosixQueue009
* @tc.desc: Test interface mq_getattr
* @tc.type: FUNC
* @tc.require: issueI603SR6
 */

VOID ItPosixQueue009(VOID)
{
    TEST_ADD_CASE("ItPosixQueue009", Testcase, TEST_POSIX, TEST_QUE, TEST_LEVEL2, TEST_FUNCTION);
}