/****************************************************************************
** Meta object code from reading C++ file 'starfield.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../development/cpp_proj/gravity-set-compute/gui/starfield.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'starfield.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_mgs__StarField_t {
    QByteArrayData data[16];
    char stringdata0[222];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mgs__StarField_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mgs__StarField_t qt_meta_stringdata_mgs__StarField = {
    {
QT_MOC_LITERAL(0, 0, 14), // "mgs::StarField"
QT_MOC_LITERAL(1, 15, 13), // "setFieldLines"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 5), // "lines"
QT_MOC_LITERAL(4, 36, 16), // "setArrowsPerLine"
QT_MOC_LITERAL(5, 53, 6), // "arrows"
QT_MOC_LITERAL(6, 60, 14), // "toggleRotation"
QT_MOC_LITERAL(7, 75, 15), // "triggerRotation"
QT_MOC_LITERAL(8, 91, 9), // "toggleSun"
QT_MOC_LITERAL(9, 101, 15), // "sl_make_polygon"
QT_MOC_LITERAL(10, 117, 5), // "stars"
QT_MOC_LITERAL(11, 123, 19), // "sl_make_tetrahedron"
QT_MOC_LITERAL(12, 143, 18), // "sl_make_octahedron"
QT_MOC_LITERAL(13, 162, 18), // "sl_make_hexahedron"
QT_MOC_LITERAL(14, 181, 20), // "sl_make_dodecahedron"
QT_MOC_LITERAL(15, 202, 19) // "sl_make_icosahedron"

    },
    "mgs::StarField\0setFieldLines\0\0lines\0"
    "setArrowsPerLine\0arrows\0toggleRotation\0"
    "triggerRotation\0toggleSun\0sl_make_polygon\0"
    "stars\0sl_make_tetrahedron\0sl_make_octahedron\0"
    "sl_make_hexahedron\0sl_make_dodecahedron\0"
    "sl_make_icosahedron"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mgs__StarField[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x0a /* Public */,
       4,    1,   72,    2, 0x0a /* Public */,
       6,    0,   75,    2, 0x0a /* Public */,
       7,    0,   76,    2, 0x0a /* Public */,
       8,    0,   77,    2, 0x0a /* Public */,
       9,    1,   78,    2, 0x0a /* Public */,
      11,    0,   81,    2, 0x0a /* Public */,
      12,    0,   82,    2, 0x0a /* Public */,
      13,    0,   83,    2, 0x0a /* Public */,
      14,    0,   84,    2, 0x0a /* Public */,
      15,    0,   85,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void mgs::StarField::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
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
        case 5: _t->sl_make_polygon((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->sl_make_tetrahedron(); break;
        case 7: _t->sl_make_octahedron(); break;
        case 8: _t->sl_make_hexahedron(); break;
        case 9: _t->sl_make_dodecahedron(); break;
        case 10: _t->sl_make_icosahedron(); break;
        default: ;
        }
    }
}

const QMetaObject mgs::StarField::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_mgs__StarField.data,
      qt_meta_data_mgs__StarField,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *mgs::StarField::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mgs::StarField::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_mgs__StarField.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int mgs::StarField::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
