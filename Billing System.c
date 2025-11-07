#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct product {
	int id;
	char name[30];
	float price;
	int quantity;
};
 
 struct purchasedItem{
 	int id;
 	char name[30];
 	float price;
 	int quantity;
 	float subtotal;
 };
 
void addProduct();
void displayProducts();
void generateBill();
void clearAllItemsFromFile();

int main()
{
	int choice;
	
	while(1)
	{
		printf("\n======BILLING SYSTEM MENU======\n");
		printf("1. Add Product\n");
		printf("2. Display Products\n");
		printf("3. Generate Bill\n");
		printf("4.Clear All Items From File.\n");
		printf("5. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		
		switch(choice)
		{
			case 1:
				addProduct();
				break;
			case 2:
				displayProducts();
				break;
			case 3:
				generateBill();
				break;
			case 4:
				clearAllItemsFromFile();
			    break;
			case 5:
				printf("Exiting....Thankyou!\n");
				exit(0);
			
			default:
				printf("Invalid choice! Try again.\n");
		}
	}
}

void addProduct()
{
	FILE *fp;
	struct product p;
	fp=fopen("products.txt","a");
	
	if(fp==NULL)
	{
		printf("Error opening file!\n");
		return;
	}
	
	printf("Enter product ID:");
	scanf("%d",&p.id);
	printf("Enter product name:");
	scanf("%s",p.name);
	printf("Enter price:");
	scanf("%f",&p.price);
	printf("Enter quantity:");
	scanf("%d",&p.quantity);
	
	fprintf(fp, "%d %s %.2f %d\n",p.id,p.name,p.price,p.quantity);
	fclose(fp);
	printf("Product added successfully!\n");
}

void displayProducts()
{
	FILE *fp;
	struct product p;
	fp=fopen("products.txt","r");
	
	if(fp==NULL)
	{
		printf("No products found!\n");
		return;
	}
	
	printf("\n=====AVAILABLE PRODUCTS=====\n");
	printf("%-10s %-20s %-10s %-10s\n","ID","Name","Price","Quantity");
	printf("----------------------------------------------------------\n");
	
	while(fscanf(fp,"%d %s %f %d",&p.id,p.name,&p.price,&p.quantity)!=EOF)
	{
		printf("%-10d %-20s %-10.2f %-10d\n",p.id,p.name,p.price,p.quantity);
	}
	fclose(fp);
}

 void clearAllItemsFromFile()
    {
    	FILE *fp=fopen("products.txt","w");
    	
    	if(fp==NULL)
    	{
    		printf("\nError opening file!|n");
    		return;
		}
		fclose(fp);
		printf("\n All Items cleared successfully from file!|n");
	}
	
	
void generateBill()
{
	FILE *fp;
	struct product p;
	struct purchasedItem items[50];
	int searchId,qty,found,count=0;
	float total=0,amount;
	
	fp=fopen("products.txt","r");
	if(fp==NULL)
	{
		printf("No products found!\n");
		return;
	}
	
	printf("Enter product ID to purchase(0 to finish):");
	while(1)
	{
		scanf("%d",&searchId);
		if(searchId==0)
		break;
		
		rewind(fp);
		found=0;
		
		while(fscanf(fp,"%d %s %f %d",&p.id,p.name,&p.price,
		&p.quantity)!=EOF)
		{
			if(p.id==searchId)
			{
				printf("Enter quantity:");
				scanf("%d",&qty);
				if(qty>p.quantity)
				{
					printf("Not enough stock available!\n");
				}
				else
				{
					amount=p.price*qty;
					total+=amount;
					
					items[count].id = p.id;
                    strcpy(items[count].name, p.name);
                    items[count].price = p.price;
                    items[count].quantity = qty;
                    items[count].subtotal = amount;
                    count++;
                    
					printf("Added");
				}
				found=1;
				break;
			}
		}
		if(!found)
		printf("Product not found!\n");
		printf("\nEnter next productId(0 to finish):");
	}
	fclose(fp);
	
	if(count==0)
	{
		printf("No items purchased.\n");
		return;
	}
	
 printf("\n=========================================================================\n");
    printf("                           FINAL BILL                         \n");
    printf("=========================================================================\n");
    printf("%-5s %-15s %-10s %-10s %-10s\n", "ID", "Product", "Qty", "Price", "Subtotal");
    printf("----------------------------------------------------------\n");

    int i;
    for (i = 0; i < count; i++)
    {
        printf("%-5d %-15s %-10d %-10.2f %-10.2f\n",
               items[i].id,
               items[i].name,
               items[i].quantity,
               items[i].price,
               items[i].subtotal);
    }
    printf("----------------------------------------------------------\n");
    printf("%-42s Rs. %.2f\n", "TOTAL BILL:", total);
    printf("============================================================\n");
    
   
}
