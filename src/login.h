#ifndef __LOGIN__
#define __LOGIN__
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QDialogButtonBox>

class LoginDialog: public QDialog
{
	Q_OBJECT
private:
	QLabel *m_loginLabel;
	QLabel *m_passwordLabel;
	QLineEdit *m_loginEdit;
	QLineEdit *m_passwordEdit;
	QDialogButtonBox *m_buttons;
	void initGUI();
public:
	LoginDialog(QWidget *parent = 0);
	void setLogin(QString login);
	void setPassword(QString passwd);
signals:
	void acceptLogin(QString &login, QString &passwd);
public slots:
	void slotAcceptLogin();
};

#endif
