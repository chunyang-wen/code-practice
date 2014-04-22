#!/usr/bin/ruby -w
# coding=utf-8

# usage
# in irb, include(Path_of_file+File::SEPATATOR+"sim-linux-shell.rb")

# This ruby scipt is to simulate linux shell commands in irb environment.
# When we are in irb, we cannot access shell commands. So this file provides
# the basic support.

# Current support:
# ls
# rename
# rm
# mv
# cp

# @author: chunyang wen
# @email: chunyang.wen@gmail.com

# @TODO: Add options command
# @history:

# in case for name pollution, wrapped all them methods in
# module Wen.
module Wen

	# ls
	def self.ls(*args)
		if args.empty?
			args<<"."
		end
		p args
		args.each {|arg|

			p arg
			puts "---------#{arg}---------------" if args.length>1
			# puts arg
			if  !File.exists?(arg) then
				puts "#{arg} does not exists."
			elsif !File.directory?(arg) then
				# Not a directory
				puts self.ls_assist(arg)
			else
				# to expand path as dir_string
				dir = arg
				Dir.foreach(arg) { |entry|

					# to be consistent, do not expand . or ..
					if entry == "." or entry == ".."
						puts self.ls_assist(entry)
						next
					end

					entry1 = File.expand_path(entry,dir)
					# p entry1
					puts self.ls_assist(entry1) 

				}
			end
		}
	end


	private
	def self.ls_assist(entry)
		is_dir = File.directory?(entry) ? "d":"-"
		r_able = File.readable?(entry) ? "r":"-"
		w_able = File.writable?(entry) ? "w":"-"
		e_able = File.executable?(entry) ? "x":"-"
		a_time = File.atime(entry).to_s
		a_time = a_time.slice!(0,a_time.length-5)
		each_list = is_dir+" "+r_able+w_able+e_able+" "+a_time + \
			File.basename(entry)
	end

end

