// SPDX-FileCopyrightText: 2022 Ruediger Ehlers
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
 * monitor
 *
 * This is an example of a (trivially simple) user project,
 * showing how the user project can connect to the logic
 * analyzer, the wishbone bus, and the I/O pads.
 *
 * This project generates an integer count, which is output
 * on the user area GPIO pads (digital output only).  The
 * wishbone connection allows the project to be controlled
 * (start and stop) from the management SoC program.
 *
 * See the testbenches in directory "mprj_counter" for the
 * example programs that drive this user project.  The three
 * testbenches are "io_ports", "la_test1", and "la_test2".
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


module monitor (
`ifdef USE_POWER_PINS
    inout vccd1,	// User area 1 1.8V supply
    inout vssd1,	// User area 1 digital ground
`endif

input         resetn,
			input         clk,
			//input         la_in_load,
			//input         la_sram_load,
			//input  [`TOTAL_SIZE-1:0] la_data_in,
			// GPIO bit to clock control register
			//input         gpio_in,
			//input         gpio_scan,
			//input         gpio_sram_load,
			//input         global_csb,

         // I/O for SRAMs A and B		
         output reg [7:0] addrA0,
         output reg [31:0] dinA0,
         input [31:0] doutA0,
         output reg webA,
         output reg [3:0] wmaskA,
         output reg [7:0]  addrA1,
         output reg csbA0,
         output reg csbA1,
         input [31:0] doutA1,
         
         output reg [8:0] addrB0,
         output reg [31:0] dinB0,
         input [31:0] doutB0,
         output reg webB,
         output reg [3:0] wmaskB,
         output reg [8:0]  addrB1,
         output reg csbB0,
         output reg csbB1,
         input [31:0] doutB1,
               
			//output reg [`TOTAL_SIZE-1:0] la_data_out,
			//output reg gpio_out,

         // Wishbone access
         input wb_clk_i,
         input wb_rst_i,
         input wbs_stb_i,
         input wbs_cyc_i,
         input wbs_we_i,
         input [3:0] wbs_sel_i,
         input [31:0] wbs_dat_i,
         input [31:0] wbs_adr_i,
         output reg wbs_ack_o,
         output reg [31:0] wbs_dat_o

);

// Main control register
reg [31:0] mainControlReg;

wire mainControlRegMonitorProcessingActive;
assign mainControlRegMonitorProcessingActive = mainControlReg[31];

wire [5:0] mainControlRegMaxBlockNum;
assign mainControlRegMaxBlockNum = mainControlReg[5:0];
wire [5:0] mainControlRegCurrentBlock;
assign mainControlRegCurrentBlock = mainControlReg[11:6];
wire [2:0] currentMonitorCycle;
assign currentMonitorCycle = mainControlReg[14:12];
wire [2:0] mainControlNofStateNibblesForAPs;
assign mainControlNofStateNibblesForAPs = mainControlReg[20:18];


// Registers for monitoring
reg [63:0] stateReg;
reg [63:0] nextBitSelectionReg;
reg [15:0] nextMonitoringOpReg;
reg [63:0] bitFilterReg;


// BExp
wire inReadySigBitextractor;
wire outValidSigBitextractor;
reg inValidSigBitextractor;
wire[63:0] outputBitExtractor;
reg[63:0] bitExtractorDataIn;
reg[63:0] bitExtractorMaskIn;


bextdep64p2 bitExtractor(
   .clock(wb_clk_i),
	.reset(wb_rst_i),
	.din_valid(inValidSigBitextractor),
	.din_ready(inReadySigBitextractor),
	.din_mode({1'b0,1'b0}),
	.din_value(bitExtractorDataIn),
	.din_mask(bitExtractorMaskIn),
	.dout_valid(outValidSigBitextractor),
	.dout_ready({1'b1}),
	.dout_result(outputBitExtractor)
);

// Address computation
wire [13:0] targetAddressTableLookup;
assign targetAddressTableLookup = outputBitExtractor[13:0] + nextMonitoringOpReg[13:0];
reg[2:0] storedLeastSignificantBitsTargetAddressTableLookup;


// Access for SRAM
reg [31:0] ramAccessDelayRegister;
reg [31:0] accessFunction;

always @(posedge clk) begin
   if (wb_rst_i) begin
      ramAccessDelayRegister <= 0;
      csbA0 <= 1;
      csbA1 <= 1;
      csbB0 <= 1;
      csbB1 <= 1;
      mainControlReg <= 0;
      wbs_ack_o <= 0;
      accessFunction <= 0;
      inValidSigBitextractor <= 0;
      nextBitSelectionReg <= 0;
      nextMonitoringOpReg <= 0;
      bitFilterReg <= 0;
      $display("Reset WBS!");
   end else begin
      // Waiting...
      if (wbs_ack_o && ~wbs_stb_i) begin
         // Undo ack after master confirms ack
         wbs_ack_o <= 0;
      end else if (mainControlRegMonitorProcessingActive) begin
         /* Here, the monitoring takes place
            Cycles:
              Case Lookup:
              7 - Pass state information to bit Extractor with mask nextBitSelectionReg
                - Trigger read access of part 0 of nextBitSelectionReg
              6 - Wait for state information from the bit extractor
                - Trigger read access of part 1 of nextBitSelectionReg
              5 - 
              4 - Store part 0 of nextBitSelectionReg
                - Forward extracted information to SRAM12
              3 - Store part 1 of nextBitSelectionReg
                - Trigger read access of part 1 of nextBitSelectionReg
              0 - Store nextMonitoringOpReg
                - update current Block Number
                - Stop This mode when 
         */
         if (currentMonitorCycle==7) begin
            addrA1 <= mainControlRegCurrentBlock*4;
            csbA1 <= 0;
            inValidSigBitextractor <= 1;
            bitExtractorDataIn <= stateReg;
            bitExtractorMaskIn <= nextBitSelectionReg;
            $display("BitExtractor 1 data: %h %h",stateReg,nextBitSelectionReg);
         end else if (currentMonitorCycle==6) begin
            addrA1 <= mainControlRegCurrentBlock*4+1;
            inValidSigBitextractor <= 0;
         end else if (currentMonitorCycle==5) begin
            addrA1 <= mainControlRegCurrentBlock*4+2;
           

         end else if (currentMonitorCycle==4) begin
            // Here, read-ack works
            addrA1 <= mainControlRegCurrentBlock*4+3;
            nextBitSelectionReg[31:0] <= doutA1;

            if (nextMonitoringOpReg[15:14]==0) begin
               // 16 Bit
               addrB1 <= targetAddressTableLookup[11:1];
            end else if (nextMonitoringOpReg[15:14]==1) begin
               // 8 bit
               addrB1 <= targetAddressTableLookup[12:2];
            end else begin
               // 4 bit
               addrB1 <= targetAddressTableLookup[13:3];
            end
            storedLeastSignificantBitsTargetAddressTableLookup <= targetAddressTableLookup[2:0];

            // Delay the actual access to SRAM12 by one

             
            bitExtractorDataIn <= stateReg; // TODO: Can this be made constant?
            bitExtractorMaskIn <= bitFilterReg;
            inValidSigBitextractor <= 1;

            $display("Cycle 4 - Output Bit Extractor: %h",outputBitExtractor);
            $display("Cycle 4 - Input Bit Extractor: %h %h", outputBitExtractor, bitFilterReg);
            $display("Cycle 4 - TAL: %h %h %b",outputBitExtractor,nextMonitoringOpReg,targetAddressTableLookup[2:0]);

         end else if (currentMonitorCycle==3) begin
            
            // Here, read-ack works
            nextBitSelectionReg[63:32] <= doutA1; 
            addrA1 <= ~mainControlRegCurrentBlock[5:1];
            csbB1 <= 0;
            inValidSigBitextractor <= 0;
            
         end else if (currentMonitorCycle==2) begin
            csbA1 <= 1;
            csbB1 <= 1;
            bitFilterReg[31:0] <= doutA1;

         end else if (currentMonitorCycle==1) begin
            bitFilterReg[63:32] <= doutA1;
            stateReg <= outputBitExtractor;
            $display("Cycle 1 - Output Bit Extractor and StoredLSB: %h %b",outputBitExtractor,storedLeastSignificantBitsTargetAddressTableLookup);

         end else if (currentMonitorCycle==0) begin

            // Read 16 bit of the nextMonitoringOpReg
            if (mainControlRegCurrentBlock[0]) begin
               nextMonitoringOpReg <= doutA1[31:16];
            end else begin
               nextMonitoringOpReg <= doutA1[15:0];
            end

            // Overwrite state part according to how many bits are used
            if (nextMonitoringOpReg[15:14]==0) begin
               // 16 Bit
               if (storedLeastSignificantBitsTargetAddressTableLookup[0]) begin
                  stateReg[63:48] <= doutB1[31:16];
               end else begin
                  stateReg[63:48] <= doutB1[15:0];
               end
            end else if (nextMonitoringOpReg[15:14]==1) begin
               // 8 bit
               if ((storedLeastSignificantBitsTargetAddressTableLookup[1:0])==2'b11) begin
                  stateReg[63:56] <= doutB1[31:24];
               end else if ((storedLeastSignificantBitsTargetAddressTableLookup[1:0])==2'b10) begin
                  stateReg[63:56] <= doutB1[23:16];
               end else if ((storedLeastSignificantBitsTargetAddressTableLookup[1:0])==2'b01) begin
                  stateReg[63:56] <= doutB1[15:8];
               end else begin
                  stateReg[63:56] <= doutB1[7:0];
               end
            end else begin
               // 4 bit
               if ((storedLeastSignificantBitsTargetAddressTableLookup[2:0])==3'b111) begin
                  stateReg[63:60] <= doutB1[31:28];
                  $display("Store msb 1: %h",doutB1[31:28]);
               end else if ((storedLeastSignificantBitsTargetAddressTableLookup[2:0])==3'b110) begin
                  stateReg[63:60] <= doutB1[27:24];
                  $display("Store msb 2: %h",doutB1[27:24]);
               end else if ((storedLeastSignificantBitsTargetAddressTableLookup[2:0])==3'b101) begin
                  stateReg[63:60] <= doutB1[23:20];
                  $display("Store msb 3: %h",doutB1[23:20]);
               end else if ((storedLeastSignificantBitsTargetAddressTableLookup[2:0])==3'b100) begin
                  stateReg[63:60] <= doutB1[19:16];
                  $display("Store msb 4: %h",doutB1[19:16]);
               end else if ((storedLeastSignificantBitsTargetAddressTableLookup[2:0])==3'b011) begin
                  stateReg[63:60] <= doutB1[15:12];
                  $display("Store msb 5: %h",doutB1[15:12]);
               end else if ((storedLeastSignificantBitsTargetAddressTableLookup[2:0])==3'b010) begin
                  stateReg[63:60] <= doutB1[11:8];
                  $display("Store msb 6: %h",doutB1[11:8]);
               end else if ((storedLeastSignificantBitsTargetAddressTableLookup[2:0])==3'b001) begin
                  stateReg[63:60] <= doutB1[7:4];
                  $display("Store msb 7: %h",doutB1[7:4]);
               end else begin
                  stateReg[63:60] <= doutB1[3:0];
                  $display("Store msb 8: %h",doutB1[3:0]);
               end
            end

            // Switch to next block
            if (mainControlRegMaxBlockNum==mainControlRegCurrentBlock) begin
               mainControlReg[11:6] <= 0;
            end else if (mainControlRegCurrentBlock==0) begin
               mainControlReg[11:6] <= mainControlReg[11:6] + 1;
               mainControlReg[31] <= 0;
            end else begin
               mainControlReg[11:6] <= mainControlReg[11:6] + 1;
            end

         end

         $display("Begin of cycle  doutB1: %h",doutB1);
         $display("Monitor cycle - mainCtrlReg: %h stateReg: %h nextBitSelectionReg: %h nextMonitoringOpReg: %h bitFilterReg: %h",mainControlReg,stateReg,nextBitSelectionReg, nextMonitoringOpReg, bitFilterReg);

         mainControlReg[14:12] <= mainControlReg[14:12] - 1; // Reduce cycle

         // Allow access to SRAM12 even when the monitor is running
         if (ramAccessDelayRegister>0) begin
            $display("Reduce register from within running monitor");
            ramAccessDelayRegister <= ramAccessDelayRegister - 1;
            wbs_ack_o <= ramAccessDelayRegister==2;
            webA <= 1;
            webB <= 1;
            
            // Reading from SRAM1
            if (accessFunction==1) begin
               wbs_dat_o <= doutA0;
               if (ramAccessDelayRegister==1) begin
                  csbA0 <= 1;
               end
            end else if (accessFunction==2) begin
               wbs_dat_o <= doutB0;
               if (ramAccessDelayRegister==1) begin
                  csbB0 <= 1;
               end
            end else begin
               csbA0 <= 1;
               csbB0 <= 1;
            end
         end else if (wbs_cyc_i && wbs_stb_i)  begin
            if (wbs_we_i) begin
               if (wbs_adr_i[31:16] == 16'h3001) begin
                  addrB0 <= wbs_adr_i[17:2];
                  dinB0 <= wbs_dat_i;
                  wmaskB <= wbs_sel_i;
                  webB <= 0;
                  ramAccessDelayRegister <= 5;
                  accessFunction <= 0;
                  csbB0 <= 0;
               end
            end else begin
               if (wbs_adr_i[31:16] == 16'h3001) begin
                  // wbs_ack_o <= 0;
                  $display("Read XS accepted 2");
                  addrB0 <= wbs_adr_i[17:2];
                  ramAccessDelayRegister <= 4;
                  accessFunction <= 2;
                  csbB0 <= 0;
               end
            end
         end

      end else if (ramAccessDelayRegister>0) begin
         $display("Reduce register");
         ramAccessDelayRegister <= ramAccessDelayRegister - 1;
         wbs_ack_o <= ramAccessDelayRegister==2;
         webA <= 1;
         webB <= 1;
         
         // Reading from SRAM1
         if (accessFunction==1) begin
            wbs_dat_o <= doutA0;
            if (ramAccessDelayRegister==1) begin
               csbA0 <= 1;
            end
         end else if (accessFunction==2) begin
            wbs_dat_o <= doutB0;
            if (ramAccessDelayRegister==1) begin
               csbB0 <= 1;
            end
         end else begin
            csbA0 <= 1;
            csbB0 <= 1;
         end
      end else if (wbs_cyc_i && wbs_stb_i)  begin
         if (wbs_we_i) begin
            $display("Write XS: ",wbs_adr_i);
            if (wbs_adr_i[31:16] == 16'h3000) begin
               $display("Writing XS accepted ");
               // wbs_ack_o <= 0;
               addrA0 <= wbs_adr_i[17:2];
               dinA0 <= wbs_dat_i;
               wmaskA <= wbs_sel_i;
               webA <= 0;
               ramAccessDelayRegister <= 5;
               accessFunction <= 0;
               csbA0 <= 0;
            end else if (wbs_adr_i[31:16] == 16'h3001) begin
               addrB0 <= wbs_adr_i[17:2];
               dinB0 <= wbs_dat_i;
               wmaskB <= wbs_sel_i;
               webB <= 0;
               ramAccessDelayRegister <= 5;
               accessFunction <= 0;
               csbB0 <= 0;
            end else if (wbs_adr_i[31:16] == 16'h3002) begin
               if (wbs_adr_i[15:0] == 16'h0000) begin
                  $display("XS Writing Main Control Register write");
                  wbs_ack_o <= 1'b1;
                  ramAccessDelayRegister <= 1;
                  if (wbs_sel_i[0]) mainControlReg[7:0]   <= wbs_dat_i[7:0];
                  if (wbs_sel_i[1]) mainControlReg[15:8]  <= wbs_dat_i[15:8];
                  if (wbs_sel_i[2]) mainControlReg[23:16] <= wbs_dat_i[23:16];
                  if (wbs_sel_i[3]) mainControlReg[31:24] <= wbs_dat_i[31:24];
               end else if (wbs_adr_i[15:0] == 16'h0004) begin
                  $display("XS Writing Main Proposition Register");
                  wbs_ack_o <= 1'b1;
                  ramAccessDelayRegister <= 1;
                  
                  // Activate cycle -- Copy propositions over to
                  // the state register. The nibbles get reversed 
                  // in the process as this makes the HDL simpler.
                  // This doesn't matter, though, as the
                  // monitor compiler can adress this.
                  //
                  // Note that htis case doesn't look at the "wbs_sel" Wishbone
                  // information as writing to this address triggers a monitoring
                  // cycle
                  stateReg[63:60] <= wbs_dat_i[3:0];
                  if (mainControlNofStateNibblesForAPs>0) begin
                     stateReg[59:56] <= wbs_dat_i[7:4];
                  end
                  if (mainControlNofStateNibblesForAPs>1) begin
                     stateReg[55:52] <= wbs_dat_i[11:8];
                  end
                  if (mainControlNofStateNibblesForAPs>2) begin
                     stateReg[51:48] <= wbs_dat_i[15:12];
                  end
                  if (mainControlNofStateNibblesForAPs>3) begin
                     stateReg[47:44] <= wbs_dat_i[19:16];
                  end
                  if (mainControlNofStateNibblesForAPs>4) begin
                     stateReg[43:40] <= wbs_dat_i[23:20];
                  end
                  if (mainControlNofStateNibblesForAPs>5) begin
                     stateReg[39:36] <= wbs_dat_i[27:24];
                  end
                  if (mainControlNofStateNibblesForAPs>6) begin
                     stateReg[35:32] <= wbs_dat_i[31:28];
                  end

                  mainControlReg[17:12] <= 7; // Monitor cycle
                  mainControlReg[31] <= 1; // Monitor active

               end else if (wbs_adr_i[15:0] == 16'h0008) begin
                  $display("XS Writing State Register Lower Half");
                  wbs_ack_o <= 1'b1;
                  ramAccessDelayRegister <= 1;
                  if (wbs_sel_i[0]) stateReg[7:0]   <= wbs_dat_i[7:0];
                  if (wbs_sel_i[1]) stateReg[15:8]  <= wbs_dat_i[15:8];
                  if (wbs_sel_i[2]) stateReg[23:16] <= wbs_dat_i[23:16];
                  if (wbs_sel_i[3]) stateReg[31:24] <= wbs_dat_i[31:24];
               end else if (wbs_adr_i[15:0] == 16'h000C) begin
                  $display("XS Writing State Register Upper Half");
                  wbs_ack_o <= 1'b1;
                  ramAccessDelayRegister <= 1;
                  if (wbs_sel_i[0]) stateReg[39:32] <= wbs_dat_i[7:0];
                  if (wbs_sel_i[1]) stateReg[47:40] <= wbs_dat_i[15:8];
                  if (wbs_sel_i[2]) stateReg[55:48] <= wbs_dat_i[23:16];
                  if (wbs_sel_i[3]) stateReg[63:56] <= wbs_dat_i[31:24];
               end  
            end else begin
               $display("unmatched!");
            end
         end else begin
            $display("Read XS: %h",wbs_adr_i);
            if (wbs_adr_i[31:16] == 16'h3000) begin
               // wbs_ack_o <= 0;
               $display("Read XS accepted ");
               addrA0 <= wbs_adr_i[17:2];
               ramAccessDelayRegister <= 4;
               accessFunction <= 1;
               csbA0 <= 0;
            end else if (wbs_adr_i[31:16] == 16'h3001) begin
               // wbs_ack_o <= 0;
               $display("Read XS accepted 2");
               addrB0 <= wbs_adr_i[17:2];
               ramAccessDelayRegister <= 4;
               accessFunction <= 2;
               csbB0 <= 0;
            end else if (wbs_adr_i[31:16] == 16'h3002) begin
               if (wbs_adr_i[15:0] == 16'h0000) begin
                  $display("XS Main Control Register read");
                  wbs_ack_o <= 1'b1;
                  wbs_dat_o <= mainControlReg;
                  ramAccessDelayRegister <= 1;
               end else if (wbs_adr_i[15:0] == 16'h0008) begin
                  $display("XS State Register Lower half read");
                  wbs_ack_o <= 1'b1;
                  wbs_dat_o <= stateReg[31:0];
                  ramAccessDelayRegister <= 1;
               end else if (wbs_adr_i[15:0] == 16'h000C) begin
                  $display("XS State Register Upper half read");
                  wbs_ack_o <= 1'b1;
                  wbs_dat_o <= stateReg[63:32];
                  ramAccessDelayRegister <= 1;
               end
            end else begin
               $display("unmatched! 2");
            end
         end
      end 
   end
   //$display("Cycle! %b %b %b %b ADRi %h wbs_datI %h datO %h StateRegister %h RDY %b",wbs_cyc_i,wbs_stb_i,wbs_we_i,wbs_ack_o,wbs_adr_i,wbs_dat_i,wbs_dat_o, stateReg,inReadySigBitextractor);
   //$fflush();
end

endmodule

`default_nettype wire
