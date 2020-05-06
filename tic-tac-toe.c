#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
#include<time.h> 
//-------------------------GLOBAL VARIABLES------------------
char Winner = '\0';
int x_count = 0;
int o_count = 0;
int user_count = 0;
int computer_count = 0;
//-----------------------------------------------------------
///----------------------FUNCTIONS---------------------------
///----------------------------------------------------------
//displays the board
void display_board(char board[9]){
	printf("%c | %c | %c\n", board[0] ,board[1], board[2]);
	printf("%c | %c | %c\n", board[3] ,board[4], board[5]);
	printf("%c | %c | %c\n", board[6] ,board[7], board[8]);
}
int check_if_tie(char board[9]){
	int i;
	for(i = 0; i < 9; i++){
		if(board[i] == '-')
			return 0;
	}
	return 1;
}

void call_winner(int pos, char board[9]){
  Winner = board[pos];
}

int check_if_win(char board[9]){
  //-----------------------------------
  //-------------CHECK ROWS------------
  //-----------------------------------
  if(((board[0] == board[1] ) && (board[1] == board[2]) && (board[2] =='X')) || ((board[0] == board[1] ) && (board[1] == board[2]) && (board[2] == 'O')) ){
    call_winner(0, board);
    return 1;
  }
  else if (((board[3] == board[4] ) && (board[4] == board[5]) && (board[5] =='X')) || ((board[3] == board[4] ) && (board[4] == board[5]) && (board[5] == 'O')) ){
    call_winner(3, board);
    return 1;
  }
  else if(((board[6] == board[7] ) && (board[7] == board[8]) && (board[8] =='X')) || ((board[6] == board[7] ) && (board[7] == board[8]) && (board[8] == 'O')) ){
    call_winner(6, board);
    return 1;
  }
  //-----------------------------------
  //-------------CHECK COLUMNS---------
  //-----------------------------------
  if(((board[0] == board[3] ) && (board[3] == board[6]) && (board[6] =='X')) || ((board[0] == board[3] ) && (board[3] == board[6]) && (board[6] =='O')) ){
    call_winner(0, board);
    return 1;
  }
  else if (((board[1] == board[4] ) && (board[4] == board[7]) && (board[7] =='X')) || ((board[1] == board[4] ) && (board[4] == board[7]) && (board[7] =='O')) ){
    call_winner(4, board);
    return 1;
  }
  else if(((board[2] == board[5] ) && (board[5] == board[8]) && (board[8] =='X')) || ((board[2] == board[5] ) && (board[5] == board[8]) && (board[8] =='O')) ){
    call_winner(8, board);
    return 1;
  }
  //-----------------------------------
  //-------------CHECK DIAGONALS-------
  //-----------------------------------
  if(((board[0] == board[4] ) && (board[4] == board[8]) && (board[8] =='X')) || ((board[0] == board[4] ) && (board[4] == board[8]) && (board[8] =='O')) ){
    call_winner(0, board);
    return 1;
  }
  else if (((board[2] == board[4] ) && (board[4] == board[6]) && (board[6] =='X')) || ((board[2] == board[4] ) && (board[4] == board[6]) && (board[6] =='O')) ){
    call_winner(4, board);
    return 1;
  }
  //send false since no one wins
  return 0;
}

int check_if_game_over(char board[9]){
	if(check_if_win(board) == 0)
		return check_if_tie(board);
	else
		return 1;
}
//displays score
void display_score(int x_count, int o_count){
	printf("SCORE\nX : %d \nO : %d\n",x_count,  o_count);
}

    
char handle_turn(char current_player, char board[9]){
	//takes valid position and makes changes to the board accordingly
	int position;
	printf("%c's turn to choose a position from 1 to 9 :",current_player);
	scanf("%d", &position);
	position = position-1;
	//handling invalid inputs
	if( position > 8 || position < 0){
		printf("Please enter a valid position!\n");
		return current_player;
	}
	if(board[position] != '-'){
		printf("Position already chosen\n");
		return current_player;
	}
	board[position] = current_player;
	printf("\e[1;1H\e[2J");//clears the screen
	display_board(board);
	//flips the turn
	if(current_player == 'X'){
		return 'O';
	}
	else{
		return 'X';
	}
}


void play_game_multiplayer(char board[9]){
	//display initial empty board
	display_board(board);
	int i;
	char current_player = 'X';
	char a;
	printf("X shall start first!\n");
	while(1){
		current_player = handle_turn(current_player, board);
		if(check_if_game_over(board) == 1)
			break;
		else
			continue;
	}
	//print the results
	if(check_if_tie(board) == 1)
		printf("There was a tie\n");
	//else there was a winner
	else{
		
		printf("%c won the game!! Congratulations %c !!\n", Winner, Winner);
		if(Winner == 'X')
			x_count = x_count + 1;
		else if(Winner == 'O')
			o_count = o_count + 1;
		display_score(x_count, o_count);
	}
	printf("Would you like to play again? (y/n):");
	scanf(" %c", &a);
	if(a == 'y' || a == 'Y'){
		printf("\e[1;1H\e[2J");//clears the screen
		for(i =0; i < 9; i++)
			board[i] = '-';
		play_game_multiplayer(board);
	}
	else{
		printf("Thank you for playing\n");
	}
}


//-------------------------SINGLE PLAYER--------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------

int max(int val1, int val2){
	if(val1 >= val2)
		return val1;
	else
		return val2;
}
int min(int val1, int val2){
	if(val1 > val2)
		return val2;
	else
		return val1;
}
void display_score_single(int user_count,int computer_count){
	printf("SCORE\nX : %d\nO : %d\n",user_count, computer_count);
}

void handle_single_player_turn(char user,char computer, char board[9]){
	int position;	
	printf("Choose a valid position from 1-9 : ");
	scanf("%d", &position);
	bool valid = false;
	while(!valid){
		//Make sure the input is valid
		while(position > 9 || position < 1){
			printf("Choose a valid position from 1-9 : ");
			scanf("%d", &position);
		}
		position = position - 1;
		//Then also make sure the spot is available on the board
		if(board[position] == '-'){
			valid = true;
		}
		else{
			printf("You can't go there. Go again.\n");
			position = 10;
		}
	}
	board[position] = user;
	printf("\e[1;1H\e[2J");//clears the screen
	display_board(board);
}

int minimax(char user, char computer, char board[9], int depth, bool Maximizing_player){
	//first check if the move completes the game
	int score;
	if(check_if_game_over(board) == 1){
		if(check_if_win(board) == 1){
			if(Winner == computer)
				score = 10;
			else
				score = -10;
		}
		else{
			//there was a tie
			score = 0;
		}
		return score;
	}
	else{
		if (Maximizing_player == true) {
			int bestScore = INT_MIN, score, i;
			for (i = 0; i < 9; i++) {
				// getting empty spots
				if (board[i] == '-') {
				  board[i] = computer;
				  score = minimax(user, computer, board, depth + 1, false);
				  board[i] = '-';
				  bestScore = max(score, bestScore);
				}
			}
			return bestScore;
		} 
		else {
			int bestScore = INT_MAX, score, i;
			for (i = 0; i < 9; i++) {
				// getting empty spots
				if (board[i] == '-') {
					board[i] = user;
					score = minimax(user, computer, board, depth + 1, true);
					board[i] = '-';
					bestScore = min(score, bestScore);
				}      
			}
			return bestScore;
		}
	}
}


void handle_computer_turn(char user,char computer,char board[9]){
	int i, bestmove, score;
	int best_score = INT_MIN;
	//checks for empty space where computer can win
	for(i = 0; i < 9; i++){
		if(board[i] == '-'){
			board[i] = computer;
			score = minimax(user, computer, board, 0, false);
			board[i] = '-';
			if(score > best_score){
				best_score = score;
				bestmove = i;
			}
		}
	}
	board[bestmove] = computer;
	printf("\e[1;1H\e[2J");//clears the screen
	display_board(board);
}

void play_game_single_player(char user,char computer,char board[9]){
	display_board(board);
	int i;
	while(1){    
		handle_single_player_turn(user, computer, board);
		if(check_if_game_over(board) == 1)
			break;
		else{
			//computers turn
			handle_computer_turn(user, computer, board);
			if(check_if_game_over(board) == 1)
				break;
		}
	}
	//print the results
	if(check_if_tie(board) == 1)
		printf("There was a tie\n");
	//else there was a winner
	else{
		printf("%c won the game!! Congratulations %c\n" , Winner, Winner);
		if(Winner == 'X')
			user_count = user_count + 1;
		else if(Winner == 'O')
			computer_count = computer_count + 1;
		display_score_single(user_count, computer_count);
	}
	char ans;
	printf("Would you like to play again? (y/n):");
	scanf(" %c", &ans);
	if(ans == 'y' || ans == 'Y'){
		printf("\e[1;1H\e[2J");//clears the screen
		for(i =0; i < 9; i++)
			board[i] = '-';
		play_game_single_player(user, computer, board);
	}
	else
		printf("THANK YOU FOR PLAYING!\n");
}

void start_single_player(char board[9]){
	//entry point for single player game
	char user, computer;
	printf("Choose your player (X / O ):");
	scanf(" %c", &user);
	if(user == 'X' || user == 'x'){
		user = 'X';
		computer = 'O';
	}  
	else{
		user = 'O';
		computer = 'X';
	}
	play_game_single_player(user, computer, board);
}




int main(){
	char board[9] = {'-','-','-','-','-','-','-','-','-'};
	char play;
	printf("Do you want to play singleplayer or multiplayer? (s/m):");
	scanf(" %c", &play);
	if(play == 's' || play == 'S'){
		start_single_player(board);
	}
	else if(play == 'm' || play == 'M'){
		play_game_multiplayer(board);
	}
	
}
