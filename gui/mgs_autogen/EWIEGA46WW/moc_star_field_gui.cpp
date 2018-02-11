/****************************************************************************
** Meta object code from reading C++ file 'star_field_gui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../development/cpp_proj/gravity-set-compute/gui/star_field_gui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'star_field_gui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_mgs__StarFieldGUI_t {
    QByteArrayData data[27];
    char stringdata0[381];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mgs__StarFieldGUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mgs__StarFieldGUI_t qt_meta_stringdata_mgs__StarFieldGUI = {
    {
QT_MOC_LITERAL(0, 0, 17), // "mgs::StarFieldGUI"
QT_MOC_LITERAL(1, 18, 15), // "sig_select_star"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 5), // "index"
QT_MOC_LITERAL(4, 41, 4), // "Star"
QT_MOC_LITERAL(5, 46, 4), // "star"
QT_MOC_LITERAL(6, 51, 23), // "sig_set_number_of_stars"
QT_MOC_LITERAL(7, 75, 5), // "count"
QT_MOC_LITERAL(8, 81, 19), // "sl_setFreePointCube"
QT_MOC_LITERAL(9, 101, 4), // "side"
QT_MOC_LITERAL(10, 106, 19), // "sl_toggleSimulation"
QT_MOC_LITERAL(11, 126, 17), // "sl_stepSimulation"
QT_MOC_LITERAL(12, 144, 15), // "sl_toggleCenter"
QT_MOC_LITERAL(13, 160, 15), // "sl_toggleArrows"
QT_MOC_LITERAL(14, 176, 15), // "sl_make_polygon"
QT_MOC_LITERAL(15, 192, 5), // "stars"
QT_MOC_LITERAL(16, 198, 19), // "sl_make_tetrahedron"
QT_MOC_LITERAL(17, 218, 18), // "sl_make_octahedron"
QT_MOC_LITERAL(18, 237, 18), // "sl_make_hexahedron"
QT_MOC_LITERAL(19, 256, 20), // "sl_make_dodecahedron"
QT_MOC_LITERAL(20, 277, 19), // "sl_make_icosahedron"
QT_MOC_LITERAL(21, 297, 16), // "sl_star_selected"
QT_MOC_LITERAL(22, 314, 14), // "sl_update_star"
QT_MOC_LITERAL(23, 329, 17), // "sl_reset_eularian"
QT_MOC_LITERAL(24, 347, 17), // "sl_update_overall"
QT_MOC_LITERAL(25, 365, 7), // "Overall"
QT_MOC_LITERAL(26, 373, 7) // "overall"

    },
    "mgs::StarFieldGUI\0sig_select_star\0\0"
    "index\0Star\0star\0sig_set_number_of_stars\0"
    "count\0sl_setFreePointCube\0side\0"
    "sl_toggleSimulation\0sl_stepSimulation\0"
    "sl_toggleCenter\0sl_toggleArrows\0"
    "sl_make_polygon\0stars\0sl_make_tetrahedron\0"
    "sl_make_octahedron\0sl_make_hexahedron\0"
    "sl_make_dodecahedron\0sl_make_icosahedron\0"
    "sl_star_selected\0sl_update_star\0"
    "sl_reset_eularian\0sl_update_overall\0"
    "Overall\0overall"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mgs__StarFieldGUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   99,    2, 0x06 /* Public */,
       6,    1,  104,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,  107,    2, 0x0a /* Public */,
      10,    0,  110,    2, 0x0a /* Public */,
      11,    0,  111,    2, 0x0a /* Public */,
      12,    0,  112,    2, 0x0a /* Public */,
      13,    0,  113,    2, 0x0a /* Public */,
      14,    1,  114,    2, 0x0a /* Public */,
      16,    0,  117,    2, 0x0a /* Public */,
      17,    0,  118,    2, 0x0a /* Public */,
      18,    0,  119,    2, 0x0a /* Public */,
      19,    0,  120,    2, 0x0a /* Public */,
      20,    0,  121,    2, 0x0a /* Public */,
      21,    1,  122,    2, 0x0a /* Public */,
      22,    2,  125,    2, 0x0a /* Public */,
      23,    0,  130,    2, 0x0a /* Public */,
      24,    1,  131,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Int,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 25,   26,

       0        // eod
};

void mgs::StarFieldGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StarFieldGUI *_t = static_cast<StarFieldGUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_select_star((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const Star(*)>(_a[2]))); break;
        case 1: _t->sig_set_number_of_stars((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sl_setFreePointCube((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->sl_toggleSimulation(); break;
        case 4: _t->sl_stepSimulation(); break;
        case 5: _t->sl_toggleCenter(); break;
        case 6: _t->sl_toggleArrows(); break;
        case 7: _t->sl_make_polygon((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->sl_make_tetrahedron(); break;
        case 9: _t->sl_make_octahedron(); break;
        case 10: _t->sl_make_hexahedron(); break;
        case 11: _t->sl_make_dodecahedron(); break;
        case 12: _t->sl_make_icosahedron(); break;
        case 13: _t->sl_star_selected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->sl_update_star((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const Star(*)>(_a[2]))); break;
        case 15: _t->sl_reset_eularian(); break;
        case 16: _t->sl_update_overall((*reinterpret_cast< const Overall(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (StarFieldGUI::*_t)(int , const Star & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StarFieldGUI::sig_select_star)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (StarFieldGUI::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StarFieldGUI::sig_set_number_of_stars)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject mgs::StarFieldGUI::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_mgs__StarFieldGUI.data,
      qt_meta_data_mgs__StarFieldGUI,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *mgs::StarFieldGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mgs::StarFieldGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_mgs__StarFieldGUI.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int mgs::StarFieldGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void mgs::StarFieldGUI::sig_select_star(int _t1, const Star & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void mgs::StarFieldGUI::sig_set_number_of_stars(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
