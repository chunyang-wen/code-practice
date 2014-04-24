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

lines = 0

MUL_REPLACE_LEFT = "__MUL_REPLACE_LEFT__"
MUL_REPLACE_RIGHT = "__MUL_REPLACE_RIGHT__"
SIG_REPLACE = "__SIG_REPLACE__"

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
			
			p "Cur LINE #{line_no}: #{line}"
			
			line.gsub!(/\".*?\"/) do |match|

				# replace the coment symbols in double or single quotes
				match.gsub!(/\/\*/) do |match1|
					match1.gsub!("/*", MUL_REPLACE_LEFT)
				end
				
				match.gsub!(/\*\//) do |match1|
					match1.gsub!("*/", MUL_REPLACE_RIGHT)
				end
				
				match.gsub!(/\/\//) do |match1|
					match1.gsub!("//", SIG_REPLACE)
				end
				
				match
				
			end
			
=begin
			# replace the coment symbols in double or single quotes
			line.gsub!(/\".*(\/\*).*\"/) do |match|
				match.gsub!("/*", MUL_REPLACE_LEFT)
			end
			
			line.gsub!(/\".*(\*\/).*\"/) do |match|
				match.gsub!("*/", MUL_REPLACE_RIGHT)
			end
			
			line.gsub!(/\".*(\/\/).*\"/) do |match|
				match.gsub!("//", SIG_REPLACE)
			end
=end
			
			p "Cur LINE #{line_no}: #{line}"
			if multi_line then
				# we alread in mult-line mode
				# try to find "*/"
				# p "In True Loop"
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
			
			line.gsub!(/\/\*.*?\*\//, '') # remove multi-line comment on one line
			line.gsub!(/\/\/.*/,'') # remove one line comment		
			
			p "Cur LINE #{line_no}: #{line}" 
			# after gsub, there still multi-line comment
			multi_line = line.include?("/*")

			p multi_line
			# p double_quotes

			if multi_line then
				stop = line.index("/*")
				line.slice!(stop, line.length)
			end
			
			# replace back all the special symbols

=begin
			i = 0

			line.gsub!(DOUBLE_QUOTES) do |match|
				temp = double_quotes[0]
				double_quotes.pop
				match.gsub!(/.+/, temp)				
			end
=end			
# =begin
			line.gsub!(MUL_REPLACE_LEFT, "/*")
			line.gsub!(MUL_REPLACE_RIGHT, "*/")
			line.gsub!(SIG_REPLACE, "//")
# =end

			result<<line<<"\n" if line.length > 0
			lines += 1 if line.lstrip.length > 0

		end

	end
end
# p result
File::open(ARGV[1], "w+") do |file|
	# p ARGV[1]
	file.puts(result)
end

puts "There are #{lines} in the program"

