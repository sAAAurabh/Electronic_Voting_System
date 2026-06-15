#include "voter_home.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFont>
#include <QFrame>

VoterHomeWindow::VoterHomeWindow(const QString& nid, QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Voter Dashboard");
    setFixedSize(600, 480);

    setStyleSheet("background-color:#1a1a2e;");

    // Title
    title = new QLabel("Voter Dashboard", this);

    QFont titleFont;
    titleFont.setPointSize(22);
    titleFont.setBold(true);

    title->setFont(titleFont);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("color:#4fc3f7; padding: 6px 0px 2px 0px;");

    // Divider
    QFrame *divider = new QFrame(this);
    divider->setFrameShape(QFrame::HLine);
    divider->setFixedHeight(2);
    divider->setStyleSheet("background-color:#4fc3f7; border:none; margin: 0px 60px;");

    // Profile Box
    QFrame *profile_box = new QFrame(this);
    profile_box->setStyleSheet(
        "QFrame {"
        "    background-color:#16213e;"
        "    border:1px solid #0f3460;"
        "    border-radius:12px;"
        "    padding:6px;"
        "}"
        );

    QGridLayout *profile_layout = new QGridLayout(profile_box);
    profile_layout->setContentsMargins(20, 20, 20, 20);
    profile_layout->setHorizontalSpacing(24);
    profile_layout->setVerticalSpacing(14);

    // Fetch voter
    Voter v;
    Admin a;
    a.find_voter(nid.toStdString(), v);

    // Photo
    photo_label = new QLabel("Photo", this);
    photo_label->setAlignment(Qt::AlignCenter);
    photo_label->setFixedSize(100, 110);
    photo_label->setStyleSheet(
        "border: 2px solid #4fc3f7;"
        "border-radius: 8px;"
        "color: #4fc3f7;"
        "font-size: 13px;"
        "background-color: #0f3460;"
        );

    // Info rows
    auto make_row = [&](const QString& key, const QString& value) -> QLabel* {
        QLabel *lbl = new QLabel(
            QString("<span style='color:#7a8caa; font-size:12px;'>%1&nbsp;&nbsp;</span>"
                    "<span style='color:#e0e0e0; font-size:14px; font-weight:600;'>%2</span>")
                .arg(key, value.isEmpty() ? QString("--") : value)
            );
        lbl->setTextFormat(Qt::RichText);
        lbl->setStyleSheet("padding: 6px 12px; background-color:#1a2a4a; border-radius:6px;");
        return lbl;
    };

    name_label   = make_row("Name",          QString::fromStdString(v.first + " " + v.last));
    dob_label    = make_row("Date of Birth", QString::fromStdString(v.dob));
    gender_label = make_row("Gender",        QString::fromStdString(v.gender));
    nid_label    = make_row("NID",           QString::fromStdString(v.nid));

    profile_layout->addWidget(photo_label,   0, 0, 4, 1, Qt::AlignTop);
    profile_layout->addWidget(name_label,    0, 1);
    profile_layout->addWidget(dob_label,     1, 1);
    profile_layout->addWidget(gender_label,  2, 1);
    profile_layout->addWidget(nid_label,     3, 1);
    profile_layout->setColumnStretch(1, 1);

    // Buttons
    view_candidates_btn = new QPushButton("View Candidates", this);
    vote_candidates_btn = new QPushButton("Vote Candidates", this);
    logout_btn          = new QPushButton("Logout",          this);

    QString btn_base =
        "font-size:13px;"
        "font-weight:600;"
        "padding:10px 0px;"
        "border-radius:8px;"
        "border:none;";

    view_candidates_btn->setStyleSheet(btn_base + "background-color:#0f3460; color:#4fc3f7;");
    view_candidates_btn->setCursor(Qt::PointingHandCursor);
    view_candidates_btn->setMinimumHeight(42);

    vote_candidates_btn->setStyleSheet(btn_base + "background-color:#4fc3f7; color:#1a1a2e;");
    vote_candidates_btn->setCursor(Qt::PointingHandCursor);
    vote_candidates_btn->setMinimumHeight(42);

    logout_btn->setStyleSheet(btn_base + "background-color:#c0392b; color:white;");
    logout_btn->setCursor(Qt::PointingHandCursor);
    logout_btn->setMinimumHeight(42);

    QHBoxLayout *button_layout = new QHBoxLayout;
    button_layout->setSpacing(12);
    button_layout->addWidget(view_candidates_btn);
    button_layout->addWidget(vote_candidates_btn);
    button_layout->addWidget(logout_btn);

    // Message
    msg = new QLabel(this);
    msg->setAlignment(Qt::AlignCenter);
    msg->setStyleSheet("color:#27ae60; font-weight:bold; font-size:13px;");

    // Main grid
    grid = new QGridLayout(this);
    grid->setContentsMargins(36, 24, 36, 24);
    grid->setVerticalSpacing(16);

    grid->addWidget(title,           0, 0, 1, 2);s
    grid->addWidget(divider,         1, 0, 1, 2);
    grid->addWidget(profile_box,     2, 0, 1, 2);
    grid->addLayout(button_layout,   3, 0, 1, 2);
    grid->addWidget(msg,             4, 0, 1, 2);

    connect(logout_btn, &QPushButton::clicked, this, &VoterHomeWindow::logout);
}

void VoterHomeWindow::logout()
{
    close();
}s