#include "WebView.hpp"

WebView::WebView()
{
    m_Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_type_hint(GTK_WINDOW(m_Window), GDK_WINDOW_TYPE_HINT_DESKTOP);

	GtkWidget* l_Scrollview = gtk_scrolled_window_new(NULL,NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(l_Scrollview), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
		
	GdkRectangle l_Size;
	gdk_monitor_get_geometry(gdk_display_get_primary_monitor(gdk_display_get_default()), &l_Size);
	gtk_window_set_default_size(GTK_WINDOW(m_Window), l_Size.width, l_Size.height);
		
	m_Webview = WEBKIT_WEB_VIEW(webkit_web_view_new());

	gtk_container_add(GTK_CONTAINER(l_Scrollview), GTK_WIDGET(m_Webview));
	gtk_container_add(GTK_CONTAINER(m_Window), l_Scrollview);

	gtk_widget_show_all(m_Window);
}

void WebView::Load(const std::string& p_AbsPath)
{
	//webkit_web_view_load_uri(webview, ("file:///root/Github/Ouranos-OS/" + path + "/" + package_json["main"].get<std::string>()).c_str());
	webkit_web_view_load_uri(m_Webview, ("file://" + p_AbsPath).c_str());
}

void WebView::LinkOCore(void *p_LinkCallback)
{
	g_signal_connect (G_OBJECT (m_Webview), "window-object-cleared", G_CALLBACK(p_LinkCallback), m_Webview);
}