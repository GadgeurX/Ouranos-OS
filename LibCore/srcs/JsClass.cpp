#include "JsClass.hpp"

JsClass::JsClass(const std::string& p_Name)
{
    this->m_Name = std::string(p_Name);
    m_InitFunc = NULL;
}

void JsClass::SetName(const std::string& p_Name)
{
    this->m_Name = std::string(p_Name);
}

void JsClass::AddStaticFunc(const std::string& p_Name, void* p_Func)
{
    std::string* l_Name = new std::string(p_Name);
    JSStaticFunction l_StaticFuncs = {l_Name->c_str(), (JSObjectCallAsFunctionCallback)p_Func, kJSPropertyAttributeReadOnly};
    this->m_StaticFunc.push_back(l_StaticFuncs);
}

void JsClass::SetInitFunc(void* p_Func)
{
    this->m_InitFunc = p_Func;
}

void JsClass::Build()
{
}

void JsClass::LinkJsObject(gpointer p_Context)
{
    JSStaticFunction l_StaticFuncs[m_StaticFunc.size() + 1];
    std::copy(m_StaticFunc.begin(), m_StaticFunc.end(), l_StaticFuncs);
    l_StaticFuncs[m_StaticFunc.size()] = { NULL, NULL, 0 };

    JSClassDefinition l_ClassDefS =
    {
        0,                     // version
        kJSClassAttributeNone, // attributes
        m_Name.c_str(),        // className
        NULL,                  // parentClass
        NULL,                  // staticValues
        l_StaticFuncs,         // staticFunctions
        (JSObjectInitializeCallback)m_InitFunc,            // initialize
        NULL,                  // finalize
        NULL,                  // hasProperty
        NULL,                  // getProperty
        NULL,                  // setProperty
        NULL,                  // deleteProperty
        NULL,                  // getPropertyNames
        NULL,                  // callAsFunction
        NULL,                  // callAsConstructor
        NULL,                  // hasInstance  
        NULL                   // convertToType
    };

    JSClassRef l_ClassDef = JSClassCreate(&l_ClassDefS);
    JSObjectRef l_ClassObj = JSObjectMake((JSContextRef)p_Context, l_ClassDef, p_Context);
    JSObjectRef l_GlobalObj = JSContextGetGlobalObject((JSContextRef)p_Context);
    JSStringRef l_Name = JSStringCreateWithUTF8CString(m_Name.c_str());
    JSObjectSetProperty((JSContextRef)p_Context, l_GlobalObj, l_Name, l_ClassObj, kJSPropertyAttributeNone, NULL);
}