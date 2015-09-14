#!/usr/bin/python

import sys

data = []

str_repeat_line = '\t<tr height=20 style=\'height:15.0pt\'>\n%SWITCH%\t</tr>\n'
str_line = '\t\t<td class=table_plain style=\'height:15.0pt;border-top:none\'>%VALUE%</td>\n%NEXT_ITEM%'
str_repeat_item = '\t\t<td class=table_plain align=right style=\'border-top:none;border-left:none\'>%VALUE%</td>\n%NEXT_ITEM%'

str_repeat_item_red = '\t\t<td class=table_red align=right style=\'border-top:none;border-left:none\'>%VALUE%</td>\n%NEXT_ITEM%'
str_repeat_item_green = '\t\t<td class=table_green align=right style=\'border-top:none;border-left:none\'>%VALUE%</td>\n%NEXT_ITEM%'

def get_data(str_filename):
	f = open(str_filename, 'r')
	for line in f:
		item = line.split()
		data.append(item)
	f.close()
	
	#for i in data:
	#	print i
	#print

def do_gen_html_work(handle_file_template, handle_file_result):
	global str_repeat_line
	global str_red_line
	global str_plain_line
	
	str_fill = ''
	for item in data:
		str_current_line = ''
		str_current_line = str_repeat_line.replace('%SWITCH%', str_line)
		str_current_line = str_current_line.replace('%VALUE%', item[0])
		for i in range(1,len(item)):
			if item[i][:1]=='-' or item[i]=='0':
				str_current_line = str_current_line.replace('%NEXT_ITEM%', str_repeat_item_green)
			elif item[i][:1]=='+':
				str_current_line = str_current_line.replace('%NEXT_ITEM%', str_repeat_item_red)
			else:
				str_current_line = str_current_line.replace('%NEXT_ITEM%', str_repeat_item)
				
			str_current_line = str_current_line.replace('%VALUE%', item[i])
		str_current_line = str_current_line.replace('%NEXT_ITEM%', '')
		str_fill = str_fill + str_current_line
	#print str_fill
	str_source = handle_file_template.read()
	#print str_source
	str_source = str_source.replace('%TABLE_LINES%', str_fill)
	#print str_source
	handle_file_result.write(str_source)
	
def main():
	if len(sys.argv) != 4:
		print 'Usage:', sys.argv[0], 'source_file template_file result_html_file'
		sys.exit()
	
	str_source_filename = sys.argv[1]
	str_template_filename = sys.argv[2]
	str_result_filename = sys.argv[3]

	get_data(str_source_filename)

	handle_file_template = open(str_template_filename, 'r')
	handle_file_result = open(str_result_filename, 'w')

	do_gen_html_work(handle_file_template, handle_file_result)

	handle_file_template.close()
	handle_file_result.close()

if __name__ == '__main__':
	main()

