# creation
l = []
l = [0] * 10
print(l)

l = list(range(5)) # sequence of number using range [range returns iterable range object[immutable]]
		   # range(end) [exclusive]
                   # range(start,end,step)
                   # range(start,end)
print(l)

s = "suriya"
l = list(s) # any iterable 
print(l)

# Access/ Update
skills = ["java", "python", "c", "typescript", "javascript"]
print(skills[0])

skills[2] = "c++"
print(skills)

print(skills[0:2])


# Adding & removing
skills.append("cmake")
print(skills)

new_skills = ["flask", "Django", "sql"]
skills.extend(new_skills) # or skills += new_skills 
print(skills)

skills.insert(1,"spring_boot") #insert(idx,value)
print(skills)

skills.pop()  #remove and return last
print(skills)

skills.pop(4) # by index
print(skills)

skills.remove("javascript") #Remove first matching value
print(skills)
