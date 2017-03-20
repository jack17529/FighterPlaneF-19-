#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

long long int strBin(char bn[]);
int binInt(int bin);
void Display();
void decode(long long int bin);
void simulate(int temp_pc);
void read(FILE *bn);
int length(long long int);
int leng(int);
void symbol(char fName[]);
int bintoInt( int flag , int n);


int pc;//program counter
long long int ir;//instruction register
int reg[15]={0};
int Label[10];
int AR=0;//Altitude register
int DR=0;//Direction register
int MSL=0;//missile register
int AIM[3]={0};//aim register(x,y,z)
int SPD=0;//speed register
int RR=0;//Radio register
int Stack[10];//stack register
int FP=0;//flap register
int STAT[3]={0};//status flag register(ov,z,n)
int SYS[3]={0};//system flag(bt,au,eng)
int tos=-1;//points to top of stack
char fName[20];


void main(){
	//char fName[20];
	FILE *bn;
	int choice;

	printf("Enter Binary file name\n");
	scanf("%s",fName);
	symbol(fName);
	while(1){
		bn=fopen(fName,"r+");
		printf("Select an option from below\n");
		printf("1>System\n");
		printf("2>Display Instructions\n");
		printf("0>exit\n");
		scanf("%d",&choice);
		if(choice==1)
		{
			simulate(0);
		}
		else if(choice==2)
			read(bn);
		else if(choice==0)
			break;
		else
			printf("wrong instructions\n");
		fclose(bn);
	}
}

/* counting lenght*/
int leng(int bin){
	int l=0;
	for(;bin>0;bin=bin/10)
	{
		l++;
	}
return l;
}


/*converting binary to integer*/

int binInt(int n)
{
	int i,bin=0,c=1;
	for(i=n;i>0;i=i/10)
	{
		bin=bin+(i%10)*c;
		c=c*2;
	}
	return bin;
}


/* managing symbols*/

void symbol(char fName[])
{
	FILE *fp,*bn;
	char temp[20];
	int i,k,c=0;
	long long int bin;
	fp=fopen("temp.dat","w+");
	bn=fopen(fName,"r+");
	while(1){

		 i=fscanf(bn,"%s\n",temp); //int fscanf(FILE *stream, const char *format, ...)
                if(i==-1) //nothing in file.
                break;
		//printf("%s\n",temp);
		bin=strBin(temp);  //converts string temp to binary.
		if(length(bin)==16)
		{
			k=bin/(pow(10,8));// because we want to check label specifically
			if(k==11100111) // opcode of label
			{
				Label[binInt(bin%1000)]=c; label number by last 4 
				continue;
			}

		}
		c++;
		fprintf(fp,"%s\n",temp);
		//printf("%lld\n",bin);
		//printf("%lld	%d\n",x,length(x));
		//ir=bin;

		//c=c+1;
		//pc=c;
	}

	fclose(fp);
	fclose(bn);
	remove(fName);
	rename("temp.dat",fName);  // extracting label out by storing their indexes and getting only  the file with only other instructions by renaming the original file.
}


/*
*/
int power(int c)
{

 int x = 1;
   while(c--)
{
    x = x*2;
}

//printf("x is %d\n" , x);

return x;
}



int bintoInt( int flag , int n)
{
	int i,bin=0,c=1;

        int loop_run = 0;
	for(i=n;i>0;i=i/10)
	{
		bin=bin+(i%10)*c;
		c=c*2;

                loop_run++;
	}

  //  printf("c is %d\n" , loop_run);

    // printf("bin is %d\n" , bin);

       if(flag==1)
            bin = bin - power(loop_run);
	return bin;
}




/*Displaying values in register*/

void Display()
{
	int i;
	printf("General purpose registers\n");
	for(i=0;i<15;i++)
	{
		printf("R%d:%d	",i,reg[i]);
		if((i+1)%5==0)
			printf("\n");
		//if(i<10)
			//printf("L[%d]=%d \n",i,Label[i]);
	}
	printf("Stauts flag OV:%d	Z:%d	N:%d\n",STAT[0],STAT[1],STAT[2]);
	printf("value of special registers\n");
	printf("Program Counter: %d	",pc);
	printf("Instruction Register: %lld\n",ir);
	printf("DirectionRegister: %d	",DR);
	printf("AltitudeRegister:%d\n",AR);
	printf("Flap:%d	",FP);
	printf("Missile:%d	",MSL);
	printf("Radio:%d\n",RR);
	printf("Speed:%d	",SPD);
	printf("System flag BT:%d	AU:%d	ENG:%d\n",SYS[0],SYS[1],SYS[2]);
	printf("AIM X:%d	Y:%d	Z:%d\n",AIM[0],AIM[1],AIM[2]);
	for(i=0;i<=tos;i++){
		printf("values in stack 	");
		printf("%d\n",Stack[i]);
	}
	printf("\n");

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

/*convert string to binary*/

long long int strBin(char bn[])		//bn takes input as string from binary file.
{
	long long int i,bin=0;
	for(i=0;i<=15;i++)
	{
		if(bn[i]=='1')
		{
			bin=(bin*10)+1;
			//printf("%ld\n",bin);

		}
		else
		{
			bin=bin*10;
			//printf("%ld\n",bin);
		}
	}
	//printf("%d\n",bin);
	return bin;
}

/*	this function will decode the instruction in IR	*/

void decode(long long int bin)
{
	int temp=bin/1000000000000000;// 15 zeros.

if(temp==0){								//checking if its aim.
	printf("AIM:OPERATION\n");
	printf("ALU STATUS:no ALU operations performed\n");
	printf("DATA MOVEMENT: values moved to register\n");
	int reg1,value1,reg2,value2,reg3,value3;			// X,Y and Z directions.
	int bin1=(bin%1000000000000000)/100000000000000;	// 15 zeros in numerator / 	14 zeros in denominator
	int bin2=(bin%100000000000000)/10000000000;		//14 zeros in numerator /	10 zeros in denominator
	if(bin1==1)						//15/3 for 3 directions 5 bits each.
	{
		reg1=binInt(bin2);
		AIM[0]=reg[reg1];				//checking 1 for register and 0 for value for starting bit.
	}							// storing in reg array as index.
	else
	{							
		//value1=binInt(bin2);					
		if(leng(bin2)==4)				// checking if value is positive or negative.
			value1=bintoInt(1,bin2);
		else
			value1=bintoInt(0,bin2);		// storing as value in AIM array.
		AIM[0]=value1;
	}
	bin1=(bin%10000000000)/1000000000;		//extracting next 5 bits.
	bin2=(bin%1000000000)/100000;
	if(bin1==1)
	{
		reg2=binInt(bin2);			
		AIM[1]=reg[reg2];
	}
	else
	{
		//value2=binInt(bin2);
		if(leng(bin2)==4)
			value2=bintoInt(1,bin2);
		else
			value2=bintoInt(0,bin2);
		AIM[1]=value2;
	}
	bin1=(bin%100000)/10000;
	bin2=(bin%10000);
	if(bin1==1)
	{
		reg3=binInt(bin2);
		AIM[2]=reg[reg3];
	}
	else
	{
		//value3=binInt(bin2);
		if(leng(bin2)==4)
			value3=bintoInt(1,bin2);
		else
			value3=bintoInt(0,bin2);
		AIM[2]=value3;
	}

}
temp=bin;

temp = bin/(1000000000000);			// 12 zeros

if(temp==1000){					//ADD operation.In both ADD and SUB we have considered that the first value is a registerbut the second value can be regester or  address.



	int reg1,reg2,value;
	int bin1=bin;
	int bin2=bin;
	bin1=(bin%1000000000000)/100000000000;	// 12 zeros in numerator / 11 zeros in denominator.
	//bin1=bin1/100000000000;
	bin2=(bin%100000000000)/1000000;	// 11 zeros in numerator / 6 zeros in denominator.
	//bin2=bin2/1000000;
	reg1=binInt(bin2);
	bin1=bin;
	bin1=bin%1000000;				// 6 zeros.
	bin1=bin1/100000;				// 5 zeros. to get the first bit in first address.
	//bin2=bin;
	bin2=bin%100000;				// 5 zeros. interpreting its value.
	if(bin1==1)
	{
		reg2=binInt(bin2);
		reg[reg1]=reg[reg1]+reg[reg2];		// amending the value in reg array.
	}
		else
		{
			//value=binInt(bin2);
			if(leng(bin2)==5)
			value=bintoInt(1,bin2);
			else
			value=bintoInt(0,bin2);
			reg[reg1]=reg[reg1]+value;
		}

	printf("ADD:OPERATION\n");
	printf("ALU STATUS:ADD operations performed\n");
	printf("DATA MOVEMENT: result moved to register %d \n",reg1);


   }

else if(temp==1001){						//SUB operationperformed for CMP(main operation).
	int reg1,reg2,value;
	int bin1=bin;
	int bin2=bin;
	bin1=(bin%1000000000000)/100000000000;			//  12 zeros in numerator /  11 zeros in denominator.
	//bin1=bin1%1000000000000;
	//bin1=bin1/100000000000;
	bin2=(bin%100000000000)/1000000;			//  11 zeros in numerator / 6 zeros in denominator.
	//bin2=bin2%100000000000;
	//bin2=bin2/1000000;
	reg1=binInt(bin2);
	bin1=bin;
	bin1=bin%1000000;						// similarly as ADD.
	bin1=bin1/100000;
	//bin2=bin;
	bin2=bin%100000;
	if(bin1==1)
	{
		reg2=binInt(bin2);					
		if(reg[reg1]==reg[reg2])
		{
			STAT[0]=0;STAT[1]=1;STAT[2]=0;			// value of overflow, z and n
		}							// overflow will always be zero as we are only considering the unsigned.

		else if(reg[reg1]<reg[reg2]){
			STAT[0]=0;STAT[1]=0;STAT[2]=1;
		}

		else{

			STAT[0]=0;STAT[1]=0;STAT[2]=0;
		}
	}
	else
	{
		value=binInt(bin2);

		if(reg[reg1]==value)
		{
			STAT[0]=0;STAT[1]=1;STAT[2]=0;
		}

		else if(reg[reg1]<value){
			STAT[0]=0;STAT[1]=0;STAT[2]=1;
		}

		else{

			STAT[0]=0;STAT[1]=0;STAT[2]=0;
		}
	}

	printf("CMP:OPERATION\n");
	printf("ALU STATUS:SUB operations performed\n");
	printf("DATA MOVEMENT: no data movement\n");


    }

else if(temp==1010){							// its for IN.
	int reg1,reg2,value;
	int bin1=bin;
	int bin2=bin;
	bin1=(bin%1000000000000)/100000000000;				//12 zeros in numerator / 11 zeros in denominator.
	//bin1=bin1%1000000000000;
	//bin1=bin1/100000000000;
	bin2=(bin%100000000000)/1000000;				// 11 zeros in numerator / 6 zeros in denominator.
	//bin2=bin2%100000000000;
	//bin2=bin2/1000000;
	reg1=binInt(bin2);
	bin1=bin;
	bin1=bin1%1000000;						// 6 zeros.
	bin1=bin1/100000;						//5 zeros.
	bin2=bin;
	bin2=bin%100000;						// 5 zeros.
	//if(bin1==1)
		reg2=binInt(bin2);
	//else
		//value=binInt(bin2);
	}

else if(temp==1011){							// MOV operation opcode.
	int reg1,reg2,value;
       	int bin1=bin;
	 int bin2=bin;
	bin1=bin%1000000000000;						// 12 zeros.we are not using bin 1 here as it is always to be register.
	bin1=bin1/100000000000;						// 11 zeros.
	bin2=(bin%1000000000000)/100000000;				// 12 zeros in numerator / 8 zeros in denominator.
	//printf("bin2 : %d\n",bin2);
	//bin2=bin2/100000000;
	reg1=binInt(bin2);
	bin1=bin;
	bin1=bin1%100000000;						// 8 zeros.
	bin1=bin1/100000000;
	bin2=bin;
	bin2=bin%10000000;
	if(bin1==1){
		reg2=binInt(bin2);
		reg[reg1]=reg[reg2];
	}
	else{
		value=binInt(bin2);
		reg[reg1]=value;
		}
	printf("MOV:OPERATION\n");
	printf("ALU STATUS:no ALU operations performed\n");
	printf("DATA MOVEMENT: data(value) moved to register %d \n",reg1);


	}

else if(temp==1100){								//OUT function we have not used.
	int reg1,reg2,value;
	int bin1=bin;
	int bin2=bin;
	bin1=(bin%1000000000000)/100000000000;					//12 zeros in numerator/ 11 zeros in denominator.
	//bin1=bin1%1000000000000;
	//bin1=bin1/100000000000;
	bin2=(bin%100000000000)/1000000;					//11 zeros in numerator / 6 zeros in denominator.
	//bin2=bin2%100000000000;
	//bin2=bin2/1000000;
	reg1=binInt(bin2);
	bin1=bin;
	bin1=bin1%1000000;							//6 zeros.
	bin1=bin1/100000;							// 5 zeros.
	bin2=bin;
	bin2=bin%100000;							// 5 zeros.
	//if(bin1==1)
		reg2=binInt(bin2);
	//else
	//	value=binInt(bin2);
	}

else if(temp==1101){								// SUB operation is performed,similar to ADD operation.
	int reg1,reg2,value;
	int bin1=bin;
	int bin2=bin;
	bin1=(bin%1000000000000)/100000000000;
	//bin1=bin1%1000000000000;
	//bin1=bin1/100000000000;
	bin2=(bin%100000000000)/1000000;
	//bin2=bin2%100000000000;
	//bin2=bin2/1000000;
	reg1=binInt(bin2);
	bin1=bin;
	bin1=bin%1000000;
	bin1=bin1/100000;
	bin2=bin;
	bin2=bin%100000;
	//printf("bin1:%d\n",bin1);
	if(bin1==1)
	{
		reg2=binInt(bin2);
		reg[reg1]=reg[reg1]-reg[reg2];
	}
		else
		{
			value=binInt(bin2);
			reg[reg1]=reg[reg1]-value;
		}

	printf("SUB:OPERATION\n");
	printf("ALU STATUS:SUB operations performed\n");
	printf("DATA MOVEMENT: result moved to register %d \n",reg1);
	}

else if(temp==1110){									// DRA operation.
	temp = (bin/(100000000))%10000;							// 8 zeros (4 are zeros) , (8 remaing ) 4 zeros.
	//printf("temp: %d\n",temp);

	if(temp==0){									// 0000 for DRA.
			int reg1,value;
			int bin1;
			bin1=bin%100000000;						// 8 zeros.
			int bin2=bin1%10000000;						// 7 zeros.
			bin1=bin1/10000000;						// 7 zeros.
			if(bin1==1)
			{
				reg1=binInt(bin2);
				DR=DR+reg[reg1];
			}
			else
			{
				//value=binInt(bin2);
				if(leng(bin2)==7)
				value=bintoInt(1,bin2);
				else
				value=bintoInt(0,bin2);
				DR=DR+value;
			}
		printf("DRA:OPERATION\n");
		printf("ALU STATUS:ADD/SUB operations performed\n");
		printf("DATA MOVEMENT: result moved to DirectionRegister\n");

		}

	else if(temp==1){
			int reg1,value;
			int bin1;
			bin1=bin%100000000;
			int bin2=bin1%10000000;
			bin1=bin1/10000000;
			if(bin1==1)
			{
				reg1=binInt(bin2);
				AR=AR+reg[reg1];
			}
			else
			{
				//value=binInt(bin2);
				if(leng(bin2)==7)
				value=bintoInt(1,bin2);
				else
				value=bintoInt(0,bin2);
				AR=AR+value;
			}
		printf("ELV:OPERATION\n");
		printf("ALU STATUS:ADD/SUB operations performed\n");
		printf("DATA MOVEMENT: result moved to AltitudeRegister\n");
		}

	else if(temp==10){
			int reg1,value;
			int bin1;
			bin1=bin%100000000;
			int bin2=bin1%10000000;
			bin1=bin1/10000000;
			if(bin1==1)
			{
				reg1=binInt(bin2);
				FP=reg[reg1];
			}
			else
			{
				value=binInt(bin2);
				FP=value;
			}
		printf("FLAP:OPERATION\n");
		printf("ALU STATUS:no operations performed\n");
		printf("DATA MOVEMENT: data moved to FlapRegister\n");

		}

	else if(temp==11){

		temp = bin%10000;
		int labelNo = binInt(temp);
		if(STAT[0]==0&&STAT[1]==0&&STAT[2]==0)
		simulate(Label[labelNo]);

		}

	else if(temp==100){

		temp = bin%10000;
		int labelNo = binInt(temp);
		if(STAT[0]==0&&STAT[1]==0&&STAT[2]==1)
		simulate(Label[labelNo]);

		}

	else if(temp==101){

		temp = bin%10000;
		int labelNo = binInt(temp);
		//printf("signal : In jump\n");
		printf("JMP:OPERATION\n");
		printf("ALU STATUS:no operations performed\n");
		printf("CONTROL MOVEMENT: control  moved to address %d\n",Label[labelNo]);
		simulate(Label[labelNo]);

		//fclose(bn);
		//simulate(14);

		}

	else if(temp==110){

		temp = bin%10000;
		int labelNo = binInt(temp);
		if(STAT[1]==0)
		simulate(Label[labelNo]);

		}

	else if (temp==111){
		temp = bin%10000;
		int labelNo = binInt(temp);
		}

	else if(temp==1000){
		int reg1,value;
		int bin1;
		int bin2=bin;
		bin1=bin%100000000;
		bin2=bin1%10000000;
		bin1=bin1/10000000;
		if(bin1==1){
			reg1=binInt(bin2);
			MSL=MSL+reg[reg1];
			}
		else
		{
			value=binInt(bin2);
			MSL=MSL+value;
		}
		printf("LOAD:OPERATION\n");
		printf("ALU STATUS:ADD operations performed\n");
		printf("DATA MOVEMENT: data moved to MissileRegister\n");
	}

	else if(temp==1001){
		temp = bin%10000;
		int labelNo = binInt(temp);
		Stack[++tos]=pc;
		printf("MSF:OPERATION\n");
		printf("ALU STATUS:no operations performed\n");
		printf("CONTROL MOVEMENT: control  moved to address %d\n",Label[labelNo]);
		simulate(Label[labelNo]);

		}

	else if(temp==1010){
		int reg1,value;
		int bin1;
		int bin2=bin;
		bin1=bin%100000000;
		bin2=bin1%10000000;
		bin1=bin1/10000000;
		if(bin1==1){
			reg1=binInt(bin2);
			RR=reg[reg1];
		}
		else{
			value=binInt(bin2);
			RR=value;
		}
	printf("RAD:OPERATION\n");
	printf("ALU STATUS:no operations performed\n");
	printf("DATA MOVEMENT: result moved to Radioregister\n");
	}
	else if(temp==1011){
		int reg1,value;
		int bin1=bin;
		int bin2=bin;
		bin1=bin1%100000000;
		bin2=bin1%10000000;
		bin1=bin1/10000000;
		if(bin1==1){
			reg1=binInt(bin2);
		}
		else{
			value=binInt(bin2);
		}
	printf("SELECT:OPERATION\n");
	printf("ALU STATUS:no operations performed\n");
	//printf("DATA MOVEMENT: result moved to Radioregister\n");
	}

	else if(temp==1100){
		int reg1,value;
		int bin1;
		int bin2=bin;
		bin1=bin%100000000;
		bin2=bin1%10000000;
		bin1=bin1/10000000;
		if(bin1==1){
			reg1=binInt(bin2);
			SPD=reg[reg1];
		}
		else{
			value=binInt(bin2);
			SPD=value;
		}
	printf("THR:OPERATION\n");
	printf("ALU STATUS:no operations performed\n");
	printf("DATA MOVEMENT: data moved to Speedregister\n");

	}
	}

else if(temp==1111){

	temp=bin/100000000;
	temp=temp%10000;

	if(temp==0){
	printf("RET:OPERATION\n");
	printf("ALU STATUS:no operations performed\n");
	printf("Control MOVEMENT:  control moved to TopOfStack\n");
		simulate(Stack[tos--]);
		}

	else if(temp==1){
	printf("SHOOT:OPERATION\n");
	printf("ALU STATUS:sub operations performed\n");
	printf("DATA MOVEMENT: result moved to Missileregister\n");
		MSL--;
		}

	else if(temp==10){
	printf("START:OPERATION\n");
	printf("ALU STATUS:no operations performed\n");
	//printf("DATA MOVEMENT: result moved to Radioregister\n");
		SYS[0]=1;
		SYS[1]=1;
		SYS[2]=1;
		}

	else if(temp==11){
		printf("HLT:OPERATON");
		exit(0);
	}

	}
}

/*
	following is the main simulator of functions
*/

void simulate(int temp_pc)
{

	FILE *bn=fopen(fName,"r+");
      //fseek(bn,0,SEEK_SET);
	int i,k;
	int c=0;
	long long int bin;
	char temp[20];
	while(1)
	{
		 i=fscanf(bn,"%s\n",temp);
                if(i==-1)
                break;
		if(c>=temp_pc)
		{
			//printf("%s\n",temp);
			bin=strBin(temp);
			printf("%lld\n",bin);
			//printf("%lld	%d\n",x,length(x));
			ir=bin;
			pc=c+1;
			decode(bin);
			Display();
		}
		c=c+1;
		pc=c;
		//Display();
	//if(c==4)
	//simulate(bn,5);
	}
	fclose(bn);
	printf("\n");
	//Display();
}


/*
	the following function is to read and diplay binary instructions
*/
void read(FILE *bn)
{
	int i;
	char temp[20];
	while(1)
	{
		i=fscanf(bn,"%s'\n",temp);
		if(i==-1)
		break;
		printf("%s\n",temp);
	}
	printf("\n");
}
