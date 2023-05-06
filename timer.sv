module countdown (
  input wire clk,  // Clock input (50 MHz)
  input wire reset,  // Reset input
  output reg [5:0] minutes,  // Output indicating the remaining minutes
  output reg [5:0] seconds, // Output indicating the remaining seconds
  output rem
  
);


  reg [25:0] count;  // Internal counter

  always @(posedge clk) begin
    if (reset == 1'b1) begin
      count <= 0;
		rem <= 1'b0;
      minutes <= 5'd3;  // Initialize minutes to 0
      seconds <= 6'b0;  // Initialize seconds to 0
    end 
	 else if (count == 50_000_000) begin  // 50 million counts represent 1 second
      count <= 0;
      if (seconds == 6'b0) 
		begin
        if (minutes > 1'b0) 
		  begin
          minutes <= minutes - 1;
			 seconds <= 59;
		  end
		  else 
				rem <= 1'b1;
      end
      if (seconds > 6'b0)
        seconds <= seconds - 1;
    end 
	 else begin
      count <= count + 1;
    end
  end

endmodule