#include"Headers.h"
//#include"Defines.h"
#include"stdio.h"
#include<string>
#include <iostream>
#include <typeinfo>
using namespace std;
int fnG_HexToByte(unsigned char *byte,const char *buf)
{
	int i,j=0,temp=strlen(buf);
	char tmp[3],byte_value[1000]={0x00};
	tmp[3]='\0';
	for(i=0;i<temp;i+=2)
	{
		tmp[0] = buf[i];
		tmp[1] = buf[i+1];
		byte[j++]=(strtol(tmp,NULL,16));
		sprintf(byte_value,"%s%d",byte_value,byte[j-1]);
	}
	cout<<"Byte Stream:"<<byte_value<<endl;
	return j;
}
void mefnS_truncate(char* pscL_ObjName)
{
	char pscL_Buffer[128];
	int siL_StrLen=0;
	char *p=NULL;
	memset(pscL_Buffer,0x00,sizeof(pscL_Buffer));
	strcpy(pscL_Buffer,pscL_ObjName);
	siL_StrLen=strlen(pscL_Buffer);
	p=pscL_Buffer + siL_StrLen-1;
	while(siL_StrLen--)
	{
		if(*p >='0' && *p <='9')
		{
			p++;
			break;
		}
		p--;
	}
	strcpy(pscL_ObjName,p);
}
int main(int siL_argc,char **pscL_argv)
{
	if(siL_argc<2)
	{
		cout<<"Please use this exe as ProtoDecoder.exe <PacketToDecode> "<<endl;
		exit(0);
	}	
	className obj;
	char pscL_ObjName[128];
	strcpy(pscL_ObjName,typeid(obj).name());
	mefnS_truncate(pscL_ObjName);
	cout<<"Enter into the main with arrgments"<<":"<<pscL_argv[0]<<":"<<pscL_argv[1]<<" ClassName is:"<<pscL_ObjName<<endl;
	unsigned char data[MaxLenPkt];
	int len = fnG_HexToByte(data,pscL_argv[1]);
	if(obj.ParseFromArray(data,len))
	{
		cout<<"Decoded Packet is:"<<endl;
		cout<<obj.ShortDebugString().c_str()<<endl;
	}
	else{
		cout<<"parsing failed packet is:"<<pscL_argv[1]<<"class is:"<<pscL_ObjName;
	}
}
