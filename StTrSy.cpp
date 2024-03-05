#include<iostream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<conio.h>
#include<fstream>
#include<iomanip>
#include<ctime>
#include<cstdio>
#include<windows.h>
#define ll long long
#define CLEAR system("cls")
#define PAUSE system("pause")
#define GET cin.get()
#define SCode stocks[i].stock_code
#define SName stocks[i].stock_name
#define CNew customers[customer_number]
#define TNew tradings[trading_number]
#define ONew operations[operation_number] 
#define CNow customers[customer_rank]
#define CNow1 customers[rank1] 
#define TnD tradings[trading_number].trading_date
#define OnD operations[operation_number].operating_date
#define OiD operations[i].operating_date
#define TiD tradings[i].trading_date
#define OntD operations[operation_number].trading_date
#define TctD tradings[c1-1].trading_date
#define IF_CODE !strcmp(SCode,stock_code1)
#define IF_NAME !strcmp(name,customers[i].customer_name) 
#define IF_PASS !strcmp(password,CNow.customer_code)
#define IF_ERROR if(!flag){printf("Your stock code is erroneous\n");PAUSE;}
#define SECS printf("\nReturn in 2 sec\n");Sleep(2000);CLEAR;
#define IF_Y if(c=='y'||c=='Y')
#define IF_N else if(c=='n'||c=='N'){printf("Canceled\n");SECS}else{printf("Error!\n");SECS};
#define CONFIRM printf("\nConfirmed?(Y/N)");scanf("%c",&c);
#define CHANGE CNow1.cash+=b*tradings[c1-1].total_prize,CNow1.market_value-=b*tradings[c1-1].total_prize,CNow1.stocks_number[stock_rank]-=b*tradings[c1-1].number,stocks[stock_rank].shares_floatable+=b*tradings[c1-1].number
#define Not_by_ad OiD.Date_show()
#define By_ad printf("      by %s ",operations[i].ad_name),OiD.Date_show()
using namespace std;
const int MAXN=5;
int customer_number,stock_number,customer_rank,trading_number,operation_number;
SYSTEMTIME sys;
class Customer;
class Trading;
class Operation;
class Stock{//��Ʊ�� 
//public:
	double issue_price,listing_price;//��Ʊ���мۡ����мۣ����м��ɹ���Ա��������������м� 
	char stock_name[50],stock_code[50];//��Ʊ���ơ�����
	bool if_hanged;//�Ƿ���𣬹�����޷������ 
	ll shares_total,shares_floatable;//��Ʊ�ܹ�������Ʊ����ͨ�����������ܹ���������ı���ͨ�� 
public: 
	Stock();
	friend class Trading;
	friend class Customer;
	void Stock_information();//��ʾ������Ϣ
	void Interface();//�û�ѡ�����
	void Hang_up_stock();//�����Ʊ/����Ա
	void Unhang_stock();//��ҹ�Ʊ/����Ա
	void Modify_stock();//�޸Ĺ�Ʊ/����Ա
	void Input_stock();//�����¹�Ʊ/����Ա
	void Delete_stock();//ɾ����Ʊ/����Ա
	void Store(Stock t[]);//�ļ��洢��Ʊ��Ϣ 
	void Read_stock();//�ļ������Ʊ��Ϣ 
	void Stop_trading();//ֹͣ����/����Ա
	void Restore_trading();//�ָ�����/����Ա 
};
class Customer{//�û��� 
//public:
	bool if_administrator;//�Ƿ����Ա
	char customer_name[50],customer_code[50],stocks_name[MAXN][50],stocks_code[MAXN][50];//�û������û����룬��Ʊ���ƣ���Ʊ����
	ll stocks_number[MAXN];//��Ʊ����
	int new_info;//�Ƿ����µ���ز��� 
	double cash,market_value,assets;//�ֽ���ֵ���ʲ����ֽ𼴳�Ʊ����ֵ�����й�Ʊ��ֵ���ʲ�Ϊ����֮�� 
public:
	Customer();
	friend class Trading;
	friend class Stock;
	void Store(Customer t[]);//�ļ��洢�û���Ϣ 
	void Read_customer();//�ļ������û���Ϣ 
	void Customer_information();//�û���Ϣ 
	void Register();//ע��
	void Login();//��¼ 
	void Add_stock();//��ӹ�Ʊ 
	void Interface();//ѡ����� 
	void Modify_code();//�������� 
	void Modify_name();//�����û���/����Ա 
	void Deregister();//ע���û� 
	void Purchase();//���Ʊ
	void Sell();//����Ʊ 
};
class Date{//������ 
//public:
	int year,month,day,hour,minute,second;
public:
	Date();
	friend class Stock;
	friend class Customer;
	void Date_show();
	void Date_input(int y,int mo,int d,int h,int mi,int s);
};
class Trading{//������ 
//public:
	char customer_name[50],stock_name[50],stock_code[50];
	int buy_or_sell,success,number;
	double prize,total_prize;
	Date trading_date;
public:
	Trading();
	friend class Customer;
	friend class Stock;
	void Trading_information(bool if_ad);
	void Read_Trading();
	void Store(Trading t[]);
};
class Operation{//������ 
//public:
	char ad_name[50],customer_name1[50],customer_name2[50],stock_name1[50],stock_name2[50],stock_code1[50],stock_code2[50];//����Ա�û���,ǰ���û�������Ʊ������Ʊ���� 
	int kind;//1�����¹�Ʊ;2��ҹ�Ʊ;3�����Ʊ;4ɾ����Ʊ;5�޸Ĺ�Ʊ;6ֹͣ����;7�ָ�����;8�޸��û��� 
	Date operating_date,trading_date; 
public:
	Operation();
	friend class Customer;
	friend class Stock;
	void Operation_information(bool if_ad);
	void Read_Operation();
	void Store(Operation t[]);
};
Date::Date(){//����ʱ�����͹��캯������ʼ�� 
	year=0,month=0,day=0,hour=0,minute=0,second=0;
}
Trading::Trading(){//�������͹��캯������ʼ�� 
	strcpy(customer_name,""),strcpy(stock_name,""),strcpy(stock_code,"");
	buy_or_sell=0,number=0,prize=0,total_prize=0,success=1;
}
Customer::Customer(){//�û����͹��캯������ʼ�� 
	for(register int i=0;i<MAXN;i++)strcpy(stocks_name[i],""),strcpy(stocks_code[i],"");
	memset(stocks_number,0,sizeof(stocks_number));
	cash=0,market_value=0,assets=0,new_info=0;
}
Stock::Stock(){//��Ʊ���͹��캯������ʼ�� 
	stock_number=0,shares_floatable=shares_total;
	strcpy(stock_code,""),strcpy(stock_name,"");
}
Operation::Operation(){//�������͹��캯������ʼ�� 
	strcpy(ad_name,""),strcpy(customer_name1,""),strcpy(customer_name2,""),
	strcpy(stock_name1,""),strcpy(stock_name2,""),strcpy(stock_code1,""),strcpy(stock_code2,"");
	kind=0;
}
Stock stock,stocks[MAXN];
Customer customer,customers[1000];
Trading trading,tradings[10000];
Operation operation,operations[10000];
void Date::Date_show(){//������ڡ�ʱ�� 
	printf("%4d/%02d/%02d %02d:%02d:%02d",year,month,day,hour,minute,second);
}
void Date::Date_input(int y,int mo,int d,int h,int mi,int s){//��������ʱ�� 
	year=y,month=mo,day=d,hour=h,minute=mi,second=s;
}
void Trading::Trading_information(register bool if_ad){//չʾ��Ʊ������Ϣ 
	trading.Read_Trading();
	register int k=0;
	printf("\nNum     User     SName    SCode    Number       Single          Total    Operation    Success     Time\n");
	for(register int i=0;i<trading_number;i++)
		if(!strcmp(CNow.customer_name,tradings[i].customer_name)||if_ad){
			printf("%3d%9s%10s%9s%10d%13.2lf%15.2lf",++k,tradings[i].customer_name,tradings[i].stock_name,tradings[i].stock_code,tradings[i].number,tradings[i].prize,tradings[i].total_prize);
			tradings[i].buy_or_sell==1?printf("          buy"):printf("         sell");
			printf("%11d     ",tradings[i].success);
			TiD.Date_show();printf("\n");
		}
}
void Customer::Customer_information(){//չʾ�û��ʲ���Ϣ 
	printf("\n        MarketValues        UsefulCash        TotalAssets\n");
	printf("%20.2lf%18.2lf        %.2lf\n\n",market_value,cash,assets);
	register int k=-1,p[MAXN];
	for(register int i=0;i<MAXN;i++)if(stocks_number[i])p[++k]=i;
	if(k<=0) return;
	printf("Num     Name    Code    Number       Single          Total\n");
	for(register int i=0;i<=k;i++){
		register double single_price;
		for(register int j=0;j<MAXN;j++)
			if(!strcmp(stocks_code[p[i]],stocks[j].stock_code)){
				single_price=stocks[j].listing_price;break;
			}
		printf("%3d%9s%8s%10d%13.2lf%15.2lf\n",i+1,stocks_name[p[i]],stocks_code[p[i]],stocks_number[p[i]],single_price,single_price*stocks_number[p[i]]);
	}
}
void Stock::Stock_information(){//չʾ������Ϣ 
	printf("          Name     Code     TotalStock     FloatableStock     IssuePrice     ListingPrice     Status\n");
	for(register int i=0;i<MAXN;i++){
		printf("%14s%9s%15lld%19lld%15.2lf%17.2lf     ",SName,SCode,stocks[i].shares_total,stocks[i].shares_floatable,stocks[i].issue_price,stocks[i].listing_price);
		!stocks[i].if_hanged?printf("Not hanged\n"):printf("Hanged\n");
	}
}
void Operation::Operation_information(register bool if_ad){//չʾ������Ϣ 
	CLEAR;
	operation.Read_Operation();
	if(if_ad) printf(" Num\t\t\t\t\tOperations\t\t\t\t\t\tOperator&Time\n");
	else printf(" Num\t\t\tOperations\t\t\t\t\t\t\tTime\n");
	register int k=0;
	for(register int i=0;i<operation_number;i++){
		if(operations[i].kind==1){
			printf("%3d New stock:  %-8s-%4s was added.    \t\t\t\t\t",++k,operations[i].stock_name1,operations[i].stock_code1);
			if_ad?By_ad:Not_by_ad;
			printf("\n");
		}
		if(operations[i].kind==2){
			printf("%3d The stock:  %-8s-%4s was unhanged.\t\t\t\t\t",++k,operations[i].stock_name1,operations[i].stock_code1);
			if_ad?By_ad:Not_by_ad;
			printf("\n");
		}
		if(operations[i].kind==3){
			printf("%3d The stock:  %-8s-%4s was hanged.  \t\t\t\t\t",++k,operations[i].stock_name1,operations[i].stock_code1);
			if_ad?By_ad:Not_by_ad;
			printf("\n");
		}
		if(operations[i].kind==4){
			printf("%3d The stock:  %-8s-%4s was deleted. \t\t\t\t\t",++k,operations[i].stock_name1,operations[i].stock_code1);
			if_ad?By_ad:Not_by_ad;
			printf("\n");
		}
		if(operations[i].kind==5){
			printf("%3d The stock:  %-8s-%4s was modified to %8s-%4s.\t\t\t",++k,operations[i].stock_name1,operations[i].stock_code1,operations[i].stock_name2,operations[i].stock_code2);
			if_ad?By_ad:Not_by_ad;
			printf("\n");
		}
		if(operations[i].kind==6){
			printf("%3d The trading:%-8s-%4s by %s at ",++k,operations[i].stock_name1,operations[i].stock_code1,operations[i].customer_name1);
			operations[i].trading_date.Date_show();
			printf(" was canceled.\t");
			if_ad?By_ad:Not_by_ad;
			printf("\n");
		}
		if(operations[i].kind==7){
			printf("%3d The trading:%-8s-%4s by %s at ",++k,operations[i].stock_name1,operations[i].stock_code1,operations[i].customer_name1);
			operations[i].trading_date.Date_show();
			printf(" was restored.\t");
			if_ad?By_ad:Not_by_ad;
			printf("\n");
		}
		if(operations[i].kind==8&&if_ad){
			printf("%3d The user name:%s was modified to %s.\t\t\t\t\t",++k,operations[i].customer_name1,operations[i].customer_name2);
			if_ad?By_ad:Not_by_ad;
			printf("\n");
		}
	}
}
void Input_number(char *a){//�������� 
	register char c;
	register int k=-1;
	cout.flush();
	c=getch();
	while(c!=13){
		*(a+(++k))=c;
		printf("*");
		cout.flush();
		c=getch();
	}
}
void Customer::Register(){//ע���û� 
	CLEAR;register char password[50]="",c,name[50]="",password1[50]="";
	printf("Register New User\n");GET;
	printf("Please input your name:");cin.getline(name,50);
	customer.Read_customer();register bool b=0;//��ȡ�û���Ϣ�ļ� 
	for(register int i=0;i<customer_number;i++)
		if(IF_NAME){b=1;break;}//���û����ѱ�ע�ᣬע��ʧ�� 
	if(b){printf("The user name was used.");SECS;return;}
	else{//�µ��û��� 
		printf("Please input your password:");Input_number(password);
		printf("\nPlease input your password again to check:");Input_number(password1);
		if(strcmp(password,password1)){
			printf("\n\nThe two passwords are not the same.");SECS
			return;
		}
		strcpy(CNew.customer_code,password),strcpy(CNew.customer_name,name);
		printf("\nPlease input your assets:");scanf("%lf",&CNew.assets);
		CNew.market_value=0,CNew.cash=CNew.assets;GET;
		printf("Are you gonna be set as a ministrator?(Y/N)\n");scanf("%c",&c);
		(c=='y'||c=='Y')?(CNew.if_administrator=1,printf("Set successfully\n")):
			((c=='n'||c=='N')?CNew.if_administrator=0:printf("Defaulted to non-administrator\n"));
		SECS printf("\n\nRegistered successfully\nPress any key to return\n");
		customer_number++;customer.Store(customers);getchar();
	}
}
void Customer::Deregister(){//ע���û�  
	register char name[50]="",c,password[50]="";
	CLEAR;GET;printf("Please input your name:");cin.getline(name,50);
	register bool b=0;customer.Read_customer();
	for(register int i=0;i<customer_number;i++)
		if(IF_NAME){b=1,customer_rank=i;break;}
	if(!b){printf("The user name was not retrieved.");SECS;}
	else{
		printf("  Please input your password:");Input_number(password);
		if(IF_PASS){
			CONFIRM
			IF_Y{
				for(register int i=customer_rank;i<customer_number;i++)
					customers[i]=customers[i+1];
				customer_number--;Store(customers);
				printf("\n\nSuccess to deregister the user.");SECS
			}
			IF_N
		}
		else{printf("\nWrong password.");SECS}
	}
}
void A(){//͵�� 1 
	CLEAR;
	printf("\n\t\t\t\t\t\tStock Trading System\n");
	stock.Stock_information();GET;
}
void B(){//͵�� 2 
	printf("You have no rights to do this operation!");
	SECS//�ǹ���Ա��ʾ 
}
void Stock::Interface(){//ѡ����� 
	while(1){
		CLEAR;
		printf("\n\nStock Trading Market\n\n");
		printf("Market------------------------------[1]\n");//�����Ʊ�����г� 
		printf("Login-------------------------------[2]\n");//��¼ 
		printf("Register----------------------------[3]\n");//ע�� 
		printf("Log off user------------------------[4]\n");//ע�� 
		printf("Exit--------------------------------[5]\n");//�˳����� 
		printf("\nPlease input your choice:");
		register char c;scanf("%c",&c);
		if(c<'1'||c>'5')continue;
		if(c=='1'){A();PAUSE;}//�����Ʊ�����г�
		if(c=='2')customer.Login();//��¼
		if(c=='3')customer.Register();//ע��
		if(c=='4')customer.Deregister();//ע�� 
		if(c=='5'){CLEAR;printf("Thank you for using.Have a good day.\n");exit(0);}//�˳�
	}
}
void Customer::Interface(){//�û����ײ���ϵͳ���� 
	register char c;
	Read_customer();
	while(1){
		CLEAR;
		printf("\n\n    Welcome to Stock Trading System\n");
		printf("Users: ");cout<<customer_name<<endl<<endl;
		printf("Buy---------------------------------[A]\n");//���Ʊ 
		printf("Sell--------------------------------[B]\n");//����Ʊ 
		printf("Add a new stock---------------------[C]\n");//�����µĹ�Ʊ/����Ա 
		printf("Hang out stocks---------------------[D]\n");//��ҹ�Ʊ/����Ա  
		printf("Suspend stocks----------------------[E]\n");//�����Ʊ/����Ա  
		printf("Delete a stock----------------------[F]\n");//ɾ����Ʊ/����Ա  
		printf("Modify a stock----------------------[G]\n");//�޸Ĺ�Ʊ/����Ա  
		printf("Check stocks------------------------[H]\n");//���ʹ�����Ϣ 
		printf("Check tradings----------------------[I]\n");//���ʽ�����Ϣ/�ǹ���Աֻ�ܷ����Լ� 
		printf("Check operations--------------------[J]\n");//���ʲ�����Ϣ 
		printf("Suspend a trading-------------------[K]\n");//ֹͣ����/����Ա 
		printf("Restore a trading-------------------[L]\n");//�ָ�����/����Ա 
		printf("Modify my password------------------[M]\n");//�޸����� 
		printf("Modify a user name------------------[N]\n");//�޸��û���/����Ա 
		printf("Exit--------------------------------[O]\n");//�˳����У����ص��û�ѡ�����
		printf("\nPlease input your choice:");
		if(new_info){
			printf("\nYou have a new operation information.\nPlease input 'J' if you wanna check.\n");
			new_info=0;Store(customers);//����Ϣ��ʾ���� 
		}
		scanf("%c",&c);
		if((c<'a'||c>'o')&&(c<'A'||c>'O'))continue;
		if(c=='a'||c=='A')A(),Customer_information(),Purchase();//���� 
		if(c=='b'||c=='B')A(),Customer_information(),Sell();//���� 
		if(c=='c'||c=='C')if_administrator?Add_stock():B();//����¹�Ʊ
		if(c=='d'||c=='D')if_administrator?(A(),stock.Unhang_stock()):B();   //���
		if(c=='e'||c=='E')if_administrator?(A(),stock.Hang_up_stock()):B();  //����
		if(c=='f'||c=='F')if_administrator?(A(),stock.Delete_stock()):B();   //ɾ��
		if(c=='g'||c=='G')if_administrator?(A(),stock.Modify_stock()):B();   //�޸�
		if(c=='k'||c=='K')if_administrator?(A(),stock.Stop_trading()):B();   //ֹͣ���� 
		if(c=='l'||c=='L')if_administrator?(A(),stock.Restore_trading()):B();//�ָ����� 
		if(c=='n'||c=='N')if_administrator?Modify_name():B();          //�޸��û��� 
		if(c=='i'||c=='I'){CLEAR;trading.Trading_information(if_administrator);PAUSE;}
		if(c=='j'||c=='J'){operation.Operation_information(if_administrator);PAUSE;}
		if(c=='h'||c=='H'){A();Customer_information();PAUSE;} //�鿴 
		if(c=='m'||c=='M')Modify_code();//�޸����� 
		if(c=='o'||c=='O')stock.Interface();//�˳���Ʊ�����г� 
	}
}
void Customer::Login(){//�û���¼ 
	CLEAR;GET;
	register char password[50]="",name[50]="";
	printf("\n    Stock Trading Market\nPlease input your name:");cin.getline(name,50);
	register bool b=0;customer.Read_customer();
	for(register int i=0;i<customer_number;i++)
		if(IF_NAME){b=1,customer_rank=i;break;}
	if(!b){printf("The user name was not retrieved.");SECS;return;}
	else{
		printf("  Please input your password:");Input_number(password);
		if(IF_PASS)CNow.Interface();
		else{printf("\nWrong password");SECS}
	}
} 
void Customer::Add_stock(){//��ӹ�Ʊ 
	for(register int i=0;i<MAXN;i++)
		if(!strcmp(SName,"")){
			stocks[i].Input_stock();
			GetLocalTime(&sys);ONew.kind=1;
			strcpy(ONew.ad_name,CNow.customer_name),strcpy(ONew.stock_name1,SName),strcpy(ONew.stock_code1,SCode);
			OnD.Date_input(sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute,sys.wSecond);
			for(register int j=0;j<customer_number;j++)customers[j].new_info=1;
			operation_number++;operation.Store(operations);stock.Store(stocks);
			printf("Added successfully");SECS;return;
		}
}
void Customer::Purchase(){//�����Ʊ 
	register bool flag=0;
	register char stock_code1[50]="",c;
	register ll stock_volumn;
	printf("\nPlease input the stock code you wanna purchase:");cin>>stock_code1;
	for(register int i=0;i<MAXN&&!flag;i++)
		if(IF_CODE)
			if(stocks[i].if_hanged){printf("The stock is hanged.");SECS;return;}
			else{
				printf("The most you can purchase:%d\n",int(cash/stocks[i].listing_price));
				flag=1;
				printf("Please input the number you wanna purchase:");scanf("%lld",&stock_volumn);
				if(stocks[i].shares_floatable>=stock_volumn&&cash>=stock_volumn*stocks[i].listing_price){
					GET;CONFIRM
					IF_Y{
						stocks_number[i]+=stock_volumn,stocks[i].shares_floatable-=stock_volumn;
						cash-=stocks[i].listing_price*stock_volumn,market_value+=stocks[i].listing_price*stock_volumn;
						strcpy(stocks_code[i],SCode),strcpy(stocks_name[i],SName);
						CLEAR;printf("Trading succecceds.");
						GetLocalTime(&sys);TNew.buy_or_sell=1;
						TNew.number=stock_volumn,TNew.prize=stocks[i].listing_price,TNew.total_prize=stocks[i].listing_price*stock_volumn;
						strcpy(TNew.customer_name,customer_name),strcpy(TNew.stock_name,SName),strcpy(TNew.stock_code,SCode);
						TnD.Date_input(sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute,sys.wSecond);
						trading_number++;
						trading.Store(tradings);SECS;
						A();Customer_information();PAUSE;
						stock.Store(stocks);customer.Store(customers);
					}
					IF_N
				}
				else if(stocks[i].shares_floatable<=stock_volumn){//�ɹ����Ʊ���� 
					printf("Shortage of stock:%s\n Exiting",SName);
					SECS;break;
				}
				else if(cash<=stock_volumn*stocks[i].listing_price){//�ֽ��� 
					printf("Your cash doesn't suffice\nExit");
					SECS;break;
				}
			}
	if(!flag){CLEAR;printf("Error\n Exiting");SECS}
} 
void Customer::Sell(){//������Ʊ 
	register bool flag=0;
	register char stock_code1[50]="",c;
	register ll stock_volumn;
	printf("\nPlease input the stock code you wanna sell:");cin>>stock_code1;
	for(register int i=0;i<MAXN&&!flag;i++)
		if(IF_CODE)
			if(stocks[i].if_hanged){printf("The stock is hanged");SECS;break;}
			else{
				flag=1;
				printf("Please input the number you wanna sell:");scanf("%lld",&stock_volumn);
				if(stocks_number[i]>=stock_volumn){
				GET;CONFIRM
				IF_Y{
					stocks_number[i]-=stock_volumn;
					stocks[i].shares_floatable+=stock_volumn;
					cash+=stocks[i].listing_price*stock_volumn;
					market_value-=stocks[i].listing_price*stock_volumn;
					CLEAR;printf("Trading succecceds");
					GetLocalTime(&sys);TNew.buy_or_sell=2;
					TNew.number=stock_volumn,TNew.prize=stocks[i].listing_price,TNew.total_prize=stocks[i].listing_price*stock_volumn;
					strcpy(TNew.customer_name,customer_name),strcpy(TNew.stock_name,SName),strcpy(TNew.stock_code,SCode);
					TnD.Date_input(sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute,sys.wSecond);
					trading_number++;
					trading.Store(tradings);
					SECS;A();Customer_information();PAUSE;
					stock.Store(stocks);customer.Store(customers);
				}
				IF_N
			}
			else{//ӵ�й�Ʊ���� 
				printf("Shortage of stock to sell:\n Exiting");
				SECS;break;
			}
		}
	if(!flag){CLEAR;printf("Error\n Exiting");SECS}
}
void Stock::Stop_trading(){//ֹͣ���� 
	register int c1,rank1,stock_rank,b;
	register char c;
	trading.Trading_information(1);
	printf("\nPlease input the number of trading you wanna stop:");scanf("%d",&c1);
	if(c1<=trading_number)
		if(!tradings[c1-1].success){
			printf("\nThe trading been stopped\n");SECS 
			return;
		}
		else{
			GET;CONFIRM
			IF_Y{
				tradings[c1-1].success=0;
				for(register int i=0;i<customer_number;i++)
					if(!strcmp(customers[i].customer_name,tradings[c1-1].customer_name))
						rank1=i;
				for(register int i=0;i<MAXN;i++)
					if(!strcmp(SCode,tradings[c1-1].stock_code))
						stock_rank=i;
				if(tradings[c1-1].buy_or_sell==1)b=1,CHANGE;
				else b=-1,CHANGE;
				GetLocalTime(&sys);ONew.kind=6;
				strcpy(ONew.ad_name,CNow.customer_name),strcpy(ONew.customer_name1,tradings[c1-1].customer_name);
				strcpy(ONew.stock_name1,tradings[c1-1].stock_name),strcpy(ONew.stock_code1,tradings[c1-1].stock_code);
				OntD.Date_input(TctD.year,TctD.month,TctD.day,TctD.hour,TctD.minute,TctD.second);
				OnD.Date_input(sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute,sys.wSecond);
				for(register int j=0;j<customer_number;j++)
					if(customers[j].if_administrator||!strcmp(customers[j].customer_name,ONew.customer_name1))
						customers[j].new_info=1;
				operation_number++;operation.Store(operations);
				stock.Store(stocks),customer.Store(customers),trading.Store(tradings);
				printf("Stopped successfully");SECS;
			}
			IF_N
		}
	else{printf("\nNo trading found.");SECS}
}
void Stock::Restore_trading(){//�ָ����� 
	register int c1,rank1,stock_rank,b;
	register char c;
	trading.Trading_information(1);
	printf("\nPlease input the number of trading you wanna restore:");scanf("%d",&c1);
	if(c1<=trading_number)
		if(tradings[c1-1].success){
			printf("\nThe trading not been stopped\n");SECS 
			return;
		}
		else{
			GET;CONFIRM
			IF_Y{
				tradings[c1-1].success=1;
				for(register int i=0;i<customer_number;i++)
					if(!strcmp(customers[i].customer_name,tradings[c1-1].customer_name))
						rank1=i;
				for(register int i=0;i<MAXN;i++)
					if(!strcmp(SCode,tradings[c1-1].stock_code))
						stock_rank=i;
				if(tradings[c1-1].buy_or_sell==1)b=-1,CHANGE;
				else b=1,CHANGE;
				GetLocalTime(&sys);ONew.kind=7;
				strcpy(ONew.ad_name,CNow.customer_name),strcpy(ONew.customer_name1,tradings[c1-1].customer_name);
				strcpy(ONew.stock_name1,tradings[c1-1].stock_name),strcpy(ONew.stock_code1,tradings[c1-1].stock_code);
				OntD.Date_input(TctD.year,TctD.month,TctD.day,TctD.hour,TctD.minute,TctD.second);
				OnD.Date_input(sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute,sys.wSecond);
				for(register int j=0;j<customer_number;j++)
					if(customers[j].if_administrator||!strcmp(customers[j].customer_name,ONew.customer_name1))
						customers[j].new_info=1;
				operation_number++;operation.Store(operations);
				stock.Store(stocks),customer.Store(customers),trading.Store(tradings);
				printf("Restored successfully");SECS;
			}
			IF_N
		}
	else{printf("\nNo trading found.");SECS}
}
void Stock::Input_stock(){//�����¹�Ʊ��Ϣ 
	CLEAR;GET;
	printf("Input the name of a new stock:");cin.getline(stock_name,50);
	printf("Input the code of the new stock:");cin>>stock_code;
	printf("Input the number of shares outstanding:");scanf("%lld",&shares_total);
	printf("Input the issue price of the shares:");scanf("%lf",&issue_price);
	++stock_number,shares_floatable=shares_total;
	srand((unsigned)time(NULL));
	listing_price=(rand()%3+1)*issue_price+(rand()%1000)/10;
}
void Stock::Hang_up_stock(){//�����Ʊ 
	register char stock_code1[50]="",c;
	register bool flag=0;
	printf("Please input the stock code you wanna hang up:");cin>>stock_code1;
	for(register int i=0;i<MAXN&&!flag;i++)
		if(IF_CODE){
			flag=1;GET;CONFIRM
			IF_Y{
				GetLocalTime(&sys);ONew.kind=3;
				strcpy(ONew.ad_name,CNow.customer_name),strcpy(ONew.stock_name1,SName),strcpy(ONew.stock_code1,SCode);
				OnD.Date_input(sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute,sys.wSecond);
				for(register int j=0;j<customer_number;j++)customers[j].new_info=1;
				operation_number++;operation.Store(operations);
				printf("Hanged successfully");SECS;
				stocks[i].if_hanged=1;stock.Store(stocks);break;
			}
			IF_N
		}
	IF_ERROR
}
void Stock::Unhang_stock(){//��ҹ�Ʊ 
	register char stock_code1[50]="",c;
	register bool flag=0;
	printf("Please input the stock code you wanna restore:");cin>>stock_code1;
	for(register int i=0;i<MAXN&&!flag;i++)
		if(IF_CODE){
			flag=1;GET;CONFIRM
			IF_Y{
				GetLocalTime(&sys);ONew.kind=2;
				strcpy(ONew.ad_name,CNow.customer_name),strcpy(ONew.stock_name1,SName),strcpy(ONew.stock_code1,SCode);
				OnD.Date_input(sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute,sys.wSecond);
				for(register int j=0;j<customer_number;j++)customers[j].new_info=1;
				operation_number++;operation.Store(operations);
				printf("Restored successfully");SECS;
				stocks[i].if_hanged=0;stock.Store(stocks);break;
			}
			IF_N
		}
	IF_ERROR
}
void Stock::Delete_stock(){//ɾ����Ʊ 
	register char c,stock_code1[50]="";
	register bool flag=0;
	printf("Input the stock code you wanna delete:");cin>>stock_code1;
	for(register int i=0;i<MAXN&&!flag;i++)
		if(IF_CODE){
			flag=1;GET;CONFIRM
			IF_Y{
				GetLocalTime(&sys);ONew.kind=4;
				strcpy(ONew.ad_name,CNow.customer_name),strcpy(ONew.stock_name1,SName),strcpy(ONew.stock_code1,SCode);
				OnD.Date_input(sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute,sys.wSecond);
				for(register int j=0;j<customer_number;j++)customers[j].new_info=1;
				operation_number++;operation.Store(operations);
				CNow.cash+=stocks[i].listing_price*CNow.stocks_number[i];
				CNow.market_value-=stocks[i].listing_price*CNow.stocks_number[i];
				CNow.stocks_number[i]=0;
				stocks[i].issue_price=0,stocks[i].listing_price=0;
				stocks[i].shares_floatable=0,stocks[i].shares_total=0;
				strcpy(SName,""),strcpy(SCode,"");
				stock_number--;
				stock.Store(stocks);
				printf("Deleted successfully");SECS;break;
			}
			IF_N
		}
	IF_ERROR
}
void Stock::Modify_stock(){//�޸Ĺ�Ʊ 
	register char stock_name1[50]="",stock_code1[50]="",c;
	register bool flag=0;
	printf("Please input the original stock code:");cin>>stock_code1;
	for(register int i=0;i<MAXN&&!flag;i++)
		if(IF_CODE) 
			if(stocks[i].if_hanged){
				printf("The stock hanged,the operation forbidden.");
				SECS;break;
			}
			else{
				printf("Please input the new stock name you wanna modify to:");GET;cin.getline(stock_name1,50);
				printf("Please input the new stock code you wanna modify to:");cin>>stock_code1;
				flag=1;
				GET;CONFIRM
				IF_Y{
					GetLocalTime(&sys);ONew.kind=5;
					strcpy(ONew.ad_name,CNow.customer_name),strcpy(ONew.stock_name1,SName),strcpy(ONew.stock_code1,SCode);
					strcpy(ONew.stock_name2,stock_name1),strcpy(ONew.stock_code2,stock_code1);
					OnD.Date_input(sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute,sys.wSecond);
					for(register int j=0;j<customer_number;j++)customers[j].new_info=1;
					operation_number++;operation.Store(operations);
					strcpy(SCode,stock_code1),strcpy(SName,stock_name1),stock.Store(stocks);
					printf("Modified successfully.");SECS;
				}
				IF_N
			}
	IF_ERROR
}
void Customer::Modify_code(){//�޸����� 
	CLEAR;
	register char password[50]="",password1[50]="",password2[50]="",c;
	printf("Users: ");cout<<customer_name<<endl<<endl;
	printf("Please input your current password:");Input_number(password);
	if(!strcmp(password,customer_code)){
		CLEAR;printf("Users: ");cout<<customer_name<<endl<<endl;
		printf("Please input your new password:");Input_number(password1);
		printf("\nPlease input your password again to check:");Input_number(password2);
		if(strcmp(password1,password2)){
			printf("\n\nThe two passwords are not the same.");SECS
			return;
		}
		GET;CONFIRM
		IF_Y{
			strcpy(customer_code,password1);customer.Store(customers);
			printf("\n\nSuccess to modify the password.");SECS
		}
		IF_N
	}
	else{printf("\nWrong password");SECS;}
}
void Customer::Modify_name(){//�޸��û��� 
	CLEAR;GET;
	register char password[50]="",c,name[50]="",name1[50]="";
	register int rank1;
	printf("Please input the name to be modified:");cin.getline(name,50);
	register bool b=0;customer.Read_customer();
	for(register int i=0;i<customer_number;i++)if(IF_NAME){b=1,rank1=i;break;}
	if(!b){printf("The user name was not retrieved.");SECS;return;}
	else{
		printf("  Please input the password:");Input_number(password);
		if(!strcmp(password,CNow1.customer_code)){
			printf("\nPlease input the new name:");cin.getline(name1,50);
			CONFIRM
			IF_Y{
				GetLocalTime(&sys);ONew.kind=8;
				strcpy(ONew.ad_name,CNow.customer_name),
				strcpy(ONew.customer_name1,CNow1.customer_name),strcpy(ONew.customer_name2,name1);
				OnD.Date_input(sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute,sys.wSecond);
				for(register int j=0;j<customer_number;j++)
					if(customers[j].if_administrator)
						customers[j].new_info=1;
				operation_number++;operation.Store(operations);
				strcpy(CNow1.customer_name,name1);customer.Store(customers);
				printf("\n\nSuccess to modify the name.");SECS
			}
			IF_N
		}
		else{printf("\nWrong password");SECS;}
	}
}
void Stock::Store(Stock t[]){//����Ʊ��Ϣ�洢���ļ��� 
	ofstream WRITE("Stock_data.txt");
	for(register int i=0;i<MAXN;i++) WRITE.write((char*)(&t[i]),sizeof(t[i]));
	WRITE.close();
}
void Customer::Store(Customer t[]){//���û���Ϣ�洢���ļ��� 
	ofstream WRITE("User_data.txt");
	WRITE.write((char*)(&customer_number),sizeof(int));
	for(register int i=0;i<customer_number;i++) WRITE.write((char*)(&t[i]),sizeof(t[i]));
	WRITE.close();
}
void Trading::Store(Trading t[]){//����Ʊ������Ϣ�洢���ļ��� 
	ofstream WRITE("Trading_records.txt");
	WRITE.write((char*)(&trading_number),sizeof(int));
	for(register int i=0;i<trading_number;i++) WRITE.write((char*)(&t[i]),sizeof(t[i]));
	WRITE.close();
}
void Operation::Store(Operation t[]){//��������Ϣ�洢���ļ��� 
	ofstream WRITE("Operation_records.txt");
	WRITE.write((char*)(&operation_number),sizeof(int));
	for(register int i=0;i<operation_number;i++) WRITE.write((char*)(&t[i]),sizeof(t[i]));
	WRITE.close();
}
void Customer::Read_customer(){//���ļ��ж�ȡ�û���Ϣ 
	ifstream READ("User_data.txt");
	READ.read((char*)(&customer_number),sizeof(int));
	for(register int i=0;i<customer_number;i++)
		READ.read((char*)(&customers[i]),sizeof(customers[i]));
	READ.close();
}
void Stock::Read_stock(){//���ļ��ж�ȡ��Ʊ��Ϣ 
	ifstream READ1("Stock_data.txt");
	for(register int i=0;i<5;i++)
		READ1.read((char*)(&stocks[i]),sizeof(stocks[i]));
	READ1.close();
}
void Trading::Read_Trading(){//���ļ��ж�ȡ��Ʊ������Ϣ 
	ifstream READ("Trading_records.txt");
	READ.read((char*)(&trading_number),sizeof(int));
	for(register int i=0;i<trading_number;i++)
		READ.read((char*)(&tradings[i]),sizeof(tradings[i]));
	READ.close();
}
void Operation::Read_Operation(){//���ļ��ж�ȡ������Ϣ 
	ifstream READ("Operation_records.txt");
	READ.read((char*)(&operation_number),sizeof(int));
	for(register int i=0;i<operation_number;i++)
		READ.read((char*)(&operations[i]),sizeof(operations[i]));
	READ.close();
}
int main(){
	customer.Read_customer();
	stock.Read_stock();
	operation.Read_Operation();
	trading.Read_Trading();
	stock.Interface();
	return 0;
}
