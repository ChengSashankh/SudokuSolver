#include "Header.cpp"

int THEFUNC(int s[9][9])
{
	static int nsols=0;
	
	if(nsols<12) {
		
	detsolve(s);

	if(isfilled(s))
	{
		if(checkifsol(s))
		{printpuz(s); nsols++;}//Sleep(1000);}
		 
		return 1;
	}
	
	int r,c,pos[9],iter=0,scp[9][9];
	int anypos=0,found=0;
	
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++)
		{
			scp[i][j]=s[i][j];
			if(s[i][j]==99&&!found)
		    {r=i;c=j;found=1;}
		}

	if(found)
		anypos=mappos_first(s,r,c,pos);

	if(!anypos)
		return(0);


	for(iter=0;iter<9;iter++)
	{
	    if(pos[iter]!=-1)
	    {

			for(int i=0;i<9;i++)
			for(int j=0;j<9;j++)
				scp[i][j]=s[i][j];

			scp[r][c]=pos[iter];

			THEFUNC(scp);
	    }
	}

	}
	return(1);

}

void solve(char *input,char *output)
{
	int s[9][9];

	getpuzzle(s,input);

	freopen(output,"w",stdout);

	THEFUNC(s);
}

/*
void main()
{

	int s[9][9];

	getpuzzle(s,"Puzzles/PuzzleExt.txt");

	cout<<endl<<"The original puzzle is :"<<endl;

	printpuz(s);
	
	cout<<endl<<"The solutions are:"<<endl;
	
	THEFUNC(s);
	
	solve("Puzzles/Useless.txt","Puzzles/UselessSol.txt");
	
}
*/
