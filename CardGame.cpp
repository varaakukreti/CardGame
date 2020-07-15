
#include<iostream>
#include<stdlib.h>
using namespace std ;
#define MAX 24
class cards//class cards
{
	//instance variables
	string num ;
	string type ;
public:
	friend class stack ;//friend class stack
	friend class list ;//friend class list
	cards()//default constructor
	{
		num = "";
		type = "" ;
	}
};
class stack//class stack
{
	//instance variables
	cards stk[MAX] ;
	int top ;

public:
	friend class node ;//friend class
	stack()//default constructor
	{
		top = -1 ;
	}
	//functions
	void push(cards c) ;
	cards pop() ;
	bool isempty() ;
	void shuffle();
	void add();
	void display();
};
void stack::add()//function definition od add
{
	cards c;
	string str;
	for(int i=1;i<5;i++)//deciding type of cards
	{
		switch(i)
		{
		case 1:
			c.type="Heart";
			break;
		case 2:
			c.type="Spade";
			break;
		case 3:
			c.type="Diamond";
			break;
		case 4:
			c.type="Club";
			break;
		}
		for(int j=8;j<14;j++)//deciding numbers of cards
		{


			switch(j)
			{
			case 11:
				c.num="Jack";
				break;
			case 12:
				c.num="Queen";
				break;
			case 13:
				c.num="King";
				break;
			default:
				str= to_string(j);
				c.num=str;
				break;
			}
			push(c);

		}
	}
}
void stack::shuffle()//function defination of shuffle
{
	stack A,B ,C;
	cards s1,s2;
	int random1,random2;
	int i=1;
	int j=1;
	for(i=1;i<50;i++)
	{
		do{
			random1=rand()%13+1;//generating random no to shuffle cards
			random2=rand()%10+1;
		}while(random1+random2>20);
		for(j=1;j<=random1;j++)//using three stacks cards are shuffled
		{
			s1=pop();
			A.push(s1);
		}
		for(int k = 1 ; k<random2 ; k++)
		{
			s1=pop();
			B.push(s1);
		}
		while(!isempty())
		{
			s2=pop();
			C.push(s2);
		}
		while(!B.isempty())
		{
			s2=B.pop();
			push(s2);
		}
		while(!C.isempty())
		{
			s2=C.pop();
			push(s2);
		}
		while(!A.isempty())
		{
			s2=A.pop();
			push(s2);
		}

	}
}
void stack::push(cards c)//pushing cards on stack
{
	top++ ;
	stk[top]=c ;
}
bool stack::isempty()//function defination of isempty
{
	if(top==-1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
cards stack::pop()//function defination of pop
{
	cards c1;
	if(isempty())
	{
		cout<<"No Cards Left!";
		return c1;
	}
	else
	{
		c1=stk[top];
		top--;
		return(c1);
	}
}
void stack::display()//function defination of display
{
	cards c2;
	while(!isempty())
	{
		c2=pop();
		cout<<c2.num<<"  "<<c2.type<<endl;
	}
}
class node//class node
{
	//instance variables
	string ltype ;
	string lnum ;

	node *next ;
	node *prev ;
public:
	node()//default constructor
{
		next = NULL ;
		prev = NULL ;
}
	friend class list ;//friend class

};
class list//class list
{
	node *head[5] ;//array for cards of each player
public:
	list()//default constructor
{
		for(int j=0;j<5;j++)
		{
			head[j]=NULL ;
		}
}
	//function declaration
	void distribute(stack s) ;
	void pairs() ;
	int count(int g) ;
	void play() ;
	void winner();
	void displayl();
};
void list::winner()//function defination of winner
{
	cout<<"Enter winner"<<endl;
	int i,j,k;
	int sum=0;
	node *ptr;
	int x;
	int max;
	for(int m=0;m<3;m++)
	{
		cout<<"Enter for"<<endl;
		ptr=head[m];
		sum=0;
		while(ptr!=NULL)//assigning value for each card
		{
			if(ptr->lnum=="King")
			{
				x=13;
			}
			else if(ptr->lnum=="Queen")
			{
				x=12;
			}
			else if(ptr->lnum=="Jack")
			{
				x=11;
			}
			else if(ptr->lnum=="10")
			{
				x=10;
			}
			else if(ptr->lnum=="9")
			{
				x=9;
			}
			else if(ptr->lnum=="8")
			{
				x=8;
			}
			sum=sum+x;//calculating total of values of cards of each player
			ptr=ptr->next;
		}
		//finding maximum among sum
		if(m==0)
		{
			i=sum;
			cout<<"i"<<i<<endl;
		}
		else if(m==1)
		{
			j=sum;
			cout<<"j"<<j<<endl;
		}
		else
		{
			k=sum;
			cout<<"k"<<k<<endl;
		}
	}
	if(i>=j &&i>=k)
	{
		max=i;
	}
	else if(k>=i && k>=j)
	{
		max=k;
	}
	else if(j>=i && j>=k)
	{
		max=j;
	}
	//winner is decided
	if(max==i)
	{
		cout<<" **  Winner is Player 1  **"<<endl;
	}
	if(max==j)
	{
		cout<<" **  Winner is player 2  **"<<endl;
	}
	if(max==k)
	{
		cout<<" **  Winner is Player 3  **"<<endl;
	}
}
void list::distribute(stack s)//distributing cards to players
{

	int i = 0 , j = 0;
	node *temp ;
	node *ptr;
	while(!s.isempty())
	{

		for (i = 0 ; i < 3 ; i++)
		{
			temp= new node() ;
			cards c8=s.pop();
			temp->ltype=c8.type;
			temp->lnum=c8.num;//card popped out is stored in node

			if(head[i]==NULL)
			{
				head[i]=temp ;
			}
			else
			{
				ptr=head[i];
				while(ptr->next != NULL)
				{
					ptr=ptr->next;
				}
				ptr->next=temp;//node is attached to list
				temp->prev = ptr;
			}
			j++ ;
		}
	}
}

void list::pairs( )//finding pairs of cards of every player
{
	node *temp1 ;
	node *temp2 ;
	for(int i = 0 ; i < 3 ; i++)
	{
		node *ptr1 = head[i] ;
		node *ptr2 ;
		while(ptr1->next != NULL)
		{
			ptr2 = ptr1->next ;
			while(ptr2 != NULL)
			{
				if(ptr1->lnum == ptr2->lnum)//matching cards
				{
					if(ptr2->prev == ptr1) //consecutive
					{
						if(ptr1==head[i]) //head
						{
							temp1 = ptr1 ;
							temp2 = ptr2 ;
							ptr1 = ptr2->next ;
							head[i] = ptr1;
							ptr2 = ptr1->next ;
							ptr1->prev = NULL ;
							delete temp1 ;
							delete temp2 ;
						}
						else if(ptr2->next==NULL)//last node
						{
							temp1 = ptr1 ;
							temp2 = ptr2 ;
							ptr1->prev->next = NULL ;

							delete temp1 ;
							delete temp2 ;
						}
						else
						{
							temp1 = ptr1 ;
							temp2 = ptr2 ;
							ptr1->prev->next = ptr2->next ;
							ptr2->next->prev = ptr1->prev ;
							ptr1 = ptr2->next ;
							ptr2 = ptr1->next ;
							delete temp1 ;
							delete temp2 ;
						}
					}
					else //non consecutive
					{
						if(ptr1 == head[i] && ptr2->next == NULL)//first and last node
						{
							temp1=ptr1;
							temp2=ptr2;
							ptr1=ptr1->next;
							head[i]=ptr1;
							ptr2 ->prev->next = NULL ;
							ptr2 = ptr1->next ;//change
							ptr1->prev = NULL ;

							delete temp1 ;
							delete temp2  ;
						}
						else if(ptr1==head[i]) //head
						{
							temp1=ptr1;
							temp2=ptr2;
							ptr1=ptr1->next;
							head[i]=ptr1;
							ptr2->prev->next = ptr2->next ;
							ptr2->next->prev = ptr2 ->prev ;
							ptr2 = ptr1->next ;//change
							ptr1->prev = NULL ;

							delete temp1 ;
							delete temp2  ;
						}

						else if(ptr2->next==NULL)//last node
						{
							temp1=ptr1;
							temp2=ptr2;
							ptr1=ptr1->next;
							ptr2->prev->next=NULL;
							ptr2=ptr1->next;
							delete temp1 ;
							delete temp2 ;
						}
						else{
							temp1 = ptr1 ;
							temp2 = ptr2 ;
							ptr1->prev->next = ptr1->next ;
							ptr1->next->prev = ptr1->prev ;
							ptr2->prev->next = ptr2->next ;
							ptr2->next->prev = ptr2->prev ;
							ptr1 = ptr1->next ;
							ptr2 = ptr1->next ;//change
							delete temp1 ;
							delete temp2 ;
						}
					}
				}
				else
				{
					ptr2 = ptr2 ->next ;
				}
			}
			ptr1 = ptr1->next ;
		}
	}
	//cout<<"----------------  pairs  ----------------"<<endl;
}
void list::displayl()//function defination of display
{
	cout<<"*********       Display      *********"<<endl;
	int i=0;
	node *ptr ;
	for(i=0;i<3;i++)
	{
		cout<<"Player = "<<i+1<<endl ;
		ptr=head[i];
		while(ptr!=NULL)
		{
			cout<<ptr->lnum<<"   "<<ptr->ltype<<endl;

			ptr=ptr->next;
		}
	}

}
int list::count(int g)//counting no of cards of each player
{
	int count1 = 0 ;
	node *ptr ;
	ptr = head[g] ;
	cout<<"g = "<<g<<endl ;
	while(ptr != NULL)
	{
		ptr = ptr->next ;
		count1++ ;
	}
	return count1 ;
}

void list::play()//playing the positioning game
{
	node *temp = new node() ;
	node *ptr ;

	int count2  ;

	int r = 3 ;
	int pos ;
	for(int i = 0 ; i < 3 ; i++ )
	{

		if(head[i]!=NULL)//list is not empty
		{

			if(i==0)
			{
				do
				{

					count2 = count(r-1) ;//counting cards of player from which another player is taking one card
					if(count2 == 0)
					{
						r = r - 1 ;
					}

				}while (count2== 0) ;
				cout<<"No .of cards of player"<<r<<" are : "<<count2<<endl ;
			}
			else
			{

				do
				{
					count2 = count(i-1) ;//counting cards of player from which another player is deleting one card
					if(count2 == 0)
					{
						i-- ;
					}
				}while(count2 == 0) ;
				cout<<"No .of cards of player"<<i<<" are : "<<count2<<endl ;
			}
			do
			{
				cout<<"Player "<<i+1<<" please select a position"<<endl ;
				cin>>pos ;//player is selecting position of card which he want to delete

			}while(pos>count2 || pos<=0 ) ;
			int j;
			int poscount=1;
			if(i==0)
			{
				j=2 ;
				ptr = head[j] ;
			}
			else
			{
				j=i-1;
				ptr = head[j] ;
			}
			//deleting that card
			if(pos == 1)
			{
				temp->lnum = ptr->lnum ;
				temp->ltype=ptr->ltype ;
				head[j]=ptr->next;
				head[j]->prev=NULL;
				delete(ptr);
			}
			else
			{
				while(ptr != NULL)
				{
					if(poscount==pos)
					{
						break;
					}
					ptr=ptr->next;
					poscount++;
				}
				temp->lnum = ptr->lnum ;
				temp->ltype = ptr->ltype ;

				if(poscount == count2)
				{
					ptr->prev->next = NULL ;
					delete ptr ;
				}
				else
				{
					ptr->prev->next = ptr->next ;
					ptr ->next->prev = ptr ->prev ;
					delete ptr ;
				}
			}



		}

	}

}
int main()
{
	char k ;
	int ch = 0 ;
	//string name1 , name2 , name3 ;
	cout<<"\t\tWelcome to World of cards!!!"<<endl;
	cout<<"\n";
	cout<<"Press any key to start the game"<<endl ;
	cin>>k ;
	/*cout<<"Enter name of player 1 = ";
	cin.ignore() ;
	getline(cin,name1) ;
	cout<<"Enter name of player 2 = ";
	cin.ignore() ;
	getline(cin,name2) ;
	cout<<"Enter name of player 3 = ";
	cin.ignore() ;
	getline(cin,name3) ;
	 */
	stack s;
	s.add();
	list l ;

	do
	{
		cout<<"\n";
		cout<<"\t\tLet's Play !!"<<endl;
		do
		{
			cout<<"Press key 1 to shuffle cards"<<endl ;
			cin>>ch ;
			if(ch == 1)
			{
				s.shuffle();
			}
			else
			{
				cout<<"You pressed wrong key.."<<endl ;
				cout<<"Try again"<<endl ;
			}
		}while(ch != 1) ;
		cout<<"Cards are Shuffled !!"<<endl ;
		cout<<"\n" ;
		cout<<"Press key 2 to distribute all the cards "<<endl ;
		cin>>ch ;
		do
		{
			if(ch == 2)
			{
				l.distribute(s) ;
			}
			else
			{
				cout<<"You pressed wrong key.."<<endl ;
				cout<<"Try again"<<endl ;
			}
		}while(ch != 2) ;
		cout<<"\n" ;
		cout<<"Cards are distributed equally !!"<<endl ;
		cout<<"\n" ;

		do
		{
			cout<<"Press key 3 to delete all the pairs of cards of each player "<<endl ;
			cin>>ch ;
			if(ch == 3)
			{
				l.pairs() ;
			}
			else
			{
				cout<<"You pressed wrong key.."<<endl ;
				cout<<"Try again"<<endl ;
			}
		}while(ch != 3) ;
		cout<<"\n" ;
		cout<<"Pairs are deleted !!"<<endl ;
		cout<<"\n" ;
		do
		{
			cout<<"Press key 4 to select position of cards "<<endl ;
			cin>>ch ;
			if(ch == 4)
			{
				l.play() ;
			}
			else
			{
				cout<<"You pressed wrong key.."<<endl ;
				cout<<"Try again"<<endl ;
			}
		}while(ch != 4) ;
		cout<<"\n" ;

		l.winner();
		cout<<"\t!!! Congratulations !!!"<<endl ;
		cout<<"\n" ;
		cout<<"Do you want to play again ?"<<endl ;
		cout<<"Press key 1 to play again and press 0 to quit the game .."<<endl ;
		cin>>ch ;
		if(ch == 0)
		{
			cout<<"Thank You !!"<<endl ;
		}

	}while(ch!=0) ;
	return 0 ;
}
