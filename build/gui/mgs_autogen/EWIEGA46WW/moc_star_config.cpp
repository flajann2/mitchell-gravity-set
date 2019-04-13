/****************************************************************************
** Meta object code from reading C++ file 'star_config.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../../development/cpp_proj/gravity-set-compute/gui/star_config.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'star_config.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_mgs__StarConfig_t {
    QByteArrayData data[17];
    char stringdata0[216];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mgs__StarConfig_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mgs__StarConfig_t qt_meta_stringdata_mgs__StarConfig = {
    {
QT_MOC_LITERAL(0, 0, 15), // "mgs::StarConfig"
QT_MOC_LITERAL(1, 16, 15), // "sig_update_star"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 5), // "index"
QT_MOC_LITERAL(4, 39, 4), // "Star"
QT_MOC_LITERAL(5, 44, 4), // "star"
QT_MOC_LITERAL(6, 49, 15), // "sig_select_star"
QT_MOC_LITERAL(7, 65, 18), // "sig_update_overall"
QT_MOC_LITERAL(8, 84, 7), // "Overall"
QT_MOC_LITERAL(9, 92, 7), // "overall"
QT_MOC_LITERAL(10, 100, 14), // "sl_select_star"
QT_MOC_LITERAL(11, 115, 22), // "sl_set_number_of_stars"
QT_MOC_LITERAL(12, 138, 5), // "count"
QT_MOC_LITERAL(13, 144, 16), // "sl_star_selected"
QT_MOC_LITERAL(14, 161, 22), // "sl_star_config_changed"
QT_MOC_LITERAL(15, 184, 5), // "_text"
QT_MOC_LITERAL(16, 190, 25) // "sl_overall_config_changed"

    },
    "mgs::StarConfig\0sig_update_star\0\0index\0"
    "Star\0star\0sig_select_star\0sig_update_overall\0"
    "Overall\0overall\0sl_select_star\0"
    "sl_set_number_of_stars\0count\0"
    "sl_star_selected\0sl_star_config_changed\0"
    "_text\0sl_overall_config_changed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mgs__StarConfig[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,
       6,    1,   59,    2, 0x06 /* Public */,
       7,    1,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    2,   65,    2, 0x0a /* Public */,
      11,    1,   70,    2, 0x0a /* Public */,
      13,    1,   73,    2, 0x0a /* Public */,
      14,    1,   76,    2, 0x0a /* Public */,
      16,    1,   79,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 8,    9,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QString,   15,

       0        // eod
};

void mgs::StarConfig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StarConfig *_t = static_cast<StarConfig *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_update_star((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const Star(*)>(_a[2]))); break;
        case 1: _t->sig_select_star((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sig_update_overall((*reinterpret_cast< const Overall(*)>(_a[1]))); break;
        case 3: _t->sl_select_star((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const Star(*)>(_a[2]))); break;
        case 4: _t->sl_set_number_of_stars((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->sl_star_selected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->sl_star_config_changed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->sl_overall_config_changed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (StarConfig::*_t)(int , const Star & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StarConfig::sig_update_star)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (StarConfig::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StarConfig::sig_select_star)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (StarConfig::*_t)(const Overall & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StarConfig::sig_update_overall)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject mgs::StarConfig::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_mgs__StarConfig.data,
      qt_meta_data_mgs__StarConfig,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *mgs::StarConfig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mgs::StarConfig::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_mgs__StarConfig.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int mgs::StarConfig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void mgs::StarConfig::sig_update_star(int _t1, const Star & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void mgs::StarConfig::sig_select_star(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void mgs::StarConfig::sig_update_overall(const Overall & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
