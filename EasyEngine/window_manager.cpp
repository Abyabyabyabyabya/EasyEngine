// çÏê¨é“ : î¬èÍ
/******************************************************************************

    include

******************************************************************************/
#include "window_manager.hpp"
#include "easy_engine.hpp"
#include <tchar.h>
#include "egeg_state.hpp"


/******************************************************************************

    definition & declaration

******************************************************************************/
namespace wm_ns = easy_engine;
namespace {
    LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
    bool registerWindow();

    constexpr DWORD kWindowStyle = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;
    constexpr DWORD kWindowStyleEx = WS_EX_OVERLAPPEDWINDOW;
    constexpr RECT  kWindowBox {
        0L, // left
        0L, // top
        easy_engine::kWindowWidth<long>, // right
        easy_engine::kWindowHeight<long> // bottom
    };
    std::vector<std::function<void(HWND, UINT, WPARAM, LPARAM)>> gCallbacks{};
} // unnamed namespace


/******************************************************************************

    WindowManager::

******************************************************************************/
wm_ns::WindowManager::WindowManager() : callbacks_{gCallbacks} {}

std::unique_ptr<wm_ns::WindowManager> wm_ns::WindowManager::create() {
    static bool registration = registerWindow();
    if(!registration) return nullptr;

    std::unique_ptr<WindowManager> ptr{new WindowManager{}};

    RECT region = kWindowBox;
    if(!AdjustWindowRectEx(&region, kWindowStyle, false, kWindowStyleEx))
        return nullptr;

    ptr->handle_ = CreateWindowEx(
        kWindowStyleEx,
        _T("Abyabyabyabyabya"),
        _T(EGEG_WINDOW_NAME),
        kWindowStyle,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        region.right - region.left,
        region.bottom - region.top,
        0,
        0,
        GetModuleHandle(nullptr),
        nullptr
    );
    if(ptr->handle_ == 0) return nullptr;
    ShowWindow(ptr->handle(), SW_NORMAL);

    return ptr;
}


/******************************************************************************

    others

******************************************************************************/
namespace { LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wPrm, LPARAM lPrm) {

    PAINTSTRUCT ps;
    HDC         hdc;

    switch( Msg )
    {
    case WM_PAINT:
        hdc = BeginPaint( hWnd, &ps );
        EndPaint( hWnd, &ps );
        return 0;

    case WM_DESTROY:
        PostQuitMessage( 0 );
        return 0;
    }

    for(auto& callback : gCallbacks) 
        callback(hWnd, Msg, wPrm, lPrm);

    return DefWindowProc(hWnd, Msg, wPrm, lPrm);
} }

namespace { bool registerWindow() {
    WNDCLASSEX wnd {
        sizeof(WNDCLASSEX),                       // cbSize,
        CS_VREDRAW,                               // style
        WndProc,                                  // lpfnWndProc
        0,                                        // cbClsExtra
        0,                                        // cbWndExtra
        GetModuleHandle(nullptr),                 // hInstance
        0,                                        // hIcon
        LoadCursor(nullptr, IDC_ARROW),           // hCursor
        reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), // hbrBackground
        nullptr,                                  // lpszMenuName
        _T("Abyabyabyabyabya"),                   // lpszClassName
        0                                         // hIconSm
    };
    return RegisterClassEx(&wnd) != 0;
} }
// EOF
