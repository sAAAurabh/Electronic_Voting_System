#pragma once

#include <QWidget>
#include <QString>
#include "admin.h"

class QLabel;
class QPushButton;
class QGridLayout;

class VoterHomeWindow : public QWidget
{
    Q_OBJECT

public:
    VoterHomeWindow(const QString& nid, QWidget *parent = nullptr);

private:
    QLabel *title;
    QLabel *photo_label;
    QLabel *name_label;
    QLabel *dob_label;
    QLabel *gender_label;
    QLabel *nid_label;
    QLabel *msg;

    QPushButton *view_candidates_btn;
    QPushButton *vote_candidates_btn;
    QPushButton *logout_btn;

    QGridLayout *grid;

private slots:
    void logout();
};