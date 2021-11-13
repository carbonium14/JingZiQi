#include<windows.h>
#include<iostream>
#include<cstring>
using namespace std;
enum players {computer,human,draw,none};
const int iswin[8][3]={{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
class ttt
{
	public:
		ttt(){p=rand()%2;reset();};
		void play();
	private:
		void reset()
		{
			for(int i=0;i<9;i++) 
			{
				field[i]=none;
			}
		}
		void drawgrid()
		{
			system("cls");
			COORD c={0,2};
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
			cout << " 1 | 2 | 3 " << endl;
        	cout << "---+---+---" << endl;
        	cout << " 4 | 5 | 6 " << endl;
        	cout << "---+---+---" << endl;
        	cout << " 7 | 8 | 9 " << endl << endl << endl;
        	int f=0;
        	for(int y=0;y<5;y+=2)
        	{
        		for(int x=1;x<11;x+=4)
        		{
        			if(field[f]!=none)
        			{
        				COORD c={(short)x,(short)(y+2)};
        				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
        				string o=(field[f]==computer?"x":"o");
        				cout<<o;
					}
					f++;
				}
			}
			c.Y=9;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
		}
		int checkvectory()
		{
			for(int i=0;i<8;i++)
			{
				if(field[iswin[i][0]]!=none&&field[iswin[i][0]]==field[iswin[i][1]]&&field[iswin[i][1]]==field[iswin[i][2]])
				{
					return field[iswin[i][0]];
				}
			}
			int i=0;
			for(int f=0;f<9;f++)
			{
				if(field[f]!=none)
				{
					i++;
				}
			}
			if(i==9)
			{
				return draw;
			}
			return none;
		}
		void gethumanmove()
		{
			int m;
			cout<<"enter your move(1-9)";
			while(1)
			{
				m=0;
				cin>>m;
				if(field[m-1]!=none)
				{
					cout<<"try again"<<endl;
				}
				else
				{
					break;
				}
			}
			field[m-1]=human;
		}
		void getcomputermove()
		{
			int move=0;
			do
			{
				move=rand()&9;
			}while(field[move]!=none);
			bool canmove=false;
			for(int i=0;i<8;i++)
			{
				int try1=iswin[i][0];
				int try2=iswin[i][1];
				int try3=iswin[i][2];
				if(field[try1]!=none&&field[try1]==field[try2]&&field[try3]==none)
				{
					move=try3;
					canmove=true;
					if(field[try1]==computer)
					{
						break;
					}
				}
				if(field[try1]!=none&&field[try1]==field[try3]&&field[try2]==none)
				{
					move=try2;
					canmove=true;
					if(field[try3]==computer)
					{
						break;
					}
				}
				if(field[try2]!=none&&field[try2]==field[try3]&&field[try1]==none)
				{
					move=try1;
					canmove=true;
					if(field[try2]==computer)
					{
						break;
					}
				}
				if(canmove==false)
				{
					if(field[try1]==none)
					{
						move=try1;
					}
					else if(field[try2]==none)
					{
						move=try2;
					}
					else if(field[try3]==none)
					{
						move=try3;
					}
				}
			}
			field[move]=computer;
		}
		int p;
		int field[9];
};
void ttt::play()
{
	int res=draw;
	while(1)
	{
		drawgrid();
		while(1)
		{
			if(p)
			{
				gethumanmove();
			}
			else
			{
				getcomputermove();
			}
			drawgrid();
			res=checkvectory();
			if(res!=none)
			{
				break;
			}
			++p%=2;
		}
		if(res==human)
		{
			cout<<"human win!"<<endl;
		}
		else if(res==computer)
		{
			cout<<"computer win!"<<endl;
		}
		else
		{
			cout<<"draw"<<endl;
		}
		cout<<endl<<endl;
		string r="";
		cout<<"play again(Y/N)?"<<endl;
		cin>>r;
		if(r!="Y"&&r!="y")
		{
			return;
		}
		++p%=2;
		reset();
	}
}
int main()
{
	srand(GetTickCount());
	ttt tic;
	tic.play();
	return 0;
} 
