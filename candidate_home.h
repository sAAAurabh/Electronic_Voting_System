#pragma once

#include <QWidget>
#include <admin.h>

class QLabel;
class QPushButton;
class QGridLayout;

class CandidateHomeWindow : public QWidget
{
    Q_OBJECT

public:
    CandidateHomeWindow(const QString& nid, QWidget *parent = nullptr);

private:
    QLabel *title;

    QLabel *name_label;
    QLabel *nid_label;
    QLabel *party_label;
    QLabel *vote_label;
    QLabel *manifesto_label;
    QLabel *msg;

    QPushButton *edit_btn;
    QPushButton *logout_btn;

    QGridLayout *grid;

private slots:
    void edit_profile();
    void logout();
};