#!/usr/bin/python

import sys, datetime

#global_dict = {}

def gen_html_merge(f_template, fin_list, fout,str_date1,str_date2):
	
	str_merged = f_template.read()
	
	str_merged = str_merged.replace('%DATA_1%', str_date1)
	str_merged = str_merged.replace('%DATA_2%', str_date2)
	#str_merged = str_merged.replace('%DATA_3%', str_date3)
	
	str_f = []
	for f in fin_list:
		str = f.read()
		#print str
		str_f.append(str)
		
	#str_f1 = f1.read()
	#str_f2 = f2.read()
	#str_f3 = f3.read()

	
	for i in range(len(str_f)):
		str_table_tag = '%TABLE_' + ('%d' % (i+1)) + '%'
		print str_table_tag
		str_f[i]
		str_merged = str_merged.replace(str_table_tag, str_f[i])
                
	#str_merged = str_merged.replace('%TABLE_1%', str_f1)
	#str_merged = str_merged.replace('%TABLE_2%', str_f2)
	#str_merged = str_merged.replace('%TABLE_3%', str_f3)


	fout.write(str_merged)
	
def main():
	source_file_list = []
	
	if len(sys.argv) < 6:
		print 'Usage:', sys.argv[0], 'base_date run_date result_file template_file source_file_1 [source_file_2 ...]  '
		sys.exit()
	else:
		for i in range(5, len(sys.argv)):
			source_file_list.append(sys.argv[i])
	
	base_date_str = sys.argv[1]
	#base_date = datetime.datetime.strptime(base_date_str,"%Y%m%d")
	
	##
	#roi_date = base_date-datetime.timedelta(days=1)
	#roi_date_str = str(roi_date)[0:4]+str(roi_date)[5:7]+str(roi_date)[8:10]
	run_date_str = sys.argv[2]
	
	template_merged_file = sys.argv[4]
	result_file = sys.argv[3]
        print template_merged_file
        print result_file

	# open template_file
	try:
		f_tmplate = open(template_merged_file, 'r')
	except IOError:
		print 'Open template_merged_file error:', template_merged_file
		sys.exit(1)
	
	# open source_file(s)
	fin_list = []
	num_source_file = len(sys.argv)-5
	for i in range(num_source_file):
		try:
			fin_list.append(open(source_file_list[i], 'r'))
			print 'source_file',i+1,': ',source_file_list[i]
		except IOError:
			print 'Open template_merged_file error:', source_file_list[i]
			sys.exit(1)
			
	# open result_file
	try:
		fout = open(result_file, 'w')
		print 'Result_file:', result_file
	except IOError:
		print 'Open result_file error:', result_file
		sys.exit(1)
		
	
	gen_html_merge(f_tmplate, fin_list, fout, base_date_str, run_date_str)

	f_tmplate.close()
	for i in range(num_source_file):
		fin_list[i].close()
	fout.close()

if __name__ == '__main__':
	main()

