#include<iomanip.h>
#include<math.h>
#include<stdio.h>

void getpuzzle(int s[9][9],char *A)        //gets the given values for the grid and set all other cells to 99
{   
	for(int i=0;i<9;i++)    //set all cells to  99.
	{
		for(int j=0;j<9;j++)
		{
			s[i][j]=99;
		}
	}
	
    int r,c,value,number;
	freopen(A,"r",stdin);

	//cout<<"How many cells do you want to fill?";
	cin>>number;
	int count=0;
	while(count<number)
	{ 	
	//cout<<"Enter from 1 to 9, in order the row, coloumn and value of the cell you want to fill.";
	cin>>r>>c>>value;
	s[r-1][c-1]=value;
	count++;
	
	}
	
}


void setu(int s[9][9][2])             //sets u to 9
{
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			if(s[i][j][0]==99)
			s[i][j][1]=9;
			else
			s[i][j][1]=0;
		}
	}
}

int checkfill(int s[9][9][2])        //check if all are filled. return 1 if filled, else return zero.
{

	int k=1;
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			if(s[i][j][1]==1)       //THis was u[i][j]==1 for some reason O.o. corrected.
			{
				k=0;
				break;
			}
		}
	}
	return k;

}

int chrowcol(int s[9][9][2],int r,int c,int val)
{
	int flag=1;
				
	for(int i=0;i<9;i++)
	{
	
		if( ( (s[i][c][0]==val)&&(i!=r) )||( (s[r][i][0]==val)&&(i!=c) ) )
		flag=0;
	
	}

	return flag;

}

int check3(int s[9][9][2],int r,int c,int val)
{
	int i=r/3;
	int j=c/3;
	int lc1,lc2,lr1,lr2;
	int flag=1;

/*	if((s[r][c][0]!=99)&&(s[r][c][0]==val))
		return(1);
	else if((s[r][c][0]!=99)&&(s[r][c][0]!=val))
		return(0);
*/		
		
	if(i==0)
	{
		lc1=0;
		lc2=2;
	}
	if(i==1)
	{
		lc1=3;
		lc2=5;
	}
	if(i==2)
	{
		lc1=6;
		lc2=8;
	}
	if(j==0)
	{
		lr1=0;
		lr2=2;
	}
	if(j==1)
	{
		lr1=3;
		lr2=5;
	}
	if(j==2)
	{
		lr1=6;
		lr2=8;
	}

	for(int col=lc1;col<=lc2;col++)              //not a mistake. Just goes coloumnwise.
	{
		for(int row=lr1;row<=lr2;row++)
		{
			if( (s[col][row][0]==val)&&( !( (col==r)&&(row==c) ) ) )
			{
				flag=0;
				break;
			}
		}
	}
	
	return flag;
}

void unc(int s[9][9][2],int r,int c)                      //gets indices
{
    
	//Why?? Starts here
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			if(s[i][j][0]!=99)
			{
				s[i][j][1]=0;
			}
		}
	}
	//Why?? Ends here
	if(s[r][c][0]==99)  // filled boxes left untouched
	{
		s[r][c][1]=9;
		
		for(int value=1;value<=9;value++)
		{ 
			if((check3(s,r,c,value)==0)||(chrowcol(s,r,c,value)==0))
			{
				 s[r][c][1]--;
			}
		}
	}

}

int fillgrid(int s[9][9][2])
{
	int value=1,filled=0;


	for(int i=0;i<=8;i++)
	{
		for(int j=0;j<=8;j++)
		{
			if(s[i][j][1]==1)
			{
				for(value=1;value<=9;value++)
				{
					if((check3(s,i,j,value)==1)&&(chrowcol(s,i,j,value)==1))
					{ 
						filled++;
						s[i][j][0]=value;
						s[i][j][1]=0;
					}
				}
			}
		}
	}
  
	return filled;
}

void printpuz(int s[9][9])
{
	for(int i=0;i<9;i++)
 	{
 		for(int j=0;j<9;j++)
		if(s[i][j]==99)
		cout<<"-"<<" ";
		else
		cout<<s[i][j]<<" ";

		cout<<endl;
	}
    cout<<endl;
}

int detsolve(int su[9][9])
{

	 int s[9][9][2];
	 for(int i=0;i<9;i++)
	 {
		for(int j=0;j<9;j++)
		{
			s[i][j][0]=su[i][j];
		}
	 }

	 setu(s);

	 int r=0,c=0;
	 int flags=1;

	//This is func.
	 while(flags>0)
	 {
		for(r=0;r<9;r++)           //maps uncertainity for all cells.
		for(c=0;c<9;c++)
			unc(s,r,c);

		flags=fillgrid(s);
	/*
		for(r=0;r<9;r++)
		{
			for(c=0;c<9;c++)
			{
				if(s[r][c][0]==99)
				s[r][c][1]=9;
				else
				s[r][c][1]=0;
			}
		}
	*/
	//  cout<<"I have filled "<<flags<<" points"<<endl;
	 }

	for(i=0;i<9;i++)
	 {
		for(int j=0;j<9;j++)
		{
			su[i][j]=s[i][j][0];
		}
	 }

	 //I am the danger.
	int solution=1;
	for(r=0;r<9;r++)           //maps uncertainity for all cells.
	for(c=0;c<9;c++)
	{
		unc(s,r,c);
		if(s[r][c][1]==0)
			solution=0;
	}
	return solution;
}

int checkifsol(int su[9][9])
{
	 int s[9][9][2];

	 for(int i=0;i<9;i++)
	 {
		for(int j=0;j<9;j++)
		{
			s[i][j][0]=su[i][j];
		}
	 }
	for(i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			if(	(chrowcol(s,i,j,s[i][j][0])==0)||(check3(s,i,j,s[i][j][0])==0)	)
			return(0);
		}
	}

	return(1);
}

int mappos_first(int su[9][9],int r,int c,int pos[9])
{
	 int s[9][9][2],count=0;
	 int shazam=0;

	 for(int i=0;i<9;i++)
	 {
	    pos[i]=-1;

		for(int j=0;j<9;j++)
		{
			s[i][j][0]=su[i][j];
		}
	 }

	for(int value=1;value<10;value++)
	{		                                                               //sets from 1 only. Does not include the first plane. Notice that count++ comes before the set command.
		if((check3(s,r,c,value)==1)&&(chrowcol(s,r,c,value)==1))
		{
			pos[count]=value;
			count++;
			shazam=1;
		}
	}

	return(shazam);
}

int isfilled(int s[9][9])
{
	int flag=1;

	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			if(s[i][j]==99)
			flag=0;
		}
	}
	return flag;
}
/*
void main()
{
	int s[9][9];

	int poss[9];

	getpuzzle(s);

	mappos_first(s,0,2,poss);

	for(int i=0;i<9;i++)
	{
		cout<<poss[i]<<endl;
	}
	printpuz(s);
	
	cout<<"The puzzle has been solved? :"<<checkifsol(s)<<endl;
	
	detsolve(s);
	
	printpuz(s);
	
	cout<<"The puzzle has been solved? :"<<checkifsol(s)<<endl;
}
*/
