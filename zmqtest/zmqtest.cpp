
#include <zmq.h>
#include <Windows.h>
#include <string.h>
#include <tchar.h>
#include <iostream>

using namespace std;

void  GetProgramCompileTime(SYSTEMTIME &st);

unsigned long file_size(char *filename)
{
	FILE *pFile = NULL;
	fopen_s(&pFile, filename, "rb");
	
	//fopen_s(&pFile, filename, );
	//fopen()
	//_fsopen()
	fseek(pFile, 0, SEEK_END);
	unsigned long size = ftell(pFile);
	fclose(pFile);
	return size;
}


VOID APIENTRY TimerAPCRoutine(PVOID pvArgToCompletionRoutine,
	DWORD dwTimerLowValue, DWORD dwTimerHighValue) {

	FILETIME ftUTC, ftLocal;
	SYSTEMTIME st;
	TCHAR szBuf[256];

	// Put the time in a FILETIME structure.
	ftUTC.dwLowDateTime = dwTimerLowValue;
	ftUTC.dwHighDateTime = dwTimerHighValue;

	// Convert the UTC time to the user's local time.
	FileTimeToLocalFileTime(&ftUTC, &ftLocal);

	// Convert the FILETIME to the SYSTEMTIME structure
	// required by GetDateFormat and GetTimeFormat.
	FileTimeToSystemTime(&ftLocal, &st);

	// Construct a string with the 
	// date/time that the timer went off.
	GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE,
		&st, NULL, szBuf, sizeof(szBuf) / sizeof(TCHAR));
	wcscat_s(szBuf, TEXT(" "));
	GetTimeFormat(LOCALE_USER_DEFAULT, 0,
		&st, NULL, wcschr(szBuf, 0),
		sizeof(szBuf) / sizeof(TCHAR) - wcslen(szBuf));

	// Show the time to the user.
	MessageBox(NULL, szBuf, TEXT("Timer went off at..."), MB_OK);
}


void SomeFunc() {
	// Create a timer. (It doesn't matter whether it's manual-reset 
	// or auto-reset.)
//	HANDLE hTimer = CreateWaitableTimer(NULL, TRUE, NULL);
	HANDLE hTimer = CreateWaitableTimer(NULL, FALSE,NULL);
	// Set timer to go off in 5 seconds.
	LARGE_INTEGER li = { 0 };
	//li.QuadPart = -(5 * 10000000);
	SetWaitableTimer(hTimer, &li, 5000, TimerAPCRoutine, NULL, FALSE);

	// Wait in an alertable state for the timer to go off.
	SleepEx(INFINITE, TRUE);

	CloseHandle(hTimer);
}

#include <iostream>

const char *version = "1.1.1.1";

void PrintVersion()
{
	printf("version: %s, %s %s \n", version, __DATE__, __TIME__);
}


	/*

	CHAR szfilename[] = "C:\\Users\\Administrator\\Documents\\Visual Studio 2015\\Projects\\scanApp\x64\\Debug\\zlog.dll";
	CHAR szdrv[_MAX_DRIVE = { 0 };
	CHAR szdir[_MAX_DIR] = { 0 };
	CHAR szname[_MAX_FNAME] = { 0 };
	CHAR ext[_MAX_EXT] = { 0 };
	_splitpath_s(szfilename, szdrv,4, szdir,MAX_PATH, szname,MAX_PATH, ext,MAX_PATH);

	printf("%s\n", szfilename);
	printf("%s\n", szdrv);
	printf("%s\n", szdir);
	printf("%s\n", szname);
	printf("%s\n", ext);
	
	*/
//	while(1)
//		SomeFunc();

/*	HANDLE hTime = CreateWaitableTimer(NULL, TRUE, NULL);
	size_t nsFilesize = 0;
	INT  nsize = sizeof(size_t);
	printf("sizeof %d", nsize);
	if (NULL == hTime)
	{
		cout << "hTime is NULL" << endl;
		return -1;
	}

	LARGE_INTEGER liDueTime;
	liDueTime.QuadPart = -50000000;
	if (!SetWaitableTimer(hTime, &liDueTime, 0, NULL, NULL, FALSE))
	{
		cout << "SetWaitableTimer error" << endl;
		return -1;
	}

	while (1)
	{
		if (WaitForSingleObject(hTime, INFINITE) != WAIT_OBJECT_0)
		{
			cout << "WaitForSingleObject error" << endl;
			return -1;
		}
		else
		{
			cout << "WaitForSingleobject succeed" << endl;
			SetWaitableTimer(hTime, &liDueTime, 0, NULL, NULL, FALSE);
		}
	}
	CloseHandle(hTime);


}
*/

    //SYSTEMTIME st;
	//
	//
	//GetProgramCompileTime(st);


	int main(int argc, char *argv[])
	{
		if (argc == 2 && _stricmp(argv[1], "-v") == 0)
			PrintVersion();



		return 0;
	}

	/*FILE* f = NULL;
	 fopen_s(&f,"d:/d.txt", "w");
	if (f)
	{
		size_t  filesize = 1024*1024*1024;
		int iret = fseek(f, filesize - 1, SEEK_SET);
		fputc(EOF, f);
		fclose(f);
	}

	*/
	/*
	
	void* context = zmq_ctx_new();
	void* responder = zmq_socket(context, ZMQ_REP);
	zmq_bind(responder, "tcp://*:5555");

	while (1)
	{
		zmq_msg_t request;
		zmq_msg_init(&request);
		zmq_msg_recv(&request, responder, 0);
		printf("received Hello\n");
		zmq_msg_close(&request);

		Sleep(1);
		zmq_msg_t reply;
		zmq_msg_init_size(&reply, 5);
		memcpy(zmq_msg_data(&reply), "World", 5);
		zmq_msg_send(&reply, responder, 0);
		zmq_msg_close(&reply);
	}
	// should not arrive here
	zmq_close(responder);
	zmq_ctx_destroy(context);
	return 0;
	
	*/



/*
//#include <zmq.h>
#include <string.h>
#include <Windows.h>

int main()
{

	/*
	void* context = zmq_ctx_new();

	printf("Connecting to hello world server...\n");

	void* requester = zmq_socket(context, ZMQ_REQ);
	zmq_connect(requester, "tcp://10.213.200.222:5555");

	int request_nbr;
	for (request_nbr = 0; request_nbr != 10; request_nbr++) {
		char buffer[10];
		printf("Sending Hello %d¡­\n", request_nbr);
		zmq_send(requester, "Hello", 5, 0);
		zmq_recv(requester, buffer, 10, 0);
		printf("Received World %d\n", request_nbr);
	}
	zmq_close(requester);
	zmq_ctx_destroy(context);


	return 0;
	*/

/*	TCHAR fsExist[] = TEXT("d:\\tools\\cJSON-master.zip");
	TCHAR fsNewFile[] = TEXT("d:\\temp\\cJSON-master.zip");

	BOOL bRet = FALSE;
		bRet = MoveFile(fsExist, fsNewFile);
		DWORD dwerror = GetLastError();

		bRet = MoveFile(fsExist, fsNewFile);
		dwerror = GetLastError();


		return 0;
		*/
		


void  GetProgramCompileTime(SYSTEMTIME &st)
{

	CHAR szDate[20];
	ZeroMemory(szDate, sizeof(szDate));
	ZeroMemory(&st, sizeof(SYSTEMTIME));
	//wsprintf(szDate, TEXT("%s"), __DATE__);
	_snprintf_s(szDate,20,_TRUNCATE,"%s",__DATE__);
//	_stprintf_s(szDate, TEXT("%s"), __DATE__);

	//st.wYear = tcstoul(szDate + 7, 0, 10);
	//st.wYear = wcstoul(szDate + 7,	0, 10);
	
	st.wDay = szDate[5] - TEXT('0');
	if (szDate[4] != TEXT(' '))
	{
		st.wDay += (szDate[4] - TEXT('0')) * 10;
	}

	switch (szDate[0])
	{
	case TEXT('A'):
		if (szDate[1] == TEXT('p'))
		{
			st.wMonth = 4;
		}
		else
		{
			st.wMonth = 8;
		}
		break;

	case TEXT('D'):
		st.wMonth = 12;
		break;

	case TEXT('F'):
		st.wMonth = 2;
		break;

	case TEXT('J'):
		if (szDate[1] == TEXT('a'))
		{
			st.wMonth = 1;
		}
		else
		{
			if (szDate[2] == TEXT('n'))
			{
				st.wMonth = 6;
			}
			else
			{
				st.wMonth = 7;
			}
		}
		break;

	case TEXT('M'):
		if (szDate[2] == TEXT('r'))
		{
			st.wMonth = 3;
		}
		else
		{
			st.wMonth = 5;
		}
		break;

	case TEXT('N'):
		st.wMonth = 11;
		break;

	case TEXT('O'):
		st.wMonth = 10;
		break;

	case TEXT('S'):
		st.wMonth = 9;
		break;
	}

	ZeroMemory(szDate, sizeof(szDate));
	//_stprintf_s(szDate, TEXT("%s"), __TIME__);

	st.wHour = (szDate[0] - TEXT('0')) * 10 + (szDate[1] - TEXT('0'));
	st.wMinute = (szDate[3] - TEXT('0')) * 10 + (szDate[4] - TEXT('0'));
	st.wSecond = (szDate[6] - TEXT('0')) * 10 + (szDate[7] - TEXT('0'));
	return;
}
	


