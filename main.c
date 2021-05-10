#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void initialize_ctop(int p[8]);
int choose_players();
void print_instructions(int g);
int first_player(int g);
void initialize_panel(char pan[8][8]);
void print_panel(char pan[8][8]);
int ask_pos(int p[2],int a);
int computer(char pan[8][8],int p[2],int a,const int ctp[8]);
int play(char pan[8][8],const int ctp[8],int row,int check,int *position);
void initialize_p(char pan[8][8],char panel[8][8]);
int random_num(int panel[8]);
int check(int a,int array[8]);
void create_panel(char pan[8][8],int p[2],int t);
int check_situation(char pan[8][8],int pos[2],int check);
void check_hor(char pan[8][8],int *win,int pos[2],int check);
void check_vert(char pan[8][8],int *win,int pos[2],int check);
void check_rdiag(char pan[8][8],int *win,int pos[2],int check);
void check_ldiag(char pan[8][8],int *win,int pos[2],int check);
void print_result(int win,int g,int p[2],int count);
void next_player(int *t,int g);
void new_game(char ng[5]);

int main(int argc, char *argv[]) {
	char panel[8][8];
	char newgame[5];
	int i,j,counter=0;
	int pos[2];
	int turn,winner;
	int players=0;
	int ctop[8]; 
	
	do{
		initialize_ctop(ctop);
		
		players=choose_players();
		print_instructions(players);
		turn=first_player(players);
		
		initialize_panel(panel);
		print_panel(panel);
		
		for(i=6;i>-1;i+=-1){
			for(j=0;j<7;j++){
				if(players==2)
					pos[1]=ask_pos(pos,i);
				if(players==1){
					if(turn==1){
						pos[1]=ask_pos(pos,i);
						ctop[pos[1]]=-1;
					}
						
					if(turn==2){
						pos[1]=computer(panel,pos,i,ctop);
						ctop[pos[1]]=-1;
					}
				}
				create_panel(panel,pos,turn);
				print_panel(panel);
				winner=check_situation(panel,pos,4);
				if(pos[0]==0)
					counter++;
				print_result(winner,players,pos,counter);
				if(winner!=0)
					break;
				next_player(&turn,players);
			}
			if(winner!=0)
				break;
			initialize_ctop(ctop);
		}
		
		new_game(newgame);
	}while(!strcmp(newgame,"yes"));
	
	return 0;
}

void initialize_ctop(int a[8]){
	int i;
	
	for(i=0;i<8;i++)
		a[i]=i;
}

int choose_players(){
	int game=0;
	
	printf("Enter '1' for one player against computer.\n");
	printf("Enter '2' for two players.\n\n");
	printf("How many players on game?:");
	scanf("%d",&game);
	
	return game;
}

void print_instructions(int g){
	if(g==1){
		printf("\n\n");
		printf("Player 1 plays with symbol '*'.\n");
		printf("Computer plays with symbol '+'.\n");
		printf("Enter 1 to play first player 1.\n");
		printf("Enter 2 to play first computer.\n\n\n");
	}
	
	if(g==2){
		printf("\n\n");
		printf("Player 1 plays with symbol '*'.\n");
		printf("Player 2 plays with symbol '+'.\n");
		printf("Enter 1 to play first player 1.\n");
		printf("Enter 2 to play first player 2.\n\n\n");
	}
}

int first_player(int g){
	int turn;
	char plf[2][10]={"Player 1","Computer"};
	
	if(g==1){
		printf("Which player plays first?:");
		scanf("%d",&turn);
		printf("\n\n");
		printf("%s plays first.",plf[turn-1]);
		printf("\n\n\n");
	}
	if(g==2){
		printf("Which player plays first?:");
		scanf("%d",&turn);
		printf("\n\n");
		printf("Player %d plays first.",turn);
		printf("\n\n\n");
	}
		
	return turn;
}

void initialize_panel(char pan[8][8]){
	int i,j;
	
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			pan[i][j]='-';
		}
	}
}

void print_panel(char pan[8][8]){
	int i,j;
	
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			printf("%c  ",pan[i][j]);
		}
		printf("\n\n");
	}
}

int ask_pos(int p[2],int a){
	int position;
	
	p[0]=a;
	
	printf("\nEnter position to play:");
	scanf("%d",&position);
	printf("\n");
	
	return position;
}

int computer(char pan[8][8],int p[2],int a,const int ctp[8]){
	int i,position=0;
	int result=-1;
	
	p[0]=a;
	printf("\nComputer plays.\n\n\n");
	
	for(i=4;i>1;i+=-1){
		result=play(pan,ctp,a,i,&position);
		if(result==2 || result==1)
			break;
	}
	
	if(result==0)
		position=random_num(ctp);
		
	return position;
}

int play(char pan[8][8],const int ctp[8],int row,int check,int *position){
	char panel[8][8];
	int pos[2];
	int i,win=0;
	
	pos[0]=row;
	
	for(i=0;i<7;i++){
		initialize_p(pan,panel);
		if(ctp[i]!=-1){
			pos[1]=ctp[i];
			create_panel(panel,pos,2);
			win=check_situation(panel,pos,check);
			if(win==2){
				*position=pos[1];
				break;
			}
		}
	}
	
	if(win==0){
		
		for(i=0;i<8;i++){
			initialize_p(pan,panel);
			if(ctp[i]!=-1){
				pos[1]=ctp[i];
				create_panel(panel,pos,1);
				win=check_situation(panel,pos,check);
				if(win==1){
					*position=pos[1];
					break;
				}
			}
		}
	}
		
	return win;
}

void initialize_p(char pan[8][8],char panel[8][8]){
	int i,j;
	
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			panel[i][j]=pan[i][j];
		}
	}
}

int random_num(int panel[8]){
	int random;
	
	srand(time(NULL));
	random=(rand()%7);
	while(check(random,panel)){
		random=(rand()%7);
	}
	
	return random;
}

int check(int a,int array[8]){
	int i,pointer=1;
	
	for(i=0;i<8;i++){
		if(array[i]==a)
			pointer=0;
	}
	
	return pointer;
}

void create_panel(char pan[8][8],int p[2],int t){
	int i,j;
	if(t==1)
		pan[p[0]][p[1]]='*';
	else
		pan[p[0]][p[1]]='+';
		
}

int check_situation(char pan[8][8],int pos[2],int check){
	int win=0;
	int row,col;
	
	row=pos[0];
	col=pos[1];
	
	check_hor(pan,&win,pos,check);
	if(row<(-check+8)){
		check_vert(pan,&win,pos,check);
		if(col>(check-2) & col<(check+3))
			check_rdiag(pan,&win,pos,check);
		if(col<(-check+8) & col>(-check+3))
			check_ldiag(pan,&win,pos,check);
	}
	
	return win;
}

void check_hor(char pan[8][8],int *win,int pos[2],int check){
	int i,j,counter=0;
	int counter1=0;
	int row,col;
	
	row=pos[0];
	col=pos[1];
	
	for(i=0;i<(-check+8);i++){
		counter=0;
		counter1=0;
		for(j=i;j<(i+check);j++){
			if(pan[row][j]=='*')
				counter++;
				
			if(pan[row][j]=='+')
				counter1++;
		}
		
		if(counter==check){
			*win=1;
			break;
		}
			
		if(counter1==check){
			*win=2;
			break;
		}
	}
}

void check_vert(char pan[8][8],int *win,int pos[2],int check){
	int i,counter=0;
	int counter1=0;
	int row,col;
	
	row=pos[0];
	col=pos[1];
	
	for(i=row;i<row+check;i++){
		if(pan[i][col]=='*')
			counter++;
			
		if(pan[i][col]=='+')
			counter1++;
	}
	
	if(counter==check)
		*win=1;
	
	if(counter1==check)
		*win=2;
}

void check_rdiag(char pan[8][8],int *win,int pos[2],int check){
	int i,counter=0;
	int counter1=0;
	int row,col;
	
	row=pos[0];
	col=pos[1];
	
	for(i=col;i>col-check;i+=-1){
		if(pan[row][i]=='*')
			counter++;
			
		if(pan[row][i]=='+')
			counter1++;
			
		row++;
	}
	
	if(counter==check)
		*win=1;
		
	if(counter1==check)
		*win=2;
}

void check_ldiag(char pan[8][8],int *win,int pos[2],int check){
	int i,counter=0;
	int counter1=0;
	int row,col;
	
	row=pos[0];
	col=pos[1];
	
	for(i=col;i<col+check;i++){
		if(pan[row][i]=='*')
			counter++;
			
		if(pan[row][i]=='+')
			counter1++;
			
		row++;
	}
	
	if(counter==check)
		*win=1;
		
	if(counter1==check)
		*win=2;
}

void print_result(int win,int g,int p[2],int count){
	if(win==1)
		printf("\n\nPlayer 1 is the winner of this round!");
	if(win==2){
		if(g==1)
			printf("\n\nComputer is the winner of this round!");
		if(g==2)
			printf("\n\nPlayer 2 is the winner of this round!");
	}
	if(win==0 & p[0]==0 & count==7)
		printf("\n\nDraw!");
}

void next_player(int *t,int g){
	char plf[2][10]={"Player 1","Computer"};
	
	if(*t==1)
		*t=2;
	else
		*t=1;
	
	if(g==1 & *t==1)
		printf("\nPlayer 1 plays.\n\n");
	
	if(g==2)
		printf("\nPlayer %d plays.\n",*t);
}

void new_game(char ng[5]){
	printf("\n\nEnter 'yes' to go on for another round.");
	printf("\nEnter 'no' to exit.");
	printf("\n\nDo you want to go on for another round?:");
	scanf("%s",ng);
	printf("\n\n");
}
