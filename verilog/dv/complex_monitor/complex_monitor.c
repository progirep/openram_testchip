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

const uint32_t monitoringLookupTables[] = {0x4a480b09,0x4a480a08,0x4a480b09,0x4a480a08,
	0x42400b09,0x42400a08,0x42400b09,0x42400a08,
	0x6e6c2f2d,0x6e6c2e2c,0x6e6c2f2d,0x6e6c2e2c,
	0x66642f2d,0x66642e2c,0x66642f2d,0x66642e2c,
	0x5b591a18,0x5b591b19,0x5b591a18,0x5b591b19,
	0x53511a18,0x53511b19,0x53511a18,0x53511b19,
	0x7f7d3e3c,0x7f7d3f3d,0x7f7d3e3c,0x7f7d3f3d,
	0x77753e3c,0x77753f3d,0x77753e3c,0x77753f3d,
	0x484a090b,0x484a080a,0x484a090b,0x484a080a,
	0x4042090b,0x4042080a,0x4042090b,0x4042080a,
	0x6c6e2d2f,0x6c6e2c2e,0x6c6e2d2f,0x6c6e2c2e,
	0x64662d2f,0x64662c2e,0x64662d2f,0x64662c2e,
	0x595b181a,0x595b191b,0x595b181a,0x595b191b,
	0x5153181a,0x5153191b,0x5153181a,0x5153191b,
	0x7d7f3c3e,0x7d7f3d3f,0x7d7f3c3e,0x7d7f3d3f,
	0x75773c3e,0x75773d3f,0x75773c3e,0x75773d3f,
	0x4a480b09,0x4a480a08,0x4a480b09,0x4a480a08,
	0x4a480b09,0x4a480a08,0x4a480b09,0x4a480a08,
	0x6e6c2f2d,0x6e6c2e2c,0x6e6c2f2d,0x6e6c2e2c,
	0x6e6c2f2d,0x6e6c2e2c,0x6e6c2f2d,0x6e6c2e2c,
	0x5b591a18,0x5b591b19,0x5b591a18,0x5b591b19,
	0x5b591a18,0x5b591b19,0x5b591a18,0x5b591b19,
	0x7f7d3e3c,0x7f7d3f3d,0x7f7d3e3c,0x7f7d3f3d,
	0x7f7d3e3c,0x7f7d3f3d,0x7f7d3e3c,0x7f7d3f3d,
	0x484a090b,0x484a080a,0x484a090b,0x484a080a,
	0x484a090b,0x484a080a,0x484a090b,0x484a080a,
	0x6c6e2d2f,0x6c6e2c2e,0x6c6e2d2f,0x6c6e2c2e,
	0x6c6e2d2f,0x6c6e2c2e,0x6c6e2d2f,0x6c6e2c2e,
	0x595b181a,0x595b191b,0x595b181a,0x595b191b,
	0x595b181a,0x595b191b,0x595b181a,0x595b191b,
	0x7d7f3c3e,0x7d7f3d3f,0x7d7f3c3e,0x7d7f3d3f,
	0x7d7f3c3e,0x7d7f3d3f,0x7d7f3c3e,0x7d7f3d3f,
	0x10101212,0x08080a0a,0x10101212,0x08080a0a,
	0x12121212,0x0a0a0a0a,0x12121212,0x0a0a0a0a,
	0x11111313,0x09090b0b,0x11111313,0x09090b0b,
	0x13131313,0x0b0b0b0b,0x13131313,0x0b0b0b0b,
	0x50505252,0x48484a4a,0x50505252,0x48484a4a,
	0x52525252,0x4a4a4a4a,0x52525252,0x4a4a4a4a,
	0x51515353,0x49494b4b,0x51515353,0x49494b4b,
	0x53535353,0x4b4b4b4b,0x53535353,0x4b4b4b4b,
	0x34343636,0x2c2c2e2e,0x34343636,0x2c2c2e2e,
	0x36363636,0x2e2e2e2e,0x36363636,0x2e2e2e2e,
	0x35353737,0x2d2d2f2f,0x35353737,0x2d2d2f2f,
	0x37373737,0x2f2f2f2f,0x37373737,0x2f2f2f2f,
	0x74747676,0x6c6c6e6e,0x74747676,0x6c6c6e6e,
	0x76767676,0x6e6e6e6e,0x76767676,0x6e6e6e6e,
	0x75757777,0x6d6d6f6f,0x75757777,0x6d6d6f6f,
	0x77777777,0x6f6f6f6f,0x77777777,0x6f6f6f6f,
	0x03000300,0x02011211,0x03000300,0x02011211,
	0x0a090a09,0x0a091a19,0x0a090a09,0x0a091a19,
	0x07040704,0x06051615,0x07040704,0x06051615,
	0x0e0d0e0d,0x0e0d1e1d,0x0e0d0e0d,0x0e0d1e1d,
	0x02010201,0x03001310,0x02010201,0x03001310,
	0x0b080b08,0x0b081b18,0x0b080b08,0x0b081b18,
	0x06050605,0x07041714,0x06050605,0x07041714,
	0x0f0c0f0c,0x0f0c1f1c,0x0f0c0f0c,0x0f0c1f1c,
	0x07040704,0x06051615,0x07040704,0x06051615,
	0x0e0d0e0d,0x0e0d1e1d,0x0e0d0e0d,0x0e0d1e1d,
	0x03000300,0x02011211,0x03000300,0x02011211,
	0x0a090a09,0x0a091a19,0x0a090a09,0x0a091a19,
	0x06050605,0x07041714,0x06050605,0x07041714,
	0x0f0c0f0c,0x0f0c1f1c,0x0f0c0f0c,0x0f0c1f1c,
	0x02010201,0x03001310,0x02010201,0x03001310,
	0x0b080b08,0x0b081b18,0x0b080b08,0x0b081b18,
	0x06050605,0x07041714,0x06050605,0x07041714,
	0x0f0c0f0c,0x0f0c1f1c,0x0f0c0f0c,0x0f0c1f1c,
	0x02010201,0x03001310,0x02010201,0x03001310,
	0x0b080b08,0x0b081b18,0x0b080b08,0x0b081b18,
	0x07040704,0x06051615,0x07040704,0x06051615,
	0x0e0d0e0d,0x0e0d1e1d,0x0e0d0e0d,0x0e0d1e1d,
	0x03000300,0x02011211,0x03000300,0x02011211,
	0x0a090a09,0x0a091a19,0x0a090a09,0x0a091a19,
	0x02010201,0x03001310,0x02010201,0x03001310,
	0x0b080b08,0x0b081b18,0x0b080b08,0x0b081b18,
	0x06050605,0x07041714,0x06050605,0x07041714,
	0x0f0c0f0c,0x0f0c1f1c,0x0f0c0f0c,0x0f0c1f1c,
	0x03000300,0x02011211,0x03000300,0x02011211,
	0x0a090a09,0x0a091a19,0x0a090a09,0x0a091a19,
	0x07040704,0x06051615,0x07040704,0x06051615,
	0x0e0d0e0d,0x0e0d1e1d,0x0e0d0e0d,0x0e0d1e1d,
	0x22220000,0x22220000,0x22222200,0x22222200,
	0x22220000,0x22220000,0x22222200,0x22222200,
	0x22220000,0x22220000,0x22222200,0x22222200,
	0x22220000,0x22220000,0x22222200,0x22222200,
	0x22220000,0x22220000,0x22222200,0x22222200,
	0x22220000,0x22220000,0x22222200,0x22222200,
	0x22220000,0x22220000,0x22222200,0x22222200,
	0x22220000,0x22220000,0x22222200,0x22222200,
	0x33331111,0x33331111,0x33333311,0x33333311,
	0x33331111,0x33331111,0x33333311,0x33333311,
	0x33331111,0x33331111,0x33333311,0x33333311,
	0x33331111,0x33331111,0x33333311,0x33333311,
	0x33331111,0x33331111,0x33333311,0x33333311,
	0x33331111,0x33331111,0x33333311,0x33333311,
	0x33331111,0x33331111,0x33333311,0x33333311,
	0x33331111,0x33331111,0x33333311,0x33333311,
	0x57555755,0x46444644,0x75557555,0x64446444,
	0x57555755,0x46444644,0x75553111,0x64442000,
	0x57555755,0x46444644,0x75557555,0x64446444,
	0x57555755,0x46444644,0x31117555,0x20006444,
	0x46444644,0x46444644,0x64446444,0x64446444,
	0x46444644,0x46444644,0x64442000,0x64442000,
	0x46444644,0x46444644,0x64446444,0x64446444,
	0x46444644,0x46444644,0x20006444,0x20006444,
	0x46444644,0x57555755,0x64446444,0x75557555,
	0x46444644,0x57555755,0x20006444,0x31117555,
	0x46444644,0x57555755,0x64446444,0x75557555,
	0x46444644,0x57555755,0x64442000,0x75553111,
	0x46444644,0x46444644,0x64446444,0x64446444,
	0x46444644,0x46444644,0x20006444,0x20006444,
	0x46444644,0x46444644,0x64446444,0x64446444,
	0x46444644,0x46444644,0x64442000,0x64442000,
	0x11111111,0x11111111,0x33333333,0x33333333,
	0x11111111,0x11111111,0x33333333,0x33333333,
	0x00000000,0x11111111,0x22222222,0x33333333,
	0x00000000,0x11111111,0x22222222,0x33333333,
	0x33333333,0x33333333,0x11111111,0x11111111,
	0x33333333,0x33333333,0x11111111,0x11111111,
	0x22222222,0x33333333,0x00000000,0x11111111,
	0x22222222,0x33333333,0x00000000,0x11111111,
	0x11111111,0x11111111,0x11111111,0x11111111,
	0x11111111,0x11111111,0x11111111,0x11111111,
	0x00000000,0x11111111,0x00000000,0x11111111,
	0x00000000,0x11111111,0x00000000,0x11111111,
	0x33333333,0x33333333,0x33333333,0x33333333,
	0x33333333,0x33333333,0x33333333,0x33333333,
	0x22222222,0x33333333,0x22222222,0x33333333,
	0x22222222,0x33333333,0x22222222,0x33333333
	};
const uint32_t monitoringMaskTable[] = {0x28d,0x17000000,0x2e7,0xe7000000,
	0x993,0x1a000000,0x1efd,0x6f000000,
	0x67c,0x20000000,0x1f9ef,0x10000000,
	0xdc,0x1d000000,0x7fe3,0x6e000000,
	0x19dc,0x2000000,0x1ee63,0x1d000000,
	0x9cf,0x10000000,0x7630,0x60000000,
	0,0,0x1ff,0x30000000};
// Starting addresses (in bytes) of the lookup tables: [0, 1280, 512, 768, 1536, 1792]
const uint32_t monitoringControlInfo[] = {0x8a004000,0x43004200,0x8e008c00,0x0000c000
	};
void resetMonitor() {
	*((volatile uint32_t*)(0x30020008)) = 0x49a;
	*((volatile uint32_t*)(0x3002000C)) = 0x0;
}

void initMonitor() {
	// Fill lookup table memory
	for (unsigned int i=0;i<2048;i+=4) {
		*((volatile uint32_t*)(0x30010000+i)) = monitoringLookupTables[i>>2];
	}
	// Fill mask table
	for (unsigned int i=0;i<28;i++) {
		*((volatile uint32_t*)(0x30000000+4*i)) = monitoringMaskTable[i];
	}
	// Fill control information part
	for (unsigned int i=0;i<4;i++) {
		*((volatile uint32_t*)(0x30000000+1024-4-4*i)) = monitoringControlInfo[i];
	}
	// Set control register
	*((volatile uint32_t*)(0x30020000)) = 6 /*Nof last block*/ + (0 << 6) /*current block*/ + (1<<18) /* Nof Nibbles of propositions minus 1 */;
	// Trigger cycle to fill buffers
	*((volatile uint32_t*)(0x30020004)) = 0;
	resetMonitor();
}

void monitorStep(uint32_t data) {
	*((volatile uint32_t*)(0x30020004)) = data;
}

void testMonitorBasic() {

    initMonitor();
   
    monitorStep(0x1a);
    if (*((volatile uint32_t*)(0x30020008))!=0x539) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x2f);
    if (*((volatile uint32_t*)(0x30020008))!=0x328) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x47);
    if (*((volatile uint32_t*)(0x30020008))!=0x7e0) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x56);
    if (*((volatile uint32_t*)(0x30020008))!=0x6a5) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x11);
    if (*((volatile uint32_t*)(0x30020008))!=0x353) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x6d);
    if (*((volatile uint32_t*)(0x30020008))!=0x78c) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x5a);
    if (*((volatile uint32_t*)(0x30020008))!=0x7fb) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x65);
    if (*((volatile uint32_t*)(0x30020008))!=0x184) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x2c);
    if (*((volatile uint32_t*)(0x30020008))!=0x50a) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x4a);
    if (*((volatile uint32_t*)(0x30020008))!=0x3b8) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x4d);
    if (*((volatile uint32_t*)(0x30020008))!=0x3c8) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x21);
    if (*((volatile uint32_t*)(0x30020008))!=0x114) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x4d);
    if (*((volatile uint32_t*)(0x30020008))!=0x78a) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x30);
    if (*((volatile uint32_t*)(0x30020008))!=0x555) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x2c);
    if (*((volatile uint32_t*)(0x30020008))!=0x70e) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x2);
    if (*((volatile uint32_t*)(0x30020008))!=0x372) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x1a);
    if (*((volatile uint32_t*)(0x30020008))!=0x23d) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x47);
    if (*((volatile uint32_t*)(0x30020008))!=0x7e2) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x45);
    if (*((volatile uint32_t*)(0x30020008))!=0x784) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x6d);
    if (*((volatile uint32_t*)(0x30020008))!=0x3ca) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x26);
    if (*((volatile uint32_t*)(0x30020008))!=0x124) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x3e);
    if (*((volatile uint32_t*)(0x30020008))!=0x32b) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x28);
    if (*((volatile uint32_t*)(0x30020008))!=0x75c) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x4a);
    if (*((volatile uint32_t*)(0x30020008))!=0x7be) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x1b);
    if (*((volatile uint32_t*)(0x30020008))!=0x7b) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x29);
    if (*((volatile uint32_t*)(0x30020008))!=0x71c) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x25);
    if (*((volatile uint32_t*)(0x30020008))!=0x742) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x6b);
    if (*((volatile uint32_t*)(0x30020008))!=0x3bc) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x5d);
    if (*((volatile uint32_t*)(0x30020008))!=0x3cb) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x31);
    if (*((volatile uint32_t*)(0x30020008))!=0x715) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x29);
    if (*((volatile uint32_t*)(0x30020008))!=0x75a) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x17);
    if (*((volatile uint32_t*)(0x30020008))!=0x725) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x51);
    if (*((volatile uint32_t*)(0x30020008))!=0x7d3) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x41);
    if (*((volatile uint32_t*)(0x30020008))!=0x194) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x3c);
    if (*((volatile uint32_t*)(0x30020008))!=0x50b) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x1c);
    if (*((volatile uint32_t*)(0x30020008))!=0x609) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x7f);
    if (*((volatile uint32_t*)(0x30020008))!=0x6e9) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x70);
    if (*((volatile uint32_t*)(0x30020008))!=0x95) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x18);
    if (*((volatile uint32_t*)(0x30020008))!=0x21b) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x5c);
    if (*((volatile uint32_t*)(0x30020008))!=0x2c9) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x54);
    if (*((volatile uint32_t*)(0x30020008))!=0x85) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x69);
    if (*((volatile uint32_t*)(0x30020008))!=0x59a) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x71);
    if (*((volatile uint32_t*)(0x30020008))!=0x395) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x37);
    if (*((volatile uint32_t*)(0x30020008))!=0x263) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x39);
    if (*((volatile uint32_t*)(0x30020008))!=0x61d) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x5a);
    if (*((volatile uint32_t*)(0x30020008))!=0x3fb) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x2f);
    if (*((volatile uint32_t*)(0x30020008))!=0x72c) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x37);
    if (*((volatile uint32_t*)(0x30020008))!=0x363) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x29);
    if (*((volatile uint32_t*)(0x30020008))!=0x31c) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x2f);
    if (*((volatile uint32_t*)(0x30020008))!=0x76a) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x74);
    if (*((volatile uint32_t*)(0x30020008))!=0x685) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x46);
    if (*((volatile uint32_t*)(0x30020008))!=0x5e2) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x4f);
    if (*((volatile uint32_t*)(0x30020008))!=0x7ac) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x29);
    if (*((volatile uint32_t*)(0x30020008))!=0x55a) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x6);
    if (*((volatile uint32_t*)(0x30020008))!=0x724) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x2e);
    if (*((volatile uint32_t*)(0x30020008))!=0x36a) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x68);
    if (*((volatile uint32_t*)(0x30020008))!=0x39c) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x53);
    if (*((volatile uint32_t*)(0x30020008))!=0x7f3) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x14);
    if (*((volatile uint32_t*)(0x30020008))!=0x705) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0xb);
    if (*((volatile uint32_t*)(0x30020008))!=0x37a) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x77);
    if (*((volatile uint32_t*)(0x30020008))!=0x7a5) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x58);
    if (*((volatile uint32_t*)(0x30020008))!=0x1db) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x51);
    if (*((volatile uint32_t*)(0x30020008))!=0x495) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x40);
    if (*((volatile uint32_t*)(0x30020008))!=0x192) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x29);
    if (*((volatile uint32_t*)(0x30020008))!=0x11c) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x38);
    if (*((volatile uint32_t*)(0x30020008))!=0x31b) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x40);
    if (*((volatile uint32_t*)(0x30020008))!=0x3d0) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x57);
    if (*((volatile uint32_t*)(0x30020008))!=0x3a5) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x6a);
    if (*((volatile uint32_t*)(0x30020008))!=0x5fa) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x3c);
    if (*((volatile uint32_t*)(0x30020008))!=0x40d) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x34);
    if (*((volatile uint32_t*)(0x30020008))!=0x303) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x7f);
    if (*((volatile uint32_t*)(0x30020008))!=0x2ed) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x43);
    if (*((volatile uint32_t*)(0x30020008))!=0x5b6) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x32);
    if (*((volatile uint32_t*)(0x30020008))!=0x137) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x15);
    if (*((volatile uint32_t*)(0x30020008))!=0x303) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x55);
    if (*((volatile uint32_t*)(0x30020008))!=0x2c1) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x52);
    if (*((volatile uint32_t*)(0x30020008))!=0x1b5) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x1a);
    if (*((volatile uint32_t*)(0x30020008))!=0x23b) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x3f);
    if (*((volatile uint32_t*)(0x30020008))!=0x76d) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x2d);
    if (*((volatile uint32_t*)(0x30020008))!=0x30e) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x3b);
    if (*((volatile uint32_t*)(0x30020008))!=0x27f) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x1);
    if (*((volatile uint32_t*)(0x30020008))!=0x316) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x24);
    if (*((volatile uint32_t*)(0x30020008))!=0x346) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x4d);
    if (*((volatile uint32_t*)(0x30020008))!=0x78e) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x26);
    if (*((volatile uint32_t*)(0x30020008))!=0x566) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x75);
    if (*((volatile uint32_t*)(0x30020008))!=0x287) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x40);
    if (*((volatile uint32_t*)(0x30020008))!=0x5d2) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x33);
    if (*((volatile uint32_t*)(0x30020008))!=0x435) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x60);
    if (*((volatile uint32_t*)(0x30020008))!=0x792) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0xe);
    if (*((volatile uint32_t*)(0x30020008))!=0x568) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x29);
    if (*((volatile uint32_t*)(0x30020008))!=0x31c) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x8);
    if (*((volatile uint32_t*)(0x30020008))!=0x35a) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x65);
    if (*((volatile uint32_t*)(0x30020008))!=0x384) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x24);
    if (*((volatile uint32_t*)(0x30020008))!=0x142) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x30);
    if (*((volatile uint32_t*)(0x30020008))!=0x715) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x66);
    if (*((volatile uint32_t*)(0x30020008))!=0x7e2) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x63);
    if (*((volatile uint32_t*)(0x30020008))!=0x7b4) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x55);
    if (*((volatile uint32_t*)(0x30020008))!=0x3c3) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x2a);
    if (*((volatile uint32_t*)(0x30020008))!=0x73c) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x13);
    if (*((volatile uint32_t*)(0x30020008))!=0x673) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x53);
    if (*((volatile uint32_t*)(0x30020008))!=0x2b5) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x43);
    if (*((volatile uint32_t*)(0x30020008))!=0x1f2) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x5b);
    if (*((volatile uint32_t*)(0x30020008))!=0x6bd) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x16);
    if (*((volatile uint32_t*)(0x30020008))!=0x363) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x7);
    if (*((volatile uint32_t*)(0x30020008))!=0x324) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x25);
    if (*((volatile uint32_t*)(0x30020008))!=0x342) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x9);
    if (*((volatile uint32_t*)(0x30020008))!=0x71c) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x18);
    if (*((volatile uint32_t*)(0x30020008))!=0x35b) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0xd);
    if (*((volatile uint32_t*)(0x30020008))!=0x70c) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x57);
    if (*((volatile uint32_t*)(0x30020008))!=0x3e3) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x2a);
    if (*((volatile uint32_t*)(0x30020008))!=0x73c) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x5e);
    if (*((volatile uint32_t*)(0x30020008))!=0x7eb) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x72);
    if (*((volatile uint32_t*)(0x30020008))!=0x1b5) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x42);
    if (*((volatile uint32_t*)(0x30020008))!=0x1b2) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x41);
    if (*((volatile uint32_t*)(0x30020008))!=0x790) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x2d);
    if (*((volatile uint32_t*)(0x30020008))!=0x148) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x4);
    if (*((volatile uint32_t*)(0x30020008))!=0x304) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x61);
    if (*((volatile uint32_t*)(0x30020008))!=0x7d2) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x38);
    if (*((volatile uint32_t*)(0x30020008))!=0x51d) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x6c);
    if (*((volatile uint32_t*)(0x30020008))!=0x38a) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x79);
    if (*((volatile uint32_t*)(0x30020008))!=0x7dd) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x1e);
    if (*((volatile uint32_t*)(0x30020008))!=0x32f) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x34);
    if (*((volatile uint32_t*)(0x30020008))!=0x747) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x46);
    if (*((volatile uint32_t*)(0x30020008))!=0x7a6) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x50);
    if (*((volatile uint32_t*)(0x30020008))!=0x3d3) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x0);
    if (*((volatile uint32_t*)(0x30020008))!=0x314) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x49);
    if (*((volatile uint32_t*)(0x30020008))!=0x3da) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x39);
    if (*((volatile uint32_t*)(0x30020008))!=0x51d) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x4);
    if (*((volatile uint32_t*)(0x30020008))!=0x702) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x14);
    if (*((volatile uint32_t*)(0x30020008))!=0x241) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x31);
    if (*((volatile uint32_t*)(0x30020008))!=0x315) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x4d);
    if (*((volatile uint32_t*)(0x30020008))!=0x3ca) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x4);
    if (*((volatile uint32_t*)(0x30020008))!=0x104) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x21);
    if (*((volatile uint32_t*)(0x30020008))!=0x312) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x77);
    if (*((volatile uint32_t*)(0x30020008))!=0x2e5) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x52);
    if (*((volatile uint32_t*)(0x30020008))!=0x5b7) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x75);
    if (*((volatile uint32_t*)(0x30020008))!=0x487) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x3a);
    if (*((volatile uint32_t*)(0x30020008))!=0x63f) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x36);
    if (*((volatile uint32_t*)(0x30020008))!=0x767) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x25);
    if (*((volatile uint32_t*)(0x30020008))!=0x306) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x2e);
    if (*((volatile uint32_t*)(0x30020008))!=0x36e) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x15);
    if (*((volatile uint32_t*)(0x30020008))!=0x307) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x8);
    if (*((volatile uint32_t*)(0x30020008))!=0x35a) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x40);
    if (*((volatile uint32_t*)(0x30020008))!=0x794) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x1e);
    if (*((volatile uint32_t*)(0x30020008))!=0x56b) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x55);
    if (*((volatile uint32_t*)(0x30020008))!=0x785) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0xd);
    if (*((volatile uint32_t*)(0x30020008))!=0x74a) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x25);
    if (*((volatile uint32_t*)(0x30020008))!=0x704) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x3d);
    if (*((volatile uint32_t*)(0x30020008))!=0x74b) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x4c);
    if (*((volatile uint32_t*)(0x30020008))!=0x78c) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x3b);
    if (*((volatile uint32_t*)(0x30020008))!=0x7b) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x70);
    if (*((volatile uint32_t*)(0x30020008))!=0x295) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x7);
    if (*((volatile uint32_t*)(0x30020008))!=0x762) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x12);
    if (*((volatile uint32_t*)(0x30020008))!=0x235) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x5a);
    if (*((volatile uint32_t*)(0x30020008))!=0x7fb) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x26);
    if (*((volatile uint32_t*)(0x30020008))!=0x724) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x19);
    if (*((volatile uint32_t*)(0x30020008))!=0x75b) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x15);
    if (*((volatile uint32_t*)(0x30020008))!=0x605) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x31);
    if (*((volatile uint32_t*)(0x30020008))!=0x753) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x6a);
    if (*((volatile uint32_t*)(0x30020008))!=0x7bc) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x3e);
    if (*((volatile uint32_t*)(0x30020008))!=0x56b) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0xe);
    if (*((volatile uint32_t*)(0x30020008))!=0x32c) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x37);
    if (*((volatile uint32_t*)(0x30020008))!=0x363) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x66);
    if (*((volatile uint32_t*)(0x30020008))!=0x7a4) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x24);
    if (*((volatile uint32_t*)(0x30020008))!=0x542) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x12);
    if (*((volatile uint32_t*)(0x30020008))!=0x735) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x3b);
    if (*((volatile uint32_t*)(0x30020008))!=0x37b) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x3b);
    if (*((volatile uint32_t*)(0x30020008))!=0x73d) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x28);
    if (*((volatile uint32_t*)(0x30020008))!=0x35a) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x53);
    if (*((volatile uint32_t*)(0x30020008))!=0x7b5) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x52);
    if (*((volatile uint32_t*)(0x30020008))!=0x1f3) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x5e);
    if (*((volatile uint32_t*)(0x30020008))!=0x4ad) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x33);
    if (*((volatile uint32_t*)(0x30020008))!=0x733) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x18);
    if (*((volatile uint32_t*)(0x30020008))!=0x759) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x5f);
    if (*((volatile uint32_t*)(0x30020008))!=0x7ad) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x6d);
    if (*((volatile uint32_t*)(0x30020008))!=0x5ca) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x5c);
    if (*((volatile uint32_t*)(0x30020008))!=0x68d) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x0);
    if (*((volatile uint32_t*)(0x30020008))!=0x752) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x61);
    if (*((volatile uint32_t*)(0x30020008))!=0x394) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x6c);
    if (*((volatile uint32_t*)(0x30020008))!=0x3ca) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x6d);
    if (*((volatile uint32_t*)(0x30020008))!=0x78c) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x3a);
    if (*((volatile uint32_t*)(0x30020008))!=0x17b) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x52);
    if (*((volatile uint32_t*)(0x30020008))!=0x2b5) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x5a);
    if (*((volatile uint32_t*)(0x30020008))!=0x1fb) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x3);
    if (*((volatile uint32_t*)(0x30020008))!=0x734) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x33);
    if (*((volatile uint32_t*)(0x30020008))!=0x373) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x7c);
    if (*((volatile uint32_t*)(0x30020008))!=0x68d) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x0);
    if (*((volatile uint32_t*)(0x30020008))!=0x752) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x39);
    if (*((volatile uint32_t*)(0x30020008))!=0x31d) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x34);
    if (*((volatile uint32_t*)(0x30020008))!=0x743) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x51);
    if (*((volatile uint32_t*)(0x30020008))!=0x695) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x7d);
    if (*((volatile uint32_t*)(0x30020008))!=0x1cb) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x57);
    if (*((volatile uint32_t*)(0x30020008))!=0x1a5) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x30);
    if (*((volatile uint32_t*)(0x30020008))!=0x213) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x45);
    if (*((volatile uint32_t*)(0x30020008))!=0x3c0) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x47);
    if (*((volatile uint32_t*)(0x30020008))!=0x3a4) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x5f);
    if (*((volatile uint32_t*)(0x30020008))!=0x2eb) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x41);
    if (*((volatile uint32_t*)(0x30020008))!=0x594) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x33);
    if (*((volatile uint32_t*)(0x30020008))!=0x33) failTest();
    if (((*((volatile uint32_t*)(0x3002000C))) & 0xfffffff)!=0x0) failTest();
    monitorStep(0x5a);
    if (*((volatile uint32_t*)(0x30020008))!=0x6b9) failTest();
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
