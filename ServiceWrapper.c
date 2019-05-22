// https://labs.mwrinfosecurity.com/assets/1089/original/Windows_Services_-_All_roads_lead_to_SYSTEM-1.1-oct15.pdf
#include <windows.h>
#include <stdio.h>

#define SLEEP_TIME 5000

SERVICE_STATUS ServiceStatus; 
SERVICE_STATUS_HANDLE hStatus;
 
void ServiceMain(int argc, char** argv); 
void ControlHandler(DWORD request); 
typedef short (CALLBACK* FuncType)(LPCTSTR);

int Run() { 
	//system("cmd.exe");
	system("calc.exe");
	return 0;
}

int main() { 
	SERVICE_TABLE_ENTRY ServiceTable[2];
	ServiceTable[0].lpServiceName = "ServiceNameGoesHere";
	ServiceTable[0].lpServiceProc = (LPSERVICE_MAIN_FUNCTION)ServiceMain;
	ServiceTable[1].lpServiceName = NULL;
	ServiceTable[1].lpServiceProc = NULL;

	StartServiceCtrlDispatcher(ServiceTable);  
	return 0;
}

void ServiceMain(int argc, char** argv) { 
	ServiceStatus.dwServiceType        = SERVICE_WIN32; 
	ServiceStatus.dwCurrentState       = SERVICE_START_PENDING; 
	ServiceStatus.dwControlsAccepted   = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
	ServiceStatus.dwWin32ExitCode      = 0; 
	ServiceStatus.dwServiceSpecificExitCode = 0; 
	ServiceStatus.dwCheckPoint         = 0; 
	ServiceStatus.dwWaitHint			= 0; 
	hStatus = RegisterServiceCtrlHandler("ServiceNameGoesHere", (LPHANDLER_FUNCTION)ControlHandler); 
	
	Run(); 
	
	ServiceStatus.dwCurrentState = SERVICE_RUNNING; 
	SetServiceStatus (hStatus, &ServiceStatus);
	
	while (ServiceStatus.dwCurrentState == SERVICE_RUNNING) {
		Sleep(SLEEP_TIME);
		}
	return; 
}
void ControlHandler(DWORD request) { 
	switch(request) { 
		case SERVICE_CONTROL_STOP: 
			ServiceStatus.dwWin32ExitCode = 0; 
			ServiceStatus.dwCurrentState  = SERVICE_STOPPED; 
			SetServiceStatus(hStatus, &ServiceStatus);
			return; 
		case SERVICE_CONTROL_SHUTDOWN: 
			ServiceStatus.dwWin32ExitCode = 0; 
			ServiceStatus.dwCurrentState  = SERVICE_STOPPED; 
			SetServiceStatus(hStatus, &ServiceStatus);
			return; 
	default:
	break;
	} 
	SetServiceStatus (hStatus,  &ServiceStatus);
	return; 
}

