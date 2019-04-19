#include "at_protocol.h"
#include "usart.h"
#include "common.h"
#include "malloc.h"

u8 AT_ECHO = 0;
AT_Command_S AT_CommandBuf[AT_MAX_NUM];

void AT_CommandInit(void)
{
	u8 i = 0;
	
	AT_CommandBuf[i].id = i;
	AT_CommandBuf[i].len = strlen("IMEI0");
	AT_CommandBuf[i].cmd = (char *)mymalloc(sizeof(char) * AT_CommandBuf[i].len + 1);
	memset(AT_CommandBuf[i].cmd,0,AT_CommandBuf[i].len);
	memcpy(AT_CommandBuf[i].cmd,"IMEI0",AT_CommandBuf[i].len);
	i ++;
	
	AT_CommandBuf[i].id = i;
	AT_CommandBuf[i].len = strlen("IMEI1");
	AT_CommandBuf[i].cmd = (char *)mymalloc(sizeof(char) * AT_CommandBuf[i].len + 1);
	memset(AT_CommandBuf[i].cmd,0,AT_CommandBuf[i].len);
	memcpy(AT_CommandBuf[i].cmd,"IMEI1",AT_CommandBuf[i].len);
	i ++;
	
	AT_CommandBuf[i].id = i;
	AT_CommandBuf[i].len = strlen("IMEI2");
	AT_CommandBuf[i].cmd = (char *)mymalloc(sizeof(char) * AT_CommandBuf[i].len + 1);
	memset(AT_CommandBuf[i].cmd,0,AT_CommandBuf[i].len);
	memcpy(AT_CommandBuf[i].cmd,"IMEI2",AT_CommandBuf[i].len);
	i ++;
	
	AT_CommandBuf[i].id = i;
	AT_CommandBuf[i].len = strlen("IMEI3");
	AT_CommandBuf[i].cmd = (char *)mymalloc(sizeof(char) * AT_CommandBuf[i].len + 1);
	memset(AT_CommandBuf[i].cmd,0,AT_CommandBuf[i].len);
	memcpy(AT_CommandBuf[i].cmd,"IMEI3",AT_CommandBuf[i].len);
	i ++;
	
	AT_CommandBuf[i].id = i;
	AT_CommandBuf[i].len = strlen("IMEI4");
	AT_CommandBuf[i].cmd = (char *)mymalloc(sizeof(char) * AT_CommandBuf[i].len + 1);
	memset(AT_CommandBuf[i].cmd,0,AT_CommandBuf[i].len);
	memcpy(AT_CommandBuf[i].cmd,"IMEI4",AT_CommandBuf[i].len);
	i ++;
	
	AT_CommandBuf[i].id = i;
	AT_CommandBuf[i].len = strlen("IMEI5");
	AT_CommandBuf[i].cmd = (char *)mymalloc(sizeof(char) * AT_CommandBuf[i].len + 1);
	memset(AT_CommandBuf[i].cmd,0,AT_CommandBuf[i].len);
	memcpy(AT_CommandBuf[i].cmd,"IMEI5",AT_CommandBuf[i].len);
	i ++;
	
	AT_CommandBuf[i].id = i;
	AT_CommandBuf[i].len = strlen("IMEI6");
	AT_CommandBuf[i].cmd = (char *)mymalloc(sizeof(char) * AT_CommandBuf[i].len + 1);
	memset(AT_CommandBuf[i].cmd,0,AT_CommandBuf[i].len);
	memcpy(AT_CommandBuf[i].cmd,"IMEI6",AT_CommandBuf[i].len);
	i ++;
	
	AT_CommandBuf[i].id = i;
	AT_CommandBuf[i].len = strlen("IMEI7");
	AT_CommandBuf[i].cmd = (char *)mymalloc(sizeof(char) * AT_CommandBuf[i].len + 1);
	memset(AT_CommandBuf[i].cmd,0,AT_CommandBuf[i].len);
	memcpy(AT_CommandBuf[i].cmd,"IMEI7",AT_CommandBuf[i].len);
	i ++;
	
	AT_CommandBuf[i].id = i;
	AT_CommandBuf[i].len = strlen("IMEI8");
	AT_CommandBuf[i].cmd = (char *)mymalloc(sizeof(char) * AT_CommandBuf[i].len + 1);
	memset(AT_CommandBuf[i].cmd,0,AT_CommandBuf[i].len);
	memcpy(AT_CommandBuf[i].cmd,"IMEI8",AT_CommandBuf[i].len);
	i ++;
	
	AT_CommandBuf[i].id = i;
	AT_CommandBuf[i].len = strlen("IMEI9");
	AT_CommandBuf[i].cmd = (char *)mymalloc(sizeof(char) * AT_CommandBuf[i].len + 1);
	memset(AT_CommandBuf[i].cmd,0,AT_CommandBuf[i].len);
	memcpy(AT_CommandBuf[i].cmd,"IMEI9",AT_CommandBuf[i].len);
	i ++;
	
	AT_CommandBuf[i].id = i;
	AT_CommandBuf[i].len = strlen("IMEIALL");
	AT_CommandBuf[i].cmd = (char *)mymalloc(sizeof(char) * AT_CommandBuf[i].len + 1);
	memset(AT_CommandBuf[i].cmd,0,AT_CommandBuf[i].len);
	memcpy(AT_CommandBuf[i].cmd,"IMEIALL",AT_CommandBuf[i].len);
}


//AT指令帧协议解析,由串口1控制单灯控制器
u16 AT_CommandDataAnalysis(u8 *inbuf,u16 inbuf_len,u8 *outbuf)
{
	u8 i = 0;
	u16 ret = 0;
	u8 err_code = 1;
	u8 cmd_id = 255;
	u8 respbuf[256];
	
//	xSemaphoreTake(xMutex_AT_COMMAND, portMAX_DELAY);
	
	if((MyStrstr(inbuf, (u8 *)"AT", inbuf_len, 2) != 0xFFFF || \
		MyStrstr(inbuf, (u8 *)"AT+", inbuf_len, 3) != 0xFFFF) &&\
		MyStrstr(inbuf, (u8 *)"\r\n", inbuf_len, 2) != 0xFFFF)
	{
//		dev->state = 3;		//调试用
		
		memset(respbuf,0,256);
		
		if(inbuf_len == 4 || inbuf_len == 6)
		{
			if(inbuf_len == 4)
			{
				err_code = 0;
			}
			
			if(inbuf_len == 6)
			{
				if(MyStrstr(inbuf, (u8 *)"ATE0", inbuf_len, 4) != 0xFFFF)
				{
					AT_ECHO = 0;
					err_code = 0;
				}
				else if(MyStrstr(inbuf, (u8 *)"ATE1", inbuf_len, 4) != 0xFFFF)
				{
					AT_ECHO = 1;
					err_code = 0;
				}
			}
		}
		else
		{
			for(i = 0; i < AT_MAX_NUM; i ++)
			{
				if(MyStrstr(inbuf, (u8 *)AT_CommandBuf[i].cmd, inbuf_len, AT_CommandBuf[i].len) != 0xFFFF)
				{
					if(inbuf_len == AT_CommandBuf[i].len + 3 + 2 || \
						MyStrstr(inbuf, (u8 *)"=", inbuf_len, 1) != 0xFFFF)
					{
						cmd_id = i;
					}
					
					break;
				}
			}
			
			switch(cmd_id)
			{
				case UUID0:
					err_code = AT_CommandUUID0(cmd_id,inbuf,inbuf_len,respbuf);
				break;
				
				case UUID1:
					err_code = AT_CommandUUID1(cmd_id,inbuf,inbuf_len,respbuf);
				break;
				
				case UUID2:
					err_code = AT_CommandUUID2(cmd_id,inbuf,inbuf_len,respbuf);
				break;
				
				case UUID3:
					err_code = AT_CommandUUID3(cmd_id,inbuf,inbuf_len,respbuf);
				break;
				
				case UUID4:
					err_code = AT_CommandUUID4(cmd_id,inbuf,inbuf_len,respbuf);
				break;
				
				case UUID5:
					err_code = AT_CommandUUID5(cmd_id,inbuf,inbuf_len,respbuf);
				break;
				
				case UUID6:
					err_code = AT_CommandUUID6(cmd_id,inbuf,inbuf_len,respbuf);
				break;
				
				case UUID7:
					err_code = AT_CommandUUID7(cmd_id,inbuf,inbuf_len,respbuf);
				break;
				
				case UUID8:
					err_code = AT_CommandUUID8(cmd_id,inbuf,inbuf_len,respbuf);
				break;
				
				case UUID9:
					err_code = AT_CommandUUID9(cmd_id,inbuf,inbuf_len,respbuf);
				break;
				
				case UUIDALL:
					err_code = AT_CommandUUIDALL(cmd_id,inbuf,inbuf_len,respbuf);
				break;
				
				default:
					
				break;
			}
		}
		
		ret = PackAT_CommandRespone(inbuf,err_code,respbuf,outbuf);
	}
	
//	xSemaphoreGive(xMutex_AT_COMMAND);
	
	return ret;
}

//打包AT指令回复数据
u16 PackAT_CommandRespone(u8 *inbuf,u8 err_code,u8 *respbuf,u8 *outbuf)
{
	u16 len = 0;
	
	if(AT_ECHO)	//开启回显
	{
		sprintf((char *)outbuf, "%s",inbuf);		//填充回显
	}
	
	if(strlen((char *)respbuf))
	{
		strcat((char *)outbuf,(char *)respbuf);		//填充返回的内容
	}
	
	if(err_code == 0)
	{
		strcat((char *)outbuf,"\r\nOK\r\n");		//填充结果OK
	}
	else
	{
		strcat((char *)outbuf,"\r\nERROR\r\n");		//填充结果ERROR
	}
	
	len = strlen((char *)outbuf);
	
	return len;
}

//获取/设置UUID
u8 AT_CommandUUID0(u8 cmd_id,u8 *inbuf,u16 inbuf_len,u8 *respbuf)
{
	u8 ret = 1;

	if(inbuf_len == AT_CommandBuf[cmd_id].len + 3 + 2)
	{

		sprintf((char *)respbuf, "imei0: %s\r\n",UUIDGroup[0]);

		ret = 0;
	}
	
	return ret;
}

//获取/设置UUID
u8 AT_CommandUUID1(u8 cmd_id,u8 *inbuf,u16 inbuf_len,u8 *respbuf)
{
	u8 ret = 1;

	if(inbuf_len == AT_CommandBuf[cmd_id].len + 3 + 2)
	{

		sprintf((char *)respbuf, "imei1: %s\r\n",UUIDGroup[1]);

		ret = 0;
	}
	
	return ret;
}

//获取/设置UUID
u8 AT_CommandUUID2(u8 cmd_id,u8 *inbuf,u16 inbuf_len,u8 *respbuf)
{
	u8 ret = 1;

	if(inbuf_len == AT_CommandBuf[cmd_id].len + 3 + 2)
	{

		sprintf((char *)respbuf, "imei2: %s\r\n",UUIDGroup[2]);

		ret = 0;
	}
	
	return ret;
}

//获取/设置UUID
u8 AT_CommandUUID3(u8 cmd_id,u8 *inbuf,u16 inbuf_len,u8 *respbuf)
{
	u8 ret = 1;

	if(inbuf_len == AT_CommandBuf[cmd_id].len + 3 + 2)
	{

		sprintf((char *)respbuf, "imei3: %s\r\n",UUIDGroup[3]);

		ret = 0;
	}
	
	return ret;
}

//获取/设置UUID
u8 AT_CommandUUID4(u8 cmd_id,u8 *inbuf,u16 inbuf_len,u8 *respbuf)
{
	u8 ret = 1;

	if(inbuf_len == AT_CommandBuf[cmd_id].len + 3 + 2)
	{

		sprintf((char *)respbuf, "imei4: %s\r\n",UUIDGroup[4]);

		ret = 0;
	}
	
	return ret;
}

//获取/设置UUID
u8 AT_CommandUUID5(u8 cmd_id,u8 *inbuf,u16 inbuf_len,u8 *respbuf)
{
	u8 ret = 1;

	if(inbuf_len == AT_CommandBuf[cmd_id].len + 3 + 2)
	{

		sprintf((char *)respbuf, "imei5: %s\r\n",UUIDGroup[5]);

		ret = 0;
	}
	
	return ret;
}

//获取/设置UUID
u8 AT_CommandUUID6(u8 cmd_id,u8 *inbuf,u16 inbuf_len,u8 *respbuf)
{
	u8 ret = 1;

	if(inbuf_len == AT_CommandBuf[cmd_id].len + 3 + 2)
	{

		sprintf((char *)respbuf, "imei6: %s\r\n",UUIDGroup[6]);

		ret = 0;
	}
	
	return ret;
}

//获取/设置UUID
u8 AT_CommandUUID7(u8 cmd_id,u8 *inbuf,u16 inbuf_len,u8 *respbuf)
{
	u8 ret = 1;

	if(inbuf_len == AT_CommandBuf[cmd_id].len + 3 + 2)
	{

		sprintf((char *)respbuf, "imei7: %s\r\n",UUIDGroup[7]);

		ret = 0;
	}
	
	return ret;
}

//获取/设置UUID
u8 AT_CommandUUID8(u8 cmd_id,u8 *inbuf,u16 inbuf_len,u8 *respbuf)
{
	u8 ret = 1;

	if(inbuf_len == AT_CommandBuf[cmd_id].len + 3 + 2)
	{

		sprintf((char *)respbuf, "imei8: %s\r\n",UUIDGroup[8]);

		ret = 0;
	}
	
	return ret;
}

//获取/设置UUID
u8 AT_CommandUUID9(u8 cmd_id,u8 *inbuf,u16 inbuf_len,u8 *respbuf)
{
	u8 ret = 1;

	if(inbuf_len == AT_CommandBuf[cmd_id].len + 3 + 2)
	{

		sprintf((char *)respbuf, "imei9: %s\r\n",UUIDGroup[9]);

		ret = 0;
	}
	
	return ret;
}

//获取/设置UUID
u8 AT_CommandUUIDALL(u8 cmd_id,u8 *inbuf,u16 inbuf_len,u8 *respbuf)
{
	u8 ret = 1;

	if(inbuf_len == AT_CommandBuf[cmd_id].len + 3 + 2)
	{

		sprintf((char *)respbuf, "imei0: %s\r\nimei1: %s\r\nimei2: %s\r\nimei3: %s\r\nimei4: %s\r\nimei5: %s\r\nimei6: %s\r\nimei7: %s\r\nimei8: %s\r\nimei9: %s\r\n",
			UUIDGroup[0],UUIDGroup[1],UUIDGroup[2],UUIDGroup[3],UUIDGroup[4],UUIDGroup[5],UUIDGroup[6],UUIDGroup[7],UUIDGroup[8],UUIDGroup[9]);

		ret = 0;
	}
	
	return ret;
}

























