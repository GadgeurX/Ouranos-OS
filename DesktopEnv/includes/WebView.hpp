#ifndef WEBVIEW_HPP_
#define WEBVIEW_HPP_

extern "C"
{
	#include <gtk/gtk.h>
	#include <gdk/gdk.h>
	#include <webkit2/webkit2.h>
}
#include <string>

class WebView {
    private:
        GtkWidget* m_Window;
        WebKitWebView* m_Webview;
    public:
        WebView();
        void Load(const std::string& p_AbsPath);
        void LinkOCore(void*);
};

#endif