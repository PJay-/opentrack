#include "ui_ftnoir_hydra_clientcontrols.h"
#include "opentrack/plugin-api.hpp"
#include "opentrack/options.hpp"
using namespace options;

struct settings : opts {
    settings() :
        opts("tracker-hydra")
    {}
};

class Hydra_Tracker : public ITracker
{
public:
    Hydra_Tracker();
    ~Hydra_Tracker();
    void start_tracker(QFrame *) override;
    void data(double *data) override;
    volatile bool should_quit;
private:
    settings s;
    QMutex mutex;
};

class TrackerControls: public ITrackerDialog
{
    Q_OBJECT
public:
    TrackerControls();
    void register_tracker(ITracker *) {}
    void unregister_tracker() {}
private:
    settings s;
    Ui::UIHydraControls ui;
private slots:
    void doOK();
    void doCancel();
};

class FTNoIR_TrackerDll : public Metadata
{
public:
    QString name() { return QString("Razer Hydra -- inertial device"); }
    QIcon icon() { return QIcon(":/images/facetracknoir.png"); }
};

