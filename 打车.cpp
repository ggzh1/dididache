#include<stdio.h> ///�궨�庯��
#include<string.h> //���������ڴ��������
#include<stdlib.h> /////����ϵͳ����
#include<time.h> ///ʱ��⺯��
#include<conio.h> ///�����������
#define N 1000 //�궨�������¼
typedef struct TICKET ////�����½ṹ��TICKET
{
char num[10]; //��������
char hour[3]; //ʱ�䣬��Сʱ
char min[3]; //����
char from[10]; //���
char to[10]; //Ŀ�ĵ�
float hours; //����ʵ��ʱ��
int max; //�����λ����
int now; //����λ��
}CLASS;
int class_num=0; ///��ʼ��������Ϊ0
CLASS records[N]; // ������¼
int system_time(); //ϵͳʱ��
void NewMessage(); //�¼�¼*¼�뺯��******
void ShowTable1(); //�߿����1����������û����
void ShowTable2(int i); //�߿����2����������û����
void Display(); //��ʾ���к���
void add(); //���Ӽ�¼
void save(); // ���溯��
void load(); // ��������ѯ����
void search(); //��ѯ����
void change(); //�޸ĺ���**
void quit(); ////////// //�˳�����******
void Ticketorder(); // //*������***
void Ticketdelete(); //ɾ������*
int menu_select(); //�˵�����*
int whether(int); ////�ж�ʱ���Ƿ񳬳�����***
void find(char s1[],char s2[]); //��ѯ������//s1Ϊ����//s2ΪĿ�ĵ�
void deletemessage(); //ɾ������
int findnum(char s1[]); //������ѯ����
void get(int,int); //�޸ļ����ӳ���*
const char *menu[]={"*****************��ӭʹ�õεδ�ϵͳ*****************",
"\n*******************MENU���ܲ˵�***********************",
"\n�� �� 1. ��˾���ˡ�¼�복����Ϣ ��",
"\n�� �� 2. ���û��ˡ���ʾ���г��� ��",
"\n�� �� 3. ���û��ˡ���ѯ���� ��",
"\n�� �� 4. ��˾���ˡ����ӳ��� ��",
"\n�� �� 5. ���û��ˡ��� ��",
"\n�� �� 6. ���û���/˾���ˡ�ȡ����/ȡ������ ��",
"\n�� �� 7. ��˾���Ρ��޸ĳ�����Ϣ ��",
"\n�� �� 8. ��˾���ˡ�ɾ������ ��",
"\n�� �� 9. �˳� ��"};
/**************************������***************************/
int main()
{
system("cls"); //ˢ��
while(1) //�˵�����ѭ��
{
switch(menu_select()) //�˵�����*
{
case 1: NewMessage();break; ////�¼�¼*¼�뺯��******
case 2: Display();break; // //��ʾ
case 3: search();break; //���Һ���**
case 4: add();break; // //���Ӽ�¼
case 5: Ticketorder();break; ////������***
case 6: Ticketdelete();break; //ɾ������*
case 7: change();break; //�޸ĺ���**
case 8: deletemessage();break; //////ѡ�����ɾ������
case 9: quit();break; //////�˳�����******
}
}
}
/***********************�˵�����**************************/
int menu_select() /////////�˵�����*
{
char s[5]; ///����Ҫ��������ֹ���
int c,i;
system("cls"); //ˢ��
system("color 09");//�ı���ɫ
for(i=0;i<11;i++)
{
printf("%s",menu[i]); //����˵����
}
i=0;
while(c<0||c>9) //�ж��Ƿ���1��9������
{
printf("\n"); ///�������
printf("******************************************************");
printf("\n��ѡ��(1-9):�x�y�z�{�}�~");
scanf("%s",s);
c=atoi(s); //atoi���ַ���ת����һ������ֵ
} ///����˵���
return c; ////��������
}
/*******************************¼�뺯��************************************/
void NewMessage() //*¼�뺯��******
{
int i=0,j=5,h; ////
char s[5];
FILE *fp; ////�����ļ���ָ�����
system("cls"); //ˢ��
if((fp=fopen("d:��Ʊ����ϵͳ0.dat","rb"))!=NULL) //fopen���ļ�
{
printf("������Ϣ�Ѿ�������ѡ�����ӹ���!\n");
printf("���������򷵻ز˵�\n");
scanf("%s",s);
i=1; //ͨ����1
}
if(i==0)
{
system("cls"); //ˢ��
printf("������Ҫ¼�복������:\n");
scanf("%d",&class_num); //ָ����ָ��
system("cls"); //ˢ��
for(i=0;i<class_num;i++)
{
system("cls"); //ˢ��
printf("�������%d��������Ϣ:\n",i+1);
h=-1;
for(;h!=i;) ///ѭ�����
{
printf("�����복����Ϣ:\n");
scanf("%s",records[i].num);
for(h=0;h<i;h++)
if(strcmp(records[h].num,records[i].num)==0)
//�ж��ַ����Ƚ��Ƿ���ȣ��� ���Ƚϵ��ַ���
{
printf("�������!�ó�����Ϣ�Ѵ���!\n");
break; ///����
}
}
get(i,j); ////�޸ļ����ӳ���*
j=5;
}
save(); //���ñ��溯��
}
}
/*******************************��ʾ���к���********************************/
void Display() //��ʾ���к���
{
int i,j;
system("cls"); //ˢ��
load(); // ���ð���β�ѯ����
ShowTable1(); //�߿����1����������û����
for(i=0,j=0;i<class_num;i++,j+=2) /////��������Ϣ˳�����
{
printf("\n|----------|----------|----------|----------|--------|--------|--------|\n");
if(whether(i)) //�ж�ʱ���Ƿ񳬳�����***
printf("|%10s|%5s:%-4s|%10s|%10s|%8.1f|%8d|%8d|",records[i].num,records[i].hour,
records[i].min, records[i].from,records[i].to,records[i].hours,
records[i].max,records[i].now);
else
printf("|%10s| �ѷ��� |%10s|%10s|%8.1f|%8d|%8d|",records[i].num,
records[i].from,records[i].to,records[i].hours,records[i].max,records[i].now);
}
ShowTable2(j); //�߿����2
printf("\n�����������....\n");
getch(); /////�ӿ���̨��ȡһ���ַ���������ʾ����Ļ��
}
/**********************************��ӡ��ͷ***********************************************/
void ShowTable1() //�߿����1����������û����
{
int i=2;
system("cls"); //ˢ��
printf("**************************MESSAGE������Ϣ**********************************\n");
printf("\n|----------|----------|----------|----------|--------|--------|--------|\n");
printf("\n| ������Ϣ | ����ʱ�� | ��� | Ŀ�ĵ� |�г�ʱ��|�����| ������λ |\n");
}
/***************************************��ӡ��β************************************************/
void ShowTable2(int i) //�߿����2������û���䡣
{
printf("\n|----------|----------|----------|----------|--------|--------|--------|\n");
}
/**************************���Һ���11**************************/
void search() ////��ѯ����
{
int i;
char s1[10]={'\0'},s2[10]={'\0'};
system("cls"); //ˢ��
printf("1. ��������Ϣ��ѯ\n");
printf("2. ��Ŀ�ĵز�ѯ\n");
printf("3. �˳�\n");
printf("��ѡ��(1-3):\n");
scanf("%d",&i);
load(); // ���ð�������Ϣ��ѯ����
switch(i) //���֦ѡ�����
{
case 1: printf("������Ҫ��ѯ�ĳ�����Ϣ:\n"); //////s1Ϊ������Ϣ
scanf("%s",s1);
find(s1,s2); /////���ò��Һ���222 2
break;
case 2: printf("������Ҫ��ѯĿ�ĵ�:\n"); /////s2ΪĿ�ĵ�
scanf("%s",s2);
find(s1,s2); /////���ò��Һ���222 2
break;
case 3: break;
default : printf("�������!\n");
break;
}
printf("�����������....\n");
getch(); ///�ӿ���̨��ȡһ���ַ���������ʾ����Ļ��
}
/********************************��ѯ����22*********************************/
void find(char s1[],char s2[])
{
int i,h=0,m;
ShowTable1(); ////�����߿�1
if(s2[0]=='\0')
m=1; ///1Ϊ������ִ��
else m=0;
for(i=0;i<class_num;i++)
if(strcmp(s1,records[i].num)==0||strcmp(s2,records[i].to)==0)
////�ж��ַ����Ƚ��Ƿ���ȣ��� ���Ƚϵ��ַ���
{
printf("\n|----------|----------|----------|----------|--------|--------|--------|\n");
printf("|%10s|%5s:%-4s|%10s|%10s|%8.1f|%8d|%8d|",records[i].num,records[i].hour,records[i].min,
records[i].from,records[i].to,records[i].hours,records[i].max,records[i].now);
h+=2;
if(m==1)
break;
}
ShowTable2(h); ////�����߿�2
if(h==0)
printf("Ҫ���ҵĳ�����Ϣ������!\n");
}
/***********************���Ӻ���****************************/
void add() // //���Ӽ�¼
{
int i,j=5;
load(); // ���ð�������Ϣ��ѯ����
system("cls"); //ˢ��
printf("1. ���ӳ���\n");
printf("2. ����\n");
printf("��ѡ��(1-2)\n");
scanf("%d",&i);
if(i==1)
{
system("cls"); //ˢ��
printf("1. ������Ҫ���ӵĳ�����Ϣ:\n");
scanf("%s",records[class_num].num);
for(i=0;i<class_num;i++)
if(strcmp(records[class_num].num,records[i].num)==0)
//�ж��ַ����Ƚ��Ƿ���ȣ��� ���Ƚϵ��ַ��� �жϳ���û�ظ�
{
printf("�������!\n");
getch(); /////�ӿ���̨��ȡһ���ַ���������ʾ����Ļ��
break;
}
if(i==class_num)
{
get(i,j); ////�޸ļ�������*
class_num++; ///ʹ��������1
save(); //���ñ��溯��
}
}
}
/********************************������*****************************/
void Ticketorder() //*������***
{
int i;
char num[10];
system("cls"); //ˢ��
printf("1. ������λ.��\n");
printf("2. ����\n");
printf("��ѡ��(1-2):\n");
scanf("%d",&i);
if(i==1)
{
load(); // ���ð�������ѯ����
search(); //���Һ���**
printf("������Ҫ�����ĳ�����Ϣ(����������0):\n");
scanf("%s",num);
for(i=0;i<class_num;i++)
if(strcmp(num,records[i].num)==0)//�ж��ַ����Ƚ��Ƿ���ȣ��� ���Ƚϵ��ַ���
if(records[i].max>records[i].now&&whether(i)==1)
//�ж�ʱ���Ƿ񳬳�����***����***û����������
{
records[i].now++; ///ʹ���۵����1
printf("ͨ��%s����Ϊ%s����λ�����ɹ�!\n",records[i].to,records[i].num);
save(); //���ñ��溯��
getch(); /////�ӿ���̨��ȡһ���ַ���������ʾ����Ļ��
break;
}
else
{
printf("�ó������������ѳ���!\n");
getch(); /////�ӿ���̨��ȡһ���ַ���������ʾ����Ļ��
}
}
}
/****************************��Ʊɾ������***************************************/
void Ticketdelete() //ɾ������*
{
int i;
char num[10];
system("cls"); //ˢ��
printf("1. �˶�����\n");
printf("2. ����\n");
printf("��ѡ��(1-2)\n:");
scanf("%d",&i);
if(i==1)
{
system("cls"); //ˢ��
load(); // ���ð�������ѯ����
printf("������Ҫ��Ʊ�ĳ���:\n");
scanf("%s",num);
i=findnum(num); //���ó�����Ϣ��ѯ����
if(strcmp(num,records[i].num)==0) //�ж��ַ����Ƚ��Ƿ���� ���Ƚϵ��ַ���
if(whether(i)) //�ж�ʱ���Ƿ񳬳�����***
{
printf("ȷ��(Y/N)?");
scanf("%s",num);
if(num[0]=='y'||num[0]=='Y')
{
records[i].now--; //ʹ����Ʊ��1
printf("�˵��ɹ�!\n");
save(); //���ñ��溯��
getch(); //�ӿ���̨��ȡһ���ַ���������ʾ����Ļ��
}
}
else
{
printf("�ó����ѷ���,�޷��˶�!\n");
getch(); /////�ӿ���̨��ȡһ���ַ���������ʾ����Ļ��
}
if(i==class_num)
{ printf("�������!\n");
getch(); /////�ӿ���̨��ȡһ���ַ���������ʾ����Ļ��
}
}
}
/********************************�޸ĺ���*********************************/
void change() //�޸ĺ���**
{
char num[10],s[10];
int h=0,j=13,i;
load(); // ���ð�������ѯ����
system("cls"); //ˢ��
printf("������Ҫ�޸ĵĳ���:\n");
scanf("%s",num);
i=findnum(num); //���ó�����ѯ����
if(i==class_num)
{
printf("�������,�޴˰��!\n");
getch(); ///�ӿ���̨��ȡһ���ַ���������ʾ����Ļ��
}
else
{
printf("ȷ���޸�(Y/N)?\n");
scanf("%s",s);
if(s[0]=='y'||s[0]=='Y')
{
get(i,j); ////�޸ļ����ӳ���*
save(); //���ñ��溯��
}
}
}
/*******************************ɾ������**********************************/
void deletemessage() //ɾ�������Ϣ
{
int i,h=0;
char num[10];
system("cls"); //ˢ��
printf("1. ɾ������\n");
printf("2. ����\n");
printf("��ѡ��(1-2):\n");
scanf("%d",&i);
if(i==1)
{
system("cls"); //ˢ��
printf("������Ҫɾ���ĳ���:\n");
scanf("%s",num);
i=findnum(num); //���ð�β�ѯ����
if(i==class_num)
{
printf("�������,�޴˳���!\n");
getch(); ///�ӿ���̨��ȡһ���ַ���������ʾ����Ļ��
}
else
{
printf("ȷ��?(y/n)\n");
scanf("%s",num);
if(num[0]=='y'||num[0]=='Y')
{
for(;i<class_num-1;i++)
records[i]=records[i+1];
class_num--; ////���������1
save(); //���ñ��溯��
printf("ɾ���ɹ�!\n");
getch();
}
}
}
}
/****************************����β�ѯ����****************************/
int findnum(char s1[]) //���Ұ��
{
int i,h=0;
ShowTable1(); //�߿����1����������û����
for(i=0;i<class_num;i++)
{
if(strcmp(s1,records[i].num)==0) //�ж��ַ����Ƚ��Ƿ���ȣ����������������ε���Ϣ
{
printf("|----------|----------|----------|----------|--------|--------|--------|\n");
printf("|%10s|%5s:%-4s|%10s|%10s|%8.1f|%8d|%8d|",records[i].num,records[i].hour,
records[i].min,records[i].from,records[i].to,records[i].hours,records[i].max,records[i].now);
h+=2; ///��2ʹ����Ŀ�ܺ���
break;
}
}
ShowTable2(h); ///���ÿ��2
return i;
}
/**************************************���溯��*******************************/
void save() //////���溯��
{
FILE *fp1,*fp2; //�ļ���ָ��
if((fp1=fopen("d:��Ʊ����ϵͳ.dat","wb"))==NULL) //���ļ���Ϊ�����һ���������ļ�
{
printf("�ļ��򿪴���!\n");
exit(0);
}
if((fp2=fopen("d:��Ʊ����ϵͳ0.dat","wb"))==NULL) //���ļ���Ϊ�����һ���������ļ�
{
printf("�ļ��򿪴���!\n");
exit(0);
}
fwrite(&class_num,sizeof(int),1,fp2); //д���ļ���Ϣ
fwrite(records,sizeof(CLASS),class_num,fp1);
fclose(fp1);fclose(fp2); ///�ر��ļ�
}
/*******************************��������ѯ����*******************************/
void load() //��������ѯ����
{
FILE *fp1,*fp2;
if((fp1=fopen("d:��Ʊ����ϵͳ.dat","rb"))==NULL)
{
system("cls"); //ˢ��
printf("�ļ��򿪴���!\n");
getch(); ///�ӿ���̨��ȡһ���ַ���������ʾ����Ļ��
exit(0);
}
if((fp2=fopen("d:��Ʊ����ϵͳ0.dat","rb"))==NULL)
{
system("cls"); //ˢ��
printf("�ļ��򿪴���!\n");
getch(); ///�ӿ���̨��ȡһ���ַ���������ʾ����Ļ��
exit(0); //�˳�
}
fread(&class_num,sizeof(int),1,fp2); ///������Ϣ
fread(records,sizeof(CLASS),class_num,fp1);/////������Ϣ
fclose(fp1);fclose(fp2); ///�ļ��ر�
}
/******************************�˳�����***************************/
void quit() //�˳�����******
{
char s[5];
printf("ȷ���˳�?(Y/N)\n");
scanf("%s",s);
if(s[0]=='y'||s[0]=='Y')
exit(0); //������ִֹ�У����ص��ù���..state 0-������ֹ��0-������
}
/*************************�޸ļ����ӳ���*******************************/
void get(int i,int j) // �޸ļ����ӳ���*
{
for(;;)
{
printf("�����뷢��ʱ��(xx xx)");scanf("%s%s",records[i].hour,records[i].min);
if((atoi(records[i].hour)<24&&atoi(records[i].hour)>=0)&&(atoi(records[i].min)<60&&atoi(records[i].min)>=0))
break;
else
{
printf("�������!\n");
getch(); /////�ӿ���̨��ȡһ���ַ���������ʾ����Ļ��
}
}
printf("���������:\n");
scanf("%s",records[i].from);
printf("������Ŀ�ĵ�:\n");
scanf("%s",records[i].to);
printf("�������г�ʱ��:\n");
scanf("%f",&records[i].hours);
printf("����������:\n");
scanf("%d",&records[i].max);
for(;;)
{
printf("����������Ʊ��:\n");
scanf("%d",&records[i].now);
if(records[i].now<=records[i].max)
break;
else
{
printf("�������!\n");
getch(); /////�ӿ���̨��ȡһ���ַ���������ʾ����Ļ��
}
}
}
/********************************�ж�ʱ���Ƿ񳬳�����**********************************/
int whether(int i) //�ж�ʱ���Ƿ񳬳�����***
{
struct tm *local; //ʱ��ṹ��
time_t t; //�ѵ�ǰʱ���t
t=time(NULL); //NULL��stdio.h�ж���Ϊ0
local=localtime(&t); /////��ȡ��ǰϵͳʱ��
if(local->tm_hour<atoi(records[i].hour)||local->tm_hour==atoi(records[i].hour)&&local->tm_min<atoi(records[i].min))
//atoi���ַ���ת����һ������ֵ
return 1;
else
return 0;
}
