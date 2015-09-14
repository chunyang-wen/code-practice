#!/usr/bin/python
#Mail service

import ConfigParser, sys, datetime, os
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

class mail_slave(object):
	def __init__(self, conf_file):
		config = ConfigParser.ConfigParser()
		if not os.path.isfile(conf_file):
			print 'ERROR ! Conf_file not exist: ',conf_file
			sys.exit(1)
			
		config.read(conf_file)
		self.send_list = config.get('mail', 'mail-to')
		self.server_name = config.get('mail', 'server')
		self.server_smtp_port = config.get('mail', 'port')
		self.user = config.get('mail', 'user')
		self.passwd = config.get('mail', 'passwd')
		self.htmltext = config.get('mail', 'htmltext')
		self.msg_file = config.get('mail', 'msg_file')
		self.attachment = config.get('mail', 'attachment')
		#self.title = config.get('mail', 'title') + str(datetime.date.today())
		self.title = config.get('mail', 'title')

	def gen_mail(self):
		msg = MIMEMultipart()

		msg['Subject'] = self.title
		msg['From'] = 'wenchunyang <wenchunyang@baidu.com>'
		msg['To'] = self.send_list
		
		print msg['Subject']
		print msg['From']
		print msg['To']
		
		try:
			handle = open(self.htmltext, 'r')
		except IOError:
			print 'Open htmltext error:', self.htmltext
			sys.exit(1)
			
		msg_text = MIMEText(handle.read(), 'html', 'gb2312')
		msg.attach(msg_text)
		handle.close()
		

                files=self.attachment
                filenames=files.split(',');
                for path in filenames:
                    name = path.split('/')[-1]
                    try:
                            handle = open(path, 'rb')
                    except IOError:
                            print 'Open attachment error:', self.attachment
                            sys.exit(1)
                    att = MIMEText(handle.read(), 'base64', 'gb2312')  
                    att['Content-Type'] = 'application/octet-stream'
                    att['Content-Disposition'] = 'attachment; filename="'+name+'.csv"'
                    msg.attach(att)
                    handle.close()
		
		try:
			handle = open(self.msg_file, 'w')
			handle.write(msg.as_string())
			handle.close()
		except IOError:
			print 'Open mail file error'
			sys.exit(2)

def main():
	if len(sys.argv) != 2:
		print 'Usage:', sys.argv[0], 'config_file'
		sys.exit()

	config_file = sys.argv[1]
	ms = mail_slave(config_file)
	ms.gen_mail()

if __name__ == '__main__':
		main()

