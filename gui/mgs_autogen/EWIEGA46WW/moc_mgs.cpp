/****************************************************************************
** Meta object code from reading C++ file 'mgs.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mgs.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mgs.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ScatterDataModifier_t {
    QByteArrayData data[9];
    char stringdata0[106];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScatterDataModifier_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScatterDataModifier_t qt_meta_stringdata_ScatterDataModifier = {
    {
QT_MOC_LITERAL(0, 0, 19), // "ScatterDataModifier"
QT_MOC_LITERAL(1, 20, 13), // "setFieldLines"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 5), // "lines"
QT_MOC_LITERAL(4, 41, 16), // "setArrowsPerLine"
QT_MOC_LITERAL(5, 58, 6), // "arrows"
QT_MOC_LITERAL(6, 65, 14), // "toggleRotation"
QT_MOC_LITERAL(7, 80, 15), // "triggerRotation"
QT_MOC_LITERAL(8, 96, 9) // "toggleSun"

    },
    "ScatterDataModifier\0setFieldLines\0\0"
    "lines\0setArrowsPerLine\0arrows\0"
    "toggleRotation\0triggerRotation\0toggleSun"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScatterDataModifier[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       4,    1,   42,    2, 0x0a /* Public */,
       6,    0,   45,    2, 0x0a /* Public */,
       7,    0,   46,    2, 0x0a /* Public */,
       8,    0,   47,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ScatterDataModifier::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ScatterDataModifier *_t = static_cast<ScatterDataModifier *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setFieldLines((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setArrowsPerLine((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->toggleRotation(); break;
        case 3: _t->triggerRotation(); break;
        case 4: _t->toggleSun(); break;
        default: ;
        }
    }
}

const QMetaObject ScatterDataModifier::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ScatterDataModifier.data,
      qt_meta_data_ScatterDataModifier,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ScatterDataModifier::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScatterDataModifier::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ScatterDataModifier.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ScatterDataModifier::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
