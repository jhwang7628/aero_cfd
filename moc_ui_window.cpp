/****************************************************************************
** Meta object code from reading C++ file 'ui_window.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "include/ui_window.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ui_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AudioStreamButton[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_AudioStreamButton[] = {
    "AudioStreamButton\0"
};

void AudioStreamButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData AudioStreamButton::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AudioStreamButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_AudioStreamButton,
      qt_meta_data_AudioStreamButton, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AudioStreamButton::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AudioStreamButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AudioStreamButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AudioStreamButton))
        return static_cast<void*>(const_cast< AudioStreamButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int AudioStreamButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_AudioGUI[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,   30,   30,   30, 0x08,
      31,   30,   30,   30, 0x08,
      51,   30,   30,   30, 0x08,
      74,   30,   30,   30, 0x08,
      96,   30,   30,   30, 0x08,
     116,   30,   30,   30, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AudioGUI[] = {
    "AudioGUI\0startStreamClicked()\0\0"
    "stopStreamClicked()\0toggleFrequencyShift()\0"
    "toggleUseLeapMotion()\0updateSensitivity()\0"
    "updateSharpness()\0"
};

void AudioGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AudioGUI *_t = static_cast<AudioGUI *>(_o);
        switch (_id) {
        case 0: _t->startStreamClicked(); break;
        case 1: _t->stopStreamClicked(); break;
        case 2: _t->toggleFrequencyShift(); break;
        case 3: _t->toggleUseLeapMotion(); break;
        case 4: _t->updateSensitivity(); break;
        case 5: _t->updateSharpness(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData AudioGUI::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AudioGUI::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AudioGUI,
      qt_meta_data_AudioGUI, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AudioGUI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AudioGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AudioGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AudioGUI))
        return static_cast<void*>(const_cast< AudioGUI*>(this));
    return QWidget::qt_metacast(_clname);
}

int AudioGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
