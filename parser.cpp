#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	char line1[1024] = {' '};
	char line2[1024] = {'*'};
	char line3[1024] = {'*'};
	int stackcount = 0;

	int maxheight;
	bool sflag [10] = {true};

	fgets(line1, 1024, stdin);
	fgets(line2, 1024, stdin);
	fgets(line3, 1024, stdin);

	maxheight = atoi(line1);

	//gives flag for not important stacks and number of stacks example stackcount = 3 then i have [0,1,2]
	for(int i=0; i<1024; i++){
		if(line3[i]=='*'){
			stackcount++;
			break;
		}
		if(line3[i]=='x' && (line3[i+1]==';' || line3[i+1]=='*')){
			sflag[stackcount]=false;
		}
		if(line3[i]==';'){
			stackcount++;
		}
	}
	//stack matrix
	char stacks[maxheight][stackcount];
	int itemcount = 0;
	
	for(int x=0; x<stackcount; x++){
		for(int y=0; y<1024; y++){
			if(itemcount==(maxheight-1) || line2[y]==';' || line2[y]=='*'){
				break;
			}
			if(line2[y]!='(' ||line2[y]!=' ' || line2[y]!=';' || line2[y]!='*' || line2[y]!=','){
				stacks[itemcount][x]=line2[y];
				itemcount++;
			}
		}
		itemcount=0;
	}



	return 0;
}