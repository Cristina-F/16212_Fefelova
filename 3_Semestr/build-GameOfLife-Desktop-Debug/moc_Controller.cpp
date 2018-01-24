/****************************************************************************
** Meta object code from reading C++ file 'Controller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../GameOfLife/Controller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Controller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Controller_t {
    QByteArrayData data[26];
    char stringdata0[278];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Controller_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Controller_t qt_meta_stringdata_Controller = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Controller"
QT_MOC_LITERAL(1, 11, 12), // "changedField"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 12), // "changedWidth"
QT_MOC_LITERAL(4, 38, 13), // "changedHeight"
QT_MOC_LITERAL(5, 52, 17), // "changedGeneration"
QT_MOC_LITERAL(6, 70, 13), // "activateRule1"
QT_MOC_LITERAL(7, 84, 13), // "activateRule2"
QT_MOC_LITERAL(8, 98, 17), // "addFieldInHistory"
QT_MOC_LITERAL(9, 116, 9), // "pauseGame"
QT_MOC_LITERAL(10, 126, 4), // "game"
QT_MOC_LITERAL(11, 131, 10), // "clearField"
QT_MOC_LITERAL(12, 142, 11), // "changeWidth"
QT_MOC_LITERAL(13, 154, 12), // "changeHeight"
QT_MOC_LITERAL(14, 167, 8), // "loadFile"
QT_MOC_LITERAL(15, 176, 8), // "QString&"
QT_MOC_LITERAL(16, 185, 8), // "fileName"
QT_MOC_LITERAL(17, 194, 8), // "saveFile"
QT_MOC_LITERAL(18, 203, 10), // "changeCell"
QT_MOC_LITERAL(19, 214, 1), // "x"
QT_MOC_LITERAL(20, 216, 1), // "y"
QT_MOC_LITERAL(21, 218, 6), // "status"
QT_MOC_LITERAL(22, 225, 12), // "activateRule"
QT_MOC_LITERAL(23, 238, 11), // "std::string"
QT_MOC_LITERAL(24, 250, 16), // "changeGeneration"
QT_MOC_LITERAL(25, 267, 10) // "changeRule"

    },
    "Controller\0changedField\0\0changedWidth\0"
    "changedHeight\0changedGeneration\0"
    "activateRule1\0activateRule2\0"
    "addFieldInHistory\0pauseGame\0game\0"
    "clearField\0changeWidth\0changeHeight\0"
    "loadFile\0QString&\0fileName\0saveFile\0"
    "changeCell\0x\0y\0status\0activateRule\0"
    "std::string\0changeGeneration\0changeRule"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Controller[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x06 /* Public */,
       3,    1,  105,    2, 0x06 /* Public */,
       4,    1,  108,    2, 0x06 /* Public */,
       5,    0,  111,    2, 0x06 /* Public */,
       6,    0,  112,    2, 0x06 /* Public */,
       7,    0,  113,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,  114,    2, 0x08 /* Private */,
       9,    0,  115,    2, 0x08 /* Private */,
      10,    0,  116,    2, 0x08 /* Private */,
      11,    0,  117,    2, 0x08 /* Private */,
      12,    1,  118,    2, 0x08 /* Private */,
      13,    1,  121,    2, 0x08 /* Private */,
      14,    1,  124,    2, 0x08 /* Private */,
      17,    1,  127,    2, 0x08 /* Private */,
      18,    3,  130,    2, 0x08 /* Private */,
      22,    1,  137,    2, 0x08 /* Private */,
      24,    1,  140,    2, 0x08 /* Private */,
      25,    0,  143,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Bool,   19,   20,   21,
    QMetaType::Void, 0x80000000 | 23,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

       0        // eod
};

void Controller::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Controller *_t = static_cast<Controller *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changedField(); break;
        case 1: _t->changedWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->changedHeight((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->changedGeneration(); break;
        case 4: _t->activateRule1(); break;
        case 5: _t->activateRule2(); break;
        case 6: _t->addFieldInHistory(); break;
        case 7: _t->pauseGame(); break;
        case 8: _t->game(); break;
        case 9: _t->clearField(); break;
        case 10: _t->changeWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->changeHeight((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->loadFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->saveFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: _t->changeCell((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 15: _t->activateRule((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 16: _t->changeGeneration((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->changeRule(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Controller::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Controller::changedField)) {
                *result = 0;
            }
        }
        {
            typedef void (Controller::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Controller::changedWidth)) {
                *result = 1;
            }
        }
        {
            typedef void (Controller::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Controller::changedHeight)) {
                *result = 2;
            }
        }
        {
            typedef void (Controller::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Controller::changedGeneration)) {
                *result = 3;
            }
        }
        {
            typedef void (Controller::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Controller::activateRule1)) {
                *result = 4;
            }
        }
        {
            typedef void (Controller::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Controller::activateRule2)) {
                *result = 5;
            }
        }
    }
}

const QMetaObject Controller::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Controller.data,
      qt_meta_data_Controller,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Controller::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Controller::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Controller.stringdata0))
        return static_cast<void*>(const_cast< Controller*>(this));
    return QObject::qt_metacast(_clname);
}

int Controller::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void Controller::changedField()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void Controller::changedWidth(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Controller::changedHeight(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Controller::changedGeneration()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void Controller::activateRule1()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void Controller::activateRule2()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
