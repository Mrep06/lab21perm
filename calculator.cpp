#include <windows.h>
#include <cstdio>

HWND textfield, button1,button2,button3,button4,textbox1,textbox2;
char textboxsaved1[100];
char textboxsaved2[100];
double resultVal = 0;
char result[100];
double number1 = 0;
double number2 = 0;
/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {

        case WM_CREATE:

            textfield = CreateWindow("STATIC",
                                     "Please input two numbers",
                                     WS_VISIBLE | WS_CHILD | WS_BORDER,
                                     234, 20, 172, 20,
                                     hwnd, NULL, NULL, NULL);

            button1 = CreateWindow("BUTTON",
                                     "+",
                                     WS_VISIBLE | WS_CHILD | WS_BORDER,
                                     240, 150, 30, 20,
                                     hwnd, (HMENU) 1, NULL, NULL);

            button2 = CreateWindow("BUTTON",
                                     "-",
                                     WS_VISIBLE | WS_CHILD | WS_BORDER,
                                     280, 150, 30, 20,
                                     hwnd, (HMENU) 2, NULL, NULL);

            button3 = CreateWindow("BUTTON",
                                     "*",
                                     WS_VISIBLE | WS_CHILD | WS_BORDER,
                                     320, 150, 30, 20,
                                     hwnd, (HMENU) 3, NULL, NULL);

            button4 = CreateWindow("BUTTON",
                                     "/",
                                     WS_VISIBLE | WS_CHILD | WS_BORDER,
                                     360, 150, 30, 20,
                                     hwnd, (HMENU) 4, NULL, NULL);

            textbox1 = CreateWindow("EDIT",
                                 "",
                                 WS_BORDER | WS_CHILD | WS_VISIBLE,
                                 120, 60, 400,20,
                                 hwnd, NULL, NULL, NULL);

            textbox2 = CreateWindow("EDIT",
                                 "",
                                 WS_BORDER | WS_CHILD | WS_VISIBLE,
                                 120, 90, 400,20,
                                 hwnd, NULL, NULL, NULL);
            break;

        case WM_COMMAND:
            GetWindowText(textbox1, &textboxsaved1[0], 100);
            GetWindowText(textbox2, &textboxsaved2[0], 100);
            number1 = atof(textboxsaved1);
            number2 = atof(textboxsaved2);

            switch(LOWORD(wParam)) {
                case 1: // Addition
                    resultVal = number1 + number2;
                    break;
                case 2: // Subtraction
                    resultVal = number1 - number2;
                    break;
                case 3: // Multiplication
                    resultVal = number1 * number2;
                    break;
                case 4: // Division
                    if (number2 == 0) {
                        ::MessageBox(hwnd, "Error: Division by Zero!", "Error", MB_OK | MB_ICONERROR);
                        return 0; // Exit early if division by zero
                    }
                    resultVal = number1 / number2;
                    break;
                default:
                    return 0;
            }

            snprintf(result, sizeof(result), "%f", resultVal);
            ::MessageBox(hwnd, result, "Result", MB_OK);
            break;

		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}

		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);

	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = CreateSolidBrush(RGB(255, 0, 102));
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		640, /* width */
		480, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
