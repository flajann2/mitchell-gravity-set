/****************************************************************************
** Meta object code from reading C++ file 'starfield.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../starfield.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'starfield.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StarField_t {
    QByteArrayData data[9];
    char stringdata0[96];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StarField_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StarField_t qt_meta_stringdata_StarField = {
    {
QT_MOC_LITERAL(0, 0, 9), // "StarField"
QT_MOC_LITERAL(1, 10, 13), // "setFieldLines"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 5), // "lines"
QT_MOC_LITERAL(4, 31, 16), // "setArrowsPerLine"
QT_MOC_LITERAL(5, 48, 6), // "arrows"
QT_MOC_LITERAL(6, 55, 14), // "toggleRotation"
QT_MOC_LITERAL(7, 70, 15), // "triggerRotation"
QT_MOC_LITERAL(8, 86, 9) // "toggleSun"

    },
    "StarField\0setFieldLines\0\0lines\0"
    "setArrowsPerLine\0arrows\0toggleRotation\0"
    "triggerRotation\0toggleSun"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StarField[] = {

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

void StarField::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StarField *_t = static_cast<StarField *>(_o);
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

const QMetaObject StarField::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_StarField.data,
      qt_meta_data_StarField,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *StarField::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StarField::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StarField.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int StarField::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
