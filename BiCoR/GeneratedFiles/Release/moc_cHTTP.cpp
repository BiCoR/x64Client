/****************************************************************************
** Meta object code from reading C++ file 'cHTTP.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../cHTTP.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cHTTP.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CHTTP_t {
    QByteArrayData data[10];
    char stringdata[131];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_CHTTP_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_CHTTP_t qt_meta_stringdata_CHTTP = {
    {
QT_MOC_LITERAL(0, 0, 5),
QT_MOC_LITERAL(1, 6, 15),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 16),
QT_MOC_LITERAL(4, 40, 18),
QT_MOC_LITERAL(5, 59, 22),
QT_MOC_LITERAL(6, 82, 8),
QT_MOC_LITERAL(7, 91, 14),
QT_MOC_LITERAL(8, 106, 8),
QT_MOC_LITERAL(9, 115, 14)
    },
    "CHTTP\0loginSuccessful\0\0logoutSuccessful\0"
    "noNetworkAvailable\0getFreshDataAfterLogin\0"
    "response\0QNetworkReply*\0fillForm\0"
    "showSignupForm\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CHTTP[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x05,
       3,    1,   52,    2, 0x05,
       4,    0,   55,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       5,    0,   56,    2, 0x0a,
       6,    1,   57,    2, 0x08,
       8,    1,   60,    2, 0x08,
       9,    1,   63,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

void CHTTP::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CHTTP *_t = static_cast<CHTTP *>(_o);
        switch (_id) {
        case 0: _t->loginSuccessful((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->logoutSuccessful((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->noNetworkAvailable(); break;
        case 3: _t->getFreshDataAfterLogin(); break;
        case 4: _t->response((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 5: _t->fillForm((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->showSignupForm((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CHTTP::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CHTTP::loginSuccessful)) {
                *result = 0;
            }
        }
        {
            typedef void (CHTTP::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CHTTP::logoutSuccessful)) {
                *result = 1;
            }
        }
        {
            typedef void (CHTTP::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CHTTP::noNetworkAvailable)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject CHTTP::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CHTTP.data,
      qt_meta_data_CHTTP,  qt_static_metacall, 0, 0}
};


const QMetaObject *CHTTP::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CHTTP::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CHTTP.stringdata))
        return static_cast<void*>(const_cast< CHTTP*>(this));
    return QObject::qt_metacast(_clname);
}

int CHTTP::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void CHTTP::loginSuccessful(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CHTTP::logoutSuccessful(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CHTTP::noNetworkAvailable()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
