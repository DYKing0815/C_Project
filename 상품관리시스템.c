#include <stdio.h>
#include <string.h>
#include <Windows.h>

void item_sell();
void stock_manage();
void close();
void manage_mode();
void stock_search();
void item_stocked();
void item_return();
void search_item();
void change_item();
void change_price();
void check_totalMoney();
void search_daylist();
void search_orderItem();
void search_customer();
void search_dealItem();
void search_stacked_dealItem();
void change_dealcost();
void open_file();

int menuChoice;

#define NAME_LEN 64
#define NUMBER 6

FILE* file;

struct menu {
	char name[NAME_LEN];
	int cost; // 금액
	int count; // 수량
	int totalCost; // 개별 총 금액
	int stock; // 재고
	int stacked_count;
	int stacked_cost;
	int deal_cost; //거래 단가
	int deal_count; //거래 수량

};
	struct menu item[NUMBER]={
		{"",0,0,0,0,0},
		{"아메리카노", 4000,0,0,10,0,0,3500,0},
		{"녹차라떼", 4000,0,0,8,0,0,3500,0},
		{"아이스크림", 3500,0,0,6,0,0,3000,0},
		{"카페라떼", 4500,0,0,4,0,0,4000,0},
		{"과일주스", 3500,0,0,2,0,0,3000,0}
	};

int main( )
{
	int i;

	open_file();

	do {
		system("cls");
	printf("========메인 메뉴========\n");
	printf("1. 상품 판매\n");
	printf("2. 재고 관리\n");
	printf("3. 종료\n");
	printf("4. 관리자 모드\n");
	printf("========================\n");

	printf("어떤 업무를 하시겠습니까?");
	scanf("%d", &menuChoice);

	switch(menuChoice)
	{
		case 1:
			item_sell( );
			break;

		case 2:
			stock_manage( );
			break;

		case 3:
			close( );
			break;

		case 4:
			manage_mode( );
			break;
		
		default :
			printf("오류 : 선택 메뉴가 1~4번까지만 있습니다.\n");
	}
	} while (menuChoice != 3);
	
	return 0;
}

// 메인메뉴 함수
void item_sell( )
{
	
	int i;
	int num;
	char choice='1';
	int money =0 ;
	int itemTotalCost = 0;
	int receive;
	int choiceNum;

	while (choice =='1' || choice == 'Y' || choice == 'y')
	{
		system("cls");
		printf("======== 상품 메뉴 ========\n");

		for(i=1; i<NUMBER; i++) {
			printf("%d. %s	%d원 %d개\n",i, item[i].name, item[i].cost, item[i].stock);
		}

		printf("===========================\n");

		printf("어떤 상품을 구매하시겠습니까?");
		scanf("%d", &num);

		printf("%s 를 선택하셨습니다.\n단가는 %d원 입니다.\n", item[num].name, item[num].cost);

		while (1) {
		printf("\n몇 개를 구매하시겠습니까?");
		scanf("%d", &choiceNum);
		if (choiceNum>item[num].stock)
			{	
				printf("구매 수량이 재고 수량 보다 %d개 더 많습니다.\n",choiceNum-item[num].stock);
			}
		else break;
		}

		item[num].count+=choiceNum; 
		// 누적 판매 수량 추가
		item[num].stacked_count+=choiceNum;
		

		item[num].stock-=choiceNum;
		item[num].totalCost = (item[num].cost)*(item[num].count);
		printf("구매하신 금액은 %d원 입니다\n", item[num].totalCost);

		// 누적 판매 금액 추가
		item[num].stacked_cost=item[num].totalCost;

		printf("\n더 구매하시겠습니까? (예: 1/Y, 아니오: 0/N)");
		scanf(" %c", &choice);

	}
		
	printf("\n");

	printf("========= 장바구니 =========\n");
	printf("품목	    수량	   금액\n");
	for (i=1; i<NUMBER; i++){
		if (item[i].count>0) {
		printf("%10s %10d %10d\n", item[i].name, item[i].count, item[i].totalCost);
		}
	}
	printf("======================\n");

	while(1) {
		printf("구매하시는 상품 정보가 맞나요? (예: 1/Y, 아니오: 0/N)\n");
		scanf(" %c",&choice);

		if(choice=='0'||choice=='N'||choice=='n')
		{
			printf("어떤 상품을 수정하시나요?\n");
			scanf("%d",&num);

		while(1) {
			printf("몇개로 수정하시나요?\n");
			scanf("%d",&choiceNum);
			
			if (choiceNum>item[num].count)
				printf("취소 수량이 재고보다 많습니다.\n");
			else break;
		}

			item[num].count -= choiceNum;
			item[num].stacked_count -= choiceNum;
			item[num].stock += choiceNum;
			item[num].totalCost = (item[num].cost)*(item[num].count);
			printf("%s 가 %d개로 변경되었습니다.\n", item[num].name, item[num].count);
		}
		else break;
	}
	
		for(i=1; i<NUMBER; i++) {

			itemTotalCost	+=item[i].totalCost;
		}

		printf("구매하신 총 금액은 %d원 입니다.\n",  itemTotalCost);

		while (1) {
			printf("결제금액을 입금해주시기 바랍니다.\n");
			printf("결제금액 : ");
			scanf("%d", &receive);
			money+= receive;
			if (itemTotalCost > money)
				{
					printf("\n결제금액에서 %d원이 부족합니다.\n", itemTotalCost-money);
				}
			else break;
		}
		
	printf("========= 영수증 =========\n");
	printf("품목	수량	금액\n");
	for (i=1; i<NUMBER; i++){
		if (item[i].count>0) {
		printf("%s %d %d\n", item[i].name, item[i].count, item[i].totalCost);
		}
	}
	printf("======================\n");
	printf("총 구매금액 %d\n",itemTotalCost);
	printf("받은금액 %d\n",money);
	printf("거스름돈 %d\n", money-itemTotalCost);

	for(i=1; i<NUMBER; i++) {
		item[i].count=0;
		item[i].totalCost=0;
	}
	system("pause");
	return ;
}
// 재고 관리 현황
void stock_manage() 
{

	do{
		system("cls");
	printf("==========재고 관리===========\n");
	printf("1. 재고 조회\n");
	printf("2. 상품 입고\n");
	printf("3. 상품 반품\n");
	printf("4. 이전 메뉴\n");
	printf("========================\n");

	printf("어떤 업무를 하시겠습니까?");
	scanf("%d", &menuChoice);

	switch(menuChoice)
	{
		case 1:
			stock_search( );
			break;

		case 2:
			item_stocked( );
			break;

		case 3:
			item_return( );
			break;

		case 4:
			return;
		
		default :
			printf("오류 : 선택 메뉴가 1~4번까지만 있습니다.\n");
	}
	} while (menuChoice != 4);


}
//
void close()
{

	int i;
	system("cls");
	printf("==========종료===========\n");
	// 상품 재고
	file=fopen("item_stock.txt", "w");

	for(i=1; i<NUMBER; i++) {
		fprintf(file, "%d\n", item[i].stock);
	}

	fclose(file);

	// 상품 변경
	file=fopen("change_item.txt", "w");

	for(i=1; i<NUMBER; i++) {
		fprintf(file, "%s\n", item[i].name);
	}

	fclose(file);

	// 판매단가 변경
	file=fopen("change_itemCost.txt", "w");

	for(i=1; i<NUMBER; i++) {
		fprintf(file, "%d\n", item[i].cost);
	}

	fclose(file);

	// 거래단가 변경
	file=fopen("change_itemDealCost.txt", "w");

	for(i=1; i<NUMBER; i++) {
		fprintf(file, "%d\n", item[i].deal_cost);
	}

	fclose(file);
}
void manage_mode()
{
	do {
		system("cls");
		printf("==========관리자 모드===========\n");
		printf("1. 상품조회\n");
		printf("2. 상품변경\n");
		printf("3. 단가변경\n");
		printf("4. 매출실적현황\n");
		printf("5. 이전메뉴\n");
		printf("=============================\n");

		printf("어떤 업무를 하시겠습니까?\n");
		scanf("%d", &menuChoice);

		switch(menuChoice)
		{
		case 1:
			search_item();
			break;
		case 2:
			change_item();
			break;
		case 3:
			change_price();
			break;
		case 4:
			check_totalMoney();
			break;
		case 5:
			return;
		default:
			printf("오류 : 선택 메뉴가 1~5번까지만 있습니다.\n");
		}
	}while(menuChoice !=5);


}

void stock_search()
{
	int i;
	system("cls");
	printf("==========재고 조회===========\n");
		
	for(i=1; i<NUMBER; i++) {
			printf("%d. %10s %10d개\n",i, item[i].name, item[i].stock);
		}
	printf("==========================\n");
	system("pause");
}
// 상품 입고 함수
void item_stocked()
{	

	int i, num, choiceNum;
	char choice;
		system("cls");
	printf("==========상품입고===========\n");
	
	while (1) {
	printf("어떤 상품을 입고하시겠습니까?");
	scanf("%d", &num);

	printf("수량을 몇개 입고하시겠습니까?");
	scanf("%d", &choiceNum);
	//재고 수량
	item[num].stock += choiceNum;
	
	// 거래된 입고 수량 
	item[num].deal_count += choiceNum;



	printf("\n더 입고하시겠습니까? (예: 1/Y, 아니오: 0/N)");
	scanf(" %c", &choice);

	if (choice == '0' || choice == 'N' || choice == 'n') break;
	}

	printf("==========================\n");
		system("pause");
}
void item_return()
{

	int i, num, choiceNum;
	char choice;
		system("cls");
	printf("==========상품 반품===========\n");
	
	while (1) {  //
	printf("어떤 상품을 반품하시겠습니까?");
	scanf("%d", &num);
	
	while (1) {  //
	printf("수량을 몇개 반품하시겠습니까?");
	scanf("%d", &choiceNum);

	if (choiceNum>item[num].stock)
		printf("오류: 재고 수량보다 반품 수량이 더 큽니다\n");
	else break;
	}

	item[num].stock -= choiceNum;
	
	printf("\n더 반품하시겠습니까? (예: 1/Y, 아니오: 0/N)");
	scanf(" %c", &choice);

	if (choice == '0' || choice == 'N' || choice == 'n') break;
	}

	printf("==========================\n");
		system("pause");

}
// 상품 조회 함수
void search_item()
{

	int i;
	system("cls");
	printf("==========상품조회===========\n");

	for(i=1; i<NUMBER; i++) {
		printf("%d. %10s %10d원\n", i, item[i].name, item[i].cost);
	}
	printf("===========================\n");
		system("pause");
}
// 상품 변경함수
void change_item()
{

	char newItemName[NAME_LEN], choice;
	int num;	
	while(1) // 상품명 변경 반복문
	{
		system("cls");
		printf("==========상품변경===========\n");
		printf("어떤 상품을 변경하시겠습니까?\n");
		scanf("%d", &num);

		printf("어떤 상품명으로 변경하시겠습니까?\n");
		scanf("%s", newItemName);

		printf("변경하시는 상품명이 \"%s\"이 맞나요?  (예: 1/Y, 아니오: 0/N)", newItemName);
		scanf(" %c", &choice);
	
		if(choice=='1' || choice =='Y' || choice =='y')
		{
			strcpy(item[num].name, newItemName); 
			printf("상품명이 변경되었습니다");
		}

		printf("\다른 상품도 변경 하시겠습니까? (예: 1/Y, 아니오: 0/N)");
		scanf(" %c",&choice);

		if(choice=='0' || choice =='N' || choice =='n') break;
	}

	printf("==========================\n");
	system("pause");
	return;

}
// 단가 변경 함수
void change_price()
{

		int num, newCost;
		char choice;
		system("cls");
		printf("==========단가변경===========\n");
		while(1) {
			printf("어떤 상품을 변경하시겠습니까?\n");
			scanf("%d", &num);

			printf("얼마로 변경하시겠습니까?\n");
			scanf("%d", &newCost );

			printf("변경하시는 금액이 \"%d원\"이 맞나요?  (예: 1/Y, 아니오: 0/N)", newCost);
			scanf(" %c", &choice);
	
			if(choice=='1' || choice =='Y' || choice =='y')
			{
				item[num].cost = newCost;
			}

			printf("\다른 상품도 변경 하시겠습니까? (예: 1/Y, 아니오: 0/N)");
			scanf("%d",&choice);

			if(choice=='0' || choice =='N' || choice =='n') break;
		}
			system("pause");
}

//매출 실적 현황
void check_totalMoney()
{
	do {
		system("cls");
		printf("==========매출실적현황===========\n");
		printf("1. 매출현황조회\n");
		printf("2. 주문상품조회\n");
		printf("3. 거래처현황\n");
		printf("4. 이전메뉴\n");
		printf("==============================\n");

		printf("어떤 업무를 하시겠습니까?\n");
		scanf("%d", &menuChoice);

		switch(menuChoice)
		{
		case 1:
			search_daylist();
			break;
		case 2:
			search_orderItem();
			break;
		case 3:
			search_customer();
			break;
		case 4:
			return;
		default:
			printf("오류 : 1~4번 이외 선택");
		}
	}while(menuChoice !=4);
}
// 매출실적현황 함수
void search_daylist()
{

	int i, dayStackedCost=0;
			system("cls");
	printf("============매출현황조회==============\n");
	for(i=1; i<NUMBER; i++) {
		printf("%d %10s %10d개 %10d원\n", i, item[i].name, item[i].stacked_count, item[i].stacked_cost);
		dayStackedCost += item[i].stacked_cost;
	}
	printf("전체 매출 금액:  %d원\n", dayStackedCost);
		system("pause");
}
// 주문 상품 조회 함수
void search_orderItem()
{

	int i, convert=1;
		system("cls");
	printf("============주문상품조회=============\n");
	for(i=1; i<NUMBER; i++) {
		if (item[i].stock<5) {
			printf("%10s   재고수량 : %10d개\n",item[i].name, item[i].stock);
			convert = !convert;
		}
			
	}
	if (convert==1)
		printf("주문하실 품목이 없습니다.\n");
	system("pause");
}

//거래처 현황 조회
void search_customer()
{
	do {
			system("cls");
		printf("============거래처현황=============\n");
		printf("1. 거래품목 현황조회\n");
		printf("2. 거래품목 입고 현황조회\n");
		printf("3. 거래단가 변경\n");
		printf("4. 이전메뉴\n");
		printf("==============================\n");

		printf("어떤 업무를 하시겠습니까?\n");
		scanf("%d", &menuChoice);

		switch(menuChoice)
		{
			case 1:
		 		search_dealItem();
				break;
			case 2:
				search_stacked_dealItem();
				break;
			case 3:
				change_dealcost();
				break;
			case 4:
				return;
			default:
				printf("오류 : 1~4번 이외 선택");
		}
	}while(menuChoice!=4);
}
//거래 품목 현황 조회 함수
void search_dealItem()
{

	int i, itemTotalCost=0;
			system("cls");
	printf("============거래품목 현황조회=============\n");
	printf("		상품명		판매단가		거래단가\n");

	for(i=1; i<NUMBER ;i++) {
		printf("%d %10s %10d %10d\n",i, item[i].name, item[i].cost, item[i].deal_cost);
	}
		system("pause");
}
//거래 품목 입고 현황조회 함수
void search_stacked_dealItem()
{	

	int i, itemTotalCost=0;
		system("cls");
	printf("============거래품목 입고 현황 조회=============\n");
	printf("상품명    총입고수량     제품별 결제 금액 \n");
	
	for(i=1;i<NUMBER;i++) {
		printf("%d %10s %10d %10d\n", i, item[i].name, item[i].deal_count, item[i].deal_cost);
		itemTotalCost += (item[i].deal_count)*(item[i].deal_cost);
	}
	printf("================================================\n");	
	printf("총 결제 금액 %10d\n",itemTotalCost);
	printf("\n");
	system("pause");
}

//거래 단가 변경 함수
void change_dealcost()
{
	int num, newCost, newCost1;
	char choice;
	system("cls");
	printf("============거래 단가 변경=============\n");
	printf("단가를 변경할 상품 번호를 입력하세요 : ");
	scanf("%d", &num);

	printf("변경할 거래 단가를 입력하세요 : ");
	scanf("%d", &newCost);

	item[num].deal_cost = newCost;

	printf("변경할 판매 단가를 입력하세요 : ");
	scanf("%d", &newCost1);

	item[num].cost = newCost1;

	while(1)
	{
		printf("변경할 거래단가(%d원), 판매단가(%d원)이 맞나요? (예: 1/Y, 아니오: 0/N) \n",item[num].deal_cost, item[num].cost );
		scanf("%c", &choice);
		if (choice=='1' || choice =='Y' || choice=='y')
		{
			printf("%d번 : 거래단가 %d원, 판매단가 %d원으로 변경\n", num, item[num].deal_cost, item[num].cost);
			break;
		}
	}

	system("pause");
}

void open_file()
{
	int i;
	// 상품 재고
	file=fopen("item_stock.txt", "r");

	for(i=1; i<NUMBER; i++) {
		fprintf(file, "%d\n", item[i].stock);
	}

	fclose(file);

	// 상품 변경
	file=fopen("change_item.txt", "r");

	for(i=1; i<NUMBER; i++) {
		fprintf(file, "%s\n", item[i].name);
	}

	fclose(file);

	// 판매단가 변경
	file=fopen("change_itemCost.txt", "r");

	for(i=1; i<NUMBER; i++) {
		fprintf(file, "%d\n", item[i].cost);
	}

	fclose(file);

	// 거래단가 변경
	file=fopen("change_itemDealCost.txt", "r");

	for(i=1; i<NUMBER; i++) {
		fprintf(file, "%d\n", item[i].deal_cost);
	}

	fclose(file);
}



