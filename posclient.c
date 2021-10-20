#include<stdio.h>
//#include<conio.h>  //only for clrscr()
#include<stdlib.h>
#include<string.h>

struct Item 
{
	char barcode[20];
	char itemname[50];
	float price;
	int freeones;
	float defqty;
	int discount;
	float soldqty;
};


struct Billitem 
{
	char barcode[20];
	char itemname[50];
	float price;
	int freeones;
	int discount;
	float qty;
};


char shopname[50] = "Change name by choosing option in setup";

char fname[20]="Inventory.dat";

char bfname[20]="Bill.dat";

char receipt[20]="Receipt.txt";

int billno=0;
int tkey=0;//transaction key

float total=0;
float cash=0;
float change=0;


void Setup();
void ChangeShop();
void Itemlist();
void Add();
void Edit();
void Delete();
void Bill();
void displaybill();
void transc();
void Update(char *barcode,float soldqty);
void editbill();
void dellbill();


int main()
{
	int opt;
	char ch;
	while(1)
	{
		system("cls");
		printf("========================================\n");
		printf("	       POS SYSTEM\n");
		printf("========================================\n");
		printf("\n");
		printf("    1.Setup\n");
		printf("    2.Display Item list\n");
		printf("    3.Bill\n");
		printf("    4.Exit\n");
		printf("========================================\n");
		printf("Enter option:");
		scanf("%d",&opt);
			
		switch(opt)
		{
			case 1:
				Setup();
				break;
			case 2:
				Itemlist();
				fflush(stdin);
				ch=getchar();
				break;//giving getchar here did not stop it form cls
			case 3:
				Bill();
				break;
			case 4:
				printf("----------Power off----------\n");
				break;
			defaulf:
				printf("invalid choice try again\n");
		}
		if (opt==4)
			break;
	}
	return 0;
}



		
void Setup()
{
	int choice;
	
	while(1)
	{
		system("cls");
		printf("----------------------------------------\n");
		printf("\t\tSetup\n");
		printf("----------------------------------------\n");
	
		printf("    1.Change Shop Name\n");
		printf("    2.Add Item\n");
		printf("    3.Edit Item\n");
		printf("    4.Delete Item\n");
		printf("    5.Main Menu\n");
		printf("-----------------------------------------\n");
	
		printf("Enter option:");
		scanf("%d",&choice);

		switch(choice)
		{

			case 1:
				ChangeShop();
				break;
			case 2:
				Add();
				break;
			case 3:
				Edit();
				break;
			case 4:
				Delete();
				break;
			case 5:
				break;
			default:
				printf("Invalid input\n");
		}
		if (choice==5)
		{
			break;
		}	
	}
	
	
}

void ChangeShop()
{
	char temp[50];
	printf("-----------------------------------------\n");
	fflush(stdin);
	printf("Enter shop name:");
	scanf("%[^\n]s",temp);
	strcpy(shopname,temp);
	printf("-----------------------------------------\n");
	
}

void Add()
{
	char ch; char barcode[20];int found=0;
	Itemlist();
	FILE *fp,*fp1;
	struct Item t,t1;
	fp=fopen(fname,"ab");
	fp1=fopen(fname,"rb");
	fflush(stdin);
	printf("Enter Barcode:");
	scanf("%[^\n]s",barcode);
	
	while(1)
	{
		fread(&t1,sizeof(t1),1,fp1);
		if(feof(fp1))
			break;
		if(strcmp(t1.barcode,barcode)==0)
			found=1;
		
	}
	
	fclose(fp1);
	if(found==1)
	{
		printf("barcode aldready exists!\n");
		fflush(stdin);
		//printf("item added\n");
		ch=getchar();
	}
	
	if(found==0)
	{	
		strcpy(t.barcode,barcode);
		fflush(stdin);
		printf("Enter Item Name:");
		scanf("%[^\n]s",t.itemname);
	
		fflush(stdin);
		printf("Price:");
		scanf("%f",&t.price);
	
		printf("default quantity(i.e sold in pack of/kgs of):");
		scanf("%f",&t.defqty);
	
		printf("Buy-free quantity:");
		scanf("%d",&t.freeones);
	
		printf("discount rate(%%):");
		scanf("%d",&t.discount);
	
		t.soldqty=0.0;

		fflush(stdin);
		printf("item added\n");
		ch=getchar();
	
		fwrite(&t,sizeof(t),1,fp);
	}
			

	fclose(fp);
}

void Itemlist()
{
	//char ch;
	int count=1;
	int buy,gfree;
	struct Item t;
	FILE *fp;
	fp=fopen(fname,"rb");
	
	printf("-----------------------------------------\n");
	printf("\t    Item List\n");
	printf("-----------------------------------------\n");
	printf("______________________________________________________________________\n");
	printf("|Sl.no|  Barcode |   Name   | Price |Qty/unit|Buy - Free|Discount|SoldQty|\n");
	printf("______________________________________________________________________\n");
	while(1)
	{
		fread(&t,sizeof(t),1,fp);
		if (feof(fp))
		{
			break;
		}
		
		buy=t.freeones/10;
		gfree=t.freeones%10;
		
		printf(" %-5d%",count++);
		printf(" %-10s",t.barcode);
		printf(" %-10s",t.itemname);
		printf(" %6.2f",t.price);
		printf(" %8.2f",t.defqty);
		printf(" %4d-%-4d",buy,gfree);
		printf(" %7d%%",t.discount);
		printf(" %5.2f",t.soldqty);
		printf("\n");
	}
	printf("______________________________________________________________________\n");
	
	fclose(fp);
	
	
}

void Edit()
{
	char ch;
	FILE *fp,*fp1; //create temp file,and store modified item in it and later over write original file
	
	struct Item t;
	Itemlist();
	char barcode[20];
	int found=0;

	fp=fopen(fname,"rb");	
	fp1=fopen("temp.dat","wb");	
	
	fflush(stdin);
	printf("\nEnter barcode:");
	scanf("%[^\n]s",barcode);
	
	while(1)
	{
		fread(&t,sizeof(t),1,fp);
		
		if(feof(fp))
			break;
		
		if(strcmp(t.barcode,barcode)==0)
		{
			found=1;
			printf("enter new attributes\n");
			
			fflush(stdin);
			printf("Enter Barcode:");
			scanf("%[^\n]s",t.barcode);
	
			fflush(stdin);
			printf("Enter Item Name:");
			scanf("%[^\n]s",t.itemname);
	
			fflush(stdin);
			printf("Price:");
			scanf("%f",&t.price);
			printf("default quantity(i.e sold in pack of/kgs of):");
			scanf("%f",&t.defqty);
			printf("discount quantity:");
			scanf("%d",&t.freeones);
			printf("discount rate(%):");
			scanf("%d",&t.discount);
			fwrite(&t,sizeof(t),1,fp1);
		}
		else
			fwrite(&t,sizeof(t),1,fp1);
	}
	
	fclose(fp);
	fclose(fp1);
	
	if(found==0)
	{
		printf("invalid barcode no item found\n");
		fflush(stdin);
		//printf("item added\n");
		ch=getchar();

	}
	else
	{
		fp=fopen(fname,"wb");
		fp1=fopen("temp.dat","rb");
		
		while(1)
		{
			fread(&t,sizeof(t),1,fp1);
			if(feof(fp1))
				break;
			fwrite(&t,sizeof(t),1,fp);
		}
			fflush(stdin);
			printf("item edited\n");
			ch=getchar();
	}
	fclose(fp);
	fclose(fp1);
	remove("temp.dat");


}

void Delete()
{
	char ch;
	Itemlist();
	FILE *fp,*fp1;
	struct Item t;
	
	char barcode[20];
	
	int found=0;
	
	fp=fopen(fname,"rb");
	fp1=fopen("temp.dat","wb");

	fflush(stdin);
	printf("Enter barcode to delete:");
	scanf("%[^\n]s",barcode);

	while(1)
	{
		fread(&t,sizeof(t),1,fp);
		if(feof(fp))
			break;
		if(strcmp(t.barcode,barcode)==0)
			found=1;
		else
			fwrite(&t,sizeof(t),1,fp1);
	}
	fclose(fp);
	fclose(fp1);
	
	if(found==0)
	{	
		printf("invalid barcode no item found\n");
		fflush(stdin);
		//printf("item added\n");
		ch=getchar();
	}
	
	else
	{
		fp=fopen(fname,"wb");
		fp1=fopen("temp.dat","rb");
		
		while(1)
		{	
			fread(&t,sizeof(t),1,fp1);
			if(feof(fp1))
				break;
			fwrite(&t,sizeof(t),1,fp);
		}
		fflush(stdin);
		printf("item deleted\n");
		ch=getchar();
	}
	fclose(fp);
	fclose(fp1);
	remove("temp.dat");
	

}

void displaybill()
{
	struct Billitem t;
	int count=1;
	
	int buy,gfree,freebase;	

	FILE *fp;
	fp=fopen(bfname,"rb");
	

	system("cls");
	printf("            {{ %s }}\n",shopname);
	printf("______________________________________________________________________\n");
	printf("|Sl.no|  Barcode |   Name   | Price |Qty/unit|Freeoff|Discount|\n");
	printf("______________________________________________________________________\n");
	while(1)
	{
		fread(&t,sizeof(t),1,fp);
		if (feof(fp))
		{
			break;
		}
		
		buy=t.freeones/10;
		gfree=t.freeones%10;
		freebase=t.qty/buy;
		
		printf(" %5d%",count++);
		printf(" %-10s",t.barcode);
		printf(" %-10s",t.itemname);
		printf(" %6.2f",t.price);
		printf(" %8.2f",t.qty);
		printf(" %7d",freebase*gfree);
		printf(" %6.2f",(t.discount*t.price*t.qty)/100);
		
		printf("\n");
		if(tkey)
			total = total + t.price*t.qty - t.price*t.qty*t.discount/100;
	}
	printf("______________________________________________________________________\n");
	if(tkey)
		printf("                                                Total = %-6.2f\n",total);
	fclose(fp);
}


void Receipt()
{
	remove("Bill.txt");
	FILE *fp,*fp1;
	fp1=fopen("Bill.txt","w");
		

	struct Billitem t;
	int count=1;
	
	int buy,gfree,freebase;	

	
	fp=fopen(bfname,"rb");
	

	//system("cls");
	fprintf(fp1,"            {{ %s }}            %s\n",shopname,__TIME__);
	fprintf(fp1,"Bill no:%d                                          %s\n",billno,__DATE__);
	fprintf(fp1,"______________________________________________________________________\n");
	fprintf(fp1,"|Sl.no|  Barcode |   Name   | Price |Qty/unit|Freeoff|Discount|\n");
	fprintf(fp1,"______________________________________________________________________\n");
	while(1)
	{
		fread(&t,sizeof(t),1,fp);
		if (feof(fp))
		{
			break;
		}
		
		buy=t.freeones/10;
		gfree=t.freeones%10;
		freebase=t.qty/buy;
		
		fprintf(fp1," %5d%",count++);
		fprintf(fp1," %-10s",t.barcode);
		fprintf(fp1," %-10s",t.itemname);
		fprintf(fp1," %6.2f",t.price);
		fprintf(fp1," %8.2f",t.qty);
		fprintf(fp1," %7d",freebase*gfree);
		fprintf(fp1," %6.2f",(t.discount*t.price*t.qty)/100);
		
		fprintf(fp1,"\n");
		
			total = total + t.price*t.qty - t.price*t.qty*t.discount/100;
	}
	fprintf(fp1,"______________________________________________________________________\n");
	
	fprintf(fp1,"                                                Total = %-6.2f\n",total);
	fclose(fp);
	fclose(fp1);
}


void transc()
{
	char ch;
	displaybill(tkey);
	printf("\tEnter cash provided by customer:");
	scanf("%f",&cash);
	fflush(stdin);
	change= cash - total;
	printf("\tChange = %-6.2f",change);
		
	printf("\n\tThank you for shopping\n\twith %s\n",shopname);
	fflush(stdin);
	ch=getchar();
	total=0;
	cash=0;
	tkey=0;
	billno++;
	Receipt();


}

void Update(char *barcode,float soldqty)
{
	FILE *fp,*fp1;
	
	struct Item t;

	int found=0;
	fp=fopen(fname,"rb");
	fp1=fopen("temp2.dat","wb");
	while(1)
	{
		fread(&t,sizeof(t),1,fp);
		
		if(feof(fp))
			break;
		
		if (strcmp(t.barcode,barcode)==0)
		{
			found=1;
			t.soldqty=soldqty;
			fwrite(&t,sizeof(t),1,fp1);
		}
		else
			fwrite(&t,sizeof(t),1,fp1);
	}
	fclose(fp);
	fclose(fp1);
	
	if(found==0)
	{
		;
	}
	
	else
	{
		fp=fopen(fname,"wb");
		fp1=fopen("temp2.dat","rb");
		
		while(1)
		{
			fread(&t,sizeof(t),1,fp1);
			if(feof(fp1))
				break;
			fwrite(&t,sizeof(t),1,fp);
		}
	}
	fclose(fp);
	fclose(fp1);
	remove("temp2.dat");	
	
}
	

/*
void editbill()
{
	char ch='y';
	FILE *fp,*fp1,*fp2,*fp3;
	tkey=0;
	char barcode[20];int qty;
	int found=0;
	struct Billitem t;
	struct Item t1;

	while(ch='y')
	{
		displaybill();
		fflush(stdin);
		printf("Enter barcode:");
		scanf("%[^\n]s",barcode);
		
		
		printf("Enter new quantity:");
		scanf("%d",qty);
		fp=fopen(bfname,"rb");
		fp1=fopen("temp.dat","wb");
		
	
		while(1)
		{
			fread(&t,sizeof(t),1,fp);
			
			if(feof(fp))
				break;
			if(strcmp(t.barcode,barcode)==0)
			{
				found=1;
				fp2=fopen(fname,"rb");
				fp3=fopen("temp2.dat","wb");

				while(1)
				{
					fread(&t1,sizeof(t1),1,fp2);
		
					if(feof(fp2))
						break;
		
					if (strcmp(t1.barcode,barcode)==0)
					{
						
						if(t1.freeones==0)
							t1.soldqty = t1.soldqty - t1.defqty*((float)(t.qty)) + t1.defqty*((float)(qty)));
//divbyzero				
						else
							t1.soldqty = t1.soldqty - t.1defqty*((float)(t.qty)) - (((float)(t.qty/(t1.freeones/10))*(t1.freeones%10))*t1.defqty) + t.1defqty*((float)(qty)) - (((float)(qty/(t1.freeones/10))*(t1.freeones%10))*t1.defqty);
						
						fwrite(&t1,sizeof(t1),1,fp3);
						
					}
					else
						fwrite(&t1,sizeof(t1),1,fp3);			
				}
				fclose(fp2);
				fclose(fp3);

				t.qty=qty;
				fwrite(&t,sizeof(t),1,fp1);
				
				
				fp2=fopen(fname,"wb");
				fp3=fopen("temp2.dat","rb");
		
				while(1)
				{
					fread(&t1,sizeof(t1),1,fp3);
					if(feof(fp3))
						break;
					fwrite(&t1,sizeof(t1),1,fp2);
				}
				
				fclose(fp2);
				fclose(fp3);
				remove("temp2.dat");
			}
	
			else
				fwrite(&t,sizeof(t),1,fp1);
			
		}
		fclose(fp);
		fclose(fp1);
		if(found==0)
			printf("invalid barcode try again\n");
		else
		{
			fp=fopen(bfname,"wb");
			fp1=fopen("temp.dat","rb");
		
			while(1)
			{
				fread(&t,sizeof(t),1,fp1);
				if(feof(fp1))
					break;
				fwrite(&t,sizeof(t),1,fp);
			}
		}			
		fclose(fp);
		fclose(fp1);
		remove("temp.dat");
		
		
		printf("Do want to edit more items(y/n):");
		fflush(stdin);
		ch=getchar();


		if(ch=='n')
			break;
	}
	displaybill();
	while((tkey==0)||(tkey==1))
	{
		printf("\npress1. to proceed with transaction\npress0. make changes to the bill\n");
		scanf("%d",&tkey);
		
		if(tkey==1)
		{
			transc();
			break;
		}

		if(tkey==0)
		{
			while(tkey!=1)
			{
				printf("1.proceed with transaction\n");
				printf("2.edit bill item quantity\n");
				printf("3.delete bill item\n");
				printf("\nenter option:");
				scanf("%d",&tkey);
				switch(tkey)
				{
					case 1:
						transc();
						break;
					case 2:
						editbill();
					case 3:
						dellbill();
						break;
					default:
						printf("invalid option\n");

				}
			}
		}

		//printf("%d",tkey);
		if((tkey!=1)||(tkey!=0))
			printf("\ninvalid option try again\n");
	}	
}

void dellbill()
{
	char barcode[20];
	char ch='y';int found=0;
	FILE *fp,*fp1,*fp2,*fp3;
	tkey=0;
	struct Billitem t;
	struct Item t1;
	
	while(ch='y')
	{
		displaybill();
		fflush(stdin);
		printf("enter barcode:");
		scanf("%[^\n]s",barcode);
		
		fp=fopen(bfname,"rb");
		fp1=fopen("temp.dat","wb");
		while(1)
		{
			fread(&t,sizeof(t),1,fp);
			
			if(strcmp(t.barcode,barcode)==0)
			{		
				found=1;
				fp2=fopen(fname,"rb");
				fp3=fopen("temp2.dat","wb");

				while(1)
				{
					fread(&t1,sizeof(t1),1,fp2);
		
					if(feof(fp2))
						break;
		
					if (strcmp(t1.barcode,barcode)==0)
					{
						
						if(t1.freeones==0)
							t1.soldqty = t1.soldqty - t1.defqty*((float)(t.qty)); 
//divbyzero				
						else
							t1.soldqty = t1.soldqty - t.1defqty*((float)(t.qty)) - (((float)(t.qty/(t1.freeones/10))*(t1.freeones%10))*t1.defqty);
						
						fwrite(&t1,sizeof(t1),1,fp3);
					}
					else
						fwrite(&t1,sizeof(t1),1,fp3);
				}
				fclose(fp2);
				fclose(fp3);
				
				fp2=fopen(fname,"wb");
				fp3=fopen("temp2.dat","rb");
				while(1)
				{
					fread(&t1,sizeof(t1),1,fp3);
					if(feof(fp3))
						break;
					fwrite(&t1,sizeof(t1),1,fp2);
				}	
				fclose(fp2);
				fclose(fp3);
				remove("temp2.dat");
			}
			else
				fwrite(&t,sizeof(t),1,fp1);
		}
		fclose(fp);
		fclose(fp1);
		if(found==0)
			printf("invalid barcode try again\n");
		else
		{
			fp=fopen(bfname,"wb");
			fp1=fopen("temp.dat","rb");
		
			while(1)
			{
				fread(&t,sizeof(t),1,fp1);
				if(feof(fp1))
					break;
				fwrite(&t,sizeof(t),1,fp);
			}
		}			
		fclose(fp);
		fclose(fp1);
		remove("temp.dat");
		
		
		printf("Do want to edit more items(y/n):");
		fflush(stdin);
		scanf("%c",&ch);


		if(ch=='n')
			break;
	}

	displaybill();
	while((tkey==0)||(tkey==1))
	{
		printf("\npress1. to proceed with transaction\npress0. make changes to the bill\n");
		scanf("%d",&tkey);
		
		if(tkey==1)
		{
			transc();
			break;
		}

		if(tkey==0)
		{
			while(tkey!=1)
			{
				printf("1.proceed with transaction\n");
				printf("2.edit bill item quantity\n");
				printf("3.delete bill item\n");
				printf("\nenter option:");
				scanf("%d",&tkey);
				switch(tkey)
				{
					case 1:
						transc();
						break;
					case 2:
						editbill();
					case 3:
						dellbill();
						break;
					default:
						printf("invalid option\n");

				}
			}
		}

		//printf("%d",tkey);
		if((tkey!=1)||(tkey!=0))
			printf("\ninvalid option try again\n");
	}	
}

*/
	
void Bill()
{
	
	
	
	
	char ch='y'; 
	int ic=0;int found=0;
	
	char barcode[20];
	int qty;
	
	struct Item t;
	struct Billitem t1;
	
	FILE *fp,*fp1;
	remove(bfname);

	
	
	while(ch='y')
	{
		system("cls");
		Itemlist();
		
		
		printf("-----------------------------------------\n");
		printf("\t   Bill\n");
		printf("-----------------------------------------\n");
		
			
		found=0;
		
		fp=fopen(fname,"rb");
		fp1=fopen(bfname,"ab");	
		
		int buy,gfree;
		struct Item t;
		struct Billitem t1;
		
		
		fflush(stdin);
		printf("Enter barcode:");
		scanf("%[^\n]s",barcode);
		
		fflush(stdin);
		printf("Enter no. of units:");
		scanf("%d",&qty);
			
		fflush(stdin);	
		while(1)
		{	
			fread(&t,sizeof(t),1,fp);
			
			if(feof(fp))
				break;
		
			if(strcmp(t.barcode,barcode)==0)
			{
				found=1;
				strcpy(t1.barcode,t.barcode);
				strcpy(t1.itemname,t.itemname);
				t1.price=t.price;
		
				t1.freeones=t.freeones;
				t1.discount=t.discount;
				t1.qty=qty;
				
				if(t.freeones==0)
					t.soldqty = t.soldqty + t.defqty*((float)(qty));
//divbyzero				
				else
					t.soldqty = t.soldqty + t.defqty*((float)(qty)) + (((float)(qty/(t.freeones/10))*(t.freeones%10))*t.defqty);
				//printf("%d\n",t.soldqty);
				
				Update(barcode,t.soldqty);
			
				fwrite(&t1,sizeof(t1),1,fp1);
			}
			
		}
		fclose(fp);
		fclose(fp1);
		
		if(found==0)
			printf("invalid barcode try again\n");	
		
		
		fflush(stdin);
		printf("Do you want to add more items to the bill(y/n):");
		scanf("%c",&ch);
			
			
	
		
		if(ch=='n')
			break;
	}
		
	displaybill();
	while((tkey==0)||(tkey==1))
	{
		printf("\npress1. to proceed with transaction\n");
		scanf("%d",&tkey);
		
		if(tkey==1)
		{
			transc();
			break;
		}

		/*if(tkey==0)
		{
			while(tkey!=1)
			{
				printf("1.proceed to transaction\n");
				printf("2.edit bill item(quantity)\n");
				printf("3.delete bill item\n");
				printf("\nenter option:");
				scanf("%d",&tkey);
				switch(tkey)
				{
					
					case 1:
						transc();
						break;
					case 2:
						editbill();
						break;
					case 3:
						dellbill();
						break;
					default:
						printf("invalid option\n");
				}

			}
			
		}*/
		
		//printf("%d",tkey);
		if((tkey!=1)||(tkey!=0))
			printf("\ninvalid option try again\n");
	}	
		
	
}
	
		
		
		




















		
					