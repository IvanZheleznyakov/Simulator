/****************************************************************************
** Meta object code from reading C++ file 'myinterpreter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../myinterpreter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myinterpreter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_twoDModel__MyInterpreter_t {
    QByteArrayData data[10];
    char stringdata0[146];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_twoDModel__MyInterpreter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_twoDModel__MyInterpreter_t qt_meta_stringdata_twoDModel__MyInterpreter = {
    {
QT_MOC_LITERAL(0, 0, 24), // "twoDModel::MyInterpreter"
QT_MOC_LITERAL(1, 25, 14), // "connectToRobot"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 9), // "interpret"
QT_MOC_LITERAL(4, 51, 9), // "stopRobot"
QT_MOC_LITERAL(5, 61, 33), // "qReal::interpretation::StopRe..."
QT_MOC_LITERAL(6, 95, 6), // "reason"
QT_MOC_LITERAL(7, 102, 11), // "timeElapsed"
QT_MOC_LITERAL(8, 114, 17), // "supportedDiagrams"
QT_MOC_LITERAL(9, 132, 13) // "qReal::IdList"

    },
    "twoDModel::MyInterpreter\0connectToRobot\0"
    "\0interpret\0stopRobot\0"
    "qReal::interpretation::StopReason\0"
    "reason\0timeElapsed\0supportedDiagrams\0"
    "qReal::IdList"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_twoDModel__MyInterpreter[] = {

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
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    1,   46,    2, 0x0a /* Public */,
       4,    0,   49,    2, 0x2a /* Public | MethodCloned */,
       7,    0,   50,    2, 0x0a /* Public */,
       8,    0,   51,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Int,
    0x80000000 | 9,

       0        // eod
};

void twoDModel::MyInterpreter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyInterpreter *_t = static_cast<MyInterpreter *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectToRobot(); break;
        case 1: _t->interpret(); break;
        case 2: _t->stopRobot((*reinterpret_cast< qReal::interpretation::StopReason(*)>(_a[1]))); break;
        case 3: _t->stopRobot(); break;
        case 4: { int _r = _t->timeElapsed();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 5: { qReal::IdList _r = _t->supportedDiagrams();
            if (_a[0]) *reinterpret_cast< qReal::IdList*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject twoDModel::MyInterpreter::staticMetaObject = {
    { &kitBase::InterpreterInterface::staticMetaObject, qt_meta_stringdata_twoDModel__MyInterpreter.data,
      qt_meta_data_twoDModel__MyInterpreter,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *twoDModel::MyInterpreter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *twoDModel::MyInterpreter::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_twoDModel__MyInterpreter.stringdata0))
        return static_cast<void*>(const_cast< MyInterpreter*>(this));
    return kitBase::InterpreterInterface::qt_metacast(_clname);
}

int twoDModel::MyInterpreter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = kitBase::InterpreterInterface::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
