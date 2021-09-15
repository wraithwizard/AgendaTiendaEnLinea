#include <windows.h>

// constantes para los menus
#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

// funciones
void AgregarMenu(HWND);

//el menu
HMENU hMenu;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	//creación de clases para la ventana
	WNDCLASSW wc = { 0 };
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = L"miClaseVentana";
	wc.lpfnWndProc = WindowProcedure;

	if (!RegisterClassW(&wc)) {
		return -1;
	}
	// define el tamaño de la ventana
	CreateWindowW(L"miClaseVentana", L"Agenda de tienda en línea", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 800, 600, NULL, NULL, NULL, NULL);

	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg) {
	case WM_COMMAND:
		switch (wp) {
		// cierra el programa
			case FILE_MENU_EXIT: 
				DestroyWindow(hWnd);
			break;
			case FILE_MENU_NEW:
				MessageBeep(MB_ICONINFORMATION);
			break;
		}
	break;
		// crea el menu
	case WM_CREATE:
		AgregarMenu(hWnd);
	break;
	// cierra la ventana
	case WM_DESTROY: 
		PostQuitMessage(0);
	break;
		default: 
			return DefWindowProcW(hWnd, msg, wp, lp);
	}
}

void AgregarMenu(HWND hWnd) {
	hMenu = CreateMenu();
	// agrega el submenu
	HMENU hFileMenu = CreateMenu();
	HMENU segundoMenu = CreateMenu();
	// submenu productos
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, L"Altas");
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, L"Bajas");
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, L"Cambios");
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, L"Consultar");
	// separador
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	// submenu envios
	AppendMenu(segundoMenu, MF_STRING, FILE_MENU_OPEN, L"Altas");
	AppendMenu(segundoMenu, MF_STRING, FILE_MENU_OPEN, L"Bajas");
	AppendMenu(segundoMenu, MF_STRING, FILE_MENU_OPEN, L"Cambios");
	AppendMenu(segundoMenu, MF_STRING, FILE_MENU_OPEN, L"Consultar");
	// agrega la primer opción del menú
	AppendMenu(hMenu, MF_STRING, 1, L"Vendedor");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"Productos");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"Envíos");
	// para salir
	AppendMenu(hMenu, MF_STRING, FILE_MENU_EXIT, L"Salir");
	SetMenu(hWnd, hMenu);
}