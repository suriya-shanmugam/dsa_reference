from collections import defaultdict

# grouping
source = [("suriya", "MSSE"),("tharun", "MSME"),("Jesu","MSSE"),("Subash", "MSSE"),("Deepak", "MSCS")]
groups = defaultdict(list)

for name, dept in source :
	groups[dept].append(name)

print(groups)

# counter 

letters = "aaaaaadflasadjflksdjnbvkasudbajbvhajhsbdv"

counts_by_letter = defaultdict(int)

for letter in letters :
	counts_by_letter[letter] += 1

print(dict(counts_by_letter))

