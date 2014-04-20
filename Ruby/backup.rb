#!usr/bin/ruby -w
# coding=utf-8

# Usage
# ruby -w backup.rb source destination

# The script is used to backup files or directory

# @author chunyang wen
# @email chunyang.wen@gmail.com

# @TODO Add permission detect before read and write
# @TODO Add options for this file

# @0.1 2014-04-19 first version

if ARGV.length < 2
	raise "Not enough arguments", caller
end

from = ARGV[0] # file or directory to backup
to = ARGV[1] # backup place
is_override = false




# backup files
def backup_file(source, destination, is_over)

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

def back_up(source, destination, is_over)
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


# p from
# p to
p is_override
p "Backup files from \{ #{from}\} to \{#{to}\}"
print "Overriding when file exsits?(y/n): "
msg = $stdin.gets.chomp!.downcase
if msg == 'y'
	is_override = true
else
	is_override = false
end

# p msg
if !File.directory?(to) then
	p "#{to} is not a directory or not not exist, try to create."
	Dir.mkdir(to)
end

if $? then
	p "Can not create directory"
	raise "Can not make the #{to} directory"
end

begin
	back_up(from, to, is_override)
rescue Exception => e
	puts e.message
end

