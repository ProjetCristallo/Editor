#include "login.h"

LoginDialog::LoginDialog(QWidget *parent):QDialog(parent)
{
	this->initGUI();
	this->setWindowTitle("Authentification");
	this->setModal(true);
}

void LoginDialog::initGUI()
{
	QGridLayout *layout = new QGridLayout();
	this->m_loginLabel = new QLabel("Nom d'utilisateur",this);
	this->m_loginEdit = new QLineEdit(this);
	this->m_passwordLabel = new QLabel("Mot de passe",this);
	this->m_passwordEdit = new QLineEdit(this);
	this->m_passwordEdit->setEchoMode(QLineEdit::Password);

	this->m_buttons = new QDialogButtonBox(this);
	this->m_buttons->addButton(QDialogButtonBox::Ok);
	this->m_buttons->addButton(QDialogButtonBox::Cancel);

	connect(this->m_buttons->button(QDialogButtonBox::Ok),
			SIGNAL(clicked()), this, SLOT(slotAcceptLogin()));
	connect(this->m_buttons->button(QDialogButtonBox::Cancel),
			SIGNAL(clicked()), this, SLOT(close()));
	layout->addWidget(this->m_loginLabel, 0,0);
	layout->addWidget(this->m_loginEdit, 0,1);
	layout->addWidget(this->m_passwordLabel, 1,0);
	layout->addWidget(this->m_passwordEdit, 1,1);
	layout->addWidget(this->m_buttons, 2,0,1,2);

	this->setLayout(layout);
}

void LoginDialog::setLogin(QString login)
{
	this->m_loginEdit->setText(login);
}

void LoginDialog::setPassword(QString passwd)
{
	this->m_passwordEdit->setText(passwd);
}

void LoginDialog::slotAcceptLogin()
{
	QString login = this->m_loginEdit->text();
	QString password = this->m_passwordEdit->text();
	emit acceptLogin(login,password);
	close();
}
