//netfilter_firewall
//cute eleven 2014-7-20

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>    
#include <unistd.h>    
#include <fcntl.h>

#include "ioctl.h"

#define CE_FW_DEV_IOC_MAGIC  'k'
#define FW_DEV_IOC_REF_DENY_IP        _IO(CE_FW_DEV_IOC_MAGIC,1)
#define FW_DEV_IOC_REF_DENY_PORT        _IO(CE_FW_DEV_IOC_MAGIC,2)
#define FW_DEV_IOC_ADD_DENY_IP  _IOW(CE_FW_DEV_IOC_MAGIC,3,unsigned int)
#define FW_DEV_IOC_ADD_DENY_PORT  _IOW(CE_FW_DEV_IOC_MAGIC,4,short)

FILE *ip_file_open,*port_file_open;

char admin_name[] = "root";
char admin_password[] = "123456";

char login_name[10];
char login_password[10];

unsigned int new_ip;
unsigned int ip_buff;
unsigned short new_port;
unsigned short port_buff;



//主菜单函数
int menu(void)
{
	int i,j;
	welcome();
	
	printf("  1,list all deny ip address\n");	
	printf("  2,list all deny port number\n");
	printf("  3,save settings\n");
	printf("  0,exit\n");
	printf("                                 :");

	
	scanf("%d",&i);
	
	switch(i)
	{
		case 1:
			ip_menu();
			break;
		case 2:
			port_menu();
			break;	
		case 3:
			save();
			int j;
			printf("enter any number to continue:");
			scanf("%d",&j);
			break;
		case 0:
			system("clear");
			exit(0);
			break;
			
		default:
			return 0;
	}
	menu();
	return 0;
}

//ip菜单
int ip_menu()
{
	list_ip();
	printf("  1,add  2,del  3,clear  0,return :");
	int i;
	
	scanf("%d",&i);
	
	switch(i)
	{
		case 1:
		{
			list_ip();
			add_ip();
		}
		break;
		
		case 2:
		{
			list_ip();
			del_ip();
		}
		break;
		
		case 3:
		{
			list_ip();
			clear_ip();
		}
		break;
		
		default:
			menu();
	}
	ip_menu();
}

//port菜单
int port_menu()
{
	list_port();
	printf("  1,add  2,del  3,clear  0,return :");
	int i;
	
	scanf("%d",&i);
	
	switch(i)
	{
		case 1:
		{
			list_port();
			add_port();
		}
		break;
		
		case 2:
		{
			list_port();
			del_port();
		}
		break;
		
		case 3:
		{
			list_port();
			clear_port();
		}
		break;
		
		default:
			menu();
	}
	port_menu();
}

//列出所有ip
int list_ip()
{
	int i;
	struct in_addr in_addr_1;
	welcome();
	for(i=0;i<10;i++)
	{
		fread(&ip_buff,sizeof(unsigned int),1,ip_file_open);
		memcpy(&in_addr_1,&ip_buff,4);
		printf("|     ip %2d:%20s       |\n",i+1,inet_ntoa(in_addr_1));
		//fseek(ip_file_open,(i+1)*sizeof(unsigned int),0);
	}
	rewind(ip_file_open);
	line();
	return 0;
}

//添加ip
int add_ip()
{
	char string[15];
	printf("enter ip address:");
	scanf("%s",string);
	new_ip = inet_addr(string);
	int i;
	
	for(i=0;i<10;i++)
	{
		fread(&ip_buff,sizeof(unsigned int),1,ip_file_open);
		if(ip_buff == 0)
			{
				rewind(ip_file_open);
				fseek(ip_file_open,(i-1)*sizeof(unsigned int),0);
				fwrite(&new_ip,sizeof(unsigned int),1,ip_file_open);
				rewind(ip_file_open);
				printf("ip [%s] add success !\n",string);
				return 0;
			}
		fseek(ip_file_open,i*sizeof(unsigned int),0);
	}
	rewind(ip_file_open);
	return 0;
}

//删除ip地址
int del_ip()
{
	printf("enter ip position:");
	int i;
	scanf("%d",&i);
	new_ip = 0;
	rewind(ip_file_open);
	fseek(ip_file_open,(i-1)*sizeof(unsigned int),0);
	fwrite(&new_ip,sizeof(unsigned int),1,ip_file_open);
	rewind(ip_file_open);
}

//清空所有ip
int clear_ip()
{
	int i;
	for(i=0;i<10;i++)
	{
		ip_buff = 0;
		fwrite(&ip_buff,sizeof(unsigned int),1,ip_file_open);
		fseek(ip_file_open,(i+1)*sizeof(unsigned int),0);
		printf("clear one\n");
	}
	rewind(ip_file_open);
	printf("all ip address clear!\n");
	return 0;
}

//列出所有port号
int list_port()
{
	int i;
	welcome();
	for(i=0;i<10;i++)
	{
		fread(&port_buff,sizeof(unsigned short),1,port_file_open);
		printf("|       port %2d:%13d         |\n",i+1,port_buff);
		//fseek(port_file_open,(i+1)*sizeof(unsigned short),0);
	}
	rewind(port_file_open);
	line();
	return 0;
}

//添加port号
int add_port()
{
	printf("enter port number:");
	scanf("%d",&new_port);
	
	int i;
	
	for(i=0;i<10;i++)
	{
		fread(&port_buff,sizeof(unsigned short),1,port_file_open);
		if(port_buff == 0)
			{
				rewind(port_file_open);
				fseek(port_file_open,(i-1)*sizeof(unsigned short),0);
				fwrite(&new_port,sizeof(unsigned short),1,port_file_open);
				rewind(port_file_open);
				printf("port %d add success !\n",new_port);
				return 0;
			}
		fseek(port_file_open,i*sizeof(unsigned short),0);
	}
	rewind(port_file_open);
	return 0;
}

//删除port号
int del_port()
{
	printf("enter port position:");
	int i;
	scanf("%d",&i);
	new_port = 0;
	rewind(port_file_open);
	fseek(port_file_open,(i-1)*sizeof(unsigned short),0);
	fwrite(&new_port,sizeof(unsigned short),1,port_file_open);
	rewind(port_file_open);
}

//清空所有port号
int clear_port()
{
	int i;
	for(i=0;i<10;i++)
	{
		port_buff = 0;
		fwrite(&port_buff,sizeof(unsigned short),1,port_file_open);
		fseek(port_file_open,(i+1)*sizeof(unsigned short),0);
		printf("clear one\n");
	}
	rewind(port_file_open);
	printf("all port number clear!\n");
	return 0;
}

int save()
{
	int find_device;
	unsigned int cmd;
	unsigned int ip_arg = 0;
	unsigned short port_arg = 0;

	//找到设备
	find_device = open("/dev/ce_fw_dev",O_RDWR);
	if(find_device < 0)
	{
		printf("open ce_fw_dev failed!\n");     
		return -1;
	}

	//调用ioctl执行命令 清除所有内核内存中ip 幻数号0
	printf("<-----call FW_DEV_IOC_REF_DENY_IP----->\n");
	cmd = FW_DEV_IOC_REF_DENY_IP;
	if(ioctl(find_device,FW_DEV_IOC_REF_DENY_IP,&ip_arg) < 0)
	{
		printf("call  FW_DEV_IOC_REF_DENY_IP fail \n");
		return -1;
	}
	printf("<---------REF_DENY_IP success--------->\n");
	
	
	//调用ioctl执行命令 添加所有ip到内核内存中 幻数号1
	printf("\n<-----call FW_DEV_IOC_ADD_DENY_IP----->\n");
	cmd = FW_DEV_IOC_ADD_DENY_IP;
	int i,j = 0;
	for(i=0;i<10;i++)
	{
		fread(&ip_arg,sizeof(unsigned int),1,ip_file_open);
		if(ioctl(find_device,FW_DEV_IOC_ADD_DENY_IP,&ip_arg) < 0)
		{
			printf("call  FW_DEV_IOC_ADD_DENY_IP fail \n");
			return -1;
		}
		printf("add ip%2d : %20d success\n",i+1,ip_arg);
	}
	rewind(ip_file_open);
	printf("<---------ADD_DENY_IP success--------->\n");
	
	
	//调用ioctl执行命令 清除所有内核内存中port 幻数号2
	printf("\n<----call FW_DEV_IOC_REF_DENY_PORT---->\n");
	cmd = FW_DEV_IOC_REF_DENY_PORT;
	if(ioctl(find_device,FW_DEV_IOC_REF_DENY_PORT,&port_arg) < 0)
	{
		printf("call  FW_DEV_IOC_REF_DENY_PORT fail \n");
		return -1;
	}
	printf("<--------REF_DENY_PORT success-------->\n");
	
	
	//调用ioctl执行命令 添加所有port到内核内存中 幻数号3
	printf("\n<----call FW_DEV_IOC_ADD_DENY_PORT---->\n");
	cmd = FW_DEV_IOC_ADD_DENY_PORT;
	i = j = 0;
	for(i=0;i<10;i++)
	{
		fread(&port_arg,sizeof(unsigned short),1,port_file_open);
		if(ioctl(find_device,FW_DEV_IOC_ADD_DENY_PORT,&port_arg) < 0)
		{
			printf("call  FW_DEV_IOC_ADD_DENY_PORT fail \n");
			return -1;
		}
		printf("add port%2d : %18d success\n",i+1,port_arg);
	}
	rewind(port_file_open);
	printf("<--------ADD_DENY_PORT success-------->\n");
	
	//release
	close(find_device);

	line();
	printf("  all save success !\n");
}

//清屏欢迎函数
int welcome()
{
	system("clear");
	printf("----cute_eleven_netfilter_fire_wall----\n");
}

//我是华丽的分割线 O(∩_∩)O~~
int line()
{
	printf("---------------------------------------\n");
}

//管理员登录函数
int login()
{
	welcome();
	
	printf("enter your name:");
	scanf("%s",&login_name);

	printf("enter your password:");
	scanf("%s",&login_password);
	
	if(strcmp(login_name,admin_name))
		if(strcmp(login_password,admin_password))
			return 1;
	else
		return 0;
}


//主函数
int main()
{
	welcome();
	
	int i;
	
	if((ip_file_open = fopen("ip_addr","rb+")) == NULL)
		{
			printf("ip_addr file open error\n");
			return 0;
		}
	if((port_file_open = fopen("port_num","rb+")) == NULL)
		{
			printf("port_num file open error\n");
			return 0;
		}
	
	if(login() != 0)
	{
		printf("login error!\nenter any number to relogin:");
		scanf("%d",&i);
		login();
	}
	
	if(menu() == 0);
		return 0;
}


