legend = ['A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S']
for i in range(19):
	a = ''
	for j in range(19):
		a = a + "'{}{}',".format(legend[i],legend[j])
	print(a)
