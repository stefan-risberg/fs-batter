#include <QApplication>
#include <QObject>
#include <QIcon>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QString>
#include <fstream>
#include <iostream>
#include <string>

void test(QSystemTrayIcon::ActivationReason r)
{
    std::cerr << "Hello " << r << std::endl;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto bat_missing = QIcon::fromTheme("battery-missing-symbolic");
    auto bat_empty = QIcon::fromTheme("battery-empty-symbolic");
    auto bat_caution = QIcon::fromTheme("battery-caution-symbolic");
    auto bat_low = QIcon::fromTheme("battery-low-symbolic");
    auto bat_good = QIcon::fromTheme("battery-good-symbolic");
    auto bat_full = QIcon::fromTheme("battery-full-symbolic");

    auto bat_empty_c = QIcon::fromTheme("battery-empty-charging-symbolic");
    auto bat_caution_c = QIcon::fromTheme("battery-caution-charging-symbolic");
    auto bat_low_c = QIcon::fromTheme("battery-low-charging-symbolic");
    auto bat_good_c = QIcon::fromTheme("battery-good-charging-symbolic");
    auto bat_full_c = QIcon::fromTheme("battery-full-charging-symbolic");

    auto bat_fully = QIcon::fromTheme("battery-full-charged-symbolic");

    QSystemTrayIcon systray;

    std::ifstream is;
    auto update = [&] () {
        if (QSystemTrayIcon::isSystemTrayAvailable() && !systray.isVisible()) {
            systray.show();
        }

        is.open("/sys/class/power_supply/BAT0/status");

        if (is.is_open()) {
            std::string msg = "";
            int cap = 0;

            is >> msg;

            is.close();
            is.open("/sys/class/power_supply/BAT0/capacity");

            is >> cap;

            is.close();

            if (msg == "Full") {
                systray.setIcon(bat_fully);
                systray.setToolTip("Fully charged");
            } else if (msg == "Charging") {
                if (cap == 0) {
                    systray.setIcon(bat_empty_c);
                } else if (cap < 25) {
                    systray.setIcon(bat_caution_c);
                } else if (cap < 50) {
                    systray.setIcon(bat_low_c);
                } else if (cap < 75) {
                    systray.setIcon(bat_good_c);
                } else {
                    systray.setIcon(bat_full_c);
                }
            } else {
                if (cap == 0) {
                    systray.setIcon(bat_empty);
                } else if (cap < 25) {
                    systray.setIcon(bat_caution);
                } else if (cap < 50) {
                    systray.setIcon(bat_low);
                } else if (cap < 75) {
                    systray.setIcon(bat_good);
                } else {
                    systray.setIcon(bat_full);
                }
            }

            QString num;
            num.setNum(cap);
            QString msg1 = "Charge level: ";
            QString proc = "%";
            QString m;
            m.append(msg1);
            m.append(num);
            m.append(proc);
            systray.setToolTip(m);
        } else {
            systray.setIcon(bat_missing);
            systray.setToolTip("Missing");
        }
    };


    QTimer timer;

    QObject::connect(&timer, &QTimer::timeout, update);
    timer.start(500);
    update();

    systray.show();

    return app.exec();
}

