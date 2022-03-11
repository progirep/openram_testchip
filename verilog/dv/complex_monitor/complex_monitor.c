/*
 * SPDX-FileCopyrightText: 2020 Efabless Corporation
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
 * SPDX-License-Identifier: Apache-2.0
 */

// This include is relative to $CARAVEL_PATH (see Makefile)
#include <defs.h>
#include <stub.c>

/*
	Wishbone Test:
		- Configures MPRJ lower 8-IO pins as outputs
		- Checks counter value through the wishbone port
*/
int i = 0; 
int clk = 0;

const uint32_t data[] = {0,1,2,3};

void failTest() {
    reg_mprj_datal = 0xAB620000;
    // while(1) {} // Block in case the TB has an error.
}

void successTest() {
    reg_mprj_datal = 0xAB610000;
}


uint32_t pseudorandom(uint32_t lastValue) {
    return lastValue ^ (lastValue << 5) ^ (lastValue << 13) ^ (lastValue >> 17);
}

const uint32_t monitoringLookupTables[] = {0x33113210,0x11331032,0x57023120};
const uint32_t monitoringMaskTable[] = {0x3,0x30000000,0x1,0x0,
	0x1,0x30000000,0x0,0x0,
	0,0,0x0,0x70000000};
const uint32_t monitoringControlInfo[] = {0x80108000,0x0000c000};
void resetMonitor() {
	*((volatile uint32_t*)(0x30020008)) = 0x2;
	*((volatile uint32_t*)(0x3002000C)) = 0x0;
}

void initMonitor() {
	// Fill lookup table memory
	for (unsigned int i=0;i<12;i+=4) {
		*((volatile uint32_t*)(0x30010000+i)) = monitoringLookupTables[i>>2];
	}
	// Fill mask table
	for (unsigned int i=0;i<12;i++) {
		*((volatile uint32_t*)(0x30000000+4*i)) = monitoringMaskTable[i];
	}
	// Fill control information part
	for (unsigned int i=0;i<2;i++) {
		*((volatile uint32_t*)(0x30000000+1024-4-4*i)) = monitoringControlInfo[i];
	}
	// Set control register
	*((volatile uint32_t*)(0x30020000)) = 2 /*Nof last block*/ + (0 << 6) /*current block*/;
	// Trigger cycle to fill buffers
	*((volatile uint32_t*)(0x30020004)) = 0;
	resetMonitor();
}

void monitorStep(uint32_t data) {
	*((volatile uint32_t*)(0x30020004)) = data;
}


void testMonitorBasic() {

    initMonitor();
   
monitorStep(0x1c);
if (*((volatile uint32_t*)(0x30020008))!=0x2) failTest();
if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
monitorStep(0x1f);
if (*((volatile uint32_t*)(0x30020008))!=0x1) failTest();
if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
monitorStep(0x5);
if (*((volatile uint32_t*)(0x30020008))!=0x3) failTest();
if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
monitorStep(0x2a);
if (*((volatile uint32_t*)(0x30020008))!=0x3) failTest();
if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
monitorStep(0x9);
if (*((volatile uint32_t*)(0x30020008))!=0x5) failTest();
if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
monitorStep(0x39);
if (*((volatile uint32_t*)(0x30020008))!=0x3) failTest();
if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
monitorStep(0x33);
if (*((volatile uint32_t*)(0x30020008))!=0x3) failTest();
if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
monitorStep(0x34);
if (*((volatile uint32_t*)(0x30020008))!=0x5) failTest();
if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
monitorStep(0x39);
if (*((volatile uint32_t*)(0x30020008))!=0x3) failTest();
if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
monitorStep(0x16);
if (*((volatile uint32_t*)(0x30020008))!=0x3) failTest();
if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();

}


/* Test writing and reading from main control register -- Leave out highest significant bit 
   to avoid activation of the monitoring cycle */
void testMainControlReg() {
    // Write to control register
    *((volatile uint32_t*)(0x30020000)) = 0x2022BEEF;

    // Clear Bus / Overwrite valud in SRAM1 for this.
    *((volatile uint32_t*)(0x30000000)) = 0x12345678;

    // Read back control register
    if (*((volatile uint32_t*)(0x30020000)) != 0x2022BEEF) failTest();
}

/* Test SRAM Component 1 */
void memoryATest() {

    #define NOF_STEPS_MEMORY_A_TEST 3

    // Write
    uint32_t val = 0xBADEAFFE;
    for (unsigned int i=0;i<NOF_STEPS_MEMORY_A_TEST;i++) {
        *((volatile uint32_t*)(0x30000000+4*i)) = val;
        val = pseudorandom(val);
    }

    // Read
    val = 0xBADEAFFE;
    for (unsigned int i=0;i<NOF_STEPS_MEMORY_A_TEST;i++) {
        if (val!=*((volatile uint32_t*)(0x30000000+4*i))) failTest();
        val = pseudorandom(val);
    }
}

/* Test SRAM Component 1 */
void memoryBTest() {

    #define NOF_STEPS_MEMORY_B_TEST 3

    // Write
    uint32_t val = 0xCAFE1337;
    for (unsigned int i=0;i<NOF_STEPS_MEMORY_B_TEST;i++) {
        *((volatile uint32_t*)(0x30010000+4*i)) = val;
        val = pseudorandom(val);
    }

    // Read
    val = 0xCAFE1337;
    for (unsigned int i=0;i<NOF_STEPS_MEMORY_B_TEST;i++) {
        if (val!=*((volatile uint32_t*)(0x30010000+4*i))) failTest();
        val = pseudorandom(val);
    }
}

void main()
{

	/* 
	IO Control Registers
	| DM     | VTRIP | SLOW  | AN_POL | AN_SEL | AN_EN | MOD_SEL | INP_DIS | HOLDH | OEB_N | MGMT_EN |
	| 3-bits | 1-bit | 1-bit | 1-bit  | 1-bit  | 1-bit | 1-bit   | 1-bit   | 1-bit | 1-bit | 1-bit   |
	Output: 0000_0110_0000_1110  (0x1808) = GPIO_MODE_USER_STD_OUTPUT
	| DM     | VTRIP | SLOW  | AN_POL | AN_SEL | AN_EN | MOD_SEL | INP_DIS | HOLDH | OEB_N | MGMT_EN |
	| 110    | 0     | 0     | 0      | 0      | 0     | 0       | 1       | 0     | 0     | 0       |
	
	 
	Input: 0000_0001_0000_1111 (0x0402) = GPIO_MODE_USER_STD_INPUT_NOPULL
	| DM     | VTRIP | SLOW  | AN_POL | AN_SEL | AN_EN | MOD_SEL | INP_DIS | HOLDH | OEB_N | MGMT_EN |
	| 001    | 0     | 0     | 0      | 0      | 0     | 0       | 0       | 0     | 1     | 0       |
	*/

	/* Set up the housekeeping SPI to be connected internally so	*/
	/* that external pin changes don't affect it.			*/

    reg_spi_enable = 1;
    reg_wb_enable = 1;

	// Connect the housekeeping SPI to the SPI master
	// so that the CSB line is not left floating.  This allows
	// all of the GPIO pins to be used for user functions.

    reg_mprj_io_31 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_30 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_29 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_28 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_27 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_26 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_25 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_24 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_23 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_22 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_21 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_20 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_19 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_18 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_17 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_16 = GPIO_MODE_MGMT_STD_OUTPUT;

     /* Apply configuration */
    reg_mprj_xfer = 1;
    while (reg_mprj_xfer == 1);

	reg_la2_oenb = reg_la2_iena = 0xFFFFFFFF;    // [95:64]

    // Flag start of the test
	reg_mprj_datal = 0xAB600000;

    
    // Do the test!
    testMonitorBasic();
    //testMainControlReg();
    //memoryATest();
    //memoryBTest();

    // There we go!
    successTest();


    
    
}
