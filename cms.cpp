#include<iostream>
#include<stdlib.h>
#include<string>
#include<cstring>
#include<ctime>
#include<fstream>
#include<sstream>
using namespace std;

typedef struct Listof_Items{
    public:
    char name[50];
    int price;
    struct Listof_Items *next;
}li;

//Dynamic Usage Array - Storing Quantity of Items Selected By User
int buylist_len = 15;
int *buylist = (int*) calloc(15,sizeof(int));

class Coupons{
    public:
        string coupon;
};

class Canteen{
    Coupons cpn[5];
    string username;
    float totalprice = 0;
    float discount = 0;
    public:
    void reset(){
        totalprice = 0;
        discount = 0;
        username = " ";
        for(int i=0;i<buylist_len;i++)
            buylist[i] = 0; 
    }

    void setCoupons(){
        cpn[0].coupon = "GET10";
        cpn[1].coupon = "FREE20";
        cpn[2].coupon = "MAKEMYDAY30";
        cpn[3].coupon = "SUPER40";
        cpn[4].coupon = "LETMELOOT50";
    }

    li *canteenMenu(li *head){
    li *temp = head;
    int i = 0;
    cout<<" -- Canteen Management System -- ";
    cout<<"\n-------------------------------------------------------------------------------";
    cout<<"\n S.No	      Item                                           Price [INR]";
    cout<<"\n===============================================================================";
    while(temp != NULL){
        i++;
        if(i<10)
            cout<<endl<<" 0"<<i<<"\t"<<temp->name;
        else
            cout<<endl<<" "<<i<<"\t"<<temp->name;
        char *p = temp->name;
        int wlen = 0;
        while(*p != '\0'){
            wlen++;
            p++;
        }
        for(int i=0;i<=55-wlen;i++)
            cout<<" ";
        cout<<temp->price;    
        temp = temp->next;
    }
    cout<<"\n-------------------------------------------------------------------------------";
    int item, qty;
    char ch;
    do{
        cout<<"\nEnter Item Serial Number To Buy: ";
        cin>>item;
        if(item<=i && item>=1){
            cout<<"Enter Quantity: ";
            cin>>qty;
            buylist[item-1] += qty;
        }
        else
            cout<<"-- Try Again, Enter Available Serial Number --\n";
    cout<<"\nDo You Want To Buy More Items (Y/N): ";
    cin>>ch;
    }
    while(ch == 'Y' || ch == 'y');

    int readyForCheckout = 0;
    for(int i=0;i<buylist_len;i++){
        if(buylist[i] > 0){
            readyForCheckout = 1;
            break;
        }
    }
    if(readyForCheckout == 1){
        cout<<"\nEnter Your Name: ";
        fflush(stdin);
        getline(cin,username);
        
        //Turing username to LowerCase
        for(int i=0;i<username.length();i++){
            if(username[i] < 97 && username[i] != ' ')
                username[i] += 32;
        }
        //Capitalizing username
            username[0] -= 32;
        for(int i=1;i<username.length();i++){
            if(username[i-1] == ' ')
                    username[i] -= 32;
        }

        checkout(head);
        buylist_len = i;
    }
    else{
        fflush(stdin);
        cout<<"\n -> You Have Not Purchased Anything";
        cout<<"\n\n -> Press Any Key To Exit";
        getchar();
    }
    
    return head;
}

li *checkout(li *head){
    char retry;
    do{
    li *temp = head;
    int i = 0;
    system("cls");
    cout<<" -> Canteen Management System\n";
    cout<<"\n [ YOUR ITEMS ]";
    cout<<"\n-------------------------------------------------------------------------------";
    cout<<"\n S.No	      Item                                         Qty   Price [INR]";
    cout<<"\n===============================================================================";
    while(temp!=NULL){
        if(buylist[i] > 0){
            if(i<9)
                cout<<endl<<" 0"<<i+1<<"\t"<<temp->name;
            else
                cout<<endl<<" "<<i+1<<"\t"<<temp->name;
            char *p = temp->name;
            int wlen = 0;
            while(*p != '\0'){
                 wlen++;
                 p++;
            }
            for(int i=0;i<=50-wlen;i++)
                cout<<" ";
            cout<<buylist[i]<<"\t  "<<temp->price * buylist[i];
            totalprice += (float)temp->price * buylist[i];
        }
        temp = temp->next;
        i++;
    }
    cout<<endl<<endl;
    for(int i=0;i<24;i++) cout<<"  ";
    cout<<".. Total Cost ->  "<<totalprice;
    char ch;  
    if(retry == 'Y' || retry == 'y'){
        cout<<"\n\nPlease Write Coupon Code Carefully\n";
    } 
    else{
        cout<<"\n\nDo You Have Discount Coupon (Y/N) : ";
        cin>>ch;
    }
    
    if(ch == 'Y' || ch == 'y'){
        cout<<"Enter Coupon Code:";
        string code;
        cin>>code;
        for(int i=0;i<5;i++){
            if(code.compare(cpn[i].coupon) == 0){
                discount = (i+1)*10;
                cout<<"\n -- Hooray !! You Got "<<discount<<"%"<<" Discount --";
                totalprice -= (totalprice)*(discount/100);
                retry = 'n';
                break;
            }
            if(i==4){
                cout<<"\nSorry, Your Coupon is Invalid !!";
                cout<<"\nDo You Want to Retry (Y/N): ";
                cin>>retry;
            }
                
        }
    }
    }while(retry == 'y' || retry == 'Y');
    // ^^^ Re-painting Will Occur Due to Invalid Coupons Retry ^^^

    cout<<"\n-------------------------------------------------------------------------------";
    cout<<"\n Final Price : "<<totalprice<<" INR"<<endl;
    cout<<"\n Press Any Key To Generate Bill .. ";
    fflush(stdin);
    getchar();
    invoice(head);

    return head;
}
li *invoice(li *head){
    li *temp = head;
    system("cls");
    int i = 0;
    time_t now = time(0);
    char* dt = ctime(&now);
    cout<<" -> Canteen Management System\n";
    cout<<"\n-----------------------------------------------------------------------------------";
    cout<<"\n # "<<username<<"\t#Invoice "<<dt;
    cout<<"===================================================================================";
    cout<<"\n S.No	      Item                                         Qty   Price [INR]";
    while(temp!=NULL){
        if(buylist[i] > 0){
            if(i<9)
                cout<<endl<<" 0"<<i+1<<"\t"<<temp->name;
            else
                cout<<endl<<" "<<i+1<<"\t"<<temp->name;
            char *p = temp->name;
            int wlen = 0;
            while(*p != '\0'){
                wlen++;
                p++;
            }
            for(int i=0;i<=50-wlen;i++)
                cout<<" ";
            cout<<buylist[i]<<"\t  "<<temp->price * buylist[i];
        }
        temp = temp->next;
        i++;
    } 
    cout<<"\n\n-----------------------------------------------------------------------------------";
    cout<<"\n Discount Applied : "<<discount<<"%"<<"\t\t\t\t\t Total Cost : "<<totalprice<<" INR";
    cout<<"\n\n -- Thank You For The Purchase --";
    updateSalesFile(username,dt,totalprice);
    getchar();
    return head;
}
    void updateSalesFile(string uname,char *dt,float price){
        ofstream wf;
        wf.open("salesdata.dat",ios::app | ios::out | ios::binary);
        wf<<username<<endl<<totalprice<<endl<<dt;
        wf.close();
    }

};

//Extension for Edit Menu Function - adminMode Class 
class editMenuServices{
    public:
        char iname[50];
        float iprice;
        void getItemDetails(){
            fflush(stdin);
            cout<<"\tEnter Item Name : ";
            fgets(iname,50,stdin);
            int length = 0;
            //Removing endline Character from iname and Lowering all Characters
            for(int i=0;i<50;i++){
                length++;
                if(iname[i] == '\n'){
                    iname[i] = '\0';
                    break;
                }
                if(iname[i] < 97 && iname[i] != ' ')
                    iname[i] += 32;
            }

            //Capitalizing iname
            iname[0] -= 32;
            for(int i=1;i<length;i++){
                if(iname[i-1] == ' ')
                        iname[i] -= 32;
            }

            cout<<"\tEnter Item Price : ";
            cin>>iprice;
        }

        li* addnewItem1(li *head){
            int pos;
            system("cls");
            cout<<" -> Canteen Management System\n\n";
            cout<<" [ Add New Item (Specific Position) ]\n\n";
            getItemDetails();
            cout<<"\tEnter Position For Your Item : ";
            cin>>pos;
            buylist_len++;
            buylist = (int*) realloc(buylist,buylist_len*sizeof(int));
            li* newnode = (li*) malloc(sizeof(li));
            strcpy(newnode->name,iname);
            newnode->price = iprice;

            //If User Demands Position that we Don't Have, we Will Give him Bottom Position
            if(pos > buylist_len || pos <= 0)
                pos = buylist_len;

            if(pos == 1){
                newnode->next = head;
                fflush(stdin);
                cout<<"\n << Item Added Sucessfully >>";
                getchar();
                return newnode;
            }
            else{
                li* temp = head;
                int i=1;
                while(i != pos-1){
                    temp = temp->next;
                    i++;
                }
                li* t1 = temp->next;
                temp->next = newnode;
                newnode->next = t1;
                fflush(stdin);
                cout<<"\n << Item Added Sucessfully >> ";
                getchar();
                return head;
            }
        }

        li* addnewItem2(li *head){
            system("cls");
            cout<<" -> Canteen Management System\n\n";
            cout<<" [ Add New Item (Beginning) ]\n\n";
            getItemDetails();
            buylist_len++;
            buylist = (int*) realloc(buylist,buylist_len*sizeof(int));

            //Adding new node to LL
            li* newnode = (li*) malloc(sizeof(li));
            strcpy(newnode->name,iname);
            newnode->price = iprice;
            newnode->next = head;
            fflush(stdin);
            cout<<"\n << Item Added Sucessfully >> ";
            getchar();
            return newnode;
        }

        li* addnewItem3(li *head){
            system("cls");
            cout<<" -> Canteen Management System\n\n";
            cout<<" [ Add New Item (Bottom) ]\n\n";
            getItemDetails();
            buylist_len++;
            buylist = (int*) realloc(buylist,buylist_len*sizeof(int));
            //Traversing to NULL
            li *temp = head;
            while(temp->next != NULL)
                temp = temp->next;
            
            //Adding new node to LL
            li* newnode = (li*) malloc(sizeof(li));
            strcpy(newnode->name,iname);
            newnode->price = iprice;
            newnode->next = NULL;
            temp->next = newnode;
            fflush(stdin);
            cout<<"\n << Item Added Sucessfully >> ";
            getchar();
            return head;
        }

        li* removeItem(li *head){
            li* temp = head;
            system("cls");
            int sno;
            cout<<" -> Canteen Management System\n\n";
            cout<<" [ Remove Item ]\n\n";
            cout<<" Enter Item Serial No. to Remove : ";
            cin>>sno;
            if(sno > buylist_len || sno <= 0)
                cout<<"\n -> You Have Entered Invalid Serial Number ";
            else{
                buylist_len--;
                buylist = (int*) realloc(buylist,buylist_len*sizeof(int));
                if(sno == 1){
                    fflush(stdin);
                    cout<<"\n << Removed Item Sucessfully >> ";
                    getchar();
                    return head->next;
                }
                int x = 1;
                while(x != sno-1){
                    head = head->next;
                    x++;
                }
                li* f0 = head->next;
                head->next = (head->next)->next;
                free(f0);
                cout<<"\n << Removed Item Sucessfully >> ";
            }

            fflush(stdin);
            getchar();
            return temp;
        }

        li* replaceItem(li *head){
            int pos;
            system("cls");
            cout<<" -> Canteen Management System\n\n";
            cout<<" [ Replace Item ]\n\n";
            cout<<"\n Which Item You want to Replace : ";
            cin>>pos;
            if(pos > buylist_len || pos <= 0)
                cout<<"\n\n -> Sorry No Such Position Exist ";
            else{
                getItemDetails();
                li* temp = head;
                int x = 1;
                while(x != pos){
                    temp = temp->next;
                    x++;
                }
                strcpy(temp->name,iname);
                temp->price = iprice;

                cout<<"\n << Item Replaced Sucessfully >> ";
            }

            fflush(stdin);
            getchar();
            return head;
        }
};
class adminMode{
    public:
    int ops;
    li* auth(li *head){
        system("cls");
        string pass;
        char retry = 'N';
        cout<<"\n-> Admin Verification\n";
        do{
            retry = 'N';
            cout<<"\n Enter The Password: ";
            cin>>pass;
            if(pass.compare("7890") == 0)
                head = selector(head);
            else{
                cout<<"\n You Have Entered Wrong Password\n";
                cout<<" Do You Want to Retry (Y/N) !! ";
                cin>>retry;
            }
        }
        while(retry == 'y' || retry == 'Y');

        return head;
    }
    li* selector(li *head){
        system("cls");
        cout<<" -> Canteen Management System\n\n";
        cout<<" [ ADMIN MODE ]\n\n";
        cout<<"(1) Edit Food Menu\n";
        cout<<"(2) Show Overall Sales\n";
        cin>>ops;
        if(ops == 1)
            head = editMenu(head);
        else if(ops == 2)
            getSales();
        
        return head;
    }
    void getSales(){
        fflush(stdin);
        system("cls");
        ifstream rf;
        string line;
        float totalRevenue = 0.0;
        cout<<" -> Canteen Management System\n\n";
        cout<<" [ Overall Sales Records ]\n\n";
        rf.open("salesdata.dat",ios::in | ios::binary);
        if(!rf){
            cout<<"\t.. No Records Found !! ";
        }
        else{
        int ix = 0, ctr = 2;
        cout<<"    ";
        for(int i=0;i<34;i++)
            cout<<"===";
        cout<<"\n\tSerial No\tCustomer Name\t\t  Spending [INR]\t  Purchase Time [IST]\n";
        cout<<"    ";
        for(int i=0;i<34;i++)
            cout<<"===";

        cout<<"\n\t   1\t\t";
        while(rf){
            getline(rf,line);
            if(ix == 3){
                //Extra Last Line Added to salesdat.dat File will not be Printed
                if(line.compare("") == 0)
                    break;
                ix = 0;
                cout<<"\t   "<<ctr++<<"\t\t";
            }
            cout<<line;
            for(int i=0;i<=4;i++) cout<<" ";
            if(ix == 0){
                for(int i=1;i<= (27 - line.length());i++) cout<<" ";
            }
            else if(ix == 1){
                for(int i=0;i<= 10 - line.length();i++) cout<<" ";
                stringstream num(line);
                float xy;
                num >> xy;
                totalRevenue += xy;
            }
            else if(ix == 2)
                cout<<endl;
                   
            ix++;
        }
        rf.close();

        //Footer of Sales Page
        cout<<"\n    ";
        for(int i=0;i<34;i++)
            cout<<"---";
        cout<<"\n\t"<<"Total Customers : "<<ctr-1<<"\t\t\t\tTotal Revenue Collected : "<<totalRevenue<<" INR";
        cout<<"\n    ";
        for(int i=0;i<34;i++)
            cout<<"---";
        }

        getchar();
    }
    li* editMenu(li *head){
        int ops;
        editMenuServices ems;
        do{
        system("cls");
        fflush(stdin);
        cout<<" -> Canteen Management System\n\n";
        cout<<"[ Edit Food Menu ]\n\n";
        cout<<"(1) Add New Item (Specific Position)\n(2) Add New Item (Beginning)";
        cout<<"\n(3) Add New Item (Bottom)\n\n(4) Remove Item\n(5) Replace Item\n";
        cout<<"\n\nEnter Your Preferred Choice: ";
        cin>>ops;
        switch(ops){
            case 1: head = ems.addnewItem1(head);
                    break;
            case 2: head = ems.addnewItem2(head);
                    break;
            case 3: head = ems.addnewItem3(head);
                    break;
            case 4: head = ems.removeItem(head);
                    break;
            case 5: head = ems.replaceItem(head);
                    break;
        }
        }
        while(ops > 5 || ops < 1);

        return head;
    }

};

void welcomePage(){
    cout<<endl;
    cout<<" << Welcome To Canteen Mangement System >>\n\n";
    cout<<"      < Press any Key To Continue >\n ";
    getchar();
    system("cls");
}
int userSelectionPage(){
    int a;
    cout<<endl;
    cout<<" -> Welcome To Canteen Mangement System \n\n";
    cout<<"\n Enter a Choice:\n  (1) Continue as Customer\n  (2) Continue as Admin\n  (3) Exit\n";
    cin>>a;
    system("cls");
    return a;
}
li *setItems(li *head){
        li *temp = head;
        for(int i=0;i<14;i++){
            temp->next = (li*) malloc(sizeof(li));
            temp = temp->next;
            if(i==14) temp->next = NULL;
        }
        temp = head;
        //1
        strcpy(temp->name,"UNIBIC Cashew Badam Cookies, 500 g\0");
        temp->price = 60;
        temp = temp->next;
        //2
        strcpy(temp->name,"MAGGI NUTRI-LICIOUS Masala Veg Atta Noodles\0");
        temp->price = 80;
        temp = temp->next;
        //3
        strcpy(temp->name,"Cadbury Bournvita Health Drink, 1Kg Pouch\0");
        temp->price = 340;
        temp = temp->next;
        //4
        strcpy(temp->name,"Del Monte Tomato Ketchup Spout Pack, 950g\0");
        temp->price = 79;
        temp = temp->next;
        //5
        strcpy(temp->name,"Sunfeast Dark Fantasy Choco Chip 350g Pack\0");
        temp->price = 75;
        temp = temp->next;
        //6
        strcpy(temp->name,"Fortune Rozana Basmati Rice, 1kg\0");
        temp->price = 67;
        temp = temp->next;
        //7
        strcpy(temp->name,"Cadbury Gems Minis Home Treats Pack, 142.2g\0");
        temp->price = 100;
        temp = temp->next;
        //8
        strcpy(temp->name,"Cadbury Dairy Milk Silk Chocolate Bar, 150g\0");
        temp->price = 432;
        temp = temp->next;
        //9
        strcpy(temp->name,"Cadbury Dairy Milk Silk Valentine Chocolate Bar\0");
        temp->price = 340;
        temp = temp->next;
        //10
        strcpy(temp->name,"Premium Californian Almonds Value Pack\0");
        temp->price = 437;
        temp = temp->next;
        //11
        strcpy(temp->name,"Cadbury Oreo Original Chocolatey Sandwich\0");
        temp->price = 55;
        temp = temp->next;
        //12
        strcpy(temp->name,"Dabur Honey:No Sugar Adulteration\0");
        temp->price = 378;
        temp = temp->next;
        //13
        strcpy(temp->name,"Tata Salt, 1kg\0");
        temp->price = 17;
        temp = temp->next;
        //14
        strcpy(temp->name,"Dabur Chyawanprash\0");
        temp->price = 299;
        temp = temp->next;
        //15
        strcpy(temp->name,"Parle Rusk, Elaichi, 300g\0"); 
        temp->price = 34;

        return head;
}
int main(){
    Canteen obj;
    adminMode am;
    li *head = (li*) malloc(sizeof(li));
    head = setItems(head);
    obj.setCoupons();
    welcomePage();
    int ops;
    do{
        system("cls");
        ops = userSelectionPage();
        switch(ops){
            case 1: head = obj.canteenMenu(head);
                    break;
            case 2: head = am.auth(head);
                    break;
        }

        //Resetting For New User
        obj.reset();
    }
    while(ops != 3);

    return 0;
}