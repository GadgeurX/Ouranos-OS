#ifndef JSCLASS_HPP_
#define JSCLASS_HPP_

#include <string>
#include <vector>
#include <webkit/webkit.h>
#include <JavaScriptCore/JavaScript.h>

class JsClass {
    private:
        std::string m_Name;
        std::vector<JSStaticFunction> m_StaticFunc;
        JSClassDefinition m_ClassDef;
        void* m_InitFunc;
    protected:
        void SetName(const std::string&);
        void AddStaticFunc(const std::string&, void*);
        void SetInitFunc(void*);
    public:
        JsClass(const std::string&);
        void Build();
        void LinkJsObject(gpointer);
};

#endif