#include <stdio.h>
#include <Windows.h>
#include <winnt.h>

int main(int argc, char * argv[]){
	PIMAGE_DOS_HEADER dos_h;
	PIMAGE_NT_HEADERS nt_h;
	HANDLE hFile, hFileMap;
	wchar_t filename[260] = { 0, };
	DWORD filesize;
	PCHAR Map_file;
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, argv[1], strlen(argv[1]), filename, 260);

	// parameter error
	if (argc != 2){
		printf("Usage : %s <File>",argv[0]);
		return 0;
	}
	/* fopen
	FILE *f = fopen(filename, "r");
	if(f == NULL){
		printf("function fail : fopen() !! gle = %08x", GetLastError());
	}*/
	SetCurrentDirectory(L"C:\\Users\\seunghyeon\\Documents\\Visual Studio 2013\\Projects\\PEviewer\\Debug");
	// File Open, use CreateFile() 
	hFile = CreateFile((LPCWSTR)filename, // ���� �̸�
						GENERIC_READ | GENERIC_WRITE, // �б� ����
						FILE_SHARE_READ, // ���� 
						NULL, // ����
						OPEN_EXISTING, // �����׻󿭱�  
						FILE_ATTRIBUTE_NORMAL, // ���ϼӼ� �븻
						NULL);

	if (hFile == INVALID_HANDLE_VALUE){
		printf("function fail : CreateFile() !! gle = %d", GetLastError());
		return 0;
	}
	filesize = GetFileSize(hFile, NULL);

	hFileMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
	if (hFileMap == NULL){
		printf("function fail : CreateFileMapping() !! gle = %d", GetLastError());
		return 0;
	}

	Map_file = (PCHAR)MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, filesize);
	if (Map_file == NULL){
		printf("function fail : MapViewOfFile() !! gle = %d", GetLastError());
		return 0;
	}

	dos_h = (PIMAGE_DOS_HEADER)Map_file; // DOS_HEADER
	nt_h = (PIMAGE_NT_HEADERS)((DWORD)dos_h + dos_h->e_lfanew); // NT_HEADER

	printf(" * IMAGE_DOS_HEADER * %X", dos_h->e_magic);
	printf(" ")
}