// SPDX-FileCopyrightText: 2020 Efabless Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// SPDX-License-Identifier: Apache-2.0

`default_nettype none
/*
 *-------------------------------------------------------------
 *
 * user_project_wrapper
 *
 * This wrapper enumerates all of the pins available to the
 * user for the user project.
 *
 * An example user project is provided in this wrapper.  The
 * example should be removed and replaced with the actual
 * user project.
 *
 *-------------------------------------------------------------
 */
`define WMASK_SIZE 4
`define ADDR_SIZE 16
`define DATA_SIZE 32
`define SELECT_SIZE 4
`define MAX_CHIPS 2
`define PORT_SIZE `ADDR_SIZE+`DATA_SIZE+`WMASK_SIZE+2
`define TOTAL_SIZE `PORT_SIZE+`PORT_SIZE+`SELECT_SIZE

module user_project_wrapper #(
    parameter BITS = 32
) (
`ifdef USE_POWER_PINS
    inout vdda1,	// User area 1 3.3V supply
    inout vdda2,	// User area 2 3.3V supply
    inout vssa1,	// User area 1 analog ground
    inout vssa2,	// User area 2 analog ground
    inout vccd1,	// User area 1 1.8V supply
    inout vccd2,	// User area 2 1.8v supply
    inout vssd1,	// User area 1 digital ground
    inout vssd2,	// User area 2 digital ground
`endif

    // Wishbone Slave ports (WB MI A)
    input wb_clk_i,
    input wb_rst_i,
    input wbs_stb_i,
    input wbs_cyc_i,
    input wbs_we_i,
    input [3:0] wbs_sel_i,
    input [31:0] wbs_dat_i,
    input [31:0] wbs_adr_i,
    output wbs_ack_o,
    output [31:0] wbs_dat_o,

    // Logic Analyzer Signals
    input  [127:0] la_data_in,
    output [127:0] la_data_out,
    input  [127:0] la_oenb,

    // IOs
    input  [`MPRJ_IO_PADS-1:0] io_in,
    output [`MPRJ_IO_PADS-1:0] io_out,
    output [`MPRJ_IO_PADS-1:0] io_oeb,

    // Analog (direct connection to GPIO pad---use with caution)
    // Note that analog I/O is not available on the 7 lowest-numbered
    // GPIO pads, and so the analog_io indexing is offset from the
    // GPIO indexing by 7 (also upper 2 GPIOs do not have analog_io).
    inout [`MPRJ_IO_PADS-10:0] analog_io,

    // Independent clock (on independent integer divider)
    input   user_clock2,

    // User maskable interrupt signals
    output [2:0] user_irq
);

// Shared control/data to the SRAMs
   wire [7:0] addrA0;
   wire [31:0] dinA0;
   
   wire webA;
   wire [3:0] wmaskA;
   wire [7:0]  addrA1;
   wire csbA0;
   wire csbA1;
   
   
   wire [8:0] addrB0;
   wire [31:0] dinB0;
   
   wire webB;
   wire [3:0] wmaskB;
   wire [8:0]  addrB1;
   wire csbB0;
   wire csbB1;

   wire [`DATA_SIZE-1:0] sram1_dout0;
   wire [`DATA_SIZE-1:0] sram1_dout1;
   wire [`DATA_SIZE-1:0] sram12_dout0;
   wire [`DATA_SIZE-1:0] sram12_dout1;  



user_project prj (
`ifdef USE_POWER_PINS
    //vdda1,	// User area 1 3.3V supply
    //vdda2,	// User area 2 3.3V supply
    //vssa1,	// User area 1 analog ground
    //vssa2,	// User area 2 analog ground
    vccd1,	// User area 1 1.8V supply
    //vccd2,	// User area 2 1.8v supply
    vssd1,	// User area 1 digital ground
    //vssd2,	// User area 2 digital ground
`endif

    // Wishbone Slave ports (WB MI A)
    wb_clk_i,
    wb_rst_i,
    wbs_stb_i,
    wbs_cyc_i,
    wbs_we_i,
    wbs_sel_i,
    wbs_dat_i,
    wbs_adr_i,
    wbs_ack_o,
    wbs_dat_o,

    // Logic Analyzer Signals
    la_data_in,
    la_data_out,
    la_oenb,

    // IOs
    io_in,
    io_out,
    io_oeb,

    // Analog (direct connection to GPIO pad---use with caution)
    // Note that analog I/O is not available on the 7 lowest-numbered
    // GPIO pads, and so the analog_io indexing is offset from the
    // GPIO indexing by 7 (also upper 2 GPIOs do not have analog_io).
    analog_io,

    // Independent clock (on independent integer divider)
    user_clock2,

    // User maskable interrupt signals
    user_irq,

    // Shared control/data to the SRAMs
   addrA0,
   dinA0,
   
   webA,
   wmaskA,
   addrA1,
   csbA0,
   csbA1,
      
   addrB0,
   dinB0,
   
   webB,
   wmaskB,
   addrB1,
   csbB0,
   csbB1,

   sram1_dout0,
   sram1_dout1,
   sram12_dout0,
   sram12_dout1

);


   

sky130_sram_1kbyte_1rw1r_32x256_8 SRAM1
     (
     `ifdef USE_POWER_PINS
      .vccd1(vccd1),
      .vssd1(vssd1),
      `endif
      .clk0   ( wb_clk_i),
      .csb0   (csbA0),
      .web0   (webA),
      .wmask0 (wmaskA),
      .addr0  (addrA0),
      .din0   (dinA0),
      .dout0  (sram1_dout0),
      .clk1   (wb_clk_i),
      .csb1   (csbA1),
      .addr1  (addrA1),
      .dout1  (sram1_dout1)
      );


sky130_sram_2kbyte_1rw1r_32x512_8 SRAM12
    (
      `ifdef USE_POWER_PINS
     .vccd1(vccd1),
     .vssd1(vssd1),
      `endif
     .clk0   ( wb_clk_i),
     .csb0   (csbB0),
     .web0   (webB),
     .wmask0 (wmaskB),
     .addr0  (addrB0),
     .din0   (dinB0),
     .dout0  (sram12_dout0),
     .clk1   (wb_clk_i),
     .csb1   (csbB1),
     .addr1  (addrB1),
     .dout1  (sram12_dout1)
     );

endmodule	// user_project_wrapper

`default_nettype wire