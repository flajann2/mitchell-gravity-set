/****************************************************************************
** Meta object code from reading C++ file 'starfield.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../../development/cpp_proj/gravity-set-compute/gui/starfield.h"
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
struct qt_meta_stringdata_mgs__gui__StarField_t {
    QByteArrayData data[16];
    char stringdata0[227];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mgs__gui__StarField_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mgs__gui__StarField_t qt_meta_stringdata_mgs__gui__StarField = {
    {
QT_MOC_LITERAL(0, 0, 19), // "mgs::gui::StarField"
QT_MOC_LITERAL(1, 20, 13), // "setFieldLines"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 5), // "lines"
QT_MOC_LITERAL(4, 41, 16), // "setArrowsPerLine"
QT_MOC_LITERAL(5, 58, 6), // "arrows"
QT_MOC_LITERAL(6, 65, 14), // "toggleRotation"
QT_MOC_LITERAL(7, 80, 15), // "triggerRotation"
QT_MOC_LITERAL(8, 96, 9), // "toggleSun"
QT_MOC_LITERAL(9, 106, 15), // "sl_make_polygon"
QT_MOC_LITERAL(10, 122, 5), // "stars"
QT_MOC_LITERAL(11, 128, 19), // "sl_make_tetrahedron"
QT_MOC_LITERAL(12, 148, 18), // "sl_make_octahedron"
QT_MOC_LITERAL(13, 167, 18), // "sl_make_hexahedron"
QT_MOC_LITERAL(14, 186, 20), // "sl_make_dodecahedron"
QT_MOC_LITERAL(15, 207, 19) // "sl_make_icosahedron"

    },
    "mgs::gui::StarField\0setFieldLines\0\0"
    "lines\0setArrowsPerLine\0arrows\0"
    "toggleRotation\0triggerRotation\0toggleSun\0"
    "sl_make_polygon\0stars\0sl_make_tetrahedron\0"
    "sl_make_octahedron\0sl_make_hexahedron\0"
    "sl_make_dodecahedron\0sl_make_icosahedron"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mgs__gui__StarField[] = {

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

void mgs::gui::StarField::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
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

const QMetaObject mgs::gui::StarField::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_mgs__gui__StarField.data,
      qt_meta_data_mgs__gui__StarField,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *mgs::gui::StarField::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mgs::gui::StarField::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_mgs__gui__StarField.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int mgs::gui::StarField::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
