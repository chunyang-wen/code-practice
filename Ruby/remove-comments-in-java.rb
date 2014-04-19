#! /usr/bin/ruby -w
# coding = UTF-8

# read in each line
# replace the comment
# @input: File to be processed, ARGV[0]
# @output: File to be stored, ARGV[1]
# @author: Chunyang Wen


result = '' # store the output string
multi_line = false
line_no = 0

File::open(ARGV[0])do |file|

	# handle each line
	loop do

		begin
			line = file.readline
			line_no += 1
		rescue
			break
		else
			# line.lstrip!
			line.rstrip!
			line.gsub!(/\/\/.*/,'') # remove one line comment
			line.gsub!(/\/\*.*\*\//, '') # remove multi-line comment on one line

			p "Cur LINE #{line_no}: #{line}"
			if multi_line then
				# we alread in mult-line mode
				# try to find "*/"
				# p "In True Loop"
				# p line.include?("*/")
				if !line.include?("*/") then
					# p "Next"
					next
				else
					# we are about to end
					start = line.index("*/")
					line = line.slice(start+2, line.length)
					multi_line  = false
				end
			end

			# after gsub, there still multi-line comment
			multi_line = line.include?("/*")

		#	p multi_line

			if multi_line then
				stop = line.index("/*")
				line.slice!(stop, line.length)
			end

			result<<line<<"\n" if line.length > 0

		end

	end
end
# p result
File::open(ARGV[1], "w+") do |file|
	# p ARGV[1]
	file.puts(result)
end

