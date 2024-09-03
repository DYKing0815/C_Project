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
	int cost; // �ݾ�
	int count; // ����
	int totalCost; // ���� �� �ݾ�
	int stock; // ���
	int stacked_count;
	int stacked_cost;
	int deal_cost; //�ŷ� �ܰ�
	int deal_count; //�ŷ� ����

};
	struct menu item[NUMBER]={
		{"",0,0,0,0,0},
		{"�Ƹ޸�ī��", 4000,0,0,10,0,0,3500,0},
		{"������", 4000,0,0,8,0,0,3500,0},
		{"���̽�ũ��", 3500,0,0,6,0,0,3000,0},
		{"ī���", 4500,0,0,4,0,0,4000,0},
		{"�����ֽ�", 3500,0,0,2,0,0,3000,0}
	};

int main( )
{
	int i;

	open_file();

	do {
		system("cls");
	printf("========���� �޴�========\n");
	printf("1. ��ǰ �Ǹ�\n");
	printf("2. ��� ����\n");
	printf("3. ����\n");
	printf("4. ������ ���\n");
	printf("========================\n");

	printf("� ������ �Ͻðڽ��ϱ�?");
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
			printf("���� : ���� �޴��� 1~4�������� �ֽ��ϴ�.\n");
	}
	} while (menuChoice != 3);
	
	return 0;
}

// ���θ޴� �Լ�
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
		printf("======== ��ǰ �޴� ========\n");

		for(i=1; i<NUMBER; i++) {
			printf("%d. %s	%d�� %d��\n",i, item[i].name, item[i].cost, item[i].stock);
		}

		printf("===========================\n");

		printf("� ��ǰ�� �����Ͻðڽ��ϱ�?");
		scanf("%d", &num);

		printf("%s �� �����ϼ̽��ϴ�.\n�ܰ��� %d�� �Դϴ�.\n", item[num].name, item[num].cost);

		while (1) {
		printf("\n�� ���� �����Ͻðڽ��ϱ�?");
		scanf("%d", &choiceNum);
		if (choiceNum>item[num].stock)
			{	
				printf("���� ������ ��� ���� ���� %d�� �� �����ϴ�.\n",choiceNum-item[num].stock);
			}
		else break;
		}

		item[num].count+=choiceNum; 
		// ���� �Ǹ� ���� �߰�
		item[num].stacked_count+=choiceNum;
		

		item[num].stock-=choiceNum;
		item[num].totalCost = (item[num].cost)*(item[num].count);
		printf("�����Ͻ� �ݾ��� %d�� �Դϴ�\n", item[num].totalCost);

		// ���� �Ǹ� �ݾ� �߰�
		item[num].stacked_cost=item[num].totalCost;

		printf("\n�� �����Ͻðڽ��ϱ�? (��: 1/Y, �ƴϿ�: 0/N)");
		scanf(" %c", &choice);

	}
		
	printf("\n");

	printf("========= ��ٱ��� =========\n");
	printf("ǰ��	    ����	   �ݾ�\n");
	for (i=1; i<NUMBER; i++){
		if (item[i].count>0) {
		printf("%10s %10d %10d\n", item[i].name, item[i].count, item[i].totalCost);
		}
	}
	printf("======================\n");

	while(1) {
		printf("�����Ͻô� ��ǰ ������ �³���? (��: 1/Y, �ƴϿ�: 0/N)\n");
		scanf(" %c",&choice);

		if(choice=='0'||choice=='N'||choice=='n')
		{
			printf("� ��ǰ�� �����Ͻó���?\n");
			scanf("%d",&num);

		while(1) {
			printf("��� �����Ͻó���?\n");
			scanf("%d",&choiceNum);
			
			if (choiceNum>item[num].count)
				printf("��� ������ ����� �����ϴ�.\n");
			else break;
		}

			item[num].count -= choiceNum;
			item[num].stacked_count -= choiceNum;
			item[num].stock += choiceNum;
			item[num].totalCost = (item[num].cost)*(item[num].count);
			printf("%s �� %d���� ����Ǿ����ϴ�.\n", item[num].name, item[num].count);
		}
		else break;
	}
	
		for(i=1; i<NUMBER; i++) {

			itemTotalCost	+=item[i].totalCost;
		}

		printf("�����Ͻ� �� �ݾ��� %d�� �Դϴ�.\n",  itemTotalCost);

		while (1) {
			printf("�����ݾ��� �Ա����ֽñ� �ٶ��ϴ�.\n");
			printf("�����ݾ� : ");
			scanf("%d", &receive);
			money+= receive;
			if (itemTotalCost > money)
				{
					printf("\n�����ݾ׿��� %d���� �����մϴ�.\n", itemTotalCost-money);
				}
			else break;
		}
		
	printf("========= ������ =========\n");
	printf("ǰ��	����	�ݾ�\n");
	for (i=1; i<NUMBER; i++){
		if (item[i].count>0) {
		printf("%s %d %d\n", item[i].name, item[i].count, item[i].totalCost);
		}
	}
	printf("======================\n");
	printf("�� ���űݾ� %d\n",itemTotalCost);
	printf("�����ݾ� %d\n",money);
	printf("�Ž����� %d\n", money-itemTotalCost);

	for(i=1; i<NUMBER; i++) {
		item[i].count=0;
		item[i].totalCost=0;
	}
	system("pause");
	return ;
}
// ��� ���� ��Ȳ
void stock_manage() 
{

	do{
		system("cls");
	printf("==========��� ����===========\n");
	printf("1. ��� ��ȸ\n");
	printf("2. ��ǰ �԰�\n");
	printf("3. ��ǰ ��ǰ\n");
	printf("4. ���� �޴�\n");
	printf("========================\n");

	printf("� ������ �Ͻðڽ��ϱ�?");
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
			printf("���� : ���� �޴��� 1~4�������� �ֽ��ϴ�.\n");
	}
	} while (menuChoice != 4);


}
//
void close()
{

	int i;
	system("cls");
	printf("==========����===========\n");
	// ��ǰ ���
	file=fopen("item_stock.txt", "w");

	for(i=1; i<NUMBER; i++) {
		fprintf(file, "%d\n", item[i].stock);
	}

	fclose(file);

	// ��ǰ ����
	file=fopen("change_item.txt", "w");

	for(i=1; i<NUMBER; i++) {
		fprintf(file, "%s\n", item[i].name);
	}

	fclose(file);

	// �ǸŴܰ� ����
	file=fopen("change_itemCost.txt", "w");

	for(i=1; i<NUMBER; i++) {
		fprintf(file, "%d\n", item[i].cost);
	}

	fclose(file);

	// �ŷ��ܰ� ����
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
		printf("==========������ ���===========\n");
		printf("1. ��ǰ��ȸ\n");
		printf("2. ��ǰ����\n");
		printf("3. �ܰ�����\n");
		printf("4. ���������Ȳ\n");
		printf("5. �����޴�\n");
		printf("=============================\n");

		printf("� ������ �Ͻðڽ��ϱ�?\n");
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
			printf("���� : ���� �޴��� 1~5�������� �ֽ��ϴ�.\n");
		}
	}while(menuChoice !=5);


}

void stock_search()
{
	int i;
	system("cls");
	printf("==========��� ��ȸ===========\n");
		
	for(i=1; i<NUMBER; i++) {
			printf("%d. %10s %10d��\n",i, item[i].name, item[i].stock);
		}
	printf("==========================\n");
	system("pause");
}
// ��ǰ �԰� �Լ�
void item_stocked()
{	

	int i, num, choiceNum;
	char choice;
		system("cls");
	printf("==========��ǰ�԰�===========\n");
	
	while (1) {
	printf("� ��ǰ�� �԰��Ͻðڽ��ϱ�?");
	scanf("%d", &num);

	printf("������ � �԰��Ͻðڽ��ϱ�?");
	scanf("%d", &choiceNum);
	//��� ����
	item[num].stock += choiceNum;
	
	// �ŷ��� �԰� ���� 
	item[num].deal_count += choiceNum;



	printf("\n�� �԰��Ͻðڽ��ϱ�? (��: 1/Y, �ƴϿ�: 0/N)");
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
	printf("==========��ǰ ��ǰ===========\n");
	
	while (1) {  //
	printf("� ��ǰ�� ��ǰ�Ͻðڽ��ϱ�?");
	scanf("%d", &num);
	
	while (1) {  //
	printf("������ � ��ǰ�Ͻðڽ��ϱ�?");
	scanf("%d", &choiceNum);

	if (choiceNum>item[num].stock)
		printf("����: ��� �������� ��ǰ ������ �� Ů�ϴ�\n");
	else break;
	}

	item[num].stock -= choiceNum;
	
	printf("\n�� ��ǰ�Ͻðڽ��ϱ�? (��: 1/Y, �ƴϿ�: 0/N)");
	scanf(" %c", &choice);

	if (choice == '0' || choice == 'N' || choice == 'n') break;
	}

	printf("==========================\n");
		system("pause");

}
// ��ǰ ��ȸ �Լ�
void search_item()
{

	int i;
	system("cls");
	printf("==========��ǰ��ȸ===========\n");

	for(i=1; i<NUMBER; i++) {
		printf("%d. %10s %10d��\n", i, item[i].name, item[i].cost);
	}
	printf("===========================\n");
		system("pause");
}
// ��ǰ �����Լ�
void change_item()
{

	char newItemName[NAME_LEN], choice;
	int num;	
	while(1) // ��ǰ�� ���� �ݺ���
	{
		system("cls");
		printf("==========��ǰ����===========\n");
		printf("� ��ǰ�� �����Ͻðڽ��ϱ�?\n");
		scanf("%d", &num);

		printf("� ��ǰ������ �����Ͻðڽ��ϱ�?\n");
		scanf("%s", newItemName);

		printf("�����Ͻô� ��ǰ���� \"%s\"�� �³���?  (��: 1/Y, �ƴϿ�: 0/N)", newItemName);
		scanf(" %c", &choice);
	
		if(choice=='1' || choice =='Y' || choice =='y')
		{
			strcpy(item[num].name, newItemName); 
			printf("��ǰ���� ����Ǿ����ϴ�");
		}

		printf("\�ٸ� ��ǰ�� ���� �Ͻðڽ��ϱ�? (��: 1/Y, �ƴϿ�: 0/N)");
		scanf(" %c",&choice);

		if(choice=='0' || choice =='N' || choice =='n') break;
	}

	printf("==========================\n");
	system("pause");
	return;

}
// �ܰ� ���� �Լ�
void change_price()
{

		int num, newCost;
		char choice;
		system("cls");
		printf("==========�ܰ�����===========\n");
		while(1) {
			printf("� ��ǰ�� �����Ͻðڽ��ϱ�?\n");
			scanf("%d", &num);

			printf("�󸶷� �����Ͻðڽ��ϱ�?\n");
			scanf("%d", &newCost );

			printf("�����Ͻô� �ݾ��� \"%d��\"�� �³���?  (��: 1/Y, �ƴϿ�: 0/N)", newCost);
			scanf(" %c", &choice);
	
			if(choice=='1' || choice =='Y' || choice =='y')
			{
				item[num].cost = newCost;
			}

			printf("\�ٸ� ��ǰ�� ���� �Ͻðڽ��ϱ�? (��: 1/Y, �ƴϿ�: 0/N)");
			scanf("%d",&choice);

			if(choice=='0' || choice =='N' || choice =='n') break;
		}
			system("pause");
}

//���� ���� ��Ȳ
void check_totalMoney()
{
	do {
		system("cls");
		printf("==========���������Ȳ===========\n");
		printf("1. ������Ȳ��ȸ\n");
		printf("2. �ֹ���ǰ��ȸ\n");
		printf("3. �ŷ�ó��Ȳ\n");
		printf("4. �����޴�\n");
		printf("==============================\n");

		printf("� ������ �Ͻðڽ��ϱ�?\n");
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
			printf("���� : 1~4�� �̿� ����");
		}
	}while(menuChoice !=4);
}
// ���������Ȳ �Լ�
void search_daylist()
{

	int i, dayStackedCost=0;
			system("cls");
	printf("============������Ȳ��ȸ==============\n");
	for(i=1; i<NUMBER; i++) {
		printf("%d %10s %10d�� %10d��\n", i, item[i].name, item[i].stacked_count, item[i].stacked_cost);
		dayStackedCost += item[i].stacked_cost;
	}
	printf("��ü ���� �ݾ�:  %d��\n", dayStackedCost);
		system("pause");
}
// �ֹ� ��ǰ ��ȸ �Լ�
void search_orderItem()
{

	int i, convert=1;
		system("cls");
	printf("============�ֹ���ǰ��ȸ=============\n");
	for(i=1; i<NUMBER; i++) {
		if (item[i].stock<5) {
			printf("%10s   ������ : %10d��\n",item[i].name, item[i].stock);
			convert = !convert;
		}
			
	}
	if (convert==1)
		printf("�ֹ��Ͻ� ǰ���� �����ϴ�.\n");
	system("pause");
}

//�ŷ�ó ��Ȳ ��ȸ
void search_customer()
{
	do {
			system("cls");
		printf("============�ŷ�ó��Ȳ=============\n");
		printf("1. �ŷ�ǰ�� ��Ȳ��ȸ\n");
		printf("2. �ŷ�ǰ�� �԰� ��Ȳ��ȸ\n");
		printf("3. �ŷ��ܰ� ����\n");
		printf("4. �����޴�\n");
		printf("==============================\n");

		printf("� ������ �Ͻðڽ��ϱ�?\n");
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
				printf("���� : 1~4�� �̿� ����");
		}
	}while(menuChoice!=4);
}
//�ŷ� ǰ�� ��Ȳ ��ȸ �Լ�
void search_dealItem()
{

	int i, itemTotalCost=0;
			system("cls");
	printf("============�ŷ�ǰ�� ��Ȳ��ȸ=============\n");
	printf("		��ǰ��		�ǸŴܰ�		�ŷ��ܰ�\n");

	for(i=1; i<NUMBER ;i++) {
		printf("%d %10s %10d %10d\n",i, item[i].name, item[i].cost, item[i].deal_cost);
	}
		system("pause");
}
//�ŷ� ǰ�� �԰� ��Ȳ��ȸ �Լ�
void search_stacked_dealItem()
{	

	int i, itemTotalCost=0;
		system("cls");
	printf("============�ŷ�ǰ�� �԰� ��Ȳ ��ȸ=============\n");
	printf("��ǰ��    ���԰����     ��ǰ�� ���� �ݾ� \n");
	
	for(i=1;i<NUMBER;i++) {
		printf("%d %10s %10d %10d\n", i, item[i].name, item[i].deal_count, item[i].deal_cost);
		itemTotalCost += (item[i].deal_count)*(item[i].deal_cost);
	}
	printf("================================================\n");	
	printf("�� ���� �ݾ� %10d\n",itemTotalCost);
	printf("\n");
	system("pause");
}

//�ŷ� �ܰ� ���� �Լ�
void change_dealcost()
{
	int num, newCost, newCost1;
	char choice;
	system("cls");
	printf("============�ŷ� �ܰ� ����=============\n");
	printf("�ܰ��� ������ ��ǰ ��ȣ�� �Է��ϼ��� : ");
	scanf("%d", &num);

	printf("������ �ŷ� �ܰ��� �Է��ϼ��� : ");
	scanf("%d", &newCost);

	item[num].deal_cost = newCost;

	printf("������ �Ǹ� �ܰ��� �Է��ϼ��� : ");
	scanf("%d", &newCost1);

	item[num].cost = newCost1;

	while(1)
	{
		printf("������ �ŷ��ܰ�(%d��), �ǸŴܰ�(%d��)�� �³���? (��: 1/Y, �ƴϿ�: 0/N) \n",item[num].deal_cost, item[num].cost );
		scanf("%c", &choice);
		if (choice=='1' || choice =='Y' || choice=='y')
		{
			printf("%d�� : �ŷ��ܰ� %d��, �ǸŴܰ� %d������ ����\n", num, item[num].deal_cost, item[num].cost);
			break;
		}
	}

	system("pause");
}

void open_file()
{
	int i;
	// ��ǰ ���
	file=fopen("item_stock.txt", "r");

	for(i=1; i<NUMBER; i++) {
		fprintf(file, "%d\n", item[i].stock);
	}

	fclose(file);

	// ��ǰ ����
	file=fopen("change_item.txt", "r");

	for(i=1; i<NUMBER; i++) {
		fprintf(file, "%s\n", item[i].name);
	}

	fclose(file);

	// �ǸŴܰ� ����
	file=fopen("change_itemCost.txt", "r");

	for(i=1; i<NUMBER; i++) {
		fprintf(file, "%d\n", item[i].cost);
	}

	fclose(file);

	// �ŷ��ܰ� ����
	file=fopen("change_itemDealCost.txt", "r");

	for(i=1; i<NUMBER; i++) {
		fprintf(file, "%d\n", item[i].deal_cost);
	}

	fclose(file);
}



