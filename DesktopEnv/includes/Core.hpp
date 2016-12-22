#ifndef CORE_HPP_
#define CORE_HPP_

extern "C"
{
	#include <gtk/gtk.h>
}
#include <fstream>
#include <string>
#include <dlfcn.h>
#include "libconfig.h++"
#include "json.hh"
#include "WebView.hpp"
#include "Path.hpp"

using namespace libconfig;
using Json = nlohmann::json;

class Core {
    private:
        WebView *m_View;
        Config* m_Config;
        void (*init_libocore)();
        void (*link_js_libocore)();
    public:
        Core(int argc, char* argv[]);
        void Init();
        void Run();
};

#endif