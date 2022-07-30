#include "clui.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

void menu(int& rows , int& cols , int& bombs , int& person);
void init(int rows , int cols , int bombs);
void show(int rows , int cols , int bombs);
void lose(int rows , int cols , int bombs , int person);
void win(int rows , int cols , int bombs , int person);
bool iswon(int rows , int cols , int bombs);
void show(int x , int y , int rows , int cols , int bombs);
void enter(int& rows , int& cols , int& bombs , int& person);

int a[31][31]={0};
char b[31][31];

struct player{
	string name;
	int score = 0;
}p[10] , t;

void bubble_sort(player p[], int size);
void swap(player& a, player& b);

struct save{
	int a[31][31];
	char b[31][31];
	int rows , cols , bombs;
	bool free = true;
}s[4];

void bubble_sort(player p[], int size) {//sort players by their scores(decsending)
	for (int i = 0; i < size-1; i++)
		for (int j = 0; j <size-1-i; j++)
			if (p[j + 1].score > p[j].score)
				swap(p[j], p[j + 1]);
}

void swap(player& a, player& b){
	t = a;
	a = b;
	b = t;
}

void init(int rows , int cols , int bombs){//build map for new game
	srand(time(0));
	
	for(int i=1; i<=bombs; i++){
		int ri = rand() % rows;
		int rj = rand() % cols;
		if(a[ri][rj] == 0) a[ri][rj] = 10;
		else if(a[ri][rj] == 10) i--;
	}
	
	for(int i=0; i<rows ; i++)
		for(int j=0; j<cols ; j++)
			if(a[i][j]==10)
				for(int x=i-1; x<=i+1; x++)
					for(int y=j-1; y<=j+1; y++)
						if(y>=0 && x>=0 && y<cols && x<rows && a[x][y]!=10 && (x!=i || y!=j)) a[x][y]++;
	
	
	for(int i=0; i<rows ; i++){
		for(int j=0; j<cols ; j++){
			b[i][j] = '-';
		}
	}

}

void show(int rows , int cols , int bombs){
	//clea screen and then show map
	clear_screen();
	cout<<"-"; for(int k=0; k<cols; k++) cout<<"----"; cout<<endl;
	for(int i=0; i<rows ; i++){
		for(int j=0; j<cols ; j++){
			if(j==0) {cout<<"| ";}
			else cout<<" | ";
			cout<<b[i][j];
			if(j==cols-1) cout<<" |";
		}
		cout<<endl;
		cout<<"-"; for(int k=0; k<cols; k++) cout<<"----"; cout<<endl;
	}
}

void lose(int rows , int cols , int bombs , int person){//lose and show map with the bombs location
	
	for(int i=0; i<rows ; i++){
		for(int j=0; j<cols ; j++){
			if(a[i][j]==10) b[i][j] = '*';
		}
	}
	show(rows , cols , bombs);
	cout<<"-------------------------------------You Lose-------------------------------------"<<endl;
	cout<<"Your score from this game: "<<0<<endl;
	p[person].score += 0;
	cout<<"Please Wait..."<<endl;
	delay(3000);
	menu(rows , cols , bombs , person);
}

void win(int rows , int cols , int bombs , int person){//win and show map with the bombs location
	
	for(int i=0; i<rows ; i++){
		for(int j=0; j<cols ; j++){
			if(a[i][j]==10) b[i][j] = '*';
		}
	}
	show(rows , cols , bombs);
	cout<<"-------------------------------------You Win-------------------------------------"<<endl;
	cout<<"Your score from this game: "<<bombs<<endl;
	p[person].score += bombs;
	cout<<"please wait..."<<endl;
	delay(3000);
	menu(rows , cols , bombs , person);
}

bool iswon(int rows , int cols , int bombs){//wining conditions
	int foundedbombs=0;
	int emps=0;
	for(int i=0; i<rows; i++)	{
		for(int j=0; j<cols; j++){
			if(b[i][j]=='*'  && a[i][j]==10) foundedbombs++;
			else if(b[i][j]=='-' || b[i][j]=='F' && a[i][j]==10) emps++;
		}
	}
	return (emps==bombs && foundedbombs==0);
}

void show(int x , int y , int rows , int cols , int bombs){
	//show new map
	if(a[x][y]==0){
		b[x][y] = ' ';
		for(int i=x-1; i<=x+1; i++)
			for(int j=y-1; j<=y+1; j++)
				if(i>=0 && i<rows && j>=0 && j<cols && b[i][j]=='-') show(i , j , rows , cols , bombs);
	}
	else if(a[x][y]==1)  b[x][y] = '1';
	else if(a[x][y]==2)  b[x][y] = '2';
	else if(a[x][y]==3)  b[x][y] = '3';
	else if(a[x][y]==4)  b[x][y] = '4';
	else if(a[x][y]==5)  b[x][y] = '5';
	else if(a[x][y]==6)  b[x][y] = '6';
	else if(a[x][y]==7)  b[x][y] = '7';
	else if(a[x][y]==8)  b[x][y] = '8';
	else if(a[x][y]==10) b[x][y] = '*';
	show(rows , cols , bombs);
}

void menu(int& rows , int& cols , int& bombs , int& person){//go to the menu
	cout<<"1. New Game\n2. Load Game\n3. Change Name\n4. Leaderboard\n5. Quit\n";
	int n;
	cin>>n;
	switch(n){
		case 1:
			for(int i=0 ; i<31; i++) for(int j=0; j<31; j++) a[i][j] = 0;
			int level;
			do{
				cout<<"Select level:\n1. Easy(5*5 , 4)\n2. Medium(12*12 , 28)\n3. Hard(20*20 , 96)\n4. Custom\n5. Return to menu\n";
				cin>>level;
				switch(level){
					case 1:
						rows = 5;  cols = 5; bombs = 4;  
						init(rows , cols , bombs);
						show(rows , cols , bombs);
						enter(rows , cols , bombs , person);break;
					case 2:
						rows = 12; cols = 12; bombs = 28;
						init(rows , cols , bombs);
						show(rows , cols , bombs);
						enter(rows , cols , bombs , person); break;
					case 3:
						rows = 20; cols = 20; bombs = 96;
						init(rows , cols , bombs);
						show(rows , cols , bombs);
						enter(rows , cols , bombs , person); break;
					case 4:
						do{
							cout<<"Enter number of rows of the field (less than or equal 20): "; cin>>rows;
							if(rows<=1 || rows>20){
								cout<<"invalid!"<<endl;
								continue;
							}
							else break;
						}while(true);
						do{
							cout<<"Enter number of columns of the field (less than or equal 30): "; cin>>cols;
							if(cols<=1 || cols>30){
								cout<<"invalid!"<<endl;
								continue;
							}
							else break;
						}while(true);
						do{
							cout<<"Enter number of bombs of the field (more than 1 less than "<<rows*cols<<"): "; cin>>bombs;
							if(bombs<=1 || bombs>=(rows * cols)){
								cout<<"invalid!"<<endl;
								continue;
							}
							else break;
						}while(true); 
						init(rows , cols , bombs);
						show(rows , cols , bombs);
						enter(rows , cols , bombs , person);
						break;
					case 5:{
						clear_screen();
						menu(rows , cols , bombs , person);
						break;
					}	
					default : {
						cout<<"Invalid!"<<endl;
						continue;
					}
					break;
				}
			}while(true);
			init(rows , cols , bombs);
			show(rows , cols , bombs);
			enter(rows , cols , bombs , person);
			break;
			 
		case 2:{
			int k;
			do{
				cout<<"1. Slot 1\n2. Slot 2\n3. Slot 3\n4. Slot 4\n5. Return to menu\n"; cin>>k;
				if(k==5){
					clear_screen();
					menu(rows , cols , bombs , person);
				}
				if(k<1 || k>4){
					cout<<"invalid!"<<endl;
					continue;
				}
				else if(s[k-1].free){
					cout<<"Nothing is saved in this slot!"<<endl;
					continue;
				}
				else break;
			}while(true);
			
			rows = s[k-1].rows;
			cols = s[k-1].cols;
			for(int i=0; i<rows; i++) for(int j=0; j<cols; j++) a[i][j] = s[k-1].a[i][j];
			for(int i=0; i<rows; i++) for(int j=0; j<cols; j++) b[i][j] = s[k-1].b[i][j];
			bombs = s[k-1].bombs;
			show(rows , cols , bombs);
			enter(rows , cols , bombs , person);
		}
		
		case 3:{
			string name;
			cout<<"Please enter your nane: "; cin>>name;
			bool isnotfound = true;
			for(int i=0; i<10; i++){
				if(p[i].name == name){
					person = i;
					isnotfound = false;
					break;
				}
			}
			if(isnotfound && person!=9) person++;
			
			else if(isnotfound) person = 0;
			p[person].name = name;
			menu(rows , cols , bombs , person);
			break;
		}
		
		case 4:{
			bubble_sort( p , 10);
			cout<<"Scores: "<<endl;
			for(int i=0; i<5; i++) cout<<"\t"<<i+1<<". "<<p[i].name<<" : "<<p[i].score<<endl ;
			cout<<endl;
			delay(1000);
			menu(rows , cols , bombs , person);
			break;
		}
		
		case 5: quit();
		default :{
			cout<<"Invalid!"<<endl;
			menu(rows , cols , bombs , person);		
		}
	}
}

void enter(int& rows , int& cols , int& bombs , int& person){//choose a home and select it or quit from game and go back to menu
	int cx = 2 , cy = 3; 
	do{
		cursor_to_pos(cx , cy);
		cx = get_cursor_x();
		cy = get_cursor_y();
		char p = getch();
		switch (p){
			case 'a':if ( cy==        3        ) cy = 4*(cols-1) + 3; else cy -= 4; break;
			case 's':if ( cx== 2*(rows-1) + 2  ) cx =       2       ; else cx += 2; break;
			case 'd':if ( cy== 4*(cols-1) + 3  ) cy =       3       ; else cy += 4; break;
			case 'w':if ( cx==        2        ) cx = 2*(rows-1) + 2; else cx -= 2; break;
			case 'f':{
				int ox = (cx-2)/2 + 1;
				int oy = (cy-3)/4 + 1;
				if(b[ox-1][oy-1]=='F') b[ox-1][oy-1]='-';
				else if (b[ox-1][oy-1]=='-') b[ox-1][oy-1]='F';
				show(rows , cols , bombs);
				break;
			}
			case 'o':{
				clear_screen();
				bool  isfreefound = false;
				for(int k=0; k<4; k++){
					if(s[k].free){
						for(int i=0; i<rows; i++) for(int j=0; j<cols; j++) s[k].a[i][j] = a[i][j];
						for(int i=0; i<rows; i++) for(int j=0; j<cols; j++) s[k].b[i][j] = b[i][j];
						s[k].rows = rows;
						s[k].cols = cols;
						s[k].bombs = bombs;
						s[k].free = 0;
						isfreefound = true;
						cout<<"Game has succesfully saved in slot "<<k+1<<"."<<endl;
						break;
					}
				}
				if(! isfreefound){
					int k;
					cout<<"All saveslots are used. Which saveslot do you want to save into? "<<endl;
					do{
						cout<<"Please enter slot: ";
						cin>>k;
						if(k<1 || k>4){
							cout<<"Invalid!"<<endl;
							continue;
						}
						else break;
					}while(true);
					for(int i=0; i<rows; i++) for(int j=0; j<cols; j++) s[k-1].a[i][j] = a[i][j];
					for(int i=0; i<rows; i++) for(int j=0; j<cols; j++) s[k-1].b[i][j] = b[i][j];
					s[k-1].rows = rows;
					s[k-1].cols = cols;
					s[k-1].bombs = bombs;
					s[k-1].free = 0;
					cout<<"Game has succesfully saved in slot "<<k<<"."<<endl;
				}
				menu(rows , cols , bombs , person);
			}	
			case 'q':{
				clear_screen();
				menu(rows , cols , bombs , person);
				break;
			}  break;
			case ' ':
				int ox = (cx-2)/2 + 1;
				int oy = (cy-3)/4 + 1;
				if(b[ox-1][oy-1] != 'F'){
					show(ox-1 , oy-1 , rows , cols , bombs);
					if(a[ox-1][oy-1]==10) {lose(rows , cols , bombs , person); return;}
					else if(iswon(rows , cols , bombs)) {win(rows , cols , bombs , person); return;}
				}	
		}
	}while(true);
}	

int main(){
	int rows , cols , bombs , person = 0;
    init_clui();
	cout<<"-------------------------------------welcome-------------------------------------"<<endl;
	cout<<"Please enter your name: "; cin>>p[person].name;
	menu(rows , cols , bombs , person);
}
