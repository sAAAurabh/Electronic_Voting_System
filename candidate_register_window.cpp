#include "candidate_register_window.h"
#include "admin.h"
#include <QVBoxLayout>
#include <QDateEdit>
#include <QComboBox>
#include <QCalendarWidget>

CandidateRegisterWindow::CandidateRegisterWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Candidate Registration");
    setFixedSize(550, 800);

    //title
    title = new QLabel("Candidate Registration", this);

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


    //party
    party_label = new QLabel("Party", this);
    party_input = new QLineEdit(this);
    party_warn = new QLabel("●", this);
    party_warn->setStyleSheet("color:red; font-size:18px");
    party_warn->setVisible(false);
    party_input->setPlaceholderText("Enter Party Name");
    party_input->setStyleSheet("padding:6px;");


    //date of birth
    dob_label = new QLabel("Date of Birth", this);
    dob_input = new QDateEdit(this);
    dob_warn = new QLabel("●", this);
    dob_warn->setStyleSheet("color:red; font-size:18px");
    dob_warn->setVisible(false);

    dob_input->setDisplayFormat("dd/MM/yyyy");
    dob_input->setCalendarPopup(true);
    dob_input->setMaximumDate(QDate::currentDate().addYears(-18));
    dob_input->setMinimumDate(QDate(1900, 1, 1));
    dob_input->setDate(QDate(2000, 1, 1));
    dob_input->setStyleSheet("padding:6px;");
    dob_input->setMaximumDate(QDate::currentDate().addYears(-18));

    QCalendarWidget *calendar = dob_input->calendarWidget();
    calendar->setStyleSheet(
        "QCalendarWidget QAbstractItemView {"
        "   color: black;"
        "}"
        "QCalendarWidget QAbstractItemView:disabled {"
        "   color: gray;"                           // disabled/out-of-range dates in gray
        "}"
        );


    //gender
    gender_label = new QLabel("Gender", this);
    gender_input = new QComboBox(this);
    gender_warn = new QLabel("●", this);
    gender_warn->setStyleSheet("color:red; font-size:18px");
    gender_warn->setVisible(false);

    gender_input->addItem("-- Select Gender --");
    gender_input->addItem("Male");
    gender_input->addItem("Female");
    gender_input->addItem("Other");
    gender_input->setStyleSheet("padding:6px;");

    //photo
    photo_label = new QLabel("Photo", this);

    photo_btn = new QPushButton("Upload Photo", this);
    photo_btn->setCursor(Qt::PointingHandCursor);
    photo_btn->setStyleSheet(
        "background-color:#3498db; color:white; padding:6px; border-radius:6px;"
        );

    photo_warn = new QLabel("●", this);
    photo_warn->setStyleSheet("color:red; font-size:18px");
    photo_warn->setVisible(false);

    photo_preview = new QLabel(this);
    photo_preview->setFixedSize(80, 80);
    photo_preview->setStyleSheet(
        "border: 2px dashed #aaa;"
        "border-radius: 6px;"
        );
    photo_preview->setAlignment(Qt::AlignCenter);
    photo_preview->setText("No Photo");
    photo_preview->setScaledContents(true);

    //pass
    pass_label = new QLabel("Password", this);
    pass_input = new QLineEdit(this);
    pass_warn = new QLabel("●", this);
    pass_warn->setStyleSheet("color:red; font-size:18px");
    pass_warn->setVisible(false);

    pass_input->setPlaceholderText("Enter Password");
    pass_input->setStyleSheet("padding:6px");
    pass_input->setEchoMode(QLineEdit::Password);


    //manifesto
    manifesto_label = new QLabel("Manifesto", this);
    manifesto_input = new QTextEdit(this);
    manifesto_input->setPlaceholderText("Write your manifesto...");
    manifesto_input->setStyleSheet("padding:6px;");
    manifesto_input->setFixedHeight(80);

    manifesto_warn = new QLabel("●", this);
    manifesto_warn->setStyleSheet("color:red; font-size:18px");
    manifesto_warn->setVisible(false);


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
    grid->setContentsMargins(50, 30, 50, 30);
    grid->setHorizontalSpacing(20);
    grid->setVerticalSpacing(14);

    grid->addWidget(title,           0, 0, 1, 3);

    grid->addWidget(f_name_label,    1, 0);
    grid->addWidget(f_name_input,    1, 1);
    grid->addWidget(f_name_warn,     1, 2);

    grid->addWidget(l_name_label,    2, 0);
    grid->addWidget(l_name_input,    2, 1);
    grid->addWidget(l_name_warn,     2, 2);

    grid->addWidget(party_label,     3, 0);
    grid->addWidget(party_input,     3, 1);
    grid->addWidget(party_warn,      3, 2);

    grid->addWidget(nid_label,       4, 0);
    grid->addWidget(nid_input,       4, 1);
    grid->addWidget(nid_warn,        4, 2);

    grid->addWidget(dob_label,       5, 0);
    grid->addWidget(dob_input,       5, 1);
    grid->addWidget(dob_warn,        5, 2);

    grid->addWidget(gender_label,    6, 0);
    grid->addWidget(gender_input,    6, 1);
    grid->addWidget(gender_warn,     6, 2);

    grid->addWidget(photo_label,   7, 0);
    grid->addWidget(photo_btn,     7, 1);
    grid->addWidget(photo_warn,    7, 2);

    grid->addWidget(photo_preview, 8, 1);  // preview below upload button

    grid->addWidget(pass_label,      9, 0);
    grid->addWidget(pass_input,      9, 1);
    grid->addWidget(pass_warn,       9, 2);

    grid->addWidget(manifesto_label, 10, 0);
    grid->addWidget(manifesto_input, 10, 1);
    grid->addWidget(manifesto_warn,  10, 2);

    grid->addWidget(msg,             11,  0, 1, 3);
    grid->addWidget(reg_btn,         12, 0, 1, 3);
    grid->addWidget(back_btn,        13, 0, 1, 1);


    //signals and slots
    connect(reg_btn,  &QPushButton::clicked, this, &CandidateRegisterWindow::register_user);
    connect(back_btn, &QPushButton::clicked, this, &CandidateRegisterWindow::close_register);
    connect(photo_btn, &QPushButton::clicked, this, &CandidateRegisterWindow::upload_photo);
}


void CandidateRegisterWindow::register_user()
{
    Candidate c;
    Admin a;

    bool f_empty      = f_name_input->text().isEmpty();
    bool l_empty      = l_name_input->text().isEmpty();
    bool pty_empty    = party_input->text().isEmpty();
    bool n_empty      = nid_input->text().isEmpty();
    bool dob_default  = (dob_input->date() == QDate(2000, 1, 1));
    bool gender_empty = (gender_input->currentIndex() == 0);
    bool p_empty      = pass_input->text().isEmpty();
    bool m_empty      = manifesto_input->toPlainText().isEmpty();
    bool photo_empty = photo_path.isEmpty();

    f_name_warn->setVisible(f_empty);
    l_name_warn->setVisible(l_empty);
    party_warn->setVisible(pty_empty);
    nid_warn->setVisible(n_empty);
    dob_warn->setVisible(dob_default);
    gender_warn->setVisible(gender_empty);
    pass_warn->setVisible(p_empty);
    manifesto_warn->setVisible(m_empty);
    photo_warn->setVisible(photo_empty);

    if(f_empty || l_empty || n_empty || dob_default || gender_empty || photo_empty || p_empty) return;

    c.nid    = nid_input->text().toStdString();
    c.first  = f_name_input->text().toStdString();
    c.last   = l_name_input->text().toStdString();
    c.party  = party_input->text().toStdString();
    c.dob    = dob_input->date().toString("dd/MM/yyyy").toStdString();
    c.gender = gender_input->currentText().toStdString();
    c.photo_path = photo_path.toStdString();

    switch(a.is_valid_pass(pass_input->text().toStdString(), c.first)){
    case is_valid:
        c.salt = admin.gen_salt();
        c.hash = admin.hash_pass(pass_input->text().toStdString(), c.salt);

        c.is_locked     = false;
        c.attempts_left = 5;

        admin.add_candidate(c);
        save_manifesto(nid_input->text(), manifesto_input->toPlainText());

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
        msg->setText("At least 1 special character required.");
        break;
    }
}

void CandidateRegisterWindow::close_register(){
    delete this;
}

void CandidateRegisterWindow::clear_fields(){
    f_name_input->clear();
    l_name_input->clear();
    nid_input->clear();
    party_input->clear();
    dob_input->setDate(QDate(2000, 1, 1));
    gender_input->setCurrentIndex(0);
    pass_input->clear();
    manifesto_input->clear();
    photo_path.clear();
    photo_preview->clear();
    photo_preview->setText("No Photo");
}


void CandidateRegisterWindow::save_manifesto(const QString &nid, const QString &manifesto)
{
    std::ofstream file("Other files/manifesto.txt", std::ios::app);

    if (!file.is_open())
        return;

    file << nid.toStdString()
         << "|"
         << manifesto.toStdString()
         << "\n";

    file.close();
}

void CandidateRegisterWindow::upload_photo()
{
    QString file_path = QFileDialog::getOpenFileName(
        this,
        "Select Photo",
        "",
        "Images (*.*)"
        );

    if(file_path.isEmpty()) return;

    photo_path = file_path;

    QPixmap pixmap(file_path);
    photo_preview->setPixmap(pixmap);
    photo_preview->setText("");
}