/****************************************************************************
** Meta object code from reading C++ file 'cGui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../cGui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cGui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CGUI_t {
    QByteArrayData data[17];
    char stringdata[247];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_CGUI_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_CGUI_t qt_meta_stringdata_CGUI = {
    {
QT_MOC_LITERAL(0, 0, 4),
QT_MOC_LITERAL(1, 5, 15),
QT_MOC_LITERAL(2, 21, 0),
QT_MOC_LITERAL(3, 22, 8),
QT_MOC_LITERAL(4, 31, 19),
QT_MOC_LITERAL(5, 51, 23),
QT_MOC_LITERAL(6, 75, 15),
QT_MOC_LITERAL(7, 91, 20),
QT_MOC_LITERAL(8, 112, 14),
QT_MOC_LITERAL(9, 127, 15),
QT_MOC_LITERAL(10, 143, 11),
QT_MOC_LITERAL(11, 155, 11),
QT_MOC_LITERAL(12, 167, 6),
QT_MOC_LITERAL(13, 174, 17),
QT_MOC_LITERAL(14, 192, 18),
QT_MOC_LITERAL(15, 211, 18),
QT_MOC_LITERAL(16, 230, 15)
    },
    "CGUI\0loginSuccessful\0\0tryLogin\0"
    "showSSLErrorMessage\0showNetworkErrorMessage\0"
    "renewPersonList\0checkBirthdayMessage\0"
    "openBrowserNew\0openBrowserEdit\0"
    "setLanguage\0std::string\0locale\0"
    "setLanguageGerman\0setLanguageEnglish\0"
    "credentialsChanged\0showAboutDialog\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CGUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x08,
       3,    0,   82,    2, 0x08,
       4,    0,   83,    2, 0x08,
       5,    0,   84,    2, 0x08,
       6,    0,   85,    2, 0x08,
       7,    0,   86,    2, 0x08,
       8,    0,   87,    2, 0x08,
       9,    0,   88,    2, 0x08,
      10,    1,   89,    2, 0x08,
      13,    0,   92,    2, 0x08,
      14,    0,   93,    2, 0x08,
      15,    0,   94,    2, 0x08,
      16,    0,   95,    2, 0x08,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CGUI *_t = static_cast<CGUI *>(_o);
        switch (_id) {
        case 0: _t->loginSuccessful((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->tryLogin(); break;
        case 2: _t->showSSLErrorMessage(); break;
        case 3: _t->showNetworkErrorMessage(); break;
        case 4: _t->renewPersonList(); break;
        case 5: _t->checkBirthdayMessage(); break;
        case 6: _t->openBrowserNew(); break;
        case 7: _t->openBrowserEdit(); break;
        case 8: _t->setLanguage((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 9: _t->setLanguageGerman(); break;
        case 10: _t->setLanguageEnglish(); break;
        case 11: _t->credentialsChanged(); break;
        case 12: _t->showAboutDialog(); break;
        default: ;
        }
    }
}

const QMetaObject CGUI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_CGUI.data,
      qt_meta_data_CGUI,  qt_static_metacall, 0, 0}
};


const QMetaObject *CGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CGUI.stringdata))
        return static_cast<void*>(const_cast< CGUI*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int CGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
