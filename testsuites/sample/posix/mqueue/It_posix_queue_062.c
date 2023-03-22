/*
 * Copyright (c) 2023 Huawei Device Co., Ltd. All rights reserved.
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
    CHAR qname[MQUEUE_STANDARD_NAME_LENGTH], msgrcd[MQUEUE_STANDARD_NAME_LENGTH];
    const CHAR *msgptr = MQUEUE_SEND_STRING_TEST;
    struct timespec ts;
    mqd_t queue;
    struct mq_attr attr = {0};
    INT32 ret;

    ret = snprintf_s(qname, MQUEUE_STANDARD_NAME_LENGTH, MQUEUE_STANDARD_NAME_LENGTH - 1, \
                     "/mq062-1_%d", LOS_CurTaskIDGet());
    ICUNIT_GOTO_NOT_EQUAL(ret, -1, ret, EXIT1);

    attr.mq_msgsize = MQUEUE_STANDARD_NAME_LENGTH;
    attr.mq_maxmsg = MAXMSG5;
    queue = mq_open(qname, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &attr);
    ICUNIT_GOTO_NOT_EQUAL(queue, (mqd_t)-1, queue, EXIT1);

    ts.tv_sec = 1;
    ts.tv_nsec = 0;
    ret = mq_timedsend(queue, msgptr, strlen(msgptr), 0, &ts);
    ICUNIT_GOTO_EQUAL(ret, 0, ret, EXIT);

    ret = mq_receive(queue, msgrcd, MQUEUE_STANDARD_NAME_LENGTH, NULL);
    ICUNIT_GOTO_NOT_EQUAL(ret, -1, ret, EXIT);

    ret = strncmp(msgptr, msgrcd, strlen(msgptr));
    ICUNIT_GOTO_EQUAL(ret, 0, ret, EXIT);

    ret = mq_close(queue);
    ICUNIT_GOTO_EQUAL(ret, 0, ret, EXIT2);

    ret = mq_unlink(qname);
    ICUNIT_GOTO_EQUAL(ret, 0, ret, EXIT1);

    return LOS_OK;
EXIT:
    mq_close(queue);
EXIT2:
    mq_unlink(qname);
EXIT1:
    return LOS_NOK;
}

/**
 * @tc.name: ItPosixQueue062
 * @tc.desc: Test interface mq_timedsend
 * @tc.type: FUNC
 * @tc.require: issueI69NAI
 */

VOID ItPosixQueue062(VOID)
{
    TEST_ADD_CASE("ItPosixQueue062", Testcase, TEST_POSIX, TEST_QUE, TEST_LEVEL2, TEST_FUNCTION);
}
