#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
#include<conio.h>
#define ENTER_CHAR '\n'
#define YES_LOWER 'y'
#define YES_UPPER 'Y'
#define NO_LOWER 'n'
#define NO_UPPER 'N'
#define A_LOWER 'a'
#define Z_LOWER 'z'
#define SPACE ' '
#define END_STRING '\0'
#define N_MAX 100
#define DISCOUNT 400000
#define ENTER_INT 13
#define ESC 27
#define BACKSPACE 8

typedef struct InfoFoodCustomer {
	// luu ten mon
	char *item;
	// ma mon
	int choice;
	// so luong
	int quantity;
	// don gia
	int price;
	// thanh tien
	int amount; 
} Food;

typedef struct Customer {
	// luu thoi gian goi mon
	char* time;
	// dem so lan order mon an
	int countFood;
	// con tro struct luu thong tin moi lan goi mon
	Food *listInforFood;
	// ban order
	int table;
	// tong tien
	int total;
	// thanh toan
	int pay;
	// giam gia
	int discount;	
} Cus; 

// Tra ve thoi gian khach hang goi mon

char* displayTime(char* saveTime){
	time_t rawtime; 
	time(&rawtime);
	struct tm *timeptr;
	timeptr = localtime(&rawtime);
	strftime(saveTime, 30, "%x - %I:%M:%S %p", timeptr);
	//tra ve con tro saveTime kieu char 
	return saveTime;
}

// Xoa bo ki tu \n khi dung ham fgets()

void deleteEnter(char* name) {
	int length = strlen(name);
	if (name[length-1] == ENTER_CHAR) {
		name[length-1] = END_STRING;
	}
}

// In hoa cac chu cai dau cua ho va ten dem

void upperCaseName(char* name) {
	int length = strlen(name);
	name[0] = name[0] - 32;
	for (int i = 1; i < length; ++i) {
		if (name[i] == SPACE && (name[i+1] >=  A_LOWER && name[i+1] <= Z_LOWER)) {
			name[i+1] = name[i+1] - 32; 
		}
	}
}

// Nhap userName

char* enterUserName() {
	char* user = NULL;
	bool isInvalid = false;
	char userName1[14] = "le hoang long";
	char userName2[17] = "nguyen dinh hung";
	do {
		user = (char*)malloc(30 * sizeof(char));
		printf("\nENTER USERNAME: ");
		fflush(stdin);
		fgets(user, 30, stdin);
		deleteEnter(user);
		if (strcmp(user, userName1) == 0) {
			isInvalid = true;
		} else if (strcmp(user, userName2) == 0) {
			isInvalid = true;
		} else {
			printf("\nINCORRECT USERNAME!\n");
			isInvalid = false;
			free(user);
		}
	}while(!isInvalid);
	upperCaseName(user);
	return user;
}

// Nhap ID

void enterID() {
	char x = 'a';
	char *password = NULL;
	char ID[10] = "201844993";
	bool check;
	int size;
	do {
		printf("\nENTER ID: ");
		size = 0;
		password = (char*)malloc(20 * sizeof(char));
		check = true;
		while (x != ENTER_INT || x != ESC) {
			//Lay ki tu tu bo nho dem va gan vao bien x
			x = getch();
			if (x == ENTER_INT || x == ESC) {
				break;
			}
			// Kiem tra neu phan tu dau tien la ky tu null
			if (password[0] == END_STRING) {
				// Neu dung, cho vao vong lap vo tan
				while(1) {
					x = getch();
					if (x != BACKSPACE) {
						break;
					}
				}
			}
			if (x == BACKSPACE) {
				if (size != 0) {
					password[size] = END_STRING;
					size--;
					printf("\b \b");
				}
			} else {
				password[size] = x;
				size++;
				printf("%c", x);
				//ma hoa ki tu thanh ki tu *
				printf("\b \b*"); 
			} 
		}
		password[size] = END_STRING;
		if (strcmp(ID, password) != 0) {
			printf("\n\nINCORRECT ID!\n");	
			check = false;
		}
	} while(!check);
	free(password);
}

// Bat dau phien lam viec 

char* login() {
	char *userName = NULL;
	printf("TO START, PLEASE ENTER USERNAME AND ID\n");
	userName = enterUserName();
	enterID();
	printf("\n\nStaff: %s\n\n", userName);
	return userName;
}

// Ket thuc phien lam viec

void logout(Cus *listCustomer, int listCus, long totalDay) {
	FILE *fptr;
	int i;
	fptr = fopen("TotalDay.txt", "a");
	for (i = 0; i <= listCus-1; ++i) {
		totalDay += listCustomer[i].total;
	}
	printf("\nTO FINISH WORK, PLEASE ENTER RIGHT ID\n");
	enterID();
	printf("\n\n");
	printf("-----------------------------------------------------------------------------\n");
	printf("|                   BANG THONG KE DOANH THU TRONG NGAY                      |\n");
	printf("-----------------------------------------------------------------------------\n");
	for (i = 0; i <= listCus-1; ++i) {
		printf("| %40s %s:  %9d%14s\n", "|", "GIAM GIA", listCustomer[i].discount, "|");
		printf("| KHACH HANG %-27d %s %s:  %8d%14s\n", i+1, "|", "TONG TIEN", listCustomer[i].total, "|");
		printf("| GIO GOI MON: %-26s| %s: %8d%14s\n", listCustomer[i].time, "THANH TOAN", listCustomer[i].pay, "|");
		printf("| %40s %s:  %8d%14s\n", "|", "TIEN THUA", (listCustomer[i].pay > listCustomer[i].total) ?
		(listCustomer[i].pay - listCustomer[i].total) : 0, "|");
		printf("-----------------------------------------------------------------------------\n");
	}
	printf("| Tong doanh thu trong ngay: %8ldVND %36s\n", totalDay, "|");
	printf("-----------------------------------------------------------------------------\n");
	char* day = (char*)malloc(30* sizeof(char));
	time_t rawtime;
	time(&rawtime);
	strftime(day, 30, "%d/%m/%Y", localtime(&rawtime));
	fprintf(fptr, "Tong doanh thu trong ngay %s: %ldVND", day, totalDay);
	fprintf(fptr, "\n");
	fclose(fptr);
	free(day);
}

//Ham tinh tien mon an cua khach hang

void priceOfFood(Cus* customer) {
	char nameOfFood[20][30] = {
		"Ca phe den phin", "Ca phe sua phin", "Ca phe den Sai Gon", "Ca phe sua Sai Gon",
		"Tra sua tran chau", "Tra sua socola (nhieu thach)", "Ca phe bot bien", "Socola bot bien",
		"Chanh tuoi da", "Sinh to dau", "Cookies Socola",
		"Kem oc que", "Kem ly Socola", "Kem ly dau",
		"Tra gung Lipton chanh", "Banh my xot Thai", "Banh my cha heo bo",
		"Banh my trung","Banh trang tron","Xuc xich chien"		
	};
	int i, j;
	bool nextFood;
	int maMon[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
	int price[20] = {
	16000, 18000, 17000, 19000, 22000, 24000, 35000, 35000, 35000, 30000,
	35000, 25000, 30000, 30000, 25000, 17000, 15000, 15000, 15000, 15000
	};
	customer->total = 0;
	customer->pay = 0;
	char *nameFood;
	for (i = 0; i < customer->countFood; ++i) {
		nextFood = true;
		nameFood = (char*)malloc(30 * sizeof(char));
		for (j = 0; j < 20 && nextFood; ++j) {
			if (maMon[j] == customer->listInforFood[i].choice) {
				customer->listInforFood[i].price = price[j];
				customer->listInforFood[i].amount = customer->listInforFood[i].quantity * price[j];
				customer->total += customer->listInforFood[i].amount;
				customer->listInforFood[i].item = strcpy(nameFood, nameOfFood[j]);	
				nextFood = false;			
			}
		}
	}
}

// Ham giup nhap mon an va so luong mon an

void choiceAndQuantity(Cus *customer) {
	int i = customer->countFood;
	bool isInvalid;
	while (1) {
		do {
			isInvalid = true;
			printf("\nNO.%d: ", i + 1);
			//ma mon nhap truoc, so luong mon nhap sau
			scanf("%d %d", &customer->listInforFood[i].choice, &customer->listInforFood[i].quantity);
			if (customer->listInforFood[i].choice > 20) {
				isInvalid = false;
			} else if (customer->listInforFood[i].choice >= 1 && customer->listInforFood[i].choice <= 20) {
				if (customer->listInforFood[i].quantity < 1) {
					isInvalid = false;
				}
			} else {
				if (customer->listInforFood[i].choice < 0) {
					isInvalid = false;
				} else if (customer->listInforFood[i].choice == 0 && customer->listInforFood[i].quantity != 0) {
					isInvalid = false;
				} 
			}
			if (!isInvalid) {
				printf("\nWRONG INPUT! PLEASE RE_ENTERED\n");
			}
		} while (!isInvalid);
		if (customer->listInforFood[i].choice == 0 && customer->listInforFood[i].quantity == 0){
			customer->countFood = i;
			break;
		} else {
			i++;
			customer->countFood++;
		}
	}
}

// Ham giup nhap them mon an

void orderMore(Cus *customer) {
	int i;
	printf("\n||||||||||||||||||||| ORDERED |||||||||||||||||||||||\n");
	for (i = 0; i < customer->countFood; ++i) {
		printf("\nNO.%d: %d %d\n", i + 1, customer->listInforFood[i].choice, customer->listInforFood[i].quantity);
	}
	printf("\n||||||||||||||||||   ORDER MORE    ||||||||||||||||||\n");
	choiceAndQuantity(customer);
	printf("\nOrder more successed!\n");
}

// Goi them mon an

void addFood(Cus *customer) {
	char addFood;
	bool isAddFood;
	do {
		printf("\nDo you want to order more? (y/n): ");
		isAddFood = false;
		fflush(stdin);
		do {
			scanf("%c", &addFood);
			if (addFood == ENTER_CHAR) {
				printf("\nWRONG INPUT! PLEASE RE_ENTERED: ");
			}
		} while (addFood == ENTER_CHAR);
		switch (addFood) {
			case YES_LOWER:
			case YES_UPPER: {
				orderMore(customer);
				isAddFood = true;
				break;
			}
			case NO_LOWER:
			case NO_UPPER: {
				break;
			}
			default: {
				printf("\nWRONG INPUT! PLEASE RE_ENTERED\n");
				isAddFood = true;
				break;
			}
		}
	} while(isAddFood);
}

// Ham giup thay doi mon an

void changeInfoFood(Cus *customer) {
	int i;
	int change;
	bool isInvalid;
	printf("\n||||||||||||||||||||||| ORDERED |||||||||||||||||||||||\n");
	for (i = 0 ; i < customer->countFood; ++i) {
		printf("\nNO.%d: %d %d\n", i+1, customer->listInforFood[i].choice, customer->listInforFood[i].quantity);
	}
	printf("\n||||||||||||||||||   CHANGE ORDER    ||||||||||||||||||\n\n");
	do {
		printf("Change order: NO.");	
		scanf("%d", &change);
		printf("\n");
		if (change <= 0 || change > i) {
			printf("WRONG INPUT! PLEASE RE_ENTERED\n\n");
		}
	} while (change <= 0 || change > i);
	printf("NO.%d: %d %d\n", change, customer->listInforFood[change-1].choice, customer->listInforFood[change-1].quantity);
	do {
		isInvalid = false;
		printf("\nChange your choice and quantity: ");
		scanf("%d %d", &customer->listInforFood[change-1].choice, &customer->listInforFood[change-1].quantity);
		if (customer->listInforFood[change-1].choice > 20) {
			isInvalid = true;
		} else if (customer->listInforFood[change-1].choice <= 20 && customer->listInforFood[change-1].choice >= 1) {
			if (customer->listInforFood[change-1].quantity < 1) {
				isInvalid = true;
			}
		} else if (customer->listInforFood[change-1].choice < 1) {
			if (customer->listInforFood[change-1].choice == 0 && customer->listInforFood[change-1].quantity != 0) {
				isInvalid = true;
			} else if (customer->listInforFood[change-1].choice < 0) {
				isInvalid = true;
			}
		}
		if (isInvalid) {
			printf("\nWRONG INPUT! PLEASE RE_ENTERED\n");
		}
	} while(isInvalid);
	printf("\nChange order successed!\n");
}

// Thay doi thong tin mon an 

void changeFood(Cus *customer) {
	char change;
	bool isInvalid;
	do {
		printf("\nChange your order? (y/n): ");
		isInvalid = false;
		fflush(stdin);
		do {
			scanf("%c", &change);
			if (change == ENTER_CHAR) {
				printf("\nWRONG INPUT! PLEASE RE_ENTERED: ");
			}
		} while (change == ENTER_CHAR);
		switch(change) {
			case YES_LOWER:
			case YES_UPPER: {
				changeInfoFood(customer);
				isInvalid = true;
				break;
			}
			case NO_LOWER:
			case NO_UPPER: {
				break;
			}
			default: {
				printf("\nWRONG INPUT! PLEASE RE_ENTERED\n");
				isInvalid = true;
				break;
			}
		}
	} while (isInvalid);
}

// Giam gia mon an

void discount(Cus *customer) {
	if (customer->total > DISCOUNT) {
		customer->discount = customer->total * 1/4;
		printf("\nORIGINAL: %dVND\n", customer->total);
		printf("\nDiscount (-25%%): -%dVND\n", customer->discount);
		customer->total = customer->total - customer->discount;
		printf("\nTOTAL: %dVND\n", customer->total);
	}
	else {
		printf("\nTOTAL: %dVND\n", customer->total);
	}
}

// Nhap thong tin ve mon an

void orderFood(Cus* customer){
	printf("\n|||||||||||||||||   Choice and Quantitty   ||||||||||||||||||||\n");
	customer->countFood = 0;
	customer->discount = 0;
	choiceAndQuantity(customer);
	do {
		printf("\nTable: ");
		scanf("%d", &customer->table);
		if (customer->table <= 0) {
			printf("\nWRONG INPUT! PLEASE RE_ENTERED\n");
		}
	} while (customer->table <= 0);
	addFood(customer);
	changeFood(customer);
	priceOfFood(customer);
	discount(customer);		
	do {
		printf("\n");
		printf("PAY: ");
		scanf("%d", &customer->pay);
		if (customer->pay - customer->total < 0) {
			printf("\nWRONG INPUT! PLEASE RE_ENTERED\n");
		}
	}while (customer->pay - customer->total < 0);
	if (customer->pay > customer->total) {
		printf("\nCHANGE: %dVND\n", customer->pay - customer->total);
	}
}

// Nhap thong tin khach hang

Cus addCustomer(){
	Cus customer;
	customer.listInforFood = (Food*)malloc(30 * sizeof(Food));
	//goi ham addInforFoodCustomer
	orderFood(&customer); 
	//cap phat 30 o nho cho con tro saveTime
	char* saveTime = (char*)malloc(30 * sizeof(char));	
	//Ham displayTime() tra ve dia chi cua con tro saveTime va gan vao con tro time
	customer.time = displayTime(saveTime); 
	return customer;
}

// In hoa don

void printBill(Cus customer, char *staff){
	char phoneNumber[11];
	if (strcmp(staff, "Le Hoang Long") == 0) {
		strcpy(phoneNumber, "0905395436");
	} else {
		strcpy(phoneNumber, "0933738242");
	}
	printf("\n");
	printf("\nADMINISTRATOR: %-43s %s: %s\n", staff, "DATE", customer.time);
	printf("PHONE NUMBER:  %-43s %s: %d\n", phoneNumber, "TABLE", customer.table);
	printf("--------------------------------------------------------------------------------------------\n");
	printf("%4s %9s %35s %15s %18s\n", "STT", "Ten Mon", "So Luong", "Don Gia", "Thanh Tien");
	printf("--------------------------------------------------------------------------------------------\n");
	for (int i = 0 ; i < customer.countFood; ++i){
		printf("%3d    %-37s %-13d %-15d %-15d\n", i + 1, customer.listInforFood[i].item, customer.listInforFood[i].quantity,
		customer.listInforFood[i].price, customer.listInforFood[i].amount);
	}
	printf("--------------------------------------------------------------------------------------------\n");
	printf("   GIAM GIA:   %dVND\n", customer.discount);
	printf("   TONG TIEN:  %dVND\n", customer.total);
	printf("   THANH TOAN: %dVND\n", customer.pay);
	printf("   TIEN THUA:  %dVND\n", (customer.pay > customer.total) ? (customer.pay - customer.total) : 0);
	printf("--------------------------------------------------------------------------------------------\n");
	printf("|||||||||||||||||||||||| THANK YOU FOR ORDERING! SEE YOU AGAIN! ||||||||||||||||||||||||||||\n\n\n");
}

//Luu du lieu vao file

void saveInfoCustomer(Cus customer, char *staff, int listCus) {
	FILE *fptr;
	if (strcmp(staff, "Le Hoang Long") == 0) {
		fptr = fopen("Staff_Le_Hoang_Long.txt", "a");
	} else {
		fptr = fopen("Staff_Nguyen_Dinh_Hung.txt", "a");
	} 
	if (fptr == NULL) {
		printf("CAN NOT OPEN FILE!\n");
	}
	fprintf(fptr, "  KHACH HANG %-45d %s: %s\n", listCus, "DATE", customer.time);
	fprintf(fptr, "--------------------------------------------------------------------------------------------\n");
	fprintf(fptr, "%4s %9s %35s %15s %18s\n", "STT", "Ten Mon", "So Luong", "Don Gia", "Thanh Tien");
	fprintf(fptr, "--------------------------------------------------------------------------------------------\n");
	for (int i = 0 ; i < customer.countFood; ++i){
		fprintf(fptr, "%3d    %-37s %-13d %-15d %-15d\n", i + 1, customer.listInforFood[i].item, customer.listInforFood[i].quantity,
		customer.listInforFood[i].price, customer.listInforFood[i].amount);
	}
	fprintf(fptr, "--------------------------------------------------------------------------------------------\n");
	fprintf(fptr, "   GIAM GIA:   %dVND\n", customer.discount);
	fprintf(fptr, "   TONG TIEN:  %dVND\n", customer.total);
	fprintf(fptr, "   THANH TOAN: %dVND\n", customer.pay);
	fprintf(fptr, "   TIEN THUA:  %dVND\n", (customer.pay > customer.total) ? (customer.pay - customer.total) : 0);
	fprintf(fptr, "--------------------------------------------------------------------------------------------\n\n\n");
	fclose(fptr);
}

//in Menu quan an

void printMenu(){
	char* menu;
	menu = (char*)malloc(2650 * sizeof(char));
	FILE *fptr = fopen("Menu.txt", "r");
	if (fptr == NULL){
		printf("Khong the mo duoc file!\n");
	} else {
		do{
			fgets(menu, 2650, fptr);
			printf("%s", menu);
		} while (!feof(fptr)); 
	}
	free(menu);
	fclose(fptr);
}

void showPBL() {
	printf("                          *====================================================================*\n");
	printf("                          |                              NHOM 1                                |\n");
	printf("                          *====================================================================*\n");
	printf("                          |       DO AN LAP TRINH TINH TOAN PBL1 (PROJECT BASED LEARNING)      |\n");
	printf("                          |   TEN CHU DE: XAY DUNG UNG DUNG DAT MON AN VA THANH TOAN DON HANG  |\n");
	printf("                          |                   LOP HOC PHAN: 20.12B                             |\n");
	printf("                          |                   GVHD: TRAN HO THUY TIEN                          |\n");
	printf("                          |                   SVTH: LE HOANG LONG                              |\n");
	printf("                          |                         NGUYEN DINH HUNG                           |\n");
	printf("                          *====================================================================*\n");
	getch();
}

int main(){ 
	Cus listCustomer[N_MAX]; 
	int listCus = 0;
	Cus customer;	
	char *staff = NULL;
	int choose;
	char choice;
	long totalDay = 0;
	bool check, isPrintBill;
	
	showPBL();
	
	staff = login();
		
	printMenu();
	
	do{
		printf("\n");
		printf("**========================**\n");
		printf("|| 1: ORDER               ||\n");
		printf("|| 0: EXIT                ||\n");
		printf("**========================**\n");
		printf("  Enter your choice: ");
		fflush(stdin);
		scanf("%d", &choose);
		check = false;
		switch(choose){  
			case 0: {
				free(staff);
				logout(listCustomer, listCus, totalDay);
				break;
			}
			case 1: {
				//ham tra ve gia tri customer va gan vao bien customer
				customer = addCustomer(); 
				// gan customer vao phan tu thu nhat cua mang, sau do tang bien list len 1
				listCustomer[listCus++] = customer; 
				check = true;
				printf("\nDo you want to see bill? (y/n): ");
				do{
					fflush(stdin);
					do {
						scanf("%c", &choice);
						if (choice == ENTER_CHAR) {
							printf("\nWRONG INPUT! PLEASE RE_ENTERED: ");
						}
					} while (choice == ENTER_CHAR);
					switch(choice) {
						case YES_LOWER:
						case YES_UPPER: {
							isPrintBill = true;
							printBill(customer, staff);
							saveInfoCustomer(customer, staff, listCus);
							free(customer.listInforFood->item);
							break;
						}
						case NO_LOWER: 
						case NO_UPPER: {
							isPrintBill = true;
							printf("\nTHANK YOU FOR ORDERING! SEE YOU AGAIN!\n\n");
							saveInfoCustomer(customer, staff, listCus);
							free(customer.listInforFood->item);
							break;
						}
						default: {
							printf("\nWRONG INPUT! PLEASE RE_ENTERED: ");
							isPrintBill = false;
							break;
						}
					}
				} while(!isPrintBill);
				printMenu();
				break;
			}
			default: {
				printf("\nWRONG INPUT! PLEASE RE_ENTERED\n");
				check = true;
				break;
			}
		}
	} while(check);
	return 0;
}
