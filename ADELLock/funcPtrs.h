#pragma once;

typedef int(__stdcall *PF_INIT)(int software, char *server, char *username, int port, int Encoder, int TMEncoder);
typedef int(__stdcall *PF_ENDSESSION)(void);
typedef int(__stdcall *PF_CHANGEUSER)(char *username);
typedef int(__stdcall *PF_NEWKEY)(char *room, char *gate, char *stime, char *guestname, char *guestid, char *lift, int overflag, int Breakfast, long *cardno, char *track1, char *track2);
typedef int(__stdcall *PF_DUPKEY)(char *room, char *gate, char *stime, char *guestname, char *guestid, char *lift, int overflag, int Breakfast, long *cardno, char *track1, char *track2);
typedef int(__stdcall *PF_READCARD)(char *room, char *gate, char *stime, char *guestname, char *guestid, char *lift, char *track1, char *track2, long *cardno, int *st, int *Breakfast);
typedef int(__stdcall *PF_ERASECARD)(long cardno, char *track1, char *track2);
typedef int(__stdcall *PF_CHECKOUT)(char *room, long cardno);
typedef int(__stdcall *PF_LOSTCARD)(char *room, long cardno);
typedef int(__stdcall *PF_SETPORT)(int software, int port, int encoder, int tmencoder);
typedef int(__stdcall *PF_READCARDID)(long *pid);
typedef int(__stdcall *PF_READER_BEEP)(int Sound);




typedef struct tagADEL_FUNCS
{
	HINSTANCE hDllInst;

	PF_INIT			pInit;
	PF_ENDSESSION	pEndSession;
	PF_CHANGEUSER	pChangeUser;
	PF_NEWKEY		pNewKey;
	PF_DUPKEY		pDupKey;
	PF_READCARD		pReadCard;
	PF_ERASECARD	pEraseCard;
	PF_CHECKOUT		pCheckOut;
	PF_LOSTCARD		pLostCard;
	PF_SETPORT		pSetPort;
	PF_READCARDID   pReadCardID;
	PF_READER_BEEP	pReaderBeep;
	
} ADEL_FUNCS, *LPADEL_FUNCS;
