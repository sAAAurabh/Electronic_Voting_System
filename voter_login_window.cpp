#include "voter_login_window.h"
#include "voter_register_window.h"
#include "voter_home.h"

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

VoterLoginWindow::VoterLoginWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Login");
    setFixedSize(450, 300);

    //title
    title = new QLabel("E-VOTE", this);

    QFont titleFont;
    titleFont.setPointSize(24);
    titleFont.setBold(true);

    title->setFont(titleFont);
    title->setAlignment(Qt::AlignCenter);

    //nid and password
    nid_label = new QLabel("National ID", this);
    nid_input = new QLineEdit(this);

    pass_label = new QLabel("Password", this);
    pass_input = new QLineEdit(this);

    nid_input->setPlaceholderText("Enter National ID");
    nid_input->setStyleSheet("padding:6px;");

    pass_input->setPlaceholderText("Enter Password");
    pass_input->setEchoMode(QLineEdit::Password);
    pass_input->setStyleSheet("padding:6px;");

    //login and reg button
    login_btn = new QPushButton("Login", this);
    reg_btn = new QPushButton("Register", this);

    login_btn->setStyleSheet(
        "background-color:#3498db; color:white; padding:8px; border-radius:6px;"
        );
    login_btn->setCursor(Qt::PointingHandCursor);

    reg_btn->setStyleSheet(
        "background-color:#2ecc71; color:white; padding:8px; border-radius:6px;"
        );
    reg_btn->setCursor(Qt::PointingHandCursor);

    //warning message
    QFont msg_font;
    msg_font.setPointSize(13);
    msg_font.setBold(true);
    msg_font.setItalic(true);

    msg = new QLabel(this);
    msg->setAlignment(Qt::AlignCenter);
    msg->setFont(msg_font);

    // layout
    grid = new QGridLayout(this);
    grid->setContentsMargins(40, 20, 40, 20);
    grid->setHorizontalSpacing(10);
    grid->setVerticalSpacing(10);

    grid->addWidget(title, 0, 0, 1, 2);
    grid->addWidget(nid_label, 1, 0);
    grid->addWidget(nid_input, 1, 1);
    grid->addWidget(pass_label, 2, 0);
    grid->addWidget(pass_input, 2, 1);
    grid->addWidget(login_btn, 3, 0, 1, 2);
    grid->addWidget(reg_btn, 4, 0, 1, 2);
    grid->addWidget(msg, 5, 0, 1, 2);

    connect(login_btn, &QPushButton::clicked, this, &VoterLoginWindow::login);
    connect(reg_btn, &QPushButton::clicked, this, &VoterLoginWindow::open_register);
}

void VoterLoginWindow::login()
{
    if (nid_input->text().isEmpty() && pass_input->text().isEmpty()){
        msg->setStyleSheet("color: red;");
        msg->setText("enter details!");
        return;
    } else if (nid_input->text().isEmpty()){
        msg->setStyleSheet("color: red;");
        msg->setText("nid field : empty");
        return;
    } else if (pass_input->text().isEmpty()){
        msg->setStyleSheet("color: red;");
        msg->setText("password field: empty!");
        return;
    }

    int rsp = admin.login_voter(
        nid_input->text().toStdString(),
        pass_input->text().toStdString()
        );

    switch(rsp)
    {
    case login_success:
    {
        msg->setStyleSheet("color: green;");
        msg->setText("Login Successful");

        VoterHomeWindow *w = new VoterHomeWindow(
            nid_input->text(),
            nullptr
            );

        w->show();
        this->hide();
        clear_fields();
        break;
    }

    case not_found:
        msg->setStyleSheet("color: red;");
        msg->setText("Voter Not Found");
        clear_fields();
        break;

    case wrong_pass:
        msg->setStyleSheet("color: red;");
        msg->setText("Wrong Password");
        clear_fields();
        break;

    case acc_locked:
        msg->setStyleSheet("color: red;");
        msg->setText("Account Locked. Contact Admin");
        clear_fields();
        break;
    }
}

void VoterLoginWindow::open_register()
{
    VoterRegisterWindow *w = new VoterRegisterWindow();
    w->show();
}

void VoterLoginWindow::clear_fields()
{
    nid_input->clear();
    pass_input->clear();
}