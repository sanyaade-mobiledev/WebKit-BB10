/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"
#include "WebKitDOMTestEventConstructor.h"

#include "DOMObjectCache.h"
#include "ExceptionCode.h"
#include "JSMainThreadExecState.h"
#include "TestEventConstructor.h"
#include "WebKitDOMBinding.h"
#include "gobject/ConvertToUTF8String.h"
#include "webkit/WebKitDOMTestEventConstructorPrivate.h"
#include "webkitdefines.h"
#include "webkitglobalsprivate.h"
#include "webkitmarshal.h"
#include <glib-object.h>
#include <wtf/GetPtr.h>
#include <wtf/RefPtr.h>

namespace WebKit {

WebKitDOMTestEventConstructor* kit(WebCore::TestEventConstructor* obj)
{
    g_return_val_if_fail(obj, 0);

    if (gpointer ret = DOMObjectCache::get(obj))
        return static_cast<WebKitDOMTestEventConstructor*>(ret);

    return static_cast<WebKitDOMTestEventConstructor*>(DOMObjectCache::put(obj, WebKit::wrapTestEventConstructor(obj)));
}

WebCore::TestEventConstructor* core(WebKitDOMTestEventConstructor* request)
{
    g_return_val_if_fail(request, 0);

    WebCore::TestEventConstructor* coreObject = static_cast<WebCore::TestEventConstructor*>(WEBKIT_DOM_OBJECT(request)->coreObject);
    g_return_val_if_fail(coreObject, 0);

    return coreObject;
}

WebKitDOMTestEventConstructor* wrapTestEventConstructor(WebCore::TestEventConstructor* coreObject)
{
    g_return_val_if_fail(coreObject, 0);

    // We call ref() rather than using a C++ smart pointer because we can't store a C++ object
    // in a C-allocated GObject structure. See the finalize() code for the matching deref().
    coreObject->ref();

    return WEBKIT_DOM_TEST_EVENT_CONSTRUCTOR(g_object_new(WEBKIT_TYPE_DOM_TEST_EVENT_CONSTRUCTOR, "core-object", coreObject, NULL));
}

} // namespace WebKit

G_DEFINE_TYPE(WebKitDOMTestEventConstructor, webkit_dom_test_event_constructor, WEBKIT_TYPE_DOM_OBJECT)

enum {
    PROP_0,
    PROP_ATTR1,
    PROP_ATTR2,
};

static void webkit_dom_test_event_constructor_finalize(GObject* object)
{

    WebKitDOMObject* domObject = WEBKIT_DOM_OBJECT(object);
    
    if (domObject->coreObject) {
        WebCore::TestEventConstructor* coreObject = static_cast<WebCore::TestEventConstructor*>(domObject->coreObject);

        WebKit::DOMObjectCache::forget(coreObject);
        coreObject->deref();

        domObject->coreObject = 0;
    }


    G_OBJECT_CLASS(webkit_dom_test_event_constructor_parent_class)->finalize(object);
}

static void webkit_dom_test_event_constructor_set_property(GObject* object, guint propertyId, const GValue* value, GParamSpec* pspec)
{
    WebCore::JSMainThreadNullState state;
    switch (propertyId) {
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, propertyId, pspec);
        break;
    }
}


static void webkit_dom_test_event_constructor_get_property(GObject* object, guint propertyId, GValue* value, GParamSpec* pspec)
{
    WebCore::JSMainThreadNullState state;

    WebKitDOMTestEventConstructor* self = WEBKIT_DOM_TEST_EVENT_CONSTRUCTOR(object);
    WebCore::TestEventConstructor* coreSelf = WebKit::core(self);

    switch (propertyId) {
    case PROP_ATTR1: {
        g_value_take_string(value, convertToUTF8String(coreSelf->attr1()));
        break;
    }
    case PROP_ATTR2: {
        g_value_take_string(value, convertToUTF8String(coreSelf->attr2()));
        break;
    }
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, propertyId, pspec);
        break;
    }
}


static void webkit_dom_test_event_constructor_constructed(GObject* object)
{

    if (G_OBJECT_CLASS(webkit_dom_test_event_constructor_parent_class)->constructed)
        G_OBJECT_CLASS(webkit_dom_test_event_constructor_parent_class)->constructed(object);
}

static void webkit_dom_test_event_constructor_class_init(WebKitDOMTestEventConstructorClass* requestClass)
{
    GObjectClass* gobjectClass = G_OBJECT_CLASS(requestClass);
    gobjectClass->finalize = webkit_dom_test_event_constructor_finalize;
    gobjectClass->set_property = webkit_dom_test_event_constructor_set_property;
    gobjectClass->get_property = webkit_dom_test_event_constructor_get_property;
    gobjectClass->constructed = webkit_dom_test_event_constructor_constructed;

    g_object_class_install_property(gobjectClass,
                                    PROP_ATTR1,
                                    g_param_spec_string("attr1", /* name */
                                                           "test_event_constructor_attr1", /* short description */
                                                           "read-only  gchar* TestEventConstructor.attr1", /* longer - could do with some extra doc stuff here */
                                                           "", /* default */
                                                           WEBKIT_PARAM_READABLE));
    g_object_class_install_property(gobjectClass,
                                    PROP_ATTR2,
                                    g_param_spec_string("attr2", /* name */
                                                           "test_event_constructor_attr2", /* short description */
                                                           "read-only  gchar* TestEventConstructor.attr2", /* longer - could do with some extra doc stuff here */
                                                           "", /* default */
                                                           WEBKIT_PARAM_READABLE));


}

static void webkit_dom_test_event_constructor_init(WebKitDOMTestEventConstructor* request)
{
}

gchar*
webkit_dom_test_event_constructor_get_attr1(WebKitDOMTestEventConstructor* self)
{
    g_return_val_if_fail(self, 0);
    WebCore::JSMainThreadNullState state;
    WebCore::TestEventConstructor* item = WebKit::core(self);
    gchar* result = convertToUTF8String(item->attr1());
    return result;
}

gchar*
webkit_dom_test_event_constructor_get_attr2(WebKitDOMTestEventConstructor* self)
{
    g_return_val_if_fail(self, 0);
    WebCore::JSMainThreadNullState state;
    WebCore::TestEventConstructor* item = WebKit::core(self);
    gchar* result = convertToUTF8String(item->attr2());
    return result;
}
