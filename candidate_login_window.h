#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "admin.h"
#include <QFont>

class CandidateLoginWindow : public QWidget
{
    Q_OBJECT

public:
    CandidateLoginWindow(QWidget *parent = nullptr);

private slots:
    void login();
    void open_register();
    void clear_fields();

private:
    QLabel *title;

    QLabel *nid_label;
    QLineEdit *nid_input;

    QLabel *pass_label;
    QLineEdit *pass_input;

    QPushButton *reg_btn;
    QPushButton *login_btn;

    QLabel *msg;
    QGridLayout *grid;

    Admin admin;
};