module user_project_wrapper (user_clock2,
    vccd1,
    vccd2,
    vdda1,
    vdda2,
    vssa1,
    vssa2,
    vssd1,
    vssd2,
    wb_clk_i,
    wb_rst_i,
    wbs_ack_o,
    wbs_cyc_i,
    wbs_stb_i,
    wbs_we_i,
    analog_io,
    io_in,
    io_oeb,
    io_out,
    la_data_in,
    la_data_out,
    la_oenb,
    user_irq,
    wbs_adr_i,
    wbs_dat_i,
    wbs_dat_o,
    wbs_sel_i);
 input user_clock2;
 input vccd1;
 input vccd2;
 input vdda1;
 input vdda2;
 input vssa1;
 input vssa2;
 input vssd1;
 input vssd2;
 input wb_clk_i;
 input wb_rst_i;
 output wbs_ack_o;
 input wbs_cyc_i;
 input wbs_stb_i;
 input wbs_we_i;
 inout [28:0] analog_io;
 input [37:0] io_in;
 output [37:0] io_oeb;
 output [37:0] io_out;
 input [127:0] la_data_in;
 output [127:0] la_data_out;
 input [127:0] la_oenb;
 output [2:0] user_irq;
 input [31:0] wbs_adr_i;
 input [31:0] wbs_dat_i;
 output [31:0] wbs_dat_o;
 input [3:0] wbs_sel_i;

 wire \addrA0[0] ;
 wire \addrA0[1] ;
 wire \addrA0[2] ;
 wire \addrA0[3] ;
 wire \addrA0[4] ;
 wire \addrA0[5] ;
 wire \addrA0[6] ;
 wire \addrA0[7] ;
 wire \addrA1[0] ;
 wire \addrA1[1] ;
 wire \addrA1[2] ;
 wire \addrA1[3] ;
 wire \addrA1[4] ;
 wire \addrA1[5] ;
 wire \addrA1[6] ;
 wire \addrA1[7] ;
 wire \addrB0[0] ;
 wire \addrB0[1] ;
 wire \addrB0[2] ;
 wire \addrB0[3] ;
 wire \addrB0[4] ;
 wire \addrB0[5] ;
 wire \addrB0[6] ;
 wire \addrB0[7] ;
 wire \addrB0[8] ;
 wire \addrB1[0] ;
 wire \addrB1[1] ;
 wire \addrB1[2] ;
 wire \addrB1[3] ;
 wire \addrB1[4] ;
 wire \addrB1[5] ;
 wire \addrB1[6] ;
 wire \addrB1[7] ;
 wire \addrB1[8] ;
 wire csbA0;
 wire csbA1;
 wire csbB0;
 wire csbB1;
 wire \dinA0[0] ;
 wire \dinA0[10] ;
 wire \dinA0[11] ;
 wire \dinA0[12] ;
 wire \dinA0[13] ;
 wire \dinA0[14] ;
 wire \dinA0[15] ;
 wire \dinA0[16] ;
 wire \dinA0[17] ;
 wire \dinA0[18] ;
 wire \dinA0[19] ;
 wire \dinA0[1] ;
 wire \dinA0[20] ;
 wire \dinA0[21] ;
 wire \dinA0[22] ;
 wire \dinA0[23] ;
 wire \dinA0[24] ;
 wire \dinA0[25] ;
 wire \dinA0[26] ;
 wire \dinA0[27] ;
 wire \dinA0[28] ;
 wire \dinA0[29] ;
 wire \dinA0[2] ;
 wire \dinA0[30] ;
 wire \dinA0[31] ;
 wire \dinA0[3] ;
 wire \dinA0[4] ;
 wire \dinA0[5] ;
 wire \dinA0[6] ;
 wire \dinA0[7] ;
 wire \dinA0[8] ;
 wire \dinA0[9] ;
 wire \dinB0[0] ;
 wire \dinB0[10] ;
 wire \dinB0[11] ;
 wire \dinB0[12] ;
 wire \dinB0[13] ;
 wire \dinB0[14] ;
 wire \dinB0[15] ;
 wire \dinB0[16] ;
 wire \dinB0[17] ;
 wire \dinB0[18] ;
 wire \dinB0[19] ;
 wire \dinB0[1] ;
 wire \dinB0[20] ;
 wire \dinB0[21] ;
 wire \dinB0[22] ;
 wire \dinB0[23] ;
 wire \dinB0[24] ;
 wire \dinB0[25] ;
 wire \dinB0[26] ;
 wire \dinB0[27] ;
 wire \dinB0[28] ;
 wire \dinB0[29] ;
 wire \dinB0[2] ;
 wire \dinB0[30] ;
 wire \dinB0[31] ;
 wire \dinB0[3] ;
 wire \dinB0[4] ;
 wire \dinB0[5] ;
 wire \dinB0[6] ;
 wire \dinB0[7] ;
 wire \dinB0[8] ;
 wire \dinB0[9] ;
 wire \sram12_dout0[0] ;
 wire \sram12_dout0[10] ;
 wire \sram12_dout0[11] ;
 wire \sram12_dout0[12] ;
 wire \sram12_dout0[13] ;
 wire \sram12_dout0[14] ;
 wire \sram12_dout0[15] ;
 wire \sram12_dout0[16] ;
 wire \sram12_dout0[17] ;
 wire \sram12_dout0[18] ;
 wire \sram12_dout0[19] ;
 wire \sram12_dout0[1] ;
 wire \sram12_dout0[20] ;
 wire \sram12_dout0[21] ;
 wire \sram12_dout0[22] ;
 wire \sram12_dout0[23] ;
 wire \sram12_dout0[24] ;
 wire \sram12_dout0[25] ;
 wire \sram12_dout0[26] ;
 wire \sram12_dout0[27] ;
 wire \sram12_dout0[28] ;
 wire \sram12_dout0[29] ;
 wire \sram12_dout0[2] ;
 wire \sram12_dout0[30] ;
 wire \sram12_dout0[31] ;
 wire \sram12_dout0[3] ;
 wire \sram12_dout0[4] ;
 wire \sram12_dout0[5] ;
 wire \sram12_dout0[6] ;
 wire \sram12_dout0[7] ;
 wire \sram12_dout0[8] ;
 wire \sram12_dout0[9] ;
 wire \sram12_dout1[0] ;
 wire \sram12_dout1[10] ;
 wire \sram12_dout1[11] ;
 wire \sram12_dout1[12] ;
 wire \sram12_dout1[13] ;
 wire \sram12_dout1[14] ;
 wire \sram12_dout1[15] ;
 wire \sram12_dout1[16] ;
 wire \sram12_dout1[17] ;
 wire \sram12_dout1[18] ;
 wire \sram12_dout1[19] ;
 wire \sram12_dout1[1] ;
 wire \sram12_dout1[20] ;
 wire \sram12_dout1[21] ;
 wire \sram12_dout1[22] ;
 wire \sram12_dout1[23] ;
 wire \sram12_dout1[24] ;
 wire \sram12_dout1[25] ;
 wire \sram12_dout1[26] ;
 wire \sram12_dout1[27] ;
 wire \sram12_dout1[28] ;
 wire \sram12_dout1[29] ;
 wire \sram12_dout1[2] ;
 wire \sram12_dout1[30] ;
 wire \sram12_dout1[31] ;
 wire \sram12_dout1[3] ;
 wire \sram12_dout1[4] ;
 wire \sram12_dout1[5] ;
 wire \sram12_dout1[6] ;
 wire \sram12_dout1[7] ;
 wire \sram12_dout1[8] ;
 wire \sram12_dout1[9] ;
 wire \sram1_dout0[0] ;
 wire \sram1_dout0[10] ;
 wire \sram1_dout0[11] ;
 wire \sram1_dout0[12] ;
 wire \sram1_dout0[13] ;
 wire \sram1_dout0[14] ;
 wire \sram1_dout0[15] ;
 wire \sram1_dout0[16] ;
 wire \sram1_dout0[17] ;
 wire \sram1_dout0[18] ;
 wire \sram1_dout0[19] ;
 wire \sram1_dout0[1] ;
 wire \sram1_dout0[20] ;
 wire \sram1_dout0[21] ;
 wire \sram1_dout0[22] ;
 wire \sram1_dout0[23] ;
 wire \sram1_dout0[24] ;
 wire \sram1_dout0[25] ;
 wire \sram1_dout0[26] ;
 wire \sram1_dout0[27] ;
 wire \sram1_dout0[28] ;
 wire \sram1_dout0[29] ;
 wire \sram1_dout0[2] ;
 wire \sram1_dout0[30] ;
 wire \sram1_dout0[31] ;
 wire \sram1_dout0[3] ;
 wire \sram1_dout0[4] ;
 wire \sram1_dout0[5] ;
 wire \sram1_dout0[6] ;
 wire \sram1_dout0[7] ;
 wire \sram1_dout0[8] ;
 wire \sram1_dout0[9] ;
 wire \sram1_dout1[0] ;
 wire \sram1_dout1[10] ;
 wire \sram1_dout1[11] ;
 wire \sram1_dout1[12] ;
 wire \sram1_dout1[13] ;
 wire \sram1_dout1[14] ;
 wire \sram1_dout1[15] ;
 wire \sram1_dout1[16] ;
 wire \sram1_dout1[17] ;
 wire \sram1_dout1[18] ;
 wire \sram1_dout1[19] ;
 wire \sram1_dout1[1] ;
 wire \sram1_dout1[20] ;
 wire \sram1_dout1[21] ;
 wire \sram1_dout1[22] ;
 wire \sram1_dout1[23] ;
 wire \sram1_dout1[24] ;
 wire \sram1_dout1[25] ;
 wire \sram1_dout1[26] ;
 wire \sram1_dout1[27] ;
 wire \sram1_dout1[28] ;
 wire \sram1_dout1[29] ;
 wire \sram1_dout1[2] ;
 wire \sram1_dout1[30] ;
 wire \sram1_dout1[31] ;
 wire \sram1_dout1[3] ;
 wire \sram1_dout1[4] ;
 wire \sram1_dout1[5] ;
 wire \sram1_dout1[6] ;
 wire \sram1_dout1[7] ;
 wire \sram1_dout1[8] ;
 wire \sram1_dout1[9] ;
 wire webA;
 wire webB;
 wire \wmaskA[0] ;
 wire \wmaskA[1] ;
 wire \wmaskA[2] ;
 wire \wmaskA[3] ;
 wire \wmaskB[0] ;
 wire \wmaskB[1] ;
 wire \wmaskB[2] ;
 wire \wmaskB[3] ;

 sky130_sram_1kbyte_1rw1r_32x256_8 SRAM1 (.csb0(csbA0),
    .csb1(csbA1),
    .web0(webA),
    .clk0(wb_clk_i),
    .clk1(wb_clk_i),
    .vccd1(vccd1),
    .vssd1(vssd1),
    .addr0({\addrA0[7] ,
    \addrA0[6] ,
    \addrA0[5] ,
    \addrA0[4] ,
    \addrA0[3] ,
    \addrA0[2] ,
    \addrA0[1] ,
    \addrA0[0] }),
    .addr1({\addrA1[7] ,
    \addrA1[6] ,
    \addrA1[5] ,
    \addrA1[4] ,
    \addrA1[3] ,
    \addrA1[2] ,
    \addrA1[1] ,
    \addrA1[0] }),
    .din0({\dinA0[31] ,
    \dinA0[30] ,
    \dinA0[29] ,
    \dinA0[28] ,
    \dinA0[27] ,
    \dinA0[26] ,
    \dinA0[25] ,
    \dinA0[24] ,
    \dinA0[23] ,
    \dinA0[22] ,
    \dinA0[21] ,
    \dinA0[20] ,
    \dinA0[19] ,
    \dinA0[18] ,
    \dinA0[17] ,
    \dinA0[16] ,
    \dinA0[15] ,
    \dinA0[14] ,
    \dinA0[13] ,
    \dinA0[12] ,
    \dinA0[11] ,
    \dinA0[10] ,
    \dinA0[9] ,
    \dinA0[8] ,
    \dinA0[7] ,
    \dinA0[6] ,
    \dinA0[5] ,
    \dinA0[4] ,
    \dinA0[3] ,
    \dinA0[2] ,
    \dinA0[1] ,
    \dinA0[0] }),
    .dout0({\sram1_dout0[31] ,
    \sram1_dout0[30] ,
    \sram1_dout0[29] ,
    \sram1_dout0[28] ,
    \sram1_dout0[27] ,
    \sram1_dout0[26] ,
    \sram1_dout0[25] ,
    \sram1_dout0[24] ,
    \sram1_dout0[23] ,
    \sram1_dout0[22] ,
    \sram1_dout0[21] ,
    \sram1_dout0[20] ,
    \sram1_dout0[19] ,
    \sram1_dout0[18] ,
    \sram1_dout0[17] ,
    \sram1_dout0[16] ,
    \sram1_dout0[15] ,
    \sram1_dout0[14] ,
    \sram1_dout0[13] ,
    \sram1_dout0[12] ,
    \sram1_dout0[11] ,
    \sram1_dout0[10] ,
    \sram1_dout0[9] ,
    \sram1_dout0[8] ,
    \sram1_dout0[7] ,
    \sram1_dout0[6] ,
    \sram1_dout0[5] ,
    \sram1_dout0[4] ,
    \sram1_dout0[3] ,
    \sram1_dout0[2] ,
    \sram1_dout0[1] ,
    \sram1_dout0[0] }),
    .dout1({\sram1_dout1[31] ,
    \sram1_dout1[30] ,
    \sram1_dout1[29] ,
    \sram1_dout1[28] ,
    \sram1_dout1[27] ,
    \sram1_dout1[26] ,
    \sram1_dout1[25] ,
    \sram1_dout1[24] ,
    \sram1_dout1[23] ,
    \sram1_dout1[22] ,
    \sram1_dout1[21] ,
    \sram1_dout1[20] ,
    \sram1_dout1[19] ,
    \sram1_dout1[18] ,
    \sram1_dout1[17] ,
    \sram1_dout1[16] ,
    \sram1_dout1[15] ,
    \sram1_dout1[14] ,
    \sram1_dout1[13] ,
    \sram1_dout1[12] ,
    \sram1_dout1[11] ,
    \sram1_dout1[10] ,
    \sram1_dout1[9] ,
    \sram1_dout1[8] ,
    \sram1_dout1[7] ,
    \sram1_dout1[6] ,
    \sram1_dout1[5] ,
    \sram1_dout1[4] ,
    \sram1_dout1[3] ,
    \sram1_dout1[2] ,
    \sram1_dout1[1] ,
    \sram1_dout1[0] }),
    .wmask0({\wmaskA[3] ,
    \wmaskA[2] ,
    \wmaskA[1] ,
    \wmaskA[0] }));
 sky130_sram_2kbyte_1rw1r_32x512_8 SRAM12 (.csb0(csbB0),
    .csb1(csbB1),
    .web0(webB),
    .clk0(wb_clk_i),
    .clk1(wb_clk_i),
    .vccd1(vccd1),
    .vssd1(vssd1),
    .addr0({\addrB0[8] ,
    \addrB0[7] ,
    \addrB0[6] ,
    \addrB0[5] ,
    \addrB0[4] ,
    \addrB0[3] ,
    \addrB0[2] ,
    \addrB0[1] ,
    \addrB0[0] }),
    .addr1({\addrB1[8] ,
    \addrB1[7] ,
    \addrB1[6] ,
    \addrB1[5] ,
    \addrB1[4] ,
    \addrB1[3] ,
    \addrB1[2] ,
    \addrB1[1] ,
    \addrB1[0] }),
    .din0({\dinB0[31] ,
    \dinB0[30] ,
    \dinB0[29] ,
    \dinB0[28] ,
    \dinB0[27] ,
    \dinB0[26] ,
    \dinB0[25] ,
    \dinB0[24] ,
    \dinB0[23] ,
    \dinB0[22] ,
    \dinB0[21] ,
    \dinB0[20] ,
    \dinB0[19] ,
    \dinB0[18] ,
    \dinB0[17] ,
    \dinB0[16] ,
    \dinB0[15] ,
    \dinB0[14] ,
    \dinB0[13] ,
    \dinB0[12] ,
    \dinB0[11] ,
    \dinB0[10] ,
    \dinB0[9] ,
    \dinB0[8] ,
    \dinB0[7] ,
    \dinB0[6] ,
    \dinB0[5] ,
    \dinB0[4] ,
    \dinB0[3] ,
    \dinB0[2] ,
    \dinB0[1] ,
    \dinB0[0] }),
    .dout0({\sram12_dout0[31] ,
    \sram12_dout0[30] ,
    \sram12_dout0[29] ,
    \sram12_dout0[28] ,
    \sram12_dout0[27] ,
    \sram12_dout0[26] ,
    \sram12_dout0[25] ,
    \sram12_dout0[24] ,
    \sram12_dout0[23] ,
    \sram12_dout0[22] ,
    \sram12_dout0[21] ,
    \sram12_dout0[20] ,
    \sram12_dout0[19] ,
    \sram12_dout0[18] ,
    \sram12_dout0[17] ,
    \sram12_dout0[16] ,
    \sram12_dout0[15] ,
    \sram12_dout0[14] ,
    \sram12_dout0[13] ,
    \sram12_dout0[12] ,
    \sram12_dout0[11] ,
    \sram12_dout0[10] ,
    \sram12_dout0[9] ,
    \sram12_dout0[8] ,
    \sram12_dout0[7] ,
    \sram12_dout0[6] ,
    \sram12_dout0[5] ,
    \sram12_dout0[4] ,
    \sram12_dout0[3] ,
    \sram12_dout0[2] ,
    \sram12_dout0[1] ,
    \sram12_dout0[0] }),
    .dout1({\sram12_dout1[31] ,
    \sram12_dout1[30] ,
    \sram12_dout1[29] ,
    \sram12_dout1[28] ,
    \sram12_dout1[27] ,
    \sram12_dout1[26] ,
    \sram12_dout1[25] ,
    \sram12_dout1[24] ,
    \sram12_dout1[23] ,
    \sram12_dout1[22] ,
    \sram12_dout1[21] ,
    \sram12_dout1[20] ,
    \sram12_dout1[19] ,
    \sram12_dout1[18] ,
    \sram12_dout1[17] ,
    \sram12_dout1[16] ,
    \sram12_dout1[15] ,
    \sram12_dout1[14] ,
    \sram12_dout1[13] ,
    \sram12_dout1[12] ,
    \sram12_dout1[11] ,
    \sram12_dout1[10] ,
    \sram12_dout1[9] ,
    \sram12_dout1[8] ,
    \sram12_dout1[7] ,
    \sram12_dout1[6] ,
    \sram12_dout1[5] ,
    \sram12_dout1[4] ,
    \sram12_dout1[3] ,
    \sram12_dout1[2] ,
    \sram12_dout1[1] ,
    \sram12_dout1[0] }),
    .wmask0({\wmaskB[3] ,
    \wmaskB[2] ,
    \wmaskB[1] ,
    \wmaskB[0] }));
 user_project prj (.csbA0(csbA0),
    .csbA1(csbA1),
    .csbB0(csbB0),
    .csbB1(csbB1),
    .user_clock2(user_clock2),
    .vccd1(vccd1),
    .vssd1(vssd1),
    .wb_clk_i(wb_clk_i),
    .wb_rst_i(wb_rst_i),
    .wbs_ack_o(wbs_ack_o),
    .wbs_cyc_i(wbs_cyc_i),
    .wbs_stb_i(wbs_stb_i),
    .wbs_we_i(wbs_we_i),
    .webA(webA),
    .webB(webB),
    .addrA0({\addrA0[7] ,
    \addrA0[6] ,
    \addrA0[5] ,
    \addrA0[4] ,
    \addrA0[3] ,
    \addrA0[2] ,
    \addrA0[1] ,
    \addrA0[0] }),
    .addrA1({\addrA1[7] ,
    \addrA1[6] ,
    \addrA1[5] ,
    \addrA1[4] ,
    \addrA1[3] ,
    \addrA1[2] ,
    \addrA1[1] ,
    \addrA1[0] }),
    .addrB0({\addrB0[8] ,
    \addrB0[7] ,
    \addrB0[6] ,
    \addrB0[5] ,
    \addrB0[4] ,
    \addrB0[3] ,
    \addrB0[2] ,
    \addrB0[1] ,
    \addrB0[0] }),
    .addrB1({\addrB1[8] ,
    \addrB1[7] ,
    \addrB1[6] ,
    \addrB1[5] ,
    \addrB1[4] ,
    \addrB1[3] ,
    \addrB1[2] ,
    \addrB1[1] ,
    \addrB1[0] }),
    .dinA0({\dinA0[31] ,
    \dinA0[30] ,
    \dinA0[29] ,
    \dinA0[28] ,
    \dinA0[27] ,
    \dinA0[26] ,
    \dinA0[25] ,
    \dinA0[24] ,
    \dinA0[23] ,
    \dinA0[22] ,
    \dinA0[21] ,
    \dinA0[20] ,
    \dinA0[19] ,
    \dinA0[18] ,
    \dinA0[17] ,
    \dinA0[16] ,
    \dinA0[15] ,
    \dinA0[14] ,
    \dinA0[13] ,
    \dinA0[12] ,
    \dinA0[11] ,
    \dinA0[10] ,
    \dinA0[9] ,
    \dinA0[8] ,
    \dinA0[7] ,
    \dinA0[6] ,
    \dinA0[5] ,
    \dinA0[4] ,
    \dinA0[3] ,
    \dinA0[2] ,
    \dinA0[1] ,
    \dinA0[0] }),
    .dinB0({\dinB0[31] ,
    \dinB0[30] ,
    \dinB0[29] ,
    \dinB0[28] ,
    \dinB0[27] ,
    \dinB0[26] ,
    \dinB0[25] ,
    \dinB0[24] ,
    \dinB0[23] ,
    \dinB0[22] ,
    \dinB0[21] ,
    \dinB0[20] ,
    \dinB0[19] ,
    \dinB0[18] ,
    \dinB0[17] ,
    \dinB0[16] ,
    \dinB0[15] ,
    \dinB0[14] ,
    \dinB0[13] ,
    \dinB0[12] ,
    \dinB0[11] ,
    \dinB0[10] ,
    \dinB0[9] ,
    \dinB0[8] ,
    \dinB0[7] ,
    \dinB0[6] ,
    \dinB0[5] ,
    \dinB0[4] ,
    \dinB0[3] ,
    \dinB0[2] ,
    \dinB0[1] ,
    \dinB0[0] }),
    .sram12_dout0({\sram12_dout0[31] ,
    \sram12_dout0[30] ,
    \sram12_dout0[29] ,
    \sram12_dout0[28] ,
    \sram12_dout0[27] ,
    \sram12_dout0[26] ,
    \sram12_dout0[25] ,
    \sram12_dout0[24] ,
    \sram12_dout0[23] ,
    \sram12_dout0[22] ,
    \sram12_dout0[21] ,
    \sram12_dout0[20] ,
    \sram12_dout0[19] ,
    \sram12_dout0[18] ,
    \sram12_dout0[17] ,
    \sram12_dout0[16] ,
    \sram12_dout0[15] ,
    \sram12_dout0[14] ,
    \sram12_dout0[13] ,
    \sram12_dout0[12] ,
    \sram12_dout0[11] ,
    \sram12_dout0[10] ,
    \sram12_dout0[9] ,
    \sram12_dout0[8] ,
    \sram12_dout0[7] ,
    \sram12_dout0[6] ,
    \sram12_dout0[5] ,
    \sram12_dout0[4] ,
    \sram12_dout0[3] ,
    \sram12_dout0[2] ,
    \sram12_dout0[1] ,
    \sram12_dout0[0] }),
    .sram12_dout1({\sram12_dout1[31] ,
    \sram12_dout1[30] ,
    \sram12_dout1[29] ,
    \sram12_dout1[28] ,
    \sram12_dout1[27] ,
    \sram12_dout1[26] ,
    \sram12_dout1[25] ,
    \sram12_dout1[24] ,
    \sram12_dout1[23] ,
    \sram12_dout1[22] ,
    \sram12_dout1[21] ,
    \sram12_dout1[20] ,
    \sram12_dout1[19] ,
    \sram12_dout1[18] ,
    \sram12_dout1[17] ,
    \sram12_dout1[16] ,
    \sram12_dout1[15] ,
    \sram12_dout1[14] ,
    \sram12_dout1[13] ,
    \sram12_dout1[12] ,
    \sram12_dout1[11] ,
    \sram12_dout1[10] ,
    \sram12_dout1[9] ,
    \sram12_dout1[8] ,
    \sram12_dout1[7] ,
    \sram12_dout1[6] ,
    \sram12_dout1[5] ,
    \sram12_dout1[4] ,
    \sram12_dout1[3] ,
    \sram12_dout1[2] ,
    \sram12_dout1[1] ,
    \sram12_dout1[0] }),
    .sram1_dout0({\sram1_dout0[31] ,
    \sram1_dout0[30] ,
    \sram1_dout0[29] ,
    \sram1_dout0[28] ,
    \sram1_dout0[27] ,
    \sram1_dout0[26] ,
    \sram1_dout0[25] ,
    \sram1_dout0[24] ,
    \sram1_dout0[23] ,
    \sram1_dout0[22] ,
    \sram1_dout0[21] ,
    \sram1_dout0[20] ,
    \sram1_dout0[19] ,
    \sram1_dout0[18] ,
    \sram1_dout0[17] ,
    \sram1_dout0[16] ,
    \sram1_dout0[15] ,
    \sram1_dout0[14] ,
    \sram1_dout0[13] ,
    \sram1_dout0[12] ,
    \sram1_dout0[11] ,
    \sram1_dout0[10] ,
    \sram1_dout0[9] ,
    \sram1_dout0[8] ,
    \sram1_dout0[7] ,
    \sram1_dout0[6] ,
    \sram1_dout0[5] ,
    \sram1_dout0[4] ,
    \sram1_dout0[3] ,
    \sram1_dout0[2] ,
    \sram1_dout0[1] ,
    \sram1_dout0[0] }),
    .sram1_dout1({\sram1_dout1[31] ,
    \sram1_dout1[30] ,
    \sram1_dout1[29] ,
    \sram1_dout1[28] ,
    \sram1_dout1[27] ,
    \sram1_dout1[26] ,
    \sram1_dout1[25] ,
    \sram1_dout1[24] ,
    \sram1_dout1[23] ,
    \sram1_dout1[22] ,
    \sram1_dout1[21] ,
    \sram1_dout1[20] ,
    \sram1_dout1[19] ,
    \sram1_dout1[18] ,
    \sram1_dout1[17] ,
    \sram1_dout1[16] ,
    \sram1_dout1[15] ,
    \sram1_dout1[14] ,
    \sram1_dout1[13] ,
    \sram1_dout1[12] ,
    \sram1_dout1[11] ,
    \sram1_dout1[10] ,
    \sram1_dout1[9] ,
    \sram1_dout1[8] ,
    \sram1_dout1[7] ,
    \sram1_dout1[6] ,
    \sram1_dout1[5] ,
    \sram1_dout1[4] ,
    \sram1_dout1[3] ,
    \sram1_dout1[2] ,
    \sram1_dout1[1] ,
    \sram1_dout1[0] }),
    .user_irq({user_irq[2],
    user_irq[1],
    user_irq[0]}),
    .wbs_adr_i({wbs_adr_i[31],
    wbs_adr_i[30],
    wbs_adr_i[29],
    wbs_adr_i[28],
    wbs_adr_i[27],
    wbs_adr_i[26],
    wbs_adr_i[25],
    wbs_adr_i[24],
    wbs_adr_i[23],
    wbs_adr_i[22],
    wbs_adr_i[21],
    wbs_adr_i[20],
    wbs_adr_i[19],
    wbs_adr_i[18],
    wbs_adr_i[17],
    wbs_adr_i[16],
    wbs_adr_i[15],
    wbs_adr_i[14],
    wbs_adr_i[13],
    wbs_adr_i[12],
    wbs_adr_i[11],
    wbs_adr_i[10],
    wbs_adr_i[9],
    wbs_adr_i[8],
    wbs_adr_i[7],
    wbs_adr_i[6],
    wbs_adr_i[5],
    wbs_adr_i[4],
    wbs_adr_i[3],
    wbs_adr_i[2],
    wbs_adr_i[1],
    wbs_adr_i[0]}),
    .wbs_dat_i({wbs_dat_i[31],
    wbs_dat_i[30],
    wbs_dat_i[29],
    wbs_dat_i[28],
    wbs_dat_i[27],
    wbs_dat_i[26],
    wbs_dat_i[25],
    wbs_dat_i[24],
    wbs_dat_i[23],
    wbs_dat_i[22],
    wbs_dat_i[21],
    wbs_dat_i[20],
    wbs_dat_i[19],
    wbs_dat_i[18],
    wbs_dat_i[17],
    wbs_dat_i[16],
    wbs_dat_i[15],
    wbs_dat_i[14],
    wbs_dat_i[13],
    wbs_dat_i[12],
    wbs_dat_i[11],
    wbs_dat_i[10],
    wbs_dat_i[9],
    wbs_dat_i[8],
    wbs_dat_i[7],
    wbs_dat_i[6],
    wbs_dat_i[5],
    wbs_dat_i[4],
    wbs_dat_i[3],
    wbs_dat_i[2],
    wbs_dat_i[1],
    wbs_dat_i[0]}),
    .wbs_dat_o({wbs_dat_o[31],
    wbs_dat_o[30],
    wbs_dat_o[29],
    wbs_dat_o[28],
    wbs_dat_o[27],
    wbs_dat_o[26],
    wbs_dat_o[25],
    wbs_dat_o[24],
    wbs_dat_o[23],
    wbs_dat_o[22],
    wbs_dat_o[21],
    wbs_dat_o[20],
    wbs_dat_o[19],
    wbs_dat_o[18],
    wbs_dat_o[17],
    wbs_dat_o[16],
    wbs_dat_o[15],
    wbs_dat_o[14],
    wbs_dat_o[13],
    wbs_dat_o[12],
    wbs_dat_o[11],
    wbs_dat_o[10],
    wbs_dat_o[9],
    wbs_dat_o[8],
    wbs_dat_o[7],
    wbs_dat_o[6],
    wbs_dat_o[5],
    wbs_dat_o[4],
    wbs_dat_o[3],
    wbs_dat_o[2],
    wbs_dat_o[1],
    wbs_dat_o[0]}),
    .wbs_sel_i({wbs_sel_i[3],
    wbs_sel_i[2],
    wbs_sel_i[1],
    wbs_sel_i[0]}),
    .wmaskA({\wmaskA[3] ,
    \wmaskA[2] ,
    \wmaskA[1] ,
    \wmaskA[0] }),
    .wmaskB({\wmaskB[3] ,
    \wmaskB[2] ,
    \wmaskB[1] ,
    \wmaskB[0] }));
endmodule
