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

#ifndef JSIDBCursor_h
#define JSIDBCursor_h

#if ENABLE(INDEXED_DATABASE)

#include "JSDOMBinding.h"
#include <runtime/JSGlobalObject.h>
#include <runtime/JSObjectWithGlobalObject.h>
#include <runtime/ObjectPrototype.h>

namespace WebCore {

class IDBCursor;

class JSIDBCursor : public JSDOMWrapper {
    typedef JSDOMWrapper Base;
public:
    JSIDBCursor(JSC::Structure*, JSDOMGlobalObject*, PassRefPtr<IDBCursor>);
    static JSC::JSObject* createPrototype(JSC::ExecState*, JSC::JSGlobalObject*);
    virtual bool getOwnPropertySlot(JSC::ExecState*, const JSC::Identifier& propertyName, JSC::PropertySlot&);
    virtual bool getOwnPropertyDescriptor(JSC::ExecState*, const JSC::Identifier& propertyName, JSC::PropertyDescriptor&);
    static const JSC::ClassInfo s_info;

    static JSC::Structure* createStructure(JSC::JSGlobalData& globalData, JSC::JSValue prototype)
    {
        return JSC::Structure::create(globalData, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), AnonymousSlotCount, &s_info);
    }

    static JSC::JSValue getConstructor(JSC::ExecState*, JSC::JSGlobalObject*);
    IDBCursor* impl() const { return m_impl.get(); }

private:
    RefPtr<IDBCursor> m_impl;
protected:
    static const unsigned StructureFlags = JSC::OverridesGetOwnPropertySlot | Base::StructureFlags;
};

JSC::JSValue toJS(JSC::ExecState*, JSDOMGlobalObject*, IDBCursor*);
IDBCursor* toIDBCursor(JSC::JSValue);

class JSIDBCursorPrototype : public JSC::JSObjectWithGlobalObject {
    typedef JSC::JSObjectWithGlobalObject Base;
public:
    static JSC::JSObject* self(JSC::ExecState*, JSC::JSGlobalObject*);
    static const JSC::ClassInfo s_info;
    virtual bool getOwnPropertySlot(JSC::ExecState*, const JSC::Identifier&, JSC::PropertySlot&);
    virtual bool getOwnPropertyDescriptor(JSC::ExecState*, const JSC::Identifier&, JSC::PropertyDescriptor&);
    static JSC::Structure* createStructure(JSC::JSGlobalData& globalData, JSC::JSValue prototype)
    {
        return JSC::Structure::create(globalData, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), AnonymousSlotCount, &s_info);
    }
    JSIDBCursorPrototype(JSC::JSGlobalData& globalData, JSC::JSGlobalObject* globalObject, JSC::Structure* structure) : JSC::JSObjectWithGlobalObject(globalData, globalObject, structure) { }
protected:
    static const unsigned StructureFlags = JSC::OverridesGetOwnPropertySlot | Base::StructureFlags;
};

// Functions

JSC::EncodedJSValue JSC_HOST_CALL jsIDBCursorPrototypeFunctionUpdate(JSC::ExecState*);
JSC::EncodedJSValue JSC_HOST_CALL jsIDBCursorPrototypeFunctionContinue(JSC::ExecState*);
JSC::EncodedJSValue JSC_HOST_CALL jsIDBCursorPrototypeFunctionDelete(JSC::ExecState*);
// Attributes

JSC::JSValue jsIDBCursorDirection(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsIDBCursorKey(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsIDBCursorPrimaryKey(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsIDBCursorSource(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsIDBCursorConstructor(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
// Constants

JSC::JSValue jsIDBCursorNEXT(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsIDBCursorNEXT_NO_DUPLICATE(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsIDBCursorPREV(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsIDBCursorPREV_NO_DUPLICATE(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);

} // namespace WebCore

#endif // ENABLE(INDEXED_DATABASE)

#endif
