/****************************************************************************
** Meta object code from reading C++ file 'interfaccia.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "interfaccia.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'interfaccia.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Dialogo_t {
    QByteArrayData data[8];
    char stringdata[145];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Dialogo_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Dialogo_t qt_meta_stringdata_Dialogo = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 17),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 16),
QT_MOC_LITERAL(4, 44, 27),
QT_MOC_LITERAL(5, 72, 28),
QT_MOC_LITERAL(6, 101, 20),
QT_MOC_LITERAL(7, 122, 21)
    },
    "Dialogo\0on_carica_clicked\0\0on_stima_clicked\0"
    "on_tipo_sift_vlsift_clicked\0"
    "on_tipo_sift_siftgpu_clicked\0"
    "salva_configurazione\0carica_configurazione\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dialogo[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08,
       3,    0,   45,    2, 0x08,
       4,    0,   46,    2, 0x08,
       5,    0,   47,    2, 0x08,
       6,    0,   48,    2, 0x08,
       7,    0,   49,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Dialogo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Dialogo *_t = static_cast<Dialogo *>(_o);
        switch (_id) {
        case 0: _t->on_carica_clicked(); break;
        case 1: _t->on_stima_clicked(); break;
        case 2: _t->on_tipo_sift_vlsift_clicked(); break;
        case 3: _t->on_tipo_sift_siftgpu_clicked(); break;
        case 4: _t->salva_configurazione(); break;
        case 5: _t->carica_configurazione(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Dialogo::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Dialogo.data,
      qt_meta_data_Dialogo,  qt_static_metacall, 0, 0}
};


const QMetaObject *Dialogo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dialogo::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Dialogo.stringdata))
        return static_cast<void*>(const_cast< Dialogo*>(this));
    if (!strcmp(_clname, "Ui::Dialogo"))
        return static_cast< Ui::Dialogo*>(const_cast< Dialogo*>(this));
    return QDialog::qt_metacast(_clname);
}

int Dialogo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
struct qt_meta_stringdata_TastoSfoglia_t {
    QByteArrayData data[3];
    char stringdata[32];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_TastoSfoglia_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_TastoSfoglia_t qt_meta_stringdata_TastoSfoglia = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 16),
QT_MOC_LITERAL(2, 30, 0)
    },
    "TastoSfoglia\0on_tasto_clicked\0\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TastoSfoglia[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x08,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void TastoSfoglia::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TastoSfoglia *_t = static_cast<TastoSfoglia *>(_o);
        switch (_id) {
        case 0: _t->on_tasto_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject TastoSfoglia::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TastoSfoglia.data,
      qt_meta_data_TastoSfoglia,  qt_static_metacall, 0, 0}
};


const QMetaObject *TastoSfoglia::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TastoSfoglia::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TastoSfoglia.stringdata))
        return static_cast<void*>(const_cast< TastoSfoglia*>(this));
    return QObject::qt_metacast(_clname);
}

int TastoSfoglia::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
