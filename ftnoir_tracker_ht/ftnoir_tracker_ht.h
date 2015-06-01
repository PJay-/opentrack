/* Copyright (c) 2013 Stanislaw Halik <sthalik@misaki.pl>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 */

#ifndef FTNOIR_TRACKER_HT_H
#define FTNOIR_TRACKER_HT_H

#include "stdafx.h"
#include "headtracker-ftnoir.h"
#include "ui_ht-trackercontrols.h"
#include "ht_video_widget.h"
#include "compat/compat.h"
#include <QObject>
#include "opentrack/options.hpp"
#include "opentrack/plugin-api.hpp"
using namespace options;

struct settings : opts {
    value<double> fov;
    value<QString> camera_name;
    value<int> fps, resolution;
    settings() :
        opts("HT-Tracker"),
        fov(b, "fov", 56),
        camera_name(b, "camera-name", ""),
        fps(b, "fps", 0),
        resolution(b, "resolution", 0)
    {}
};

class Tracker : public QObject, public ITracker
{
    Q_OBJECT
public:
	Tracker();
    ~Tracker() override;
    void start_tracker(QFrame* frame);
    void data(double *data);
    void load_settings(ht_config_t* config);
private:
    settings s;
    PortableLockedShm lck_shm;
    ht_shm_t* shm;
	QProcess subprocess;
    HTVideoWidget* videoWidget;
	QHBoxLayout* layout;
};

// Widget that has controls for FTNoIR protocol client-settings.
class TrackerControls : public ITrackerDialog
{
    Q_OBJECT
public:
	explicit TrackerControls();
    void register_tracker(ITracker *) {}
    void unregister_tracker() {}

private:
	Ui::Form ui;
    settings s;

private slots:
	void doOK();
	void doCancel();
};

#endif

