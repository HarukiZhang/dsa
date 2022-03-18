def c_or_a():
    print('Please enter c to confirm, a to abandan.')
    while True:
        dec = input('Please enter c to confirm, a to abandan')
        if dec == 'c':
            return False
        elif dec == 'a':
            return True
        else:
            print('Unrecognized input, please enter again.')

def read_scale(f):
	'''
	Attention: The line breaks of file should be '\n'

	Usage: read a plain text file of paper records and return the scale of its indices for reading contents

	: param f: the fileIO of the record file

	Suggestion: when TY is not equal to ER: check for record file to complete the 'TY -> ER' frame
	'''
	f.seek(0)
	# count the frequency
	dct = {}
	for item in f.readlines():
		if not item == '\n': # it is possible a file do not contain any blank row
			dct[item[:2]] = dct.get(item[:2], 0) + 1
		else:
			dct['NullStr'] = dct.get('NullStr', 0) + 1
	# check for the equality of each indices charactors
	print(f"Please check for equality of TY and ER, and check other index's frequency:")
	for key in dct:
		print(f'{key} : {dct[key]}')
	if c_or_a():
		return
	return tuple(dct.keys())

def start_reading(f, scale):
	'''
	it must be ensured that each record in file(f) starts with 'TY' and ends with 'ER', not of each can be missing;

	debug log:
		'count-not-equl' problem: check for the equality of two indices (TY & ER) in read_scale()
	'''
	f.seek(0)
	dct = {}
	count = 0
	for line in f:
		if line[:2] == 'TY':
			imdct = {}
			imdct['TY'] = line[6:-1]
		elif line[:2] == 'ER':
			dct[count] = imdct
			count += 1
		elif line[:2] in scale:
			imdct[line[:2]] = imdct.get(line[:2],[]).append(line[6:-1])
	return dct

with open('Data\My Collection.md', 'rt', encoding='utf_8') as f:
    scale = read_scale(f)
    dct_text = start_reading(f, scale)
    f.close()