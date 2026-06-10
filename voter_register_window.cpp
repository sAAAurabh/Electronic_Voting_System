#include "voter_register_window.h"
#include "admin.h"
#include <QVBoxLayout>

VoterRegisterWindow::VoterRegisterWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Voter Registration");
    setFixedSize(550,450);

    //title
    title = new QLabel("Voter Registratrion", this);

    QFont title_font;
    title_font.setPointSize(24);
    title_font.setBold(true);


    title->setFont(title_font);
    title->setAlignment(Qt::AlignCenter);


    //names
    f_name_label = new QLabel("First Name", this);
    f_name_input = new QLineEdit(this);
    f_name_warn = new QLabel("●", this);
    f_name_warn->setStyleSheet("color:red; font-size:18px");
    f_name_warn->setVisible(false);

    l_name_label = new QLabel("Last Name", this);
    l_name_input = new QLineEdit(this);
    l_name_warn = new QLabel("●", this);
    l_name_warn->setStyleSheet("color:red; font-size:18px");
    l_name_warn->setVisible(false);

    f_name_input->setPlaceholderText("Enter First Name");
    f_name_input->setStyleSheet("padding:6px;");

    l_name_input->setPlaceholderText("Enter Last Name");
    l_name_input->setStyleSheet("padding:6px;");


    //nid
    nid_label = new QLabel("National ID", this);
    nid_input = new QLineEdit(this);
    nid_warn = new QLabel("●", this);
    nid_warn->setStyleSheet("color:red; font-size:18px");
    nid_warn->setVisible(false);
    nid_input->setPlaceholderText("Enter National ID");
    nid_input->setStyleSheet("padding:6px;");

    //pass
    pass_label = new QLabel("Password", this);
    pass_input = new QLineEdit(this);
    pass_warn = new QLabel("●", this);
    pass_warn->setStyleSheet("color:red; font-size:18px");
    pass_warn->setVisible(false);

    pass_input->setPlaceholderText("Enter Password");
    pass_input->setStyleSheet("padding:6px");
    pass_input->setEchoMode(QLineEdit::Password);


    //registration button
    reg_btn = new QPushButton("Register", this);
    reg_btn->setCursor(Qt::PointingHandCursor);

    reg_btn->setStyleSheet(
        "background-color:#2ecc71; color:white; padding:8px; border-radius:6px;"
        );


    //warning message
    QFont msg_font;
    msg_font.setPointSize(15);
    msg_font.setBold(true);
    msg_font.setItalic(true);

    msg = new QLabel(this);
    msg->setAlignment(Qt::AlignCenter);
    msg->setFont(msg_font);
    msg->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);



    //back to login
    back_btn = new QPushButton("← Back to Login", this);
    back_btn->setStyleSheet(
        "background: transparent;"
        "color: #3498db;"
        "border: none;"
        "font-size: 12px;"
        "text-align: left;"
        );
    back_btn->setFixedSize(120, 20);
    back_btn->setCursor(Qt::PointingHandCursor);

    // grid layout
    grid = new QGridLayout(this);

    // layout design
    grid->setContentsMargins(50, 30, 50, 30);
    grid->setHorizontalSpacing(20);
    grid->setVerticalSpacing(14);

    grid->addWidget(title, 0, 0, 1, 3);

    grid->addWidget(f_name_label, 1, 0);
    grid->addWidget(f_name_input, 1, 1);
    grid->addWidget(f_name_warn,  1, 2);

    grid->addWidget(l_name_label, 2, 0);
    grid->addWidget(l_name_input, 2, 1);
    grid->addWidget(l_name_warn,  2, 2);

    grid->addWidget(nid_label, 3, 0);
    grid->addWidget(nid_input, 3, 1);
    grid->addWidget(nid_warn,  3, 2);

    grid->addWidget(pass_label, 4, 0);
    grid->addWidget(pass_input, 4, 1);
    grid->addWidget(pass_warn,  4, 2);

    grid->addWidget(msg, 5, 0, 1, 3);

    grid->addWidget(reg_btn, 6, 0, 1, 3);

    grid->addWidget(back_btn, 7, 0, 1, 1);


    //signals and slots
    connect(reg_btn, &QPushButton::clicked, this, &VoterRegisterWindow::register_user);
    connect(back_btn, &QPushButton::clicked, this, &VoterRegisterWindow::close_register);


}


void VoterRegisterWindow::register_user()
{
    Voter v;
    Admin a;


    bool f_empty = f_name_input->text().isEmpty();
    bool l_empty = l_name_input->text().isEmpty();
    bool n_empty = nid_input->text().isEmpty();
    bool p_empty = pass_input->text().isEmpty();

    f_name_warn->setVisible(f_empty);
    l_name_warn->setVisible(l_empty);
    nid_warn->setVisible(n_empty);
    pass_warn->setVisible(p_empty);


    if(f_empty || l_empty || n_empty || p_empty) return;


    v.nid = nid_input->text().toStdString();
    v.first = f_name_input->text().toStdString();
    v.last = l_name_input->text().toStdString();


    switch(a.is_valid_pass(pass_input->text().toStdString(), v.first)){
    case is_valid:
        v.salt = admin.gen_salt();
        v.hash = admin.hash_pass(pass_input->text().toStdString(), v.salt);

        v.is_locked = false;
        v.attempts_left = 5;

        admin.add_voter(v);

        msg->setStyleSheet("color: green;");
        msg->setText("Registered Successfully");


        back_btn->setStyleSheet(
            "background: transparent;"
            "color: #3498db;"
            "border: none;"
            "font-size: 13px;"
            "text-align: center;"
            "font-weight: bold;"
            "font-style: italic;"
        );

        clear_fields();
        break;

    case letter:
        msg->setStyleSheet("color: red;");
        msg->setText("Password must be at least 7 characters.");
        break;

    case number:
        msg->setStyleSheet("color: red;");
        msg->setText("At least 3 digits required.");
        break;

    case capital:
        msg->setStyleSheet("color: red;");
        msg->setText("At least 1 capital letter required.");
        break;

    case name:
        msg->setStyleSheet("color: red;");
        msg->setText("Password must not be same as your name");
        break;

    case special:
        msg->setStyleSheet("color: red;");
        msg->setText("At least 1 speical character required.");
        break;
    }
}

void VoterRegisterWindow::close_register(){
    delete this;
}

void VoterRegisterWindow::clear_fields(){
    f_name_input->clear();
    l_name_input->clear();
    pass_input->clear();
    nid_input->clear();
}
