#ifndef __AT_PROTOCOL_H
#define __AT_PROTOCOL_H

#include "sys.h"
#include "common.h"

#define AT_MAX_NUM	11

#define UUID0			0
#define UUID1			1
#define UUID2			2
#define UUID3			3
#define UUID4			4
#define UUID5			5
#define UUID6			6
#define UUID7			7
#define UUID8			8
#define UUID9			9
#define UUIDALL			10



typedef struct AT_Command
{
	char *cmd;
	u8 len;
	u8 id;
}AT_Command_S;



extern AT_Command_S AT_CommandBuf[AT_MAX_NUM];

/******************************************************************************************
/                                    通讯错误码
/	
/	
/	
/	
/	
/	
/	
/
******************************************************************************************/
void AT_CommandInit(void);
u16 AT_CommandDataAnalysis(u8 *buf,u16 len,u8 *outbuf);
u16 PackAT_CommandRespone(u8 *inbuf,u8 err_code,u8 *respbuf,u8 *outbuf);


u8 AT_CommandUUID0(u8 cmd_id,u8 *inbuf,u16 inbuf_len,u8 *respbuf);
u8 AT_CommandUUID1(u8 cmd_id,u8 *inbuf,u16 inbuf_len,u8 *respbuf);
u8 AT_CommandUUID2(u8 cmd_id,u8 *inbuf,u16 inbuf_len,u8 *respbuf);
u8 AT_CommandUUID3(u8 cmd_id,u8 *inbuf,u16 inbuf_len,u8 *respbuf);
u8 AT_CommandUUID4(u8 cmd_id,u8 *inbuf,u16 inbuf_len,u8 *respbuf);
u8 AT_CommandUUID5(u8 cmd_id,u8 *inbuf,u16 inbuf_len,u8 *respbuf);
u8 AT_CommandUUID6(u8 cmd_id,u8 *inbuf,u16 inbuf_len,u8 *respbuf);
u8 AT_CommandUUID7(u8 cmd_id,u8 *inbuf,u16 inbuf_len,u8 *respbuf);
u8 AT_CommandUUID8(u8 cmd_id,u8 *inbuf,u16 inbuf_len,u8 *respbuf);
u8 AT_CommandUUID9(u8 cmd_id,u8 *inbuf,u16 inbuf_len,u8 *respbuf);
u8 AT_CommandUUIDALL(u8 cmd_id,u8 *inbuf,u16 inbuf_len,u8 *respbuf);










































#endif
