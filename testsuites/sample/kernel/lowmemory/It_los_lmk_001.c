/*
 * Copyright (c) 2021-2021 Huawei Device Co., Ltd. All rights reserved.
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

#include "osTest.h"
#include "It_los_lmk.h"
#include "los_list.h"

#if (LOSCFG_KERNEL_LMK == 1)
static LOS_DL_LIST g_losLmkOps;

static UINT32 release_lmk001(VOID)
{
    return LOS_OK;
}

static VOID restore_lmk001(VOID)
{
    return;
}

static UINT32 TestCase(VOID)
{
    UINT32 ret;
    LosLmkOpsNode *opsNode = NULL;

    LosLmkOpsNode firstOpsNode = {
        .priority = LMK_PRIORITY_LOW,
        .release = NULL,
        .restore = restore_lmk001,
    };

    LosLmkOpsNode anotherOpsNode = {
        .priority = LMK_PRIORITY_MEDIUM,
        .release = release_lmk001,
        .restore = restore_lmk001,
    };

    LosLmkOpsNode thirdOpsNode = {
        .priority = LMK_PRIORITY_HIGH,
        .release = release_lmk001,
        .restore = restore_lmk001,
    };
    
    OsLmkOpsListGet(&g_losLmkOps);
    LOS_ListDelInit(&g_losLmkOps);

    ret = LOS_LmkOpsNodeRegister(&firstOpsNode);
    ICUNIT_ASSERT_EQUAL(ret, LOS_OK, ret);
    opsNode = LOS_DL_LIST_ENTRY(LOS_DL_LIST_FIRST(&g_losLmkOps), LosLmkOpsNode, node);
    ret = opsNode->priority;
    ICUNIT_ASSERT_EQUAL(ret, LMK_PRIORITY_LOW, ret);

    ret = LOS_LmkOpsNodeRegister(NULL);
    ICUNIT_ASSERT_EQUAL(ret, LOS_NOK, ret);

    ret = LOS_LmkOpsNodeRegister(&anotherOpsNode);
    ICUNIT_ASSERT_EQUAL(ret, LOS_OK, ret);
    opsNode = LOS_DL_LIST_ENTRY(LOS_DL_LIST_FIRST(&g_losLmkOps), LosLmkOpsNode, node);
    ret = opsNode->priority;
    ICUNIT_ASSERT_EQUAL(ret, LMK_PRIORITY_MEDIUM, ret);

    ret = LOS_LmkOpsNodeRegister(&thirdOpsNode);
    ICUNIT_ASSERT_EQUAL(ret, LOS_OK, ret);
    opsNode = LOS_DL_LIST_ENTRY(LOS_DL_LIST_FIRST(&g_losLmkOps), LosLmkOpsNode, node);
    ret = opsNode->priority;
    ICUNIT_ASSERT_EQUAL(ret, LMK_PRIORITY_HIGH, ret);

    return LOS_OK;
}

VOID ItLosLmk001(VOID)
{
    TEST_ADD_CASE("ItLosLmk001", TestCase, TEST_LOS, TEST_COMP, TEST_LEVEL0, TEST_FUNCTION);
}
#endif
