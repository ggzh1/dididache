#include<stdio.h> ///宏定义函数
#include<string.h> //串操作及内存操作函数
#include<stdlib.h> /////调用系统函数
#include<time.h> ///时间库函数
#include<conio.h> ///输入输出函数
#define N 1000 //宏定义多条记录
typedef struct TICKET ////定义新结构体TICKET
{
char num[10]; //车车辆号
char hour[3]; //时间，，小时
char min[3]; //分钟
char from[10]; //起点
char to[10]; //目的地
float hours; //车程实际时间
int max; //最大座位容量
int now; //已座位数
}CLASS;
int class_num=0; ///初始车辆总数为0
CLASS records[N]; // 多条记录
int system_time(); //系统时间
void NewMessage(); //新纪录*录入函数******
void ShowTable1(); //线框调用1，，，不用没次输
void ShowTable2(int i); //线框调用2，，，不用没次输
void Display(); //显示所有函数
void add(); //增加记录
void save(); // 保存函数
void load(); // 按车辆查询函数
void search(); //查询函数
void change(); //修改函数**
void quit(); ////////// //退出函数******
void Ticketorder(); // //*购买函数***
void Ticketdelete(); //删除函数*
int menu_select(); //菜单函数*
int whether(int); ////判断时间是否超出函数***
void find(char s1[],char s2[]); //查询函数★//s1为车辆//s2为目的地
void deletemessage(); //删除函数
int findnum(char s1[]); //车辆查询函数
void get(int,int); //修改及增加车辆*
const char *menu[]={"*****************欢迎使用滴滴打车系统*****************",
"\n*******************MENU功能菜单***********************",
"\n◤ ★ 1. 【司机端】录入车辆信息 ◥",
"\n◆ ★ 2. 【用户端】显示所有车辆 ◆",
"\n◆ ★ 3. 【用户端】查询车辆 ◆",
"\n◆ ★ 4. 【司机端】增加车辆 ◆",
"\n◆ ★ 5. 【用户端】打车 ◆",
"\n◆ ★ 6. 【用户端/司机端】取消打车/取消订单 ◆",
"\n◆ ★ 7. 【司机段】修改车辆信息 ◆",
"\n◆ ★ 8. 【司机端】删除车辆 ◆",
"\n◣ ★ 9. 退出 ◢"};
/**************************主函数***************************/
int main()
{
system("cls"); //刷屏
while(1) //菜单函数循环
{
switch(menu_select()) //菜单函数*
{
case 1: NewMessage();break; ////新纪录*录入函数******
case 2: Display();break; // //显示
case 3: search();break; //查找函数**
case 4: add();break; // //增加记录
case 5: Ticketorder();break; ////购买函数***
case 6: Ticketdelete();break; //删除函数*
case 7: change();break; //修改函数**
case 8: deletemessage();break; //////选择调用删除函数
case 9: quit();break; //////退出函数******
}
}
}
/***********************菜单函数**************************/
int menu_select() /////////菜单函数*
{
char s[5]; ///定义要输入的数字功能
int c,i;
system("cls"); //刷屏
system("color 09");//改变颜色
for(i=0;i<11;i++)
{
printf("%s",menu[i]); //输出菜单各项）
}
i=0;
while(c<0||c>9) //判断是否是1到9的命令
{
printf("\n"); ///输出换行
printf("******************************************************");
printf("\n请选择(1-9):▁▂▃▄▆▇");
scanf("%s",s);
c=atoi(s); //atoi将字符串转换成一个整数值
} ///输出菜单面
return c; ////返回请求
}
/*******************************录入函数************************************/
void NewMessage() //*录入函数******
{
int i=0,j=5,h; ////
char s[5];
FILE *fp; ////定义文件型指针变量
system("cls"); //刷屏
if((fp=fopen("d:车票管理系统0.dat","rb"))!=NULL) //fopen打开文件
{
printf("车辆信息已经存在请选择增加功能!\n");
printf("任意输入则返回菜单\n");
scanf("%s",s);
i=1; //通过是1
}
if(i==0)
{
system("cls"); //刷屏
printf("请输入要录入车辆总数:\n");
scanf("%d",&class_num); //指向班次指针
system("cls"); //刷屏
for(i=0;i<class_num;i++)
{
system("cls"); //刷屏
printf("请输入第%d个车辆信息:\n",i+1);
h=-1;
for(;h!=i;) ///循环输出
{
printf("请输入车牌信息:\n");
scanf("%s",records[i].num);
for(h=0;h<i;h++)
if(strcmp(records[h].num,records[i].num)==0)
//判断字符串比较是否相等，， 待比较的字符串
{
printf("输入错误!该车辆信息已存在!\n");
break; ///返回
}
}
get(i,j); ////修改及增加车辆*
j=5;
}
save(); //调用保存函数
}
}
/*******************************显示所有函数********************************/
void Display() //显示所有函数
{
int i,j;
system("cls"); //刷屏
load(); // 调用按班次查询函数
ShowTable1(); //线框调用1，，，不用没次输
for(i=0,j=0;i<class_num;i++,j+=2) /////按车辆信息顺序输出
{
printf("\n|----------|----------|----------|----------|--------|--------|--------|\n");
if(whether(i)) //判断时间是否超出函数***
printf("|%10s|%5s:%-4s|%10s|%10s|%8.1f|%8d|%8d|",records[i].num,records[i].hour,
records[i].min, records[i].from,records[i].to,records[i].hours,
records[i].max,records[i].now);
else
printf("|%10s| 已发车 |%10s|%10s|%8.1f|%8d|%8d|",records[i].num,
records[i].from,records[i].to,records[i].hours,records[i].max,records[i].now);
}
ShowTable2(j); //线框调用2
printf("\n按任意键继续....\n");
getch(); /////从控制台读取一个字符，但不显示在屏幕上
}
/**********************************打印表头***********************************************/
void ShowTable1() //线框调用1，，，不用没次输
{
int i=2;
system("cls"); //刷屏
printf("**************************MESSAGE车程信息**********************************\n");
printf("\n|----------|----------|----------|----------|--------|--------|--------|\n");
printf("\n| 车辆信息 | 发车时间 | 起点 | 目的地 |行车时间|额定载量| 已售座位 |\n");
}
/***************************************打印表尾************************************************/
void ShowTable2(int i) //线框调用2。不用没次输。
{
printf("\n|----------|----------|----------|----------|--------|--------|--------|\n");
}
/**************************查找函数11**************************/
void search() ////查询调用
{
int i;
char s1[10]={'\0'},s2[10]={'\0'};
system("cls"); //刷屏
printf("1. 按车辆信息查询\n");
printf("2. 按目的地查询\n");
printf("3. 退出\n");
printf("请选择(1-3):\n");
scanf("%d",&i);
load(); // 调用按车辆信息查询函数
switch(i) //多分枝选择语句
{
case 1: printf("请输入要查询的车辆信息:\n"); //////s1为车辆信息
scanf("%s",s1);
find(s1,s2); /////调用查找函数222 2
break;
case 2: printf("请输入要查询目的地:\n"); /////s2为目的地
scanf("%s",s2);
find(s1,s2); /////调用查找函数222 2
break;
case 3: break;
default : printf("输入错误!\n");
break;
}
printf("按任意键继续....\n");
getch(); ///从控制台读取一个字符，但不显示在屏幕上
}
/********************************查询函数22*********************************/
void find(char s1[],char s2[])
{
int i,h=0,m;
ShowTable1(); ////调用线框1
if(s2[0]=='\0')
m=1; ///1为无条件执行
else m=0;
for(i=0;i<class_num;i++)
if(strcmp(s1,records[i].num)==0||strcmp(s2,records[i].to)==0)
////判断字符串比较是否相等，， 待比较的字符串
{
printf("\n|----------|----------|----------|----------|--------|--------|--------|\n");
printf("|%10s|%5s:%-4s|%10s|%10s|%8.1f|%8d|%8d|",records[i].num,records[i].hour,records[i].min,
records[i].from,records[i].to,records[i].hours,records[i].max,records[i].now);
h+=2;
if(m==1)
break;
}
ShowTable2(h); ////调用线框2
if(h==0)
printf("要查找的车辆信息不存在!\n");
}
/***********************增加函数****************************/
void add() // //增加记录
{
int i,j=5;
load(); // 调用按车辆信息查询函数
system("cls"); //刷屏
printf("1. 增加车辆\n");
printf("2. 返回\n");
printf("请选择(1-2)\n");
scanf("%d",&i);
if(i==1)
{
system("cls"); //刷屏
printf("1. 请输入要增加的车辆信息:\n");
scanf("%s",records[class_num].num);
for(i=0;i<class_num;i++)
if(strcmp(records[class_num].num,records[i].num)==0)
//判断字符串比较是否相等，， 待比较的字符串 判断车次没重复
{
printf("输入错误!\n");
getch(); /////从控制台读取一个字符，但不显示在屏幕上
break;
}
if(i==class_num)
{
get(i,j); ////修改及增车辆*
class_num++; ///使车辆数加1
save(); //调用保存函数
}
}
}
/********************************购买函数*****************************/
void Ticketorder() //*购买函数***
{
int i;
char num[10];
system("cls"); //刷屏
printf("1. 购买座位.打车\n");
printf("2. 返回\n");
printf("请选择(1-2):\n");
scanf("%d",&i);
if(i==1)
{
load(); // 调用按车辆查询函数
search(); //查找函数**
printf("请输入要订座的车辆信息(若无请输入0):\n");
scanf("%s",num);
for(i=0;i<class_num;i++)
if(strcmp(num,records[i].num)==0)//判断字符串比较是否相等，， 待比较的字符串
if(records[i].max>records[i].now&&whether(i)==1)
//判断时间是否超出函数***并且***没超出最大客量
{
records[i].now++; ///使已售的暑假1
printf("通向%s车辆为%s的座位订单成功!\n",records[i].to,records[i].num);
save(); //调用保存函数
getch(); /////从控制台读取一个字符，但不显示在屏幕上
break;
}
else
{
printf("该车辆已满或车辆已出发!\n");
getch(); /////从控制台读取一个字符，但不显示在屏幕上
}
}
}
/****************************退票删除函数***************************************/
void Ticketdelete() //删除函数*
{
int i;
char num[10];
system("cls"); //刷屏
printf("1. 退订订单\n");
printf("2. 返回\n");
printf("请选择(1-2)\n:");
scanf("%d",&i);
if(i==1)
{
system("cls"); //刷屏
load(); // 调用按车辆查询函数
printf("请输入要退票的车辆:\n");
scanf("%s",num);
i=findnum(num); //调用车辆信息查询函数
if(strcmp(num,records[i].num)==0) //判断字符串比较是否相等 待比较的字符串
if(whether(i)) //判断时间是否超出函数***
{
printf("确定(Y/N)?");
scanf("%s",num);
if(num[0]=='y'||num[0]=='Y')
{
records[i].now--; //使已售票加1
printf("退单成功!\n");
save(); //调用保存函数
getch(); //从控制台读取一个字符，但不显示在屏幕上
}
}
else
{
printf("该车辆已发出,无法退订!\n");
getch(); /////从控制台读取一个字符，但不显示在屏幕上
}
if(i==class_num)
{ printf("输入错误!\n");
getch(); /////从控制台读取一个字符，但不显示在屏幕上
}
}
}
/********************************修改函数*********************************/
void change() //修改函数**
{
char num[10],s[10];
int h=0,j=13,i;
load(); // 调用按车辆查询函数
system("cls"); //刷屏
printf("请输入要修改的车辆:\n");
scanf("%s",num);
i=findnum(num); //调用车辆查询函数
if(i==class_num)
{
printf("输入错误,无此班次!\n");
getch(); ///从控制台读取一个字符，但不显示在屏幕上
}
else
{
printf("确定修改(Y/N)?\n");
scanf("%s",s);
if(s[0]=='y'||s[0]=='Y')
{
get(i,j); ////修改及增加车辆*
save(); //调用保存函数
}
}
}
/*******************************删除函数**********************************/
void deletemessage() //删除班次信息
{
int i,h=0;
char num[10];
system("cls"); //刷屏
printf("1. 删除车辆\n");
printf("2. 返回\n");
printf("请选择(1-2):\n");
scanf("%d",&i);
if(i==1)
{
system("cls"); //刷屏
printf("请输入要删除的车辆:\n");
scanf("%s",num);
i=findnum(num); //调用班次查询函数
if(i==class_num)
{
printf("输入错误,无此车辆!\n");
getch(); ///从控制台读取一个字符，但不显示在屏幕上
}
else
{
printf("确定?(y/n)\n");
scanf("%s",num);
if(num[0]=='y'||num[0]=='Y')
{
for(;i<class_num-1;i++)
records[i]=records[i+1];
class_num--; ////班次总数减1
save(); //调用保存函数
printf("删除成功!\n");
getch();
}
}
}
}
/****************************按班次查询函数****************************/
int findnum(char s1[]) //查找班次
{
int i,h=0;
ShowTable1(); //线框调用1，，，不用没次输
for(i=0;i<class_num;i++)
{
if(strcmp(s1,records[i].num)==0) //判断字符串比较是否相等，如果符合则输出车次等信息
{
printf("|----------|----------|----------|----------|--------|--------|--------|\n");
printf("|%10s|%5s:%-4s|%10s|%10s|%8.1f|%8d|%8d|",records[i].num,records[i].hour,
records[i].min,records[i].from,records[i].to,records[i].hours,records[i].max,records[i].now);
h+=2; ///加2使输出的框架合适
break;
}
}
ShowTable2(h); ///调用框架2
return i;
}
/**************************************保存函数*******************************/
void save() //////保存函数
{
FILE *fp1,*fp2; //文件行指针
if((fp1=fopen("d:车票管理系统.dat","wb"))==NULL) //打开文件、为输出打开一个二进制文件
{
printf("文件打开错误!\n");
exit(0);
}
if((fp2=fopen("d:车票管理系统0.dat","wb"))==NULL) //打开文件、为输出打开一个二进制文件
{
printf("文件打开错误!\n");
exit(0);
}
fwrite(&class_num,sizeof(int),1,fp2); //写入文件信息
fwrite(records,sizeof(CLASS),class_num,fp1);
fclose(fp1);fclose(fp2); ///关闭文件
}
/*******************************按车辆查询函数*******************************/
void load() //按车辆查询函数
{
FILE *fp1,*fp2;
if((fp1=fopen("d:车票管理系统.dat","rb"))==NULL)
{
system("cls"); //刷屏
printf("文件打开错误!\n");
getch(); ///从控制台读取一个字符，但不显示在屏幕上
exit(0);
}
if((fp2=fopen("d:车票管理系统0.dat","rb"))==NULL)
{
system("cls"); //刷屏
printf("文件打开错误!\n");
getch(); ///从控制台读取一个字符，但不显示在屏幕上
exit(0); //退出
}
fread(&class_num,sizeof(int),1,fp2); ///读入信息
fread(records,sizeof(CLASS),class_num,fp1);/////读入信息
fclose(fp1);fclose(fp2); ///文件关闭
}
/******************************退出函数***************************/
void quit() //退出函数******
{
char s[5];
printf("确认退出?(Y/N)\n");
scanf("%s",s);
if(s[0]=='y'||s[0]=='Y')
exit(0); //程序中止执行，返回调用过程..state 0-正常中止非0-非正常
}
/*************************修改及增加车辆*******************************/
void get(int i,int j) // 修改及增加车辆*
{
for(;;)
{
printf("请输入发车时间(xx xx)");scanf("%s%s",records[i].hour,records[i].min);
if((atoi(records[i].hour)<24&&atoi(records[i].hour)>=0)&&(atoi(records[i].min)<60&&atoi(records[i].min)>=0))
break;
else
{
printf("输入错误!\n");
getch(); /////从控制台读取一个字符，但不显示在屏幕上
}
}
printf("请输入起点:\n");
scanf("%s",records[i].from);
printf("请输入目的地:\n");
scanf("%s",records[i].to);
printf("请输入行车时间:\n");
scanf("%f",&records[i].hours);
printf("请输入额定载量:\n");
scanf("%d",&records[i].max);
for(;;)
{
printf("请输入已售票数:\n");
scanf("%d",&records[i].now);
if(records[i].now<=records[i].max)
break;
else
{
printf("输入错误!\n");
getch(); /////从控制台读取一个字符，但不显示在屏幕上
}
}
}
/********************************判断时间是否超出函数**********************************/
int whether(int i) //判断时间是否超出函数***
{
struct tm *local; //时间结构体
time_t t; //把当前时间给t
t=time(NULL); //NULL在stdio.h中定义为0
local=localtime(&t); /////获取当前系统时间
if(local->tm_hour<atoi(records[i].hour)||local->tm_hour==atoi(records[i].hour)&&local->tm_min<atoi(records[i].min))
//atoi将字符串转换成一个整数值
return 1;
else
return 0;
}
