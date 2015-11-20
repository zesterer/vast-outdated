import random as r

class Language:
	def __init__(self):
		self.c_chance = []
		self.v_chance = []
		self.end_chance = []
	
	def generate(self):
		for i in range(0, 25):
			if r.randint(0, 2) == 1:
				self.c_chance.append(0)
			else:
				self.c_chance.append(r.randint(0, r.randint(6, 10)))
		for i in range(0, 9):
			if r.randint(0, 3) == 1:
				self.v_chance.append(0)
			else:
				self.v_chance.append(r.randint(0, r.randint(6, 10)))
		for i in range(0, 9):
			if r.randint(0, 3) == 1:
				self.end_chance.append(0)
			else:
				self.end_chance.append(r.randint(0, r.randint(6, 10)))

def generateName(lang = None):
	
	if lang != None:
		c_chance = lang.c_chance
		v_chance = lang.v_chance
		end_chance = lang.end_chance
	
	length = r.randint(r.randint(3, 4), r.randint(4, 7))
	name = " "
	c =            "b c d dr f g h j k uk l m n p qu r s sh st t tr th v w y z".split(" ")
	if lang == None:
		c_chance = [4,1,4, 3,2,3,5,1,5, 2,5,7,6,4, 3,6,8, 9, 6,8, 3, 5,1,7,5,2]
	v =            "a ar e i ir o u oo ie ur".split(" ")
	if lang == None:
		v_chance = [8, 3,5,7, 2,6,5, 1, 0, 1]
	end =            "n m p d k a x lt lf".split(" ")
	if lang == None:
		end_chance = [1,1,1,1,1,1,0, 0, 1]
	
	if r.randint(0, 4) == -1:
		name += chooseFrom(v, v_chance, name[-1])[0]
	
	while len(name) < length:
		name += chooseFrom(c, c_chance, name[-1])
		name += chooseFrom(v, v_chance, name[-1])
	
	if r.randint(0, 4) != 0:
		name += chooseFrom(end, end_chance, name[-1])
	
	return name[1:]

def chooseFrom(values, chances, last = ""):
	total = sum(chances)
	rand = r.randint(0, total)
	for i in range(0, len(values)):
		rand -= chances[i % len(chances)]
		if rand <= 0 and values[i][0] != last:
			return values[i]
	return values[0]

if __name__ == "__main__":
	
	for lang in range(0, 10):
	
		test = Language()
		test.generate()
		
		print("\nA few sample words from the " + generateName(test) + " language...\n")
		
		for i in range(0, 10):
			l = ""
			while len(l) < 20:
				l += generateName(test) + ", "
			print(l)
	
	print("\nAnd now a few sample words from the STANDARD language...\n")
	
	for i in range(0, 10):
		l = ""
		while len(l) < 20:
			l += generateName() + ", "
		print(l)
