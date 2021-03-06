//---------------------------------------------------------------------------------------------------------------------------
#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"
//---------------------------------------------------------------------------------------------------------------------------
using namespace cocos2d;
//---------------------------------------------------------------------------------------------------------------------------
// uncomment below line, open debug console
// #define USE_WIN32_CONSOLE
//---------------------------------------------------------------------------------------------------------------------------
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	#ifdef USE_WIN32_CONSOLE
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
	#endif

    // create the application instance
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    //eglView->setFrameSize(128*10, 128*8); // 1280x1024
    //eglView->setFrameSize(800,1280);
	 eglView->setFrameSize(800,1280);
   // eglView->setFrameSize(800,1280);
	eglView->setFrameZoomFactor(0.50f);

    int ret = CCApplication::sharedApplication()->run();

	#ifdef USE_WIN32_CONSOLE
    FreeConsole();
	#endif

    return ret;
}
//---------------------------------------------------------------------------------------------------------------------------
