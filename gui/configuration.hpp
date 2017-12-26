#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <QDialog>

namespace Ui {
class Configuration : public Ui_Configuration {};
}

class Configuration : public QDialog
{
    Q_OBJECT

public:
    explicit Configuration(QWidget *parent = 0);
    ~Configuration();

private:
    Ui::Configuration *ui;
};

#endif // CONFIGURATION_HPP
