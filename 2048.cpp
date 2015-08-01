#include <bits/stdc++.h>
using namespace std;

class game2048{
	const static int len=4;
	int board[len][len];
	public :
		bool reproduce=false;
		void init();
		void printBoard();
		void addRandom();
		bool isOver();
		void slide(bool,bool,bool,bool,int);
		void moveRight();
		void moveLeft();
		void moveUp();
		void moveDown();
	};
void game2048 :: init(){
	for(int i=0;i<len;i++)
		for(int j=0;j<len;j++)
			board[i][j]=0;
	int p=rand()%len,q=rand()%len;//select first rand pos in initial board
	//p=1;q=0;
	board[p][q]=2;
	//cout<<p<<" "<<q<<"\n";
	q=(rand()+5)%len,p=(rand()+7)%len;// add 5 and 7 so that the prev and cur number dont match 
									// and only 5 and 7 bcoz these are in different on %4
									//like 6 6 than 2 2 than 7 9 than 3 1.. got it ?
									// ithink it will avoid any collision..
										//select second rand pos in initial board
	//p=2;q=0;
	board[p][q]=2;
	//cout<<p<<" "<<q<<"\n";
	}
void game2048 :: printBoard(){
	cout<<"\n\n\n\n\t\t";
	for(int i=0;i<len;i++){
		for(int j=0;j<len;j++){
			cout<<setw(4)<<board[i][j]<<"  ";
			}
		cout<<"\n\t\t";
		}
	cout<<"\n\n";
	}
void game2048 :: addRandom(){
	vector<pair<int,int> >vec;
	for(int i=0;i<len;i++){
		for(int j=0;j<len;j++){
			if(board[i][j]==0)vec.push_back(make_pair(i,j));
			}
		}
	int temp=vec.size();
	temp = (rand()+892389)%temp;
	int k,l;
	k=vec[temp].first;
	l=vec[temp].second;
	//cout<<k<<l<<"\n";
	board[k][l] = (rand()%10 < 7)?2:4;
	vec.clear();
	}
bool game2048 :: isOver(){
	for(int i=0;i<len;i++)
	if(board[i][0]==0)return false;
	else if(i<len-1 && board[i][0]==board[i+1][0])return false;
	// i know it looks bad yeah.. bear with it.. :D or improve..
	for(int i=0;i<len;i++)
	if(board[0][i]==0)return false;
	else if(i<len-1 && board[0][i]==board[0][i+1])return false;
	
	for(int i=0;i<len;i++)
	if(board[i][len-1]==0)return false;
	else if(i<len-1 && board[i][len-1]==board[i+1][len-1])return false;
	
	for(int i=0;i<len;i++)
	if(board[len-1][i]==0)return false;
	else if(i<len-1 && board[len-1][i]==board[len-1][i+1])return false;
	
	for(int i=0;i<len-1;i++){
		for(int j=1;j<len-1;j++){
			if(board[i][j]==0)return false;
			if(board[i][j]==board[i][j-1])return false;
			if(board[i][j]==board[i][j+1])return false;
			if(board[i][j]==board[i+1][j])return false;
			if(board[i][j]==board[i-1][j])return false;
			}
		}
	return true;
	}
void game2048 :: slide(bool left,bool right,bool up, bool down,int pos){
	if(left){
		for(int i=0;i<len;i++){
			int j=i;
			while(board[pos][j]==0 && j<len)j++;
			if(board[pos][i]!=board[pos][j] && j<len)
			reproduce=true,swap(board[pos][i],board[pos][j]);
			}
		for(int i=0;i<len;i++){
			if(i<len-1)if(board[pos][i]==board[pos][i+1] && board[pos][i]!=0)
			reproduce=true,board[pos][i]*=2,board[pos][i+1]=0,i+=2;
			}
		for(int i=0;i<len;i++){
			if(board[pos][i]>0)continue;
			int j=i;
			while(board[pos][j]==0 && j<len){j++;}
			if(j<len)swap(board[pos][i],board[pos][j]);
			}
		}
	else if(right){
		for(int i=len-1;i>=0;i--){
			int j=i;
			while(board[pos][j]==0 && j>=0)j--;
			if(board[pos][i]!=board[pos][j] && j>=0)
			reproduce=true,swap(board[pos][i],board[pos][j]);//cout<<i<<j<<pos<<"rep\n";
			}
		for(int i=len-1;i>=0;i--){
			if(i>0)if(board[pos][i]==board[pos][i-1] && board[pos][i]!=0)//basically board[i][pos]!=0
					//is to handle cases like 
					//0 0 0 0
					//2 0 0 0
					//2 0 0 0
					//0 0 0 0
			reproduce=true,board[pos][i]*=2,board[pos][i-1]=0,i-=2;
			}
		for(int i=len-1;i>=0;i--){
			if(board[pos][i]>0)continue;
			int j=i;
			while(board[pos][j]==0 && j>=0){j--;}
			if(j>=0)swap(board[pos][i],board[pos][j]);
			}
		}
	else if(up){
		for(int i=0;i<len;i++){
			int j=i;
			while(board[j][pos]==0 && j<len)j++;
			if(board[i][pos]!=board[j][pos] && j<len)
			reproduce=true,swap(board[i][pos],board[j][pos]);
			}
		for(int i=0;i<len;i++){
			if(i<len-1)if(board[i][pos]==board[i+1][pos] && board[i][pos]!=0)
			reproduce=true,board[i][pos]*=2,board[i+1][pos]=0,i+=2;
			}
		for(int i=0;i<len;i++){
			if(board[i][pos]>0)continue;
			int j=i;
			while(board[j][pos]==0 && j<len){j++;}
			if(j<len)swap(board[i][pos],board[j][pos]);
			}
		}
	else if(down){
		for(int i=len-1;i>=0;i--){
			int j=i;
			while(board[j][pos]==0 && j>=0)j--;
			if(board[i][pos]!=board[j][pos] && j>=0)
			reproduce=true,swap(board[i][pos],board[j][pos]);
			}
		for(int i=len-1;i>=0;i--){
			if(i>0)if(board[i][pos]==board[i-1][pos] && board[i][pos]!=0)
			reproduce=true,board[i][pos]*=2,board[i-1][pos]=0,i-=2;
			}
		for(int i=len-1;i>=0;i--){
			if(board[i][pos]>0)continue;
			int j=i;
			while(board[j][pos]==0 && j>=0){j--;}
			if(j>=0)swap(board[i][pos],board[j][pos]);
			}
		}
	}
void game2048 :: moveLeft(){
	for(int i=0;i<len;i++){
		slide(1,0,0,0,i);
		}
	}
void game2048 :: moveRight(){
	for(int i=0;i<len;i++){
		slide(0,1,0,0,i);
		}
	}
void game2048 :: moveUp(){
	for(int i=0;i<len;i++){
		slide(0,0,1,0,i);
		}
	}
void game2048 :: moveDown(){
	for(int i=0;i<len;i++){
		slide(0,0,0,1,i);
		}
	}
int main(){
	srand(time(0)); // seed rand() algo
	game2048 play;
	play.init();
	char c;
	play.printBoard();
	//gotoxy(5,3);
	//cout<<"HELLO WORLD";
	while(true){
		system("stty raw");
		cin>>c;
		system("stty cooked");
		//c=getchar();
		switch(c){
			case 97 :// 'a'
				play.moveLeft();
				break;
			case 100 :// 'd'
				play.moveRight();
				break;
			case 119 :// 'w'
				play.moveUp();
				break;
			case 115 :// 's'
				play.moveDown();
				break;
			case 'q' :
				return 0;
			}
		system("clear");
		if(play.reproduce)play.addRandom();
		play.reproduce=false;
		play.printBoard();
		if(play.isOver()){cout<<"GAME OVER";return 0;}
		}
	return 0;
	}
