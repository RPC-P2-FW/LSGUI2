#pragma once

#include <WinSock2.h>
#include <specstrings_strict.h>

//sure it will be included only once
#ifndef _YASINLANLIB_H_
#define _YASINLANLIB_H_

// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the YASINLANLIB_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// YASINLANLIB_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef YASINLANLIB_EXPORTS
#define YASINLANLIB_API __declspec(dllexport)
#else
#define YASINLANLIB_API __declspec(dllimport)
#endif

#define RECV_PACKET_SIZE 512 //maximum length in each Receive
#define SEND_PACKET_SIZE 536 //maximum length in each Send
#define PACKET_HEADER_SIZE 8
//#define RECV_PACKET_DATA_SIZE (RECV_PACKET_SIZE - PACKET_HEADER_SIZE)
//#define SEND_PACKET_DATA_SIZE (SEND_PACKET_SIZE - PACKET_HEADER_SIZE)

#define DEFAULT_TCP_PORT "27015"
#define DEFAULT_UDP_PORT 27015

enum command : unsigned __int8
{
    readRegCommand		= 0x01,	//read register command
    readRegFBCommand	= 0xF1,	//read register feed back command
    writeRegCommand		= 0x02,	//write register command
    writeRegAckCommand	= 0xF2,	//write register Acknowledge command
    readMemCommand		= 0x03,	//read memory command
    readMemFBCommand	= 0xF3,	//read memory feed back command
    writeMemCommand		= 0x04,	//write memory command
    writeMemAckCommand	= 0xF4,	//write memory Acknowledge command
    readCfgCommand		= 0x05,	//read configuration command
    readCfgFBCommand	= 0xF5,	//read configuration feed back command
    writeCfgCommand		= 0x06,	//write configuration command
    writeCfgAckCommand	= 0xF6,	//write configuration Acknowledge command
};

//to export for C++ & C
#ifdef __cplusplus
extern "C"
{
#endif

// This class is exported from the YasinLanLib.dll
class YASINLANLIB_API CYasinLanLib {
public:
    CYasinLanLib(void);
    // TODO: add your methods here.
};
/*
extern YASINLANLIB_API int nYasinLanLib;

YASINLANLIB_API int fnYasinLanLib(void);
*/

YASINLANLIB_API int GetLastWSAError(void);

YASINLANLIB_API bool YE_LanStartup(void);
YASINLANLIB_API bool YE_LanCleanup(void);

YASINLANLIB_API bool YE_Ping(_In_ const char *pIP, _Out_ PDWORD numOfEchoReply, _Out_writes_z_(16) char address[16], _Out_ PULONG status, _Out_ PULONG roundTripTime, _Out_ PUSHORT dataSize);
//YASINLANLIB_API bool YE_Ping(_In_ const char *pIP, _Out_ PDWORD numOfEchoReply, _Out_z_cap_(16) char address[16], _Out_ PULONG status, _Out_ PULONG roundTripTime, _Out_ PUSHORT dataSize);


YASINLANLIB_API bool YE_SetRecvPacketSize(_In_opt_ USHORT packetSize=RECV_PACKET_SIZE);
YASINLANLIB_API bool YE_SetSendPacketSize(_In_opt_ USHORT packetSize=SEND_PACKET_SIZE);

YASINLANLIB_API bool YE_TCP_Connect(_In_opt_ PCSTR pIP, _In_opt_ PCSTR pPort=DEFAULT_TCP_PORT);
YASINLANLIB_API bool YE_TCP_Disconnect(void);
YASINLANLIB_API bool YE_UDP_CreateSocket(_In_ const char *pIP, _In_opt_ unsigned short port=DEFAULT_UDP_PORT);
YASINLANLIB_API bool YE_UDP_CloseSocket(void);

YASINLANLIB_API bool YE_TCP_WriteConfig(_In_ UCHAR address, _In_ UINT value);
YASINLANLIB_API bool YE_UDP_WriteConfig(_In_ UCHAR address, _In_ UINT value);
YASINLANLIB_API bool YE_TCP_ReadConfig(_In_ UCHAR address);
YASINLANLIB_API bool YE_UDP_ReadConfig(_In_ UCHAR address);
YASINLANLIB_API bool YE_TCP_WriteReg(_In_ USHORT address, _In_ UINT value);
YASINLANLIB_API bool YE_UDP_WriteReg(_In_ USHORT address, _In_ UINT value);
YASINLANLIB_API bool YE_TCP_ReadReg(_In_ USHORT address);
YASINLANLIB_API bool YE_UDP_ReadReg(_In_ USHORT address);
YASINLANLIB_API bool YE_TCP_WriteMem(_In_ USHORT address,  _In_reads_bytes_(length) void* buffer, _In_ USHORT length);
//YASINLANLIB_API bool YE_UDP_WriteMem(_In_ USHORT address, _In_bytecount_(length) void* buffer, _In_ USHORT length);
YASINLANLIB_API bool YE_TCP_ReadMem(_In_ USHORT address, _In_ USHORT length);
YASINLANLIB_API bool YE_UDP_ReadMem(_In_ USHORT address, _In_ USHORT length);

YASINLANLIB_API bool YE_TCP_SendMem(_In_reads_(length) const char buffer[], _In_ size_t length);
//YASINLANLIB_API bool YE_UDP_SendMem(_In_count_(length) const char buffer[], _In_ size_t length, _In_ int packetLength);
YASINLANLIB_API void YE_TCP_StopSend(void);
YASINLANLIB_API void YE_UDP_StopSend(void);
YASINLANLIB_API INT64 YE_TCP_GetSentSize(void);
YASINLANLIB_API INT64 YE_UDP_GetSentSize(void);
YASINLANLIB_API bool YE_TCP_RecvPacket(_Out_ PUCHAR command, _Out_ PUSHORT address, _Out_ PUINT value, _Out_writes_bytes_(*length) void* buffer, _Out_ PUSHORT length, _Out_ PUCHAR packetCounter);
//YASINLANLIB_API bool YE_TCP_RecvPacket(_Out_ PUCHAR command, _Out_ PUSHORT address, _Out_ PUINT value, _Out_bytecap_(*length) void* buffer, _Out_ PUSHORT length, _Out_ PUCHAR packetCounter);
YASINLANLIB_API bool YE_UDP_RecvPacket(_Out_ PUCHAR command, _Out_ PUSHORT address, _Out_ PUINT value, _Out_writes_bytes_(*length) void* buffer, _Out_ PUSHORT length, _Out_ PUCHAR packetCounter);
//YASINLANLIB_API bool YE_UDP_RecvPacket(_Out_ PUCHAR command, _Out_ PUSHORT address, _Out_ PUINT value, _Out_bytecap_(*length) void* buffer, _Out_ PUSHORT length, _Out_ PUCHAR packetCounter);

#ifdef __cplusplus
}
#endif

//EOF Header body
#endif
