#!/usr/bin/ruby -w
# coding=utf-8

# usage
# in irb, include(Path_of_file+File::SEPATATOR+"sim-linux-shell.rb")
# As ruby 1.9 DO NOT support multi-parameters with space between 
# parameters and function name, there should be double quotes to wrap
# paramters and a comma between paramters.

# This ruby scipt is to simulate linux shell commands in irb environment.
# When we are in irb, we cannot access shell commands. So this file provides
# the basic support.

# Current support:
# ls
# rename
# rm
# mv
# cp
# mkdir
# rmdir
# pwd

# @author: chunyang wen
# @email: chunyang.wen@gmail.com

# @TODO: Add options command
# @TODO: Find a way to solve multi-paramters on one-line problem.
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

	def self.cd(entry)
		if !File.directory?(entry) then
			puts "#{entry} not a dirtory"
		else
			Dir.chdir(entry)
		end
	end

	def self.pwd
		puts Dir.pwd
	end

	def self.cp(src, des)

		# make sure to overide
		puts "Overrided when exists?(y/n)"
		input = $stdin.gets.chomp!.downcase
		if input == 'y' then
			is_override = true
		else
			is_override = false
		end
		back_up(src,des,is_override)
	end

	def self.rename(old_name, new_name)
		if File.exists?(old_name) then
			File.rename(old_name, new_name)
		else
			puts "Not a valid name"
		end
	end

	def self.mv(src, des)
		if File.directory?(src) then
			self.back_up(src,des,true)
			Dir.rmdir(src)
		else
			self.back_up(src,des,true)
			File.delete(src)
		end
	end

	def self.mkdir(dir)
		Dir.mkdir(dir)
	end

	def self.rmdir(dir)
		Dir.rmdir(dir)
	end

	def self.touch(filename, pes="w+")
		File.new(filename,pes)
	end

	private
	# backup files
	def self.backup_file(source, destination, is_over)

		out_file_path = destination + File::SEPARATOR + File.basename(source)

		if File.exist?(out_file_path) && !is_over
			raise "File #{File.basename(out_file_path)} alread exists", caller
		end
		p out_file_path

		begin
			out_file = File.new(out_file_path, "w+")
		rescue
			raise "Can not create file" + File.basename(source),caller
		end
		open(source) { |f|
			p "copying"
			while record = f.read(256)
				out_file.write(record)
			end
		}
	end

	def self.back_up(source, destination, is_over)
		if File.directory?(source) then
			# back up directory
			destination = destination + File::SEPARATOR + File.basename(source)
			p "Creating DIR: " + destination

			if !Dir.exist?(destination) then
				# directory does not exist
				Dir.mkdir(destination)
			end
			Dir.foreach(source) {|entry|
				if entry != "." &&  entry != ".." then
					p "DIR NAME: " + File.dirname(entry)
					p "BASE NAME: " + File.basename(entry)
					basename = File.basename(entry)
					back_up(source+File::SEPARATOR+entry,destination, is_over)
				end
			}
		else
			# back up files
			backup_file(source, destination, is_over)
		end
	end

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

