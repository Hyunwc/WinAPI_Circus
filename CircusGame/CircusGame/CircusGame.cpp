// GetInput.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "CircusGame.h"
#include "GameManager.h"

#pragma comment(lib, "msimg32.lib")


#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

HBITMAP audience, elephant, grass; //관객과 코끼리
float g_nX1 = 0;

void Draw(HWND hWnd, HDC hdc);
#include <string>
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
   // LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CIRCUSGAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    HWND hWnd = CreateWindowW(szWindowClass, L"서커스 찰리", WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

  /*  audience = (HBITMAP)LoadImage(NULL, L"RES//back_3.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    elephant = (HBITMAP)LoadImage(NULL, L"RES//back_2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    grass = (HBITMAP)LoadImage(NULL, L"RES//back_1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);*/

    HDC hdc = GetDC(hWnd);

    GameManager::Instance()->Init(hWnd, hdc);

    ULONGLONG FPS = 30; //Frame Per Seconds
    //1초에 몇번 갱신할것인지를 위한 계산
    INT invFPS = 1000 / FPS; //1초 : 1000 

    auto currentTime = GetTickCount64(), checkTime = currentTime;
    float timer = 0;
    MSG msg;
    // 게임 루프:
    while (true)
    {
        //메시지가 있으면 true(1) 없으면 false(0)을 반환
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            //프로그램이 종료되었다는 거을 알리는 WM_QUIT를 확인하여 루프 종료
            //PostQuitMessage 함수가 호출되면 발생.
            if (msg.message == WM_QUIT)  break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            //그리기와 이벤트 처리하는 내용 추가
            currentTime = GetTickCount64(); //윈도우가 시작된 후 지금까지 시간. 1/1000초를 반환
            //
            if (checkTime <= currentTime) //0.03초마다 업데이트
            {
                float deltaTime = (currentTime - checkTime + invFPS) * 0.001f;
                checkTime += invFPS;

                GameManager::Instance()->Update(deltaTime);
                GameManager::Instance()->Draw();
                //GameManager::Instance()->TestDraw();

                /* timer += deltaTime;
                 TextOutA(hdc,0,0,std::to_string(timer).c_str(), std::to_string(timer).length());*/

                 /*if (GetAsyncKeyState(VK_RIGHT))
                 {
                     g_nX += 10 * deltaTime;
                 }
                 if (GetAsyncKeyState(VK_LEFT))
                 {
                     g_nX -= 10 * deltaTime;
                 }*/

                 //현재시간 기준으로 X포지션 -
                //g_nX1 -= 100 * deltaTime;

                ////포지션이 -몇까지 도달시 800으로
                //if (g_nX1 <= -800) g_nX1 += 800;

                //Draw(hWnd, hdc);

                /*InvalidateRect(hWnd, NULL, FALSE);
                UpdateWindow(hWnd);*/
            }
        }
    }

    /*DeleteObject(audience);
    DeleteObject(elephant);
    DeleteObject(grass);*/
    ReleaseDC(hWnd, hdc);
    GameManager::Release();

    return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CIRCUSGAME));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_GETINPUT);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = NULL;//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


void Draw(HWND hWnd, HDC hdc)
{
    //여기서 SelectObject(backDC, backBitmap)까지는 매번 생성 삭제하면
    //비용 낭비이므로 어딘가에 저장해두고 재사용하는게 좋을 것.
    RECT clientRect;
    //클라이언트의 영역을 알려줌
    GetClientRect(hWnd, &clientRect);

    //버퍼
    //덮어쓸 그림을 그리는 캔버스부분
    HBITMAP backBitmap = CreateCompatibleBitmap(hdc, clientRect.right + 1, clientRect.bottom + 1);//MyCreateDIBSection(hdc, clientRect.right + 1, clientRect.bottom + 1);
    //backBitmap을 클리어 시키기 위해 매번 생성 삭제 반복
    HDC backDC = CreateCompatibleDC(hdc);
    SelectObject(backDC, backBitmap);

    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, audience);

    //StretchBlt(DC, 화면상 x, y, 그려지는 너비, 높이, 원본x,y, 
    for (int i = 0; i < 7; i++)
    {
        StretchBlt(backDC, g_nX1 + i * 100, 100, 230, 300, memDC, 0, 0, 145, 245, SRCCOPY);
    }
    oldBitmap = (HBITMAP)SelectObject(memDC, elephant); //코끼리
    StretchBlt(backDC, g_nX1 + 7 * 100, 100, 230, 300, memDC, 0, 0, 145, 245, SRCCOPY);

    oldBitmap = (HBITMAP)SelectObject(memDC, audience); //다시 관객으로
    for (int i = 0; i < 7; i++)
    {
        StretchBlt(backDC, g_nX1 + (i + 8) * 100, 100, 230, 300, memDC, 0, 0, 145, 245, SRCCOPY);
    }
    oldBitmap = (HBITMAP)SelectObject(memDC, elephant);
    StretchBlt(backDC, g_nX1 + (7 + 8) * 100, 100, 230, 300, memDC, 0, 0, 145, 245, SRCCOPY);

    oldBitmap = (HBITMAP)SelectObject(memDC, grass);
    StretchBlt(backDC, 0, 180, 1700, 510, memDC, 0, 0, 145, 245, SRCCOPY);

    SelectObject(memDC, oldBitmap);
    DeleteDC(memDC);

    //덮어쓰는곳
    BitBlt(hdc, 0, 0, clientRect.right + 1, clientRect.bottom + 1, backDC, 0, 0, SRCCOPY);

    //사용 끝났으니 삭제 
    DeleteObject(backDC);
    DeleteObject(backBitmap);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

