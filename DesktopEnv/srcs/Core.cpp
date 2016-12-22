#include "Core.hpp"

Core::Core(int argc, char* argv[])
{
	gtk_init(&argc, &argv);
	m_View = new WebView();
	m_Config = new Config();

	try
  	{
    	m_Config->readFile("./init.cfg");
  	}
  	catch(const FileIOException &fioex)
  	{
    	std::cerr << "I/O error while reading file." << std::endl;
    	exit(EXIT_FAILURE);
  	}
  	catch(const ParseException &pex)
  	{
    	std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
    	exit(EXIT_FAILURE);
  	}
}

void Core::Run()
{
	gtk_main();
}

void Core::Init()
{
	void* handle = dlopen("../LibCore/libOCore.so", RTLD_LAZY);

  	init_libocore = (void (*)())dlsym(handle, "init_libocore");
  	link_js_libocore = (void (*)())dlsym(handle, "export_libocore_js");

	init_libocore();
	m_View->LinkOCore((void*)link_js_libocore);

	try
  	{
    	std::string path = m_Config->lookup("desktop");
		std::ifstream ifs(Path::Format(path) + "/package.json");
		std::cout << Path::Format(path) + "/package.json" << std::endl;
		if (!ifs.good())
		{
			std::cerr << "Apps no valid: " << path << std::endl;
    		exit(EXIT_FAILURE);
		}
		Json package_json;
		ifs >> package_json;
		std::string l_AppPath = Path::Format(path + "/" + package_json["main"].get<std::string>());
		m_View->Load(l_AppPath);
	}
  	catch(const SettingNotFoundException &nfex)
  	{
    	std::cerr << "No 'name' setting in configuration file." << std::endl;
  	}
}

