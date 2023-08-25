/*
 * Copyright (c) 2013-2019 Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020-2021 Huawei Device Co., Ltd. All rights reserved.
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


#include "It_los_queue.h"

static CHAR g_buff[QUEUE_BASE_MSGSIZE] = "UniDSP";

static VOID HwiF01(VOID)
{
	UINT32 ret;    
    CHAR * buff2 = NULL;
    
    ret = LOS_QueueReadIsr(g_testQueueID01, &buff2, QUEUE_BASE_MSGSIZE);
    ICUNIT_ASSERT_EQUAL_VOID(ret, LOS_OK, ret);		
    for (UINT8 index = 0; index < QUEUE_BASE_MSGSIZE - 1; index++) { // 7, QUEUE_BASE_MSGSIZE - 1
        ICUNIT_ASSERT_EQUAL_VOID(*((CHAR *)(intptr_t)buff2 + index), g_buff[index],
            *((CHAR *)(intptr_t)buff2 + index));
    }
}

static UINT32 Testcase(VOID)
{
    UINT32 ret;    
	HWI_PRIOR_T hwiPrio = 3;
    HWI_MODE_T mode = 0;
	HwiIrqParam irqParam;

	ret = LOS_QueueCreate("Q1", QUEUE_BASE_NUM, &g_testQueueID01, 0, QUEUE_BASE_MSGSIZE);
    ICUNIT_GOTO_EQUAL(ret, LOS_OK, ret, EXIT);
	
	(void)memset_s(&irqParam, sizeof(HwiIrqParam), 0, sizeof(HwiIrqParam));
    irqParam.pDevId = 0;
    ret = LOS_HwiCreate(HWI_NUM_TEST, hwiPrio, mode, (HWI_PROC_FUNC)HwiF01, &irqParam);
    ICUNIT_ASSERT_EQUAL(ret, LOS_OK, ret);
	
    ret = LOS_QueueWrite(g_testQueueID01, &g_buff, QUEUE_BASE_MSGSIZE, 0);
    ICUNIT_GOTO_EQUAL(ret, LOS_OK, ret, EXIT);

    TestHwiTrigger(HWI_NUM_TEST);

EXIT:
	TestHwiDelete(HWI_NUM_TEST);
    ret = LOS_QueueDelete(g_testQueueID01);
    ICUNIT_ASSERT_EQUAL(ret, LOS_OK, ret);
    return LOS_OK;
}

VOID ItLosQueueIsr011(VOID)
{
    TEST_ADD_CASE("ItLosQueueIsr011", Testcase, TEST_LOS, TEST_QUE, TEST_LEVEL1, TEST_FUNCTION);
}

