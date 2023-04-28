/************************************************************************
Avalon-MM Interface VGA Text mode display

Register Map:
0x000-0x0257 : VRAM, 80x30 (2400 byte, 600 word) raster order (first column then row)
0x258        : control register

VRAM Format:
X->
[ 31  30-24][ 23  22-16][ 15  14-8 ][ 7    6-0 ]
[IV3][CODE3][IV2][CODE2][IV1][CODE1][IV0][CODE0]

IVn = Draw inverse glyph
CODEn = Glyph code from IBM codepage 437

Control Register Format:
[[31-25][24-21][20-17][16-13][ 12-9][ 8-5 ][ 4-1 ][   0    ] 
[[RSVD ][FGD_R][FGD_G][FGD_B][BKG_R][BKG_G][BKG_B][RESERVED]

VSYNC signal = bit which flips on every Vsync (time for new frame), used to synchronize software
BKG_R/G/B = Background color, flipped with foreground when IVn bit is set
FGD_R/G/B = Foreground color, flipped with background when Inv bit is set

************************************************************************/
`define NUM_REGS 601 //80*30 characters / 4 characters per register
`define CTRL_REG 600 //index of control register

module vga_text_avl_interface (
	// Avalon Clock Input, note this clock is also used for VGA, so this must be 50Mhz
	// We can put a clock divider here in the future to make this IP more generalizable
	input logic CLK,
	
	// Avalon Reset Input
	input logic RESET,
	
	// Avalon-MM Slave Signals
	input  logic AVL_READ,					// Avalon-MM Read
	input  logic AVL_WRITE,					// Avalon-MM Write
	input  logic AVL_CS,					// Avalon-MM Chip Select
	input  logic [3:0] AVL_BYTE_EN,			// Avalon-MM Byte Enable
	input  logic [11:0] AVL_ADDR,			// Avalon-MM Address
	input  logic [31:0] AVL_WRITEDATA,		// Avalon-MM Write Data
	output logic [31:0] AVL_READDATA,		// Avalon-MM Read Data
	
	// Exported Conduit (mapped to VGA port - make sure you export in Platform Designer)
	output logic [3:0]  red, green, blue,	// VGA color channels (mapped to output pins in top-level)
	output logic hs, vs						// VGA HS/VS
);

logic [31:0] LOCAL_REG       [`NUM_REGS]; // Registers
logic [31:0] palette       [8]; 
//put other local variables here
////logic hs, vs, pixel_clk, blank, sync;

logic [7:0] from_data;
logic [10:0] from_addr;
logic [7:0] Xgrid;
logic [6:0] Ygrid;
logic [7:0] vram_code;
logic pixel_clk, blank, sync;					
logic [9:0] DrawX, DrawY;	
logic [31:0] word_addr;
logic [31:0] register;
logic [31:0] temp, temp2;
logic [11:0] test;
//
//vga vga_controller ( .Clk(CLK), .Reset(RESET), .hs(hs), .vs(vs), .pixel_clk(pixel_clk), .blank(blank), .sync(sync), .DrawX(DrawX), .DrawY(DrawY));
//from font_rom (.addr(from_addr), .data(from_data));
// 

//Declare submodules..e.g. VGA controller, ROMS, etc
vga_controller vga_controller (.Clk(CLK), .Reset(RESET), .hs(hs), .vs(vs), .pixel_clk(pixel_clk), .blank(blank), .sync(sync), .DrawX(DrawX), .DrawY(DrawY));
font_rom fm(.addr(from_addr), .data(from_data));	

ram ram0(.address_a(AVL_ADDR), 
			.address_b(register),
			.byteena_a(AVL_BYTE_EN), 
			.clock(CLK), 
			.data_a(AVL_WRITEDATA), 
			.data_b(), 
			.rden_a(AVL_READ & AVL_CS & ~(AVL_ADDR[11])), 
			.rden_b(1'b1), 
			.wren_a(AVL_WRITE & AVL_CS & ~(AVL_ADDR[11])), 
			.wren_b(1'b0), 
			.q_a(temp2), 
			.q_b(temp));


always_ff  @(posedge CLK) begin
	if (RESET)
		begin
			for (int i = 0; i < 8; i++)
					palette[i] <= 32'b0;	
		end

	else if (AVL_WRITE & AVL_CS & AVL_ADDR[11])
		palette[AVL_ADDR[2:0]] <= AVL_WRITEDATA;

end

always_ff  @(posedge CLK) begin
	 if (AVL_READ  & AVL_CS & AVL_ADDR[11])
			AVL_READDATA <= palette[AVL_ADDR[2:0]];
	else if (AVL_READ  & AVL_CS & ~AVL_ADDR[11])
		AVL_READDATA <= temp2;
end
			

//assign AVL_READDATA = temp2;


assign Xgrid = DrawX[9:3];							
assign Ygrid = DrawY[9:4]; 							
assign word_addr = Ygrid * 80 + Xgrid; 		
assign register = word_addr[11:1]; 				
assign from_addr = letter[14:8]*16 + DrawY[3:0];

logic [15:0] letter;

//always_ff @(posedge CLK)
//	begin
//		if(word_addr[1:0] == 2'b00)									
//			vram_code <= palette[AVL_ADDR[2:0][7:0];
//		else if(word_addr[1:0] == 2'b01)
//			vram_code <= palette[AVL_ADDR[2:0][15:8];				
//		else if(word_addr[1:0] == 2'b10)								
//			vram_code <= palette[AVL_ADDR[2:0][23:16];				
//		else if(word_addr[1:0] == 2'b11)									
//			vram_code <= palette[AVL_ADDR[2:0][31:24];		
//	end		

//logic check;
always_comb begin
	if (word_addr[0])
	begin
		letter = temp[31:16];
		//check = 1'b1;
	end
	else 
	begin
		letter = temp[15:0];
		//check=1'b0;
	end
end


always_ff @(posedge pixel_clk)
begin
	if (blank == 1'b1)									
	begin
		if (from_data[7 - DrawX[2:0]] == 1'b1) 			
		begin
			if (letter[15] == 1'b0)
				begin
					if (letter[4] == 1'b0) begin
						red 	<=	palette[letter[7:5]][12:9];
						green	<= palette[letter[7:5]][8:5];
						blue 	<=	palette[letter[7:5]][4:1];
					end
					else begin
						red 	<=	palette[letter[7:5]][24:21];
						green <= palette[letter[7:5]][20:17];
						blue 	<=	palette[letter[7:5]][16:13];
					end
				end
			else
				begin
					if (letter[0] == 1'b0) begin
						red 	<=	palette[letter[3:1]][12:9];
						green	<= palette[letter[3:1]][8:5];
						blue 	<=	palette[letter[3:1]][4:1];
					end
					else begin
						red 	<=	palette[letter[3:1]][24:21];
						green <= palette[letter[3:1]][20:17];
						blue 	<=	palette[letter[3:1]][16:13];
					end
				end
			end
		else if (from_data[7 - DrawX[2:0]] == 1'b0) 			
			begin	
			if (letter[15] == 1'b0)
				begin
					if (letter[0] == 1'b0) begin
						red 	<=	palette[letter[3:1]][12:9];
						green	<= palette[letter[3:1]][8:5];
						blue 	<=	palette[letter[3:1]][4:1];
					end
					else begin
						red 	<=	palette[letter[3:1]][24:21];
						green <= palette[letter[3:1]][20:17];
						blue 	<=	palette[letter[3:1]][16:13];
					end
				end
			else
				begin
					if (letter[4] == 1'b0) begin
						red 	<=	palette[letter[7:5]][12:9];
						green	<= palette[letter[7:5]][8:5];
						blue 	<=	palette[letter[7:5]][4:1];
					end
					else begin
						red 	<=	palette[letter[7:5]][24:21];
						green <= palette[letter[7:5]][20:17];
						blue 	<=	palette[letter[7:5]][16:13];
					end
				end
			end
		end
		

		else begin
			red 	<=	4'h0000;
			green <=	4'h0000;
			blue 	<=	4'h0000;
		end
end


endmodule
