#!/usr/bin/ruby -w
# coding=utf-8

# usage
# ruby -w find-patterns.rb pattern file/directory t/f repalce_str
# pattern can be regular expressions
# file/directory can be directory
# t/f means 
# 	true, to replace and have to supply replace str.
#	false, do not replace, do not have to supply replace str
# replace_str, a string to replace pattern

# This script is used to find specified patterns in file
# or files. You can search or search & replace a pattern.
# When dealing with multiple files, put them in a single
# directory or you may have to provide each specified
# location.

# @author: chunyang wen
# @email: chunyang.wen@gmail.com

# @TODO: cmd line options


$file_name = Hash.new

pattern = ARGV[0]
directory = ARGV[1] # will be tested whether is a file
will_replace = false
replace_str = nil
will_replace = ARGV[2].downcase == 't' if ARGV.length > 2
replace_str = ARGV[3] if will_replace && ARGV.length > 3 # when replaced

def search_in_file(pattern, file_name, replace_str)
	$file_name[file_name] = Hash.new()
	result = replace_str.nil?? nil:[]
	File::open(file_name,"r") do |f|
		puts "start to find and/or replace?"
		loop do
			begin
				line = f.readline
				puts line
			rescue
				break
			else
				if !line.index(pattern).nil?
					# $file_name[file_name][f.lineno] = 0 if !line.index(pattern).nil?
					sub_num = 0
					while !(line.index(pattern).nil?) && !replace_str.nil?
						line.sub!(pattern,replace_str)
						sub_num += 1
					end

					$file_name[file_name][f.lineno] = sub_num
				end
				
				result<<line if !result.nil?
			end
		end
	end	
	
	if !result.nil?
		puts "storing files"
		File.open(file_name,"w+") {|f|
			f.puts(result)
		}
	end
end

def search_in_dir(pattern, dir_name, replace_str)
	
	Dir.foreach(dir_name) {|entry|
		if !File.directory?(entry)
			file_loc = dir_name+File::SEPARATOR+entry
			search_in_file(pattern, file_loc , replace_str)
		end
	}
end

def search(pattern, directory, will_replace, replace_str)

	replace_str = nil if !will_replace
	if File.directory?(directory) then
		puts "searching directory"
		search_in_dir(pattern, directory, replace_str)
	else
		puts "searching in file"
		search_in_file(pattern,directory, replace_str)
	end
end

puts pattern
puts directory
puts will_replace
puts replace_str

if will_replace and replace_str.nil?
	puts "please provide repalce str"
	raise "NOT ENOUGH ARGS"
end

search(pattern, directory, will_replace, replace_str)

# output findings
$file_name.each {|file_name,lines|
	if  $file_name[file_name].empty?
		puts "#{file_name} does not contain #{pattern}"
	else 
		puts "#{file_name} in lines: "
		$file_name[file_name].each { |lineno, subs|
			print lineno.to_s+"," 
			if will_replace then
				puts "#{subs} #{pattern} being replaced."
			end
		}
		puts
	end
}
