#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct items{
    char item[20];
    float price;
    int quantity;
};

struct orders{
    char customer[50];
    char date[50];
    int noOfitems;
    struct items itm[50];
};



//function to generate bills
//billheader
void generateBillHeader(char name[50] , char date[30]){
    printf("\n\n");
    printf("\t    Undergraduates Cafe");
    printf("\n\t  -----------------------");
    printf("\nDate:%s",date);
    printf("\nInvoice To: %s",name);
    printf("\n");
    printf("------------------------------------------\n");
    printf("Items\t\t");
    printf("Quantity\t");
    printf("Total\t");
    printf("\n------------------------------------------");
    printf("\n\n");

}


//billbody
void generateBillBody(char item[30] , int quantity , float price){
    printf("%s\t\t",item);
    printf("%d\t\t",quantity);
    printf("%.2f\t\t",quantity*price);
    printf("\n");
}

//billfooter
void generateBillFooter(float total){
    printf("\n");
    float discount = 0.1 * total;
    float net_total= total - discount;
    float cgst = 0.12*net_total;
    float grand_total = net_total + 2*cgst;  // grand_total = net_toal + cgst + sgst
    printf("------------------------------------------\n");
    printf("Sub Total\t\t\t%.2f",total);
    printf("\nDiscount 10%s\t\t\t%.2f","%",discount);
    printf("\n\t\t\t\t-------");
    printf("\nNet Total\t\t\t%.2f",net_total);
    printf("\nCGST 12%s\t\t\t%.2f","%",cgst);
    printf("\nSGST 12%s\t\t\t%.2f","%",cgst);    
    printf("\n------------------------------------------");
    printf("\nGrand Total\t\t\t%.2f",grand_total);
    printf("\n------------------------------------------\n");
}

int main(){
    int optiion,n;
    struct orders order;  //calling the structure
    struct orders ord;
    FILE *fp;  //fp = file pointer
    char saveBill = 'y' ,continue_flag = 'y';
    char name[50];

    //dashboard
while(continue_flag == 'y'){
    float total=0.0;
    int invoice_found=0;
        printf("\n\t========== Undergraduates Cafe ==========");
        printf("\n\nPlease select your prefered option  ");
        printf("\n\n1.Generate Invoice");
        printf("\n2.Show all Invoices");
        printf("\n3.Search Invoice");
        printf("\n4.Exit");

        printf("\n\nYour Choice : ");
        scanf("%d",&optiion);
        fgetc(stdin);  //this line is here just to consume \n
    switch(optiion){
        case 1:
        system("cls");  // and system("cls") works only on windows
        //it is use to clear the interphase after choosing case 1
        

        printf("\nPlease enter the name of the castomer: \t");
        fgets(order.customer , 50 , stdin);  // Reads a line including spaces bcz of stdin
        order.customer[strlen(order.customer)-1] = 0; 
        /* line 83 is just to remove \n from the input
            as if we input tanvir ,it stores as tanvir\n  so just identifing the
            actual length of the string and deducting the last \n by assigning value 0 for that*/
        strcpy(order.date,__DATE__);  //copying date from real time date function
        
        printf("\nPlease enter the number of items : ");
        scanf("%d",&n);
        order.noOfitems = n ;

        for(int i=0 ; i < n ; i++){
            fgetc(stdin);
            printf("\n\n");
            printf("Please enter the item %d :\t",i+1);
            fgets(order.itm[i].item,20,stdin);
            order.itm[i].item[strlen(order.itm[i].item)-1] = 0;

            printf("Please enter the unit price:\t");
            scanf("%f",&order.itm[i].price);
            printf("Please enter the quantity:\t");
            scanf("%d",&order.itm[i].quantity);
            

            total += order.itm[i].quantity * order.itm[i].price;
        }

        generateBillHeader(order.customer , order.date);
        for(int i=0 ; i<order.noOfitems ; i++){
            generateBillBody(order.itm[i].item , order.itm[i].quantity , order.itm[i].price);
        }
        generateBillFooter(total);

        printf("\nDo you want to save the invoice [y/n]:\t");
        scanf(" %c",&saveBill);

        if(saveBill == 'y'){
            fp = fopen("RestaurantBill.dat","ab");  //ab refers to append mood 
            // fwrite(&order,sizeof(struct orders),1,fp);
            // if(fwrite != 0 ){
            if(fp == NULL){
                printf("\nError opening file for writing!");
            }
            else{
                if(fwrite(&order,sizeof(struct orders),1,fp) == 1 ){
                    printf("\nSuccessfully saved");
                }
                else printf("\nError saving");
            }
            fclose(fp);
        }
        break;

        case 2:
        system("cls");
        fp = fopen("RestaurantBill.dat","r");
        printf("\n   *****Your Previous Invoices*****");
        while(fread(&ord,sizeof(struct orders),1,fp)){
            total=0;  //reseting total for every different invoices
            generateBillHeader(ord.customer,ord.date);
            for(int i=0 ; i<ord.noOfitems ; i++){
                generateBillBody(ord.itm[i].item ,ord.itm[i].quantity ,ord.itm[i].price );
                total += ord.itm[i].quantity * ord.itm[i].price;
            }
            generateBillFooter(total);
        }
        fclose(fp);
        break;

        case 3:
        printf("\nEnter the name of the customer :\t");
        // fgetc(stdin);
        fgets(name,50,stdin);
        name[strlen(name)-1] = 0;
        system("cls");
        fp = fopen("RestaurantBill.dat","r");
        printf("\t*****Invoice Of %s*****\n",name);
        while(fread(&ord,sizeof(struct orders),1,fp)){
            total=0;  //reseting total for every different invoices
            if(!strcmp(ord.customer , name)){
                generateBillHeader(ord.customer,ord.date);
                for(int i=0 ; i<ord.noOfitems ; i++){
                    generateBillBody(ord.itm[i].item ,ord.itm[i].quantity ,ord.itm[i].price );
                    total += ord.itm[i].quantity * ord.itm[i].price;
                }
                generateBillFooter(total);
                invoice_found = 1;
            }
            
        }
        if(!invoice_found){
            printf("Sorry the invoice for %s does not exists",name);
        }
        fclose(fp);
        break;

        case 4:
        printf("\n\t\t Bye Bye :\") \n\n");
        exit(0);  //to terminate whole program
        break;

        default:
        printf("Sorry invalid option");
        break;
    }
    printf("\nDo you want to perform another operation ? [y/n] :");
    scanf(" %c",&continue_flag);

}
    printf("\n\n");
    return 0 ;
}



