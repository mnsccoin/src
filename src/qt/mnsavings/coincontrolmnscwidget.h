// Copyright (c) 2019 The MNSAVINGS developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef COINCONTROLMNSCWIDGET_H
#define COINCONTROLMNSCWIDGET_H

#include <QDialog>

namespace Ui {
class CoinControlmnscWidget;
}

class CoinControlmnscWidget : public QDialog
{
    Q_OBJECT

public:
    explicit CoinControlmnscWidget(QWidget *parent = nullptr);
    ~CoinControlmnscWidget();

private:
    Ui::CoinControlmnscWidget *ui;
};

#endif // COINCONTROLMNSCWIDGET_H
