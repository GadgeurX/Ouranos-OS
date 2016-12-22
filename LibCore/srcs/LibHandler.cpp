#include <webkit/webkit.h>
#include <JavaScriptCore/JavaScript.h>
#include <vector>
#include "JsClass.hpp"
#include "Application.hpp"

std::vector<JsClass> g_JsClasses;

extern "C" void init_libocore()
{
    g_JsClasses.push_back(Application());
}

extern "C" void export_libocore_js(WebKitWebView  *web_view,
                                     WebKitWebFrame *frame,
                                     gpointer        context,
                                     gpointer        window_object,
                                     gpointer        user_data)
{
    for (auto &l_JsClass : g_JsClasses)
        l_JsClass.LinkJsObject(context);
}