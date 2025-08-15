#dictionary basics

details = {"name":"suriya", "clg":"sjsu"}
#details = dict([("name","suriya"),("clg","sjsu")])
#details = dict(name="suriya",clg="sjsu")

details["location"] = "san jose"

print(details)

print(details.get("name"))
print(details.get("first_name", "NAN"))
print(details.pop("middle_name",None))

value = details.pop("location")
print(f"popped location : {value}")

print(details)

key,value = details.popitem()
print(f"key is {key} and value is {value}")

print(details)

for k,v in details.items():
	print(k,"  ",v)

# working with snapshots if wants to manipulate original
for k,v in list(details.items()):
	if len(v) >= 3:
		details.pop("name") 

print(details)

d = {12:"mit",1:"sjsu",3:"berkeley"}
print(d)

# sort without changing original
# print(sorted(d)) # sorted returns key in sorted order
for k in sorted(d, reverse=True):
	print (k,"   ",d[k])

# sort by values
for k,v in sorted(d.items(), key=lambda kv : kv[1]):
	print(k,"   ",v)
