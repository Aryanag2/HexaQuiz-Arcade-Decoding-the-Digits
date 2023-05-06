module HexCalcStateMachine (
  input logic clk,
  input logic reset,
  input logic choose,
  input logic [9:0]   SW,
  input logic rem,
  output logic [2:0] state,
  output logic time_check
);
  // Define the states
   enum logic [2:0] {
    MAIN_MENU,
    EASY_DIFFICULTY,
    MEDIUM_DIFFICULTY,
    HARD_DIFFICULTY,
	 TRY_AGAIN,
    LEADERBOARD} GameState, Next_state;
  
  //logic [2:0] currentState;
  
  // FSM always block
  always_ff @(posedge clk) begin
    if (reset) 
      GameState <= MAIN_MENU;
    else
		GameState <= Next_state;
	end
	 
always_comb
	begin 

	Next_state = GameState;
	//logic to be added
	state = 3'b1;
	time_check = 1'b0;
      unique case (GameState)
        MAIN_MENU:
          if (choose == 1'b0) begin
				if (SW == 9'b1)
					Next_state = EASY_DIFFICULTY;
				else if (SW == 9'd2)
					Next_state = MEDIUM_DIFFICULTY;
				else if (SW == 9'd3)
					Next_state = HARD_DIFFICULTY;
				else
					Next_state = TRY_AGAIN;
          end
			TRY_AGAIN:
          if (choose == 1'b0) begin
				if (SW == 9'b1)
					Next_state = EASY_DIFFICULTY;
				else if (SW == 9'd2)
					Next_state = MEDIUM_DIFFICULTY;
				else if (SW == 9'd3)
					Next_state = HARD_DIFFICULTY;
				else
					Next_state = TRY_AGAIN;
          end
        EASY_DIFFICULTY:
          if (rem == 1) 
            Next_state = LEADERBOARD;
        MEDIUM_DIFFICULTY:
          if (rem == 1) 
            Next_state = LEADERBOARD;
        HARD_DIFFICULTY:
          if (rem == 1) 
            Next_state = LEADERBOARD;
        LEADERBOARD:
		    if (reset) 
            Next_state = MAIN_MENU;
      endcase
		
		case (GameState)
		  MAIN_MENU:
				begin
				state = 3'd1;
				time_check = 1'b1;
				end
		  TRY_AGAIN:
				begin
				state = 3'd2;
				time_check = 1'b1;
				end
        EASY_DIFFICULTY:
				state = 3'd3;
        MEDIUM_DIFFICULTY:
				state = 3'd4;
        HARD_DIFFICULTY:
				state = 3'd5;
        LEADERBOARD:
				state = 3'd6;
      endcase
  end
   
endmodule
