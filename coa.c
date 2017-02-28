#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>


void flight(FILE *fp,FILE *bn);
void control_transfer(FILE *fp,FILE *bn);
void input_output(FILE *fp,FILE *bn);
void datcmp(FILE *fp,FILE *bn);
void arithmetic(FILE *fp,FILE *bn);
void read(char fName[]);
int length(long long int);
int * binary_num(int , int);


void main(){
	 char fName[20];
	FILE *fp;
	FILE *bn;
	int i,choice,ch_ins;
	char temp[20];
	system("cls||clear");
	printf("		Welcome to Flight controller\n\n");
	printf("Enter file name :");
	scanf("%s",fName);
	strcpy(temp,fName);
	strcat(temp,".dat");	
//choices to be offered


while(1){
        fp=fopen(fName,"a+");
        bn=fopen(temp,"a+");
	printf("Select an option from below\n");
	printf("1>Add Instruction\n");
	printf("2>Show Instruction\n");
	printf("0>exit\nEnter choice:");
	scanf("%d",&choice);
	
  //adding Instructions to the file
	if(choice==1){
		system("cls||clear");
		while(1){
			printf("Select type of Instructions\n");
			printf("1>FLIGHT INSTRUCTIONS\n");
			printf("2>CONTROL TRANSFER\n");	
			printf("3>DATA TRANSFER and COMPARISION\n");
			printf("4>ARITHMETIC INSTRUCTIONS\n");
			printf("5>I/O INSTRUCTIONS\n");
			printf("0> BACK\n");
			scanf("%d",&ch_ins);
		
			switch(ch_ins)
			{
				case 1:flight(fp,bn);
				break;
				case 2:control_transfer(fp,bn);
				break;
				case 3:datcmp(fp,bn);
				break;
				case 4:arithmetic(fp,bn);
				break;
				case 5:input_output(fp,bn);
				break;
				case 0:system("cls||clear");
				break;
				default:printf("Error: wrong choice\n");
			}
			if(ch_ins==0)
				break;
			
	      	}//inner while closed
		
	}
  //Display file
	else if(choice==2){
		read(fName);
	}

 //exit from thew loop and program terminates
	else if(choice==0)
		break;
	else
		printf("wrong instructions");
//closing the files
	printf("\n");
         fclose(fp);
        fclose(bn);



 }
	
	
}




/*instruction will compute length
	of the binary number
*/

int length(long long int bin){
	int l=0;
	for(;bin>0;bin=bin/10)
	{
		l++;
	}
return l;
}	
/*instruuction nhere will return binary code
 to a decimal number*/

int  fn(int number , int length)
{


	int a = 1;
	int b = 0;
	int k = 0;
	int bin=0;
	if(number<0)
  	{
       		k = 1;
       		number =number * -1;

  	}

     	while(1)
     	{

        	 if(number/a == 0)
        	    break;
                 a  = a * 2;
 		 b++;
	}



   	int* binary_no = calloc(length,sizeof(int));
	memset(binary_no,0,sizeof(binary_no));
	int r = length - 1;
	if(k == 1)
   	{
	 while(r > b)
	{
	    binary_no[r] = 1;
	      r--;
      	}
	}
	int x = b ;
        int g = a;

   	while(x>-1)
   	{
	binary_no[x] = number/g;
      	 //printf("%d\n" , number/g);
         //printf("binary[%d] == %d" , x , binary_no[x]);
      	 number = number % g;
      	 //printf("%d\n" , number);
      	 x--;
      	 g= g/2;
	}
/*for(x = b ; x >-1 ; x = x - 1)

   printf("%d " , binary_no[x]);



   printf("\n");*/

if (k == 1)
{
    for(x = b ; x >-1 ; x = x - 1)
              {
                  binary_no[x] = binary_no[x] - 1;
                 // printf("%d\n" , binary_no[x]);
                  binary_no[x] = binary_no[x] * (-1);
  }


/*for(x = length - 1; x >-1 ; x = x - 1)
   printf("%d " , binary_no[x]);

*/


//printf("\n");

x = 0;
  while(x<b+1)
{
if(binary_no[x] == 0)
    {
        binary_no[x] = 1;
         break;
    }
    else
        binary_no[x] = 0;
    x++;
}
}
for(x = length - 1; x >-1 ; x = x - 1)
	bin=bin*10+binary_no[x];
  // printf("%d " , binary_no[x]);

 //printf("\n");

return bin;
}



char* conv(int n){
        int i,temp;
        char *c =(char*) calloc(3,sizeof(char) );
        for(i=2;i>=1;i--){
                c[i]=(char)((n%10)+48);
                n=n/10;
        }
        c[0]='R';
        return c;
}


void flight(FILE *fp,FILE *bn){
	int choice,c,value,z;
	char code[20];
	char tmp[3];
	long long int bin;

	printf("1>AIM\n");
	printf("2>DRA\n");
	printf("3>ELV\n");
	printf("4>FLAP\n");
	printf("5>LOAD\n");
	printf("6>RAD\n");
	printf("7>SELECT\n");
	printf("8>SHOOT\n");
	printf("9>START\n");
	printf("10>THR\n");
	printf("Any other digit to return\n");
	scanf("%d",&choice);

		if(choice==1)
		{
			strcpy(code,"AIM,");
			bin=2;
			fprintf(bn,"0");
			printf("select for X\n");
			printf("1>Register\n");
			printf("2>value\n");
			scanf("%d",&c);
			if(c==1){
				bin=bin*10+1;
				printf("Select register from (00-15)\n");
				scanf("%d",&value);
				strcat(code,conv(value));
				strcat(code,",");
				bin=bin*pow(10,4)+fn(value,4);
			}
			if(c==2){
                                bin=bin*10+0;
                                printf("Enter value in range(-8 to 7)\n");
                                scanf("%d",&value);
				 sprintf(tmp,"#%d,",value);
                                 strcat(code,tmp);
				bin=bin*pow(10,4)+fn(value,4);
			}

                        
                        
			printf("select for Y\n");
                        printf("1>Register\n"); 
                        printf("2>value\n");
                        scanf("%d",&c);
                        if(c==1){
                                bin=bin*10+1;
                                printf("Select register from (00-15)\n");
                                scanf("%d",&value);
                                strcat(code,conv(value));
                                strcat(code,",");
                                bin=bin*pow(10,4)+fn(value,4);

                        }
                        if(c==2){
                                bin=bin*10+0;
                                printf("Enter value in range(-8 to 7)\n");
                                scanf("%d",&value);
                                 sprintf(tmp,"#%d,",value);
                                 strcat(code,tmp);
				 bin=bin*pow(10,4)+fn(value,4);
                                //bin=bin*math.pow(10,7)+fn(value,7);
                        }
			 printf("select for Z\n");
                         printf("1>Register\n");
                         printf("2>value\n");
                         scanf("%d",&c);
                        if(c==1){
                                bin=bin*10+1;
                                printf("Select register from (00-15)\n");
                                scanf("%d",&value);
                                strcat(code,conv(value));
                                bin=bin*pow(10,4)+fn(value,4);
                                //strcat(code,",");
                        }
                        if(c==2){
                                bin=bin*10+0;
                                printf("Enter value in range(-8 to 7)");
                                scanf("%d",&value);
                                sprintf(tmp,"#%d",value);
                                strcat(code,tmp);
                                bin=bin*pow(10,4)+fn(value,4);
                                //bin=bin*math.pow(10,7)+fn(value,7);
                        }
				if(length(bin)<16){
				printf("Error\n");
				return;
				}
			 fprintf(fp,"%s\n",code);
		    	 sprintf(tmp,"%lld",bin);
			char ch[20];
			for(z=1;z<16;z++)
				ch[z-1]=tmp[z];
			 fprintf(bn,"%s\n",ch);

		}
		else if(choice==2)
		{
			strcpy(code,"DRA,");
			bin=11100000;
			printf("1>Register\n");
			printf("2>value\n");	
			scanf("%d",&c);
			if(c==1){
				bin=bin*10+1;
				printf("select register from (00 to 15)");
				scanf("%d",&value);
				strcat(code,conv(value));
				bin=bin*pow(10,7)+fn(value,7);
			}
			if(c==2){
				bin=bin*10+0;
				printf("Enter value in range(-90 to 90)");
				scanf("%d",&value);
				sprintf(tmp,"#%d",value);
				strcat(code,tmp);
				bin=bin*pow(10,7)+fn(value,7);

			}
				if(length(bin)<16){
				printf("Error\n");
				return;
				}
			fprintf(fp,"%s\n",code);
			fprintf(bn,"%lld\n",bin);
			
		}

		else if(choice==3)
                {
                        strcpy(code,"ELV,");
                        bin=11100001;
                        printf("1>Register\n");
                        printf("2>value\n");
                        scanf("%d",&c);
                        if(c==1){
                                bin=bin*10+1;
                                printf("select register from (00 to 15)");
                                scanf("%d",&value);
                                strcat(code,conv(value));
                                bin=bin*pow(10,7)+fn(value,7);
                        }
                        if(c==2){
                                bin=bin*10+0;
                                printf("Enter value in range(-125 to 125)");
                                scanf("%d",&value);
                                sprintf(tmp,"#%d",value);
                                strcat(code,tmp);
                                bin=bin*pow(10,7)+fn(value,7);
			 }
				if(length(bin)<16){
				printf("Error\n");
				return;
				}
                        fprintf(fp,"%s\n",code);
                        fprintf(bn,"%lld\n",bin);

                }
		else if(choice==4)
		{
	
                        strcpy(code,"FLAP,");
                        bin=11100010;
                        printf("1>Register\n");
                        printf("2>value\n");
                        scanf("%d",&c);
                        if(c==1){
                                bin=bin*10+1;
                                printf("select register from (00 to 15)");
                                scanf("%d",&value);
                                strcat(code,conv(value));
                                bin=bin*pow(10,7)+fn(value,7);
                        }
                        if(c==2){
                                bin=bin*10+0;
                                printf("Enter value in range(0 to 2)");
                                scanf("%d",&value);
                                sprintf(tmp,"#%d",value);
                                strcat(code,tmp);
                                bin=bin*pow(10,7)+fn(value,7);

                        }
				if(length(bin)<16){
				return;
				printf("Error\n");
				}
                        fprintf(fp,"%s\n",code);
			fprintf(bn,"%lld\n",bin);
		
		}

		else if(choice==5)
		{
			strcpy(code,"LOAD,");
                        bin=11101000;
                        printf("1>Register\n");
                        printf("2>value\n");
                        scanf("%d",&c);
                        if(c==1){
                                bin=bin*10+1;
                                printf("select register from (00 to 15)");
                                scanf("%d",&value);
                                strcat(code,conv(value));
                                bin=bin*pow(10,7)+fn(value,7);
                        }
                        if(c==2){
                                bin=bin*10+0;
                                printf("Enter value in range(0 to 100)");
                                scanf("%d",&value);
                                sprintf(tmp,"#%d",value);
                                strcat(code,tmp);
                                bin=bin*pow(10,7)+fn(value,7);

                        }
				if(length(bin)<16){
				printf("Error\n");
				return;
				}
                        fprintf(fp,"%s\n",code);
                        fprintf(bn,"%lld\n",bin);

		} 
		else if(choice==6)
		{
			strcpy(code,"RAD,");
                        bin=11101010;
                        printf("1>Register\n");
                        printf("2>value\n");
                        scanf("%d",&c);
                        if(c==1){
                                bin=bin*10+1;
                                printf("select register from (00 to 15)");
                                scanf("%d",&value);
                                strcat(code,conv(value));
                                bin=bin*pow(10,7)+fn(value,7);
                        }
                        if(c==2){
                                bin=bin*10+0;
                                printf("Enter value in range(0 to 3)");
                                scanf("%d",&value);
                                sprintf(tmp,"#%d",value);
                                strcat(code,tmp);
                                bin=bin*pow(10,7)+fn(value,7);

                        }
				if(length(bin)<16){
				printf("Error\n");
				return;
				}
                        fprintf(fp,"%s\n",code);
                        fprintf(bn,"%lld\n",bin);

		}
		else if(choice==7)
		{
		        strcpy(code,"SELECT,");
                        bin=11101011;
                        printf("1>Register\n");
                        printf("2>value\n");
                        scanf("%d",&c);
                        if(c==1){
                                bin=bin*10+1;
                                printf("select register from (00 to 15)");
                                scanf("%d",&value);
                                strcat(code,conv(value));
                                bin=bin*pow(10,7)+fn(value,7);
                        }
                        if(c==2){
                                bin=bin*10+0;
                                printf("Enter value in range(1 to 3)");
                                scanf("%d",&value);
                                sprintf(tmp,"#%d",value);
                                strcat(code,tmp);
                                bin=bin*pow(10,7)+fn(value,7);

                        }
				if(length(bin)<16){
				printf("Error\n");
				return;
				}
                        fprintf(fp,"%s\n",code);
              	        fprintf(bn,"%lld\n",bin);

		}
		else if(choice==8)
		{
			strcpy(code,"SHOOT");
                        bin=1111000100000000;     
                        fprintf(fp,"%s\n",code);
                        fprintf(bn,"%lld\n",bin);

		}
		else if(choice==9)
		{
			strcpy(code,"START");
                        bin=1111001000000000;
                        fprintf(fp,"%s\n",code);
                        fprintf(bn,"%lld\n",bin);
		}
		else if(choice==10)
		{
		        strcpy(code,"THR,");
                        bin=11101100;
                        printf("1>Register\n");
                        printf("2>value\n");
                        scanf("%d",&c);
                        if(c==1){
                                bin=bin*10+1;
                                printf("select register from (00 to 15)");
                                scanf("%d",&value);
                                strcat(code,conv(value));
                                bin=bin*pow(10,7)+fn(value,7);
                        }
                        if(c==2){
                                bin=bin*10+0;
                                printf("Enter value in range(0 to 180)");
                                scanf("%d",&value);
                                sprintf(tmp,"#%d",value);
                                strcat(code,tmp);
                                bin=bin*pow(10,7)+fn(value,7);

                        }
			if(length(bin)<16){
				printf("Error\n");
				return;
				}
                        fprintf(fp,"%s\n",code);
                        fprintf(bn,"%lld\n",bin);
	
		}

}

/*the method will be used for control transfer
	statements*/

void control_transfer(FILE* fp,FILE* bn){
	int choice,c,value;
	char code[20];
	char tmp[3];
	long long int bin;
	printf("1>MSF\n");
	printf("2>RET\n");
	printf("3>JMP\n");
	printf("4>JGE\n");
	printf("5>JLE\n");
	printf("6>JNE\n");
	printf("7>LABEL\n");
	printf("Any other digit to return\n");
	scanf("%d",&choice);

	if(choice==1)

		{

			strcpy(code,"MSF,");

			

			bin=11101001;

				bin=bin*10+0;

                                printf("Enter value in range(0 to 10)");

                                scanf("%d",&value);

                                sprintf(tmp,"L%d",value);

                                strcat(code,tmp);

				bin=bin*pow(10,7)+fn(value,7);

				fprintf(fp,"%s\n",code);

                        	fprintf(bn,"%lld\n",bin);

		}


	else if(choice==2)

		{

			strcpy(code,"RET");

                        bin=1111000000000000;     

                        fprintf(fp,"%s\n",code);

                        fprintf(bn,"%lld\n",bin);

		}


	else if(choice==3)

		{

			strcpy(code,"JMP,");

			

			bin=11100101;

				bin=bin*10+0;

                                printf("Enter value in range(0 to 10)");

                                scanf("%d",&value);

                                sprintf(tmp,"L%d",value);

                                strcat(code,tmp);

				bin=bin*pow(10,7)+fn(value,7);

				fprintf(fp,"%s\n",code);

                        	fprintf(bn,"%lld\n",bin);

		}


	else if(choice==4)

		{

			strcpy(code,"JGE,");

			

			bin=11100011;

				bin=bin*10+0;

                                printf("Enter value in range(0 to 10)");

                                scanf("%d",&value);

                                sprintf(tmp,"L%d",value);

                                strcat(code,tmp);

				bin=bin*pow(10,7)+fn(value,7);

				fprintf(fp,"%s\n",code);

                        	fprintf(bn,"%lld\n",bin);

		}

	else if(choice==5){
		strcpy(code,"JLE,");
		bin=11100100;
		printf("Enter the label no. where you want to jump(between 0 to 9)\n");
		scanf("%d",&value);
		sprintf(tmp,"L%d",value);
		strcat(code,tmp);
		bin=bin*pow(10,8)+fn(value,8);
		fprintf(fp,"%s\n",code);
		fprintf(bn,"%lld\n",bin);
	}
	
	else if(choice==6){
		strcpy(code,"JNE,");
		bin=11100110;
		printf("Enter the label no. where you want to jump(between 0 to 9)\n");
		scanf("%d",&value);
		sprintf(tmp,"L%d",value);
		strcat(code,tmp);
		bin=bin*pow(10,8)+fn(value,8);
		fprintf(fp,"%s\n",code);
		fprintf(bn,"%lld\n",bin);
	}

	else if(choice==7){
		strcpy(code,"LABEL,");
		bin=11100111;
		printf("Enter the label number (between 0 to 9)\n");
		scanf("%d",&value);
		sprintf(tmp,"L%d",value);
		strcat(code,tmp);
		bin=bin*pow(10,8)+fn(value,8);
		fprintf(fp,"%s\n",code);
		fprintf(bn,"%lld\n",bin);
	}
}

/*the method below will be used for
dta transfer and compare instruction*/
void datcmp(FILE *fp,FILE*bn)
{
	 int choice,c,value,z;
        char code[20];
        char tmp[3];
        long long int bin;

        printf("1>MOV\n");
        printf("2>CMP\n");
     	printf("3>HLT\n");
	printf("any other digit to return\n");
        scanf("%d",&choice);
	
	if(choice==1)
	{
	   strcpy(code,"MOV,");
           bin=1011;
	   printf("Value 1 :Select register from(00to15)");
	   scanf("%d",&value);
           strcat(code,conv(value));
	   strcat(code,",");
           bin=bin*pow(10,4)+fn(value,4);
	   printf("value 2\n");
	   printf("1>Register\n");
           printf("2>value\n");
           scanf("%d",&c);
            if(c==1){
                  bin=bin*10+1;
                  printf("select register from (00 to 15)");
                  scanf("%d",&value);
                  strcat(code,conv(value));
                  bin=bin*pow(10,7)+fn(value,7);
              }
             if(c==2){
                   bin=bin*10+0;
                   printf("Enter value in range(-127 to 127)");
                   scanf("%d",&value);
                   sprintf(tmp,"#%d",value);
                   strcat(code,tmp);
                   bin=bin*pow(10,7)+fn(value,7);

                }
                        fprintf(fp,"%s\n",code);
                        fprintf(bn,"%lld\n",bin);

	}
	else if(choice==2)
	{
		 strcpy(code,"CMP,");
                 bin=10011;
                 printf("Value 1 :Select register from(00to15)");
                 scanf("%d",&value);
       	         strcat(code,conv(value));
          	 strcat(code,",");
                 bin=bin*pow(10,5)+fn(value,5);
	         printf("value 2\n");
                 printf("1>Register\n");
                 printf("2>value\n");
                 scanf("%d",&c);
                 if(c==1){
                  bin=bin*10+1;
                  printf("select register from (00 to 15)");
                  scanf("%d",&value);
                  strcat(code,conv(value));
                  bin=bin*pow(10,5)+fn(value,5);
                 }
              if(c==2){
                bin=bin*10+0;
                printf("Enter value in range(-32 to 31)");
                scanf("%d",&value);
                sprintf(tmp,"#%d",value);
                strcat(code,tmp);
                bin=bin*pow(10,5)+fn(value,5);
	       }
              fprintf(fp,"%s\n",code);
              fprintf(bn,"%lld\n",bin);
	    }
	else if(choice==3)
	{
                        strcpy(code,"HLT");
                        bin=1111001100000000;
                        fprintf(fp,"%s\n",code);
                        fprintf(bn,"%lld\n",bin);
	}

	
}

/*the method below will be used for
 Arithmetic Instructions
*/

void arithmetic(FILE* fp,FILE* bn){	
	int choice,c,value;
	char code[20];
	char tmp[3];
	long long int bin;
	printf("1>ADD\n");
	printf("2>SUB\n");
	printf("any other digit to return\n");
	scanf("%d",&choice);
	if(choice==1)
		{
			strcpy(code,"ADD,");
			bin=1000;
			printf("select for first \n");
				bin=bin*10+1;
				printf("Select register from (00-15)\n");
				scanf("%d",&value);
				strcat(code,conv(value));
				strcat(code,",");
				bin=bin*pow(10,5)+fn(value,5);

			printf("select for Second\n");
                        printf("1>Register\n");
                        printf("2>value\n");
                        scanf("%d",&c);
                        if(c==1){
                                bin=bin*10+1;
                                printf("Select register from (00-15)\n");
                                scanf("%d",&value);
                                strcat(code,conv(value));
				bin=bin*pow(10,5)+fn(value,5);
                        }
                        if(c==2){
                                bin=bin*10+0;
                                printf("Enter value in range(-32 to 31)\n");
                                scanf("%d",&value);
                                 sprintf(tmp,"#%d",value);
                                 strcat(code,tmp);
                                bin=bin*pow(10,5)+fn(value,5);
                        }

			 fprintf(fp,"%s\n",code);
			 fprintf(bn,"%lld\n",bin);
                       

		}
		else if(choice==2)
				{
			strcpy(code,"SUB,");
			bin=1101;
			printf("select for first \n");
				bin=bin*10+1;
				printf("Select register from (00-15)\n");
				scanf("%d",&value);
				strcat(code,conv(value));
				strcat(code,",");
				bin=bin*pow(10,5)+fn(value,5);

			printf("select for Second\n");
                        printf("1>Register\n");
                        printf("2>value\n");
                        scanf("%d",&c);
                        if(c==1){
                                bin=bin*10+1;
                                printf("Select register from (00-15)\n");
                                scanf("%d",&value);
                                strcat(code,conv(value));
				bin=bin*pow(10,5)+fn(value,5);
                        }
                        if(c==2){
                                bin=bin*10+0;
                                printf("Enter value in range(-32 to 31)\n");
                                scanf("%d",&value);
                                 sprintf(tmp,"#%d",value);
                                 strcat(code,tmp);
                                bin=bin*pow(10,5)+fn(value,5);
                        }

			 fprintf(fp,"%s\n",code);
			 fprintf(bn,"%lld\n",bin);
                       

		}

}

/* the instruciton below will be used
   to take input from port and send out to port*/ 

void input_output(FILE* fp,FILE* bn){	
	int choice,c,value;
	char code[20];
	char tmp[3];
	long long int bin;
	printf("1>IN\n");
	printf("2>OUT\n");
	scanf("%d",&choice);
	
	if(choice==1){
		strcpy(code,"IN,");
		bin=1010;

		printf("Select register from (00-15)\n");
		scanf("%d",&value);
		strcat(code,conv(value));
		strcat(code,",");
		bin=bin*pow(10,6)+fn(value,6);
		
		printf("Enter port number(between 1 to 15)\n");
		scanf("%d",&value);
		sprintf(tmp,"P%d",value);
		strcat(code,tmp);
		bin=bin*pow(10,6)+fn(value,6);
		fprintf(fp,"%s\n",code);
		fprintf(bn,"%lld\n",bin);
	}

	else if(choice==2){
		strcpy(code,"OUT,");
		bin=1100;

		printf("Enter port number(between 1 to 15)\n");
		scanf("%d",&value);
		sprintf(tmp,"P%d",value);
		strcat(code,tmp);
		strcat(code,",");
		bin=bin*pow(10,6)+fn(value,6);

		printf("Select register from (00-15)\n");
		scanf("%d",&value);
		strcat(code,conv(value));
		bin=bin*pow(10,6)+fn(value,6);
		
		fprintf(fp,"%s\n",code);
		fprintf(bn,"%lld\n",bin);
	}
}




/* the method below will be used to display
the content of the file*/


void read(char fName[]){
	FILE *fp;
	char temp[20];
	int i;
	fp=fopen(fName,"r+");
	printf("\n");
	 while(1){
                i=fscanf(fp,"%s\n",temp);
                if(i==-1)
                break;
                printf("%s\n",temp);
        }
	printf("\n");
	fclose(fp);

}
