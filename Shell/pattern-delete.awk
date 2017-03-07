#!/bin/env awk
# Usage
# This file is used to delete lines before and after a matched pattern.
# It is a pity that sed only support delete lines after a match.
#  sed '/pattern/, +2d' # will delete matched line and followed two lines.
# awk's way is to maintain a window of size w. If target line is:
#   1. matched, delete the entire window
#   2. not matched, delete the head of the window.

# awk -vw=36 -vlb=num1 -vla=num2 -vp="your-pattern" -f pattern-delete.awk source > target
# w: window size
# lb: delete lines before pattern
# lb: delete lines after pattern
# p : pattern

# for example, delete watermarks from it-ebooks.info
# awk -vw=36 -vlb=32 -vla=3 -vp="\/URI (http:\/\/www.it-ebooks.info\/)" -f pattern-delete.awk  source > target

BEGIN{
	FS = "\n";
	OFS = "\t";
	window = w; #36;
	line_before = lb; #32;
	line_after = la;  #3;
	target_line = line_before;
	shift_index = 0; # when remove ++shift_index
	current_index = 0;
	pattern = p; # get from input
	skip_index = 0;
	BINMODE = 3;
}
{
	if (skip_index > 0) {
		--skip_index;
		next;
	}
	#print "Index", current_index, shift_index, target_line
	if (current_index - shift_index < target_line) {
		a[current_index] = $0;
		++current_index;
		next;
	}
	#print "Cur: ", $0, pattern, match($0, pattern)
	if (match($0, pattern) != 0) {
		# found a match
		shift_index += window;
		current_index = shift_index;
		skip_index = line_after;
		delete a;
	} else {
		print a[shift_index];
		delete a[shift_index];
		a[current_index] = $0;
		++shift_index;
		++current_index;
	}
}
END {
	# print shift_index to current_index
	while (shift_index < current_index) {
		print a[shift_index];
		++shift_index;
	}
}
