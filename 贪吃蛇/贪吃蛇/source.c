#include<stdio.h>
#include<stdlib.h>         //malloc
#include<time.h>           //获取系统时间所有函数
#include<conio.h>          //_getch()
#include<Windows.h>        //设置光标信息 malloc

#define Length 20    /*蛇的最大长度*/
#define width  50    /*边界的宽*/
#define higth  30    /*边界的高*/
#define  F1 100      /*1阶段的速度*/
#define  F2 75      /*2阶段的速度*/
#define  F3 50      /*3阶段的速度*/
#define  F4 25      /*4阶段的速度*/

void Remove();
void gameover();

int x0 = 12, y0 = 21;/*起始位置*/
int *px, *py;/*生成节点的坐标*/
int num = 0;/*序号*/


static char *point = "*";/*占用2个单位*/

//蛇的坐标
typedef struct locate
{
	int xx; 
	int yy;
}_locate,*P_locate;
/*定义贪吃蛇的数据结构*/
typedef struct node
{
	int ss; //蛇的序号	
	_locate locate;
	//struct node *next;

}Linksnake;

typedef struct
{
	Linksnake stack[Length];
	int top;
}Stacksnake;

/*初始化蛇*/
void initsnake(Stacksnake *s)
{
	s->top = 0;
}
/*开吃（入栈）*/
void Eatsnake(Stacksnake *s, Linksnake sk)
{
	if (s->top == Length - 1)
	{
		printf_s("恭喜你，成功通关！"); /*如果栈满*/
	}
	else
	{
		s->stack[s->top] = sk;	
		s->top += 1;
	}
}

//移动光标到（x，y）点
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
/*画图-画出系统界面*/
void panitPL()
{
	int i, j, x, y, a[2][4] = { 2,0,0,1,-2,0,0,-1 };
	gotoxy(25, 4);
	printf_s("***********************************操作框**********************************");
	x = 10, y = 6;//起点
	/*上边界10--110，下边界6-36*/
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < width; j++)
		{
			x += a[i][0];
			y += a[i][1];
			gotoxy(x, y);
			printf_s("■");
		}
		for (j = 0; j < higth; j++)
		{
			x += a[i][2];
			y += a[i][3];
			gotoxy(x, y);
			printf_s("■");
		}
		
	}
	gotoxy(20, 38);
	printf_s("开始游戏");
	gotoxy(60, 38);
	printf_s("得分：");
}

/*生成随机坐标*/
P_locate Random()
{
	_locate *L;
	L = (_locate*)malloc(sizeof(_locate));
	srand(time(NULL));//产生时间种子  
	int a = rand() % 98 + 12;//生成X坐标 
	int b = rand() % 30 + 6;//生成y坐标
	L->xx = a;
	L->yy = b;
	gotoxy(a, b);
	printf_s("%s", point);
	return L;
}
/*生成节点*/
//void productsnake()
//{		
//	px = &x0, py = &y0;
//	Random(px, py);
//	gotoxy(x0, y0);
//	printf_s("%s", point);
//}
/*获取新生成节点信息*/
Linksnake getsnakeinfo()
{
	P_locate P;
	Linksnake ls;
	P = Random();
	num += 1;
	ls.ss = num;
	ls.locate = *P;
	return ls;
}
/*选择运动方向*/
void getkey(Stacksnake *sk1, Stacksnake *sk5, Linksnake sk3)
{
	char c; 
	Linksnake S;
	int tag = -1;/*0向右，1向下，2向左，3向上*/
	c = _getch();
	while (1)
	{		
		if (c == -32 || c==13||c==72 || c==75 || c==77 ||c==80)/*是方向键进行操作*/
		{
			switch (c)
			{
			case 13:
			case 77:
				if (tag != 3)
				{
					if (tag == -1)
					{
						S = getsnakeinfo();						
					}
					Remove(sk1, 0);
					gameover(sk1);
					Sleep(400);
					if (sk1->stack[num-1].locate.xx == S.locate.xx && sk1->stack[num-1].locate.yy == S.locate.yy)/*判断是否吃到食物*/
					{
						S.locate.xx = sk1->stack[num - 1].locate.xx + 1;
						Eatsnake(sk1, S);
						S = getsnakeinfo();/*再次生成食物*/
					}
				}
				tag = 0;
				break;/*右*/
			case 72:
				if (tag != 1)
				{
					if (tag == -1)
					{
						S = getsnakeinfo();
					}
					Remove(sk1, 3);
					gameover(sk1);
					Sleep(400);
					if (sk1->stack[num-1].locate.xx == S.locate.xx && sk1->stack[num-1].locate.yy == S.locate.yy)/*判断是否吃到食物*/
					{
						S.locate.yy = sk1->stack[num - 1].locate.yy - 1;
						Eatsnake(sk1, S);
						S = getsnakeinfo();/*再次生成食物*/
					}
					tag = 3;
				}
				break;/*上*/
			case 80:
				if (tag != 3)
				{
					if (tag == -1)
					{
						S = getsnakeinfo();
					}
					Remove(sk1, 1);
					gameover(sk1);
					Sleep(400);
					if (sk1->stack[num-1].locate.xx == S.locate.xx && sk1->stack[num-1].locate.yy  == S.locate.yy)/*判断是否吃到食物*/
					{
						S.locate.yy = sk1->stack[num - 1].locate.yy + 1;
						Eatsnake(sk1, S);
						S = getsnakeinfo();/*再次生成食物*/
					}
					tag = 1;
				}
				break;/*下*/
			case 75:
				if (tag !=0)/*不是开始动且运动方向不是向右*/
				{
					if (tag == -1)
					{
						S = getsnakeinfo();
					}
					Remove(sk1, 2);
					gameover(sk1);
					Sleep(400);
					if (sk1->stack[num-1].locate.xx == S.locate.xx && sk1->stack[num-1].locate.yy == S.locate.yy)/*判断是否吃到食物*/
					{
						S.locate.xx = sk1->stack[num - 1].locate.xx - 1;
						Eatsnake(sk1, S);
						S = getsnakeinfo();/*再次生成食物*/
					}
					tag = 2;
				}
				break;/*左*/
			}
		}
		if (_kbhit())  //有键盘敲击
		{
			c = _getch();
		}
	}
}

/*动起来*/
void Remove(Stacksnake *_sk,int t)
{	
	Stacksnake sk2;
	initsnake(&sk2);
	Linksnake sk0;
	gotoxy(_sk->stack[0].locate.xx, _sk->stack[0].locate.yy);
	printf_s(" ");/*消除第一个点的位置*/
	switch (t)
	{
	case 0:            /*0向右，1向下，2向左，3向上*/
		if (_sk->top == 1)
		{		
			_sk->stack[0].locate.xx = _sk->stack[0].locate.xx + 1;
			_sk->stack[0].locate.yy = _sk->stack[0].locate.yy;
			gotoxy(_sk->stack[0].locate.xx, _sk->stack[0].locate.yy);
			printf_s("%s", point);/*打印新的位置*/
		}
		else
		{
			for (int i = 0; i < num - 1; i++)
			{
				//gotoxy(_sk->stack[i].locate.xx, _sk->stack[i].locate.yy);
				//printf_s(" ");/*消除原来的位置*/
				_sk->stack[i].locate.xx = _sk->stack[i + 1].locate.xx;
				_sk->stack[i].locate.yy = _sk->stack[i + 1].locate.yy;
				gotoxy(_sk->stack[i].locate.xx, _sk->stack[i].locate.yy);
				printf_s("%s", point);/*打印新的位置*/
			}
			_sk->stack[num-1].locate.xx = _sk->stack[num - 1].locate.xx + 1;
			_sk->stack[num-1].locate.yy = _sk->stack[num - 1].locate.yy;
			gotoxy(_sk->stack[num-1].locate.xx, _sk->stack[num-1].locate.yy);
			printf_s("%s", point);/*打印新的位置*/
		}	
		break;
	case 1:
		if (_sk->top == 1)
		{
			//gotoxy(_sk->stack[0].locate.xx, _sk->stack[0].locate.yy);
			//printf_s(" ");/*消除原来的位置*/
			_sk->stack[0].locate.xx = _sk->stack[0].locate.xx;
			_sk->stack[0].locate.yy = _sk->stack[0].locate.yy+1;
			gotoxy(_sk->stack[0].locate.xx, _sk->stack[0].locate.yy);
			printf_s("%s", point);/*打印新的位置*/
		}
		else
		{
			for (int i = 0; i < num - 1; i++)
			{
				//gotoxy(_sk->stack[i].locate.xx, _sk->stack[i].locate.yy);
				//printf_s(" ");/*消除原来的位置*/
				_sk->stack[i].locate.xx = _sk->stack[i + 1].locate.xx;
				_sk->stack[i].locate.yy = _sk->stack[i + 1].locate.yy;
				gotoxy(_sk->stack[i].locate.xx, _sk->stack[i].locate.yy);
				printf_s("%s", point);/*打印新的位置*/
			}
			_sk->stack[num - 1].locate.xx = _sk->stack[num - 1].locate.xx;
			_sk->stack[num - 1].locate.yy = _sk->stack[num - 1].locate.yy + 1;
			gotoxy(_sk->stack[num-1].locate.xx, _sk->stack[num-1].locate.yy);
			printf_s("%s", point);/*打印新的位置*/
		}
		break;
	case 2:
		if (_sk->top == 1)
		{
			//gotoxy(_sk->stack[0].locate.xx, _sk->stack[0].locate.yy);
			//printf_s(" ");/*消除原来的位置*/
			_sk->stack[0].locate.xx = _sk->stack[0].locate.xx - 1;
			_sk->stack[0].locate.yy = _sk->stack[0].locate.yy;
			gotoxy(_sk->stack[0].locate.xx, _sk->stack[0].locate.yy);
			printf_s("%s", point);/*打印新的位置*/
		}
		else
		{
			for (int i = 0; i < num - 1; i++)
			{
				//gotoxy(_sk->stack[i].locate.xx, _sk->stack[i].locate.yy);
				//printf_s(" ");/*消除原来的位置*/
				_sk->stack[i].locate.xx = _sk->stack[i + 1].locate.xx;
				_sk->stack[i].locate.yy = _sk->stack[i + 1].locate.yy;
				gotoxy(_sk->stack[i].locate.xx, _sk->stack[i].locate.yy);
				printf_s("%s", point);/*打印新的位置*/
			}
			_sk->stack[num - 1].locate.xx = _sk->stack[num - 1].locate.xx - 1;
			_sk->stack[num - 1].locate.yy = _sk->stack[num - 1].locate.yy;
			gotoxy(_sk->stack[num-1].locate.xx, _sk->stack[num-1].locate.yy);
			printf_s("%s", point);/*打印新的位置*/
		}
		break;
	case 3:
		if (_sk->top == 1)
		{
			//gotoxy(_sk->stack[0].locate.xx, _sk->stack[0].locate.yy);
			//printf_s(" ");/*消除原来的位置*/
			_sk->stack[0].locate.xx = _sk->stack[0].locate.xx;
			_sk->stack[0].locate.yy = _sk->stack[0].locate.yy - 1;
			gotoxy(_sk->stack[0].locate.xx, _sk->stack[0].locate.yy);
			printf_s("%s", point);/*打印新的位置*/
		}
		else
		{
			for (int i = 0; i < num - 1; i++)
			{
				//gotoxy(_sk->stack[i].locate.xx, _sk->stack[i].locate.yy);
				//printf_s(" ");/*消除原来的位置*/
				_sk->stack[i].locate.xx = _sk->stack[i + 1].locate.xx;
				_sk->stack[i].locate.yy = _sk->stack[i + 1].locate.yy;
				gotoxy(_sk->stack[i].locate.xx, _sk->stack[i].locate.yy);
				printf_s("%s", point);/*打印新的位置*/
			}
			_sk->stack[num - 1].locate.xx = _sk->stack[num - 1].locate.xx ;
			_sk->stack[num - 1].locate.yy = _sk->stack[num - 1].locate.yy - 1;
			gotoxy(_sk->stack[num-1].locate.xx, _sk->stack[num-1].locate.yy);
			printf_s("%s", point);/*打印新的位置*/
		}
		break;
	}
	
}

/*判断gameover*/
void gameover(Stacksnake *p)
{
	int f = 2 * width + 10;
	int g = higth + 6;
	if (num != 1 && ((p->stack[num - 1].locate.yy == p->stack[0].locate.yy)
		&& (p->stack[num - 1].locate.xx == p->stack[0].locate.xx)))
	{
		gotoxy(40, 30);
		printf_s("game over !");
		_getch();
		return;
	}
	if (p->stack[num - 1].locate.xx >= f || p->stack[num - 1].locate.xx <= 11
		|| p->stack[num - 1].locate.yy <= 6 || p->stack[num - 1].locate.yy >= g)
	{
		gotoxy(40, 30);
		printf_s("game over !");
		_getch();
		return;
	}
	
}

void main(void)
{
	Linksnake S;
	Stacksnake ss;
	Stacksnake ss1;
	initsnake(&ss1);
	initsnake(&ss);
	S.locate.xx = x0;
	S.locate.yy = y0;
	S.ss = num;
	
	Eatsnake(&ss,S);
	panitPL();
	gotoxy(S.locate.xx, S.locate.yy);	
	printf_s("%s", point);
	getkey(&ss, &ss1,S);
	_getch();
}