#include <stdio.h>

int main(){
	FILE* fp = NULL;
	fopen(&fp,"data.txt","wt");
	
	fprintf(fp,"%d %d %d",100,100,100);
	fprintf(fp,"%d %d %d",100,100,100);
	
	fclose(fp);
	
}
