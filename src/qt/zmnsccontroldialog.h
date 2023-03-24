// Copyright (c) 2017-2019 The MNSAVINGS developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ZMNSCCONTROLDIALOG_H
#define ZMNSCCONTROLDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "zmnsc/zerocoin.h"

class CZerocoinMint;
class WalletModel;

namespace Ui {
class ZmnscControlDialog;
}

class CZmnscControlWidgetItem : public QTreeWidgetItem
{
public:
    explicit CZmnscControlWidgetItem(QTreeWidget *parent, int type = Type) : QTreeWidgetItem(parent, type) {}
    explicit CZmnscControlWidgetItem(int type = Type) : QTreeWidgetItem(type) {}
    explicit CZmnscControlWidgetItem(QTreeWidgetItem *parent, int type = Type) : QTreeWidgetItem(parent, type) {}

    bool operator<(const QTreeWidgetItem &other) const;
};

class ZmnscControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZmnscControlDialog(QWidget *parent);
    ~ZmnscControlDialog();

    void setModel(WalletModel* model);

    static std::set<std::string> setSelectedMints;
    static std::set<CMintMeta> setMints;
    static std::vector<CMintMeta> GetSelectedMints();

private:
    Ui::ZmnscControlDialog *ui;
    WalletModel* model;

    void updateList();
    void updateLabels();

    enum {
        COLUMN_CHECKBOX,
        COLUMN_DENOMINATION,
        COLUMN_PUBCOIN,
        COLUMN_VERSION,
        COLUMN_PRECOMPUTE,
        COLUMN_CONFIRMATIONS,
        COLUMN_ISSPENDABLE
    };
    friend class CZmnscControlWidgetItem;

private slots:
    void updateSelection(QTreeWidgetItem* item, int column);
    void ButtonAllClicked();
};

#endif // ZMNSCCONTROLDIALOG_H
