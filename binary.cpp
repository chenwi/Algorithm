 #include<iostream>
 using namespace std;
 
 void chang()
 {
	FILE *in = NULL;
	FILE *out = NULL;

	in=fopen("Text","rb"); 
	out=fopen("FileWrite.txt","wt+"); 

	char s;

	while(!feof(in)) 
	{  
	int c=fgetc(in); 
	sprintf(&s,"%c",c); 
	fputs(&s,out); 
	}

	fclose( in );
	fclose( out ); 
 }

int main()
{
	chang();
	return 0;
}