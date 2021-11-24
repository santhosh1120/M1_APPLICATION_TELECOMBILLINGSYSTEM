#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<windows.h>
#include<stdlib.h>
struct subscriber
{
char phonenumber[20];
char name[50];
float amount;
}s;
void addrecords();
void listrecords();
void modifyrecords();
void deleterecords();
void searchrecords();
void payment();
char get;
int main()
{	int password;
	int phonenumber;
	char choice;
	system("cls");
	system("color 3f");
	printf("**Knowledge 360**");
	printf("\n\n\n\n\n\n\n\n\n\t\t**************************************************************");
	printf("\n\t\t------WELCOME TO THE TELECOM BILLING MANAGEMENT SYSTEM---");
	printf("\n\t\t**************************************************************");
	printf("\n\t\tPress Any Key To Continue...");
	Sleep(2000);
	getch();
    system("cls");
	while (1)
	{
		system("cls");
		printf("\n A : For Adding New Records.");
		printf("\n L : For Listing Records");
		printf("\n M : For Modifying Records.");
		printf("\n P : For Payments");
		printf("\n S : For Searching Records.");
		printf("\n D : For Deleting Records.");
		printf("\n E : For Exit\n");
		printf("\n\n\n Enter You Choice: ");
		choice=getche();
		choice=toupper(choice);
		switch(choice)
		{
			case 'P':
				payment();break;
			case 'A':
				addrecords();break;
			case 'L':
				listrecords();break;
			case 'M':
				modifyrecords();break;
			case 'S':
				searchrecords();break;
			case 'D':
				deleterecords();break;
			case 'E':
				system("cls");
				printf("\n\n\t\t\t\tTHANK YOU FOR USING OUR SERVICE.");
				Sleep(2000);
				exit(0);
				break;
			default:
				system("cls");
				printf("Incorrect Input");
				printf("\nPress Any key to continue");
				getch();
		}
	}
}
void addrecords()
{
	FILE *f;
	char test;
	f=fopen("d:/file.ojs","ab+");
	if(f==0)
	{   f=fopen("d:/file.ojs","wb+");
		system("cls");
		printf("Please Wait While We Configure Your Computer");
		printf("\nPress Any Key To Continue...");
		getch();
	}
	while(1)
	{
		system("cls");
		printf("\n Enter Phone Number: ");
		scanf("%s",&s.phonenumber);
		printf("\n Enter Name: ");
		fflush(stdin);
		scanf("%[^\n]",&s.name);
		printf("\n Enter Amount: ");
		scanf("%f",&s.amount);
		fwrite(&s,sizeof(s),1,f);
		fflush(stdin);
		system("cls");
		printf("1 Record Successfully Added");
		printf("\n Press ESC Key To Exit, Any Other Key To Add Another Record: ");
		test=getche();
		if(test==27)
			break;
	}
	fclose(f);
}
void listrecords()
{
	FILE *f;
	int i;
	if((f=fopen("d:/file.ojs","rb"))==NULL)
		exit(0);
	system("cls");
	printf("Phone Number\t\tUser Name\t\t\tAmount\n");
	for(i=0;i<79;i++)
		printf("-");
	while(fread(&s,sizeof(s),1,f)==1)
	{
		printf("\n%-10s\t\t%-20s\t\tRs. %.2f /-",s.phonenumber,s.name,s.amount);
	}
	printf("\n");
	for(i=0;i<79;i++)
		printf("-");

fclose(f);
getch();
}
void deleterecords()//This funtion is used to delete the record.//
{
	FILE *f,*t;
	int i=1;
	char phonenumber[20];
	if((t=fopen("d:/temp.ojs","w+"))==NULL)
	exit(0);
	if((f=fopen("d:/file.ojs","rb"))==NULL)
	exit(0);
	system("cls");
	printf("Enter The Phone Number To Be Deleted From The Database: ");
	fflush(stdin);
	scanf("%[^\n]",phonenumber);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)==0)
		{       i=0;
			continue;

		}
		else
			fwrite(&s,sizeof(s),1,t);
	}
	if(i==1)
	{       system("cls");
		printf("Ooops !! Phone Number \"%s\" Not Found",phonenumber);
		remove("d:/file.ojs");
		rename("d:/temp.ojs","d:/file.ojs");
		getch();
		fclose(f);
		fclose(t);
		main();
	}
	remove("d:/file.ojs");
	rename("d:/temp.ojs","d:/file.ojs");
	system("cls");
	printf("The Number %s Successfully Deleted!!!!",phonenumber);
	fclose(f);
	fclose(t);
	getch();
}
void searchrecords()
{
	FILE *f;
	char phonenumber[20];
	int flag=1;
	f=fopen("d:/file.ojs","rb+");
	if(f==0)
		exit(0);
	fflush(stdin);
	system("cls");
	printf("Enter Phone Number To Search In Our Database");
	scanf("%s", phonenumber);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)==0)
		{	system("cls");
			printf(" Record Found ");
			printf("\n\nPhoneNumber: %s\nName: %s\nAmount: Rs.%0.2f\n",s.phonenumber,s.name,s.amount);
			flag=0;
			break;
		}
		else if(flag==1)
		{	system("cls");
			printf("Oops !! Requested Phone Number Not Found In Our Database");
		}
	}
	getch();
	fclose(f);
}
void modifyrecords()
{
	FILE *f;
	char phonenumber[20];
	long int size=sizeof(s);
	if((f=fopen("d:/file.ojs","rb+"))==NULL)
		exit(0);
	system("cls");
	printf("Enter Phone Number Of The Subscriber To Modify: ");
	scanf("%[^\n]",phonenumber);
	fflush(stdin);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)==0)
		{
			system("cls");
			printf("\n Enter Phone Number: ");
			scanf("%s",&s.phonenumber);
			printf("\n Enter Name: ");
			fflush(stdin);
			scanf("%[^\n]",&s.name);
			printf("\n Enter Amount: ");
			scanf("%f",&s.amount);
			fseek(f,-size,SEEK_CUR);
			fwrite(&s,sizeof(s),1,f);
			break;
		}
	}
	fclose(f);
}
void payment()
{
	FILE *f;
	char phonenumber[20];
	long int size=sizeof(s);
	float amt;
	int i;
	if((f=fopen("d:/file.ojs","rb+"))==NULL)
		exit(0);
	system("cls");
	printf("Enter Phone Number Of The Subscriber For Payment");
	scanf("%[^\n]",phonenumber);
	fflush(stdin);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)==0)
		{
			system("cls");
			printf("\n Phone No.: %s",s.phonenumber);
			printf("\n Name: %s",s.name);
			printf("\n Current Amount: %f",s.amount);
			printf("\n");
			for(i=0;i<79;i++)
				printf("-");
			printf("\n\nEnter Amount Of Payment : ");
			fflush(stdin);
			scanf(" %f",&amt);
			s.amount=s.amount-amt;
			fseek(f,-size,SEEK_CUR);
			fwrite(&s,sizeof(s),1,f);
			break;
		}
	}
	system("cls");
	printf("THANK YOU %s FOR YOUR TIMELY PAYMENTS",s.name);
	getch();
	fclose(f);
}

