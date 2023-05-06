 module progress(input logic CLK, 
						input logic [5:0] minutes, seconds,
						input logic [9:0] DrawX, DrawY,
						output logic [3:0] red, green, blue);

					
logic [7:0] increments;
	
always_ff  @(posedge CLK) begin
increments <= (minutes*60)+seconds;
 
 //x- ccord from 10 to 20 
 //y - coord from 330 to 150
 //green from case 35-24
 //yellow from case 23 -12
 // red from case 11 - 0
 
if(DrawX == 10 || DrawX == 20 || DrawY == 420 || DrawY == 60)
begin
	red <= 4'h0;
	green <= 4'h0;
	blue <= 4'h0;
end
 
if(DrawX < 20 && DrawX > 10 && DrawY < 420 && DrawY > 60)
begin
case (increments)
8'd180, 8'd179:
		begin
		red <= 4'h0;
		green <= 4'ha;
		blue <= 4'h0;
		end
8'd178, 8'd177, 8'd176, 8'd175, 8'd174, 8'd173, 8'd172, 8'd171, 8'd170, 8'd169, 8'd168,
8'd167, 8'd166, 8'd165, 8'd164, 8'd163, 8'd162, 8'd161, 8'd160, 8'd159, 8'd158,
8'd157, 8'd156, 8'd155, 8'd154, 8'd153, 8'd152, 8'd151, 8'd150, 8'd149, 8'd148,
8'd147, 8'd146, 8'd145, 8'd144, 8'd143, 8'd142, 8'd141, 8'd140, 8'd139, 8'd138,
8'd137, 8'd136, 8'd135, 8'd134, 8'd133, 8'd132, 8'd131, 8'd130, 8'd129, 8'd128,
8'd127, 8'd126, 8'd125, 8'd124, 8'd123, 8'd122, 8'd121, 8'd120:
	if ( DrawY > 60 + 2*(180-increments))
	begin
		red <= 4'h0;
		green <= 4'ha;
		blue <= 4'h0;
	end
	else
	begin
		red <= 4'ha;
		green <= 4'ha;
		blue <= 4'ha;
	end
8'd119, 8'd118, 8'd117, 8'd116, 8'd115, 8'd114, 8'd113, 8'd112, 8'd111, 8'd110, 8'd109,
8'd108, 8'd107, 8'd106, 8'd105, 8'd104, 8'd103, 8'd102, 8'd101, 8'd100, 8'd99,
8'd98, 8'd97, 8'd96, 8'd95, 8'd94, 8'd93, 8'd92, 8'd91, 8'd90, 8'd89,
8'd88, 8'd87, 8'd86, 8'd85, 8'd84, 8'd83, 8'd82, 8'd81, 8'd80, 8'd79,
8'd78, 8'd77, 8'd76, 8'd75, 8'd74, 8'd73, 8'd72, 8'd71, 8'd70, 8'd69,
8'd68, 8'd67, 8'd66, 8'd65, 8'd64, 8'd63, 8'd62, 8'd61, 8'd60:
	if ( DrawY > 60 + 2*(180-increments))
	begin
		red <= 4'hf;
		green <= 4'hf;
		blue <= 4'h5;
	end
	else
	begin
		red <= 4'ha;
		green <= 4'ha;
		blue <= 4'ha;
	end
		
8'd59, 8'd58, 8'd57, 8'd56, 8'd55, 8'd54, 8'd53, 8'd52, 8'd51, 8'd50, 8'd49,
8'd48, 8'd47, 8'd46, 8'd45, 8'd44, 8'd43, 8'd42, 8'd41, 8'd40, 8'd39,
8'd38, 8'd37, 8'd36, 8'd35, 8'd34, 8'd33, 8'd32, 8'd31, 8'd30, 8'd29,
8'd28, 8'd27, 8'd26, 8'd25, 8'd24, 8'd23, 8'd22, 8'd21, 8'd20, 8'd19,
8'd18, 8'd17, 8'd16, 8'd15, 8'd14, 8'd13, 8'd12, 8'd11, 8'd10, 8'd9,
8'd8, 8'd7, 8'd6, 8'd5, 8'd4, 8'd3, 8'd2, 8'd1:
	if ( DrawY > 60 + 2*(180-increments))
	begin
		red <= 4'ha;
		green <= 4'h0;
		blue <= 4'h0;
	end
	else
	begin
		red <= 4'ha;
		green <= 4'ha;
		blue <= 4'ha;
	end
8'd0:
		begin
		red <= 4'ha;
		green <= 4'ha;
		blue <= 4'ha;
	end
		
endcase		
end
end

endmodule	