`define WMASK_SIZE 4
`define ADDR_SIZE 16
`define DATA_SIZE 32
`define SELECT_SIZE 4
`define MAX_CHIPS 2
`define PORT_SIZE `ADDR_SIZE+`DATA_SIZE+`WMASK_SIZE+2
`define TOTAL_SIZE `PORT_SIZE+`PORT_SIZE+`SELECT_SIZE

module user_project #(
    parameter BITS = 32
) (
`ifdef USE_POWER_PINS
    //inout vdda1,	// User area 1 3.3V supply
    //inout vdda2,	// User area 2 3.3V supply
    //inout vssa1,	// User area 1 analog ground
    //inout vssa2,	// User area 2 analog ground
    inout vccd1,	// User area 1 1.8V supply
    //inout vccd2,	// User area 2 1.8v supply
    inout vssd1,	// User area 1 digital ground
    //inout vssd2,	// User area 2 digital ground
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
    //input  [127:0] la_data_in,
    //output [127:0] la_data_out,
    //input  [127:0] la_oenb,

    // IOs
    //input  [`MPRJ_IO_PADS-1:0] io_in,
    //output [`MPRJ_IO_PADS-1:0] io_out,
    //output [`MPRJ_IO_PADS-1:0] io_oeb,

    // Analog (direct connection to GPIO pad---use with caution)
    // Note that analog I/O is not available on the 7 lowest-numbered
    // GPIO pads, and so the analog_io indexing is offset from the
    // GPIO indexing by 7 (also upper 2 GPIOs do not have analog_io).
    //inout [`MPRJ_IO_PADS-10:0] analog_io,

    // Independent clock (on independent integer divider)
    input   user_clock2,

    // User maskable interrupt signals
    output [2:0] user_irq,

    // Shared control/data to the SRAMs
    output [7:0] addrA0,
    output [31:0] dinA0,
   
   output webA,
   output [3:0] wmaskA,
   output [7:0]  addrA1,
   output csbA0,
   output csbA1,
   
   
   output [8:0] addrB0,
   output [31:0] dinB0,
   
   output webB,
   output [3:0] wmaskB,
   output [8:0]  addrB1,
   output csbB0,
   output csbB1,

   input [`DATA_SIZE-1:0] sram1_dout0,
   input [`DATA_SIZE-1:0] sram1_dout1,
   input [`DATA_SIZE-1:0] sram12_dout0,
   input [`DATA_SIZE-1:0] sram12_dout1   


);

   // Hold dout from SRAM
   // clocked by SRAM clk
   reg [`DATA_SIZE-1:0] sram1_data0;
   reg [`DATA_SIZE-1:0] sram1_data1;
   reg [`DATA_SIZE-1:0] sram12_data0;
   reg [`DATA_SIZE-1:0] sram12_data1;



   //assign la_data_out[127:112] = 0;

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
   
   
//   wire     in_select = io_in[16];
//   wire     gpio_resetn = io_in[15];
//   wire     gpio_clk = io_in[17];
//   wire     gpio_scan = io_in[19];
//   wire     gpio_sram_load = io_in[20];
//   wire     gpio_global_csb = io_in[21];
//   wire     gpio_in = io_in[18];
//   wire     la_clk = la_data_in[127];
//   wire     la_reset = la_data_in[126];
//   wire     la_in_load = la_data_in[125];
//   wire     la_sram_load = la_data_in[124];
//   wire     la_global_cs = la_data_in[123];
   // Only io_out[22] is output
//   assign io_oeb = ~(1'b1 << 22);
   // Assign other outputs to 0
//   assign io_out[`MPRJ_IO_PADS-1:23] = 0;
//   wire     gpio_out;
//   assign io_out[22] = gpio_out;
//   assign io_out[21:0] = 0;

   // Selecting clock pin
   wire clk;
   assign clk = wb_clk_i; // (~la_oenb[64]) ? la_data_in[64]:wb_clk_i

   // global csb is low with either GPIO or LA csb
   // la_global_cs is low because default LA values are 0
 //  wire global_csb = gpio_global_csb & ~la_global_cs;
   // rstn is low with either GPIO or LA reset
   // la_reset is not active low because default LA values are 0
 //  wire rstn = gpio_resetn & ~la_reset;
   
   monitor CONTROL_LOGIC(
				  .resetn(rstn),
				  .clk(clk),
				  //.global_csb(global_csb),
				  //.gpio_scan(gpio_scan),
				  //.gpio_sram_load(gpio_sram_load),
				  //.gpio_in(gpio_in),
				  //.gpio_out(gpio_out),

				  //.la_in_load(la_in_load),
				  //.la_sram_load(la_sram_load),
				  //.la_data_in(la_data_in[111:0]),
				  //.la_data_out(la_data_out[111:0]),

				  // Shared control/data to the SRAMs
				  .addrA0(addrA0),
                  .dinA0(dinA0),
                  .doutA0(sram1_data0),
                  .webA(webA),
                  .wmaskA(wmaskA),
                  .addrA1(addrA1),
                  .csbA0(csbA0),
                  .csbA1(csbA1),
                  .doutA1(sram1_data1),
         
                  .addrB0(addrB0),
                  .dinB0(dinB0),
                  .doutB0(sram12_data0),
                  .webB(webB),
                  .wmaskB(wmaskB),
                  .addrB1(addrB1),
                  .csbB0(csbB0),
                  .csbB1(csbB1),
                  .doutB1(sram12_data1),

                  // Wishbone connectivity
                  .wb_clk_i(wb_clk_i),
                  .wb_rst_i(wb_rst_i),
                  .wbs_stb_i(wbs_stb_i),
                  .wbs_cyc_i(wbs_cyc_i),
                  .wbs_we_i(wbs_we_i),
                  .wbs_sel_i(wbs_sel_i),
                  .wbs_dat_i(wbs_dat_i),
                  .wbs_adr_i(wbs_adr_i),
                  .wbs_ack_o(wbs_ack_o),
                  .wbs_dat_o(wbs_dat_o)

				  );



   wire [63:0] temp_sram12_dout0;
   assign sram12_dout0 = {temp_sram12_dout0[63:48], temp_sram12_dout0[15:0]};



   always @(posedge clk) begin
      //if (!rstn) begin
//	 sram1_data0 <= 0;
//	 sram1_data1 <= 0;
//	 sram12_data0 <= 0;
//	 sram12_data1 <= 0;
//      end
//      else begin
	 sram1_data0 <= sram1_dout0;
	 sram1_data1 <= sram1_dout1;
	 sram12_data0 <= sram12_dout0;
	 sram12_data1 <= sram12_dout1;
//      end
   end

endmodule	// user_project_wrapper

`default_nettype wire
