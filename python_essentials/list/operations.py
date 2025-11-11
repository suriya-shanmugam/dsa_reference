# common query

sections = ["Summary","Education","Experience","Projects","skills"]
print("Length of sections_list",len(sections))

# Linear operations
print("Is skills in sections ?", "skills" in sections)

b_vec = [1,0,1,0,1,1,0,1]
print("Number of 1s", b_vec.count(1))

print("First index of 0 is ", b_vec.index(0)) # Find is only for strings

numbers = [5,2,-1,90]
print(f"""
min is {min(numbers)}
max is {max(numbers)}
sum is {sum(numbers)}
""")

# Shallow copy - creates new object but reference the same object by origin - if ***mutable**** - new object changes reference of original object

class date:
	def __init__(self,d,m,y):
		self.d = d
		self.m = m
		self.y = y
	def __str__(self):
		return f"{self.d}/{self.m}/{self.y}"

name = ["suriya", "shanmugam"]
dob = date(4,9,1996)
details = [name,dob]
print("Before modifying shallow copy ", details[1])

clone = list(details)
clone[1].d = 10
print("After modifying shallow copy ", details[1])

# slicing and list() - creates shallow copies

numbers = [1,2,3,4]
copy = list(numbers) # or copy = numbers[0:len(numbers)] 
print(copy)
