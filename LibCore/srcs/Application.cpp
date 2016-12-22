#include "Application.hpp"
#include <iostream>

static JSValueRef print_cb(JSContextRef context,
                       JSObjectRef function,
                       JSObjectRef thisObject,
                       size_t argumentCount,
                       const JSValueRef arguments[],
                       JSValueRef *exception)
{
    std::cout << "ca marche" << std::endl;
    return JSValueMakeUndefined(context);
}

Application::Application() : JsClass("Application")
{
    this->AddStaticFunc("print", (void*)print_cb);
    this->Build();
}