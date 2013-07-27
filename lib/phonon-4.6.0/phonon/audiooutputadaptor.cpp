/*
 * This file was generated by dbusidl2cpp version 0.4
 * when processing input file org.kde.Phonon.AudioOutput.xml
 *
 * dbusidl2cpp is Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file. This file has been hand-edited.
 */

#include "audiooutputadaptor_p.h"
#include "audiooutput.h"
#include <QtCore/QArgument>
#include <QtCore/QByteRef>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include "phononconfig_p.h"
#include "phononnamespace_p.h"
#include "objectdescription.h"

#ifndef PHONON_NO_DBUS

/*
 * Implementation of adaptor class AudioOutputAdaptor
 */

QT_BEGIN_NAMESPACE

namespace Phonon
{

AudioOutputAdaptor::AudioOutputAdaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

AudioOutputAdaptor::~AudioOutputAdaptor()
{
    // destructor
}

double AudioOutputAdaptor::volume() const
{
    // get the value of property volume
    return qvariant_cast<qreal>(parent()->property("volume"));
}

void AudioOutputAdaptor::setVolume(double value)
{
    // set the value of property volume
    parent()->setProperty("volume", QVariant::fromValue(static_cast<qreal>(value)));
}

bool AudioOutputAdaptor::muted() const
{
    return parent()->property("muted").toBool();
}

void AudioOutputAdaptor::setMuted(bool value)
{
    parent()->setProperty("muted", value);
}

QString AudioOutputAdaptor::category()
{
    // handle method call org.kde.Phonon.AudioOutput.category
    return Phonon::categoryToString(static_cast<Phonon::AudioOutput *>(parent())->category());
}

QString AudioOutputAdaptor::name()
{
    // handle method call org.kde.Phonon.AudioOutput.name
    QString name;
    //QMetaObject::invokeMethod(parent(), "name", Q_RETURN_ARG(QString, name));

    // Alternative:
    name = static_cast<Phonon::AudioOutput *>(parent())->name();
    return name;
}

int AudioOutputAdaptor::outputDeviceIndex() const
{
    return static_cast<Phonon::AudioOutput *>(parent())->outputDevice().index();
}

void AudioOutputAdaptor::setOutputDeviceIndex(int newAudioOutputDeviceIndex)
{
    static_cast<Phonon::AudioOutput *>(parent())
        ->setOutputDevice(Phonon::AudioOutputDevice::fromIndex(newAudioOutputDeviceIndex));
}

} // namespace Phonon

QT_END_NAMESPACE

#include "moc_audiooutputadaptor_p.cpp"

#endif
