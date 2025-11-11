from collections import defaultdict

class PubSub :
	def __init__(self):
		self.messages = []
		self.users = {}
		self.users_by_choice = defaultdict(list)
	
	def add_user(self, user_id, choices, min_weight):
		self.users[user_id] = (choices, min_weight)
		for choice in choices :
			self.users_by_choice[choice].append(user_id)
	
	def add_news(self, news_id, category, time, min_weight):
		self.messages.append((news_id, category, time, min_weight))

	def compute_broadcast(self, timestamp):
		self.messages.sort(key=lambda x : x[2])
		filtered_messages = [x for x in self.messages if x[2] >= timestamp]
		print("Filtered messages are : ")
		print(filtered_messages)
		
		print("Users and Preferences: ")
		print(self.users)
		
		print("User id indexed by choice :")
		print(self.users_by_choice)
		
		res = defaultdict(set)
		for msg in filtered_messages :
			for c in msg[1] :
				for user_id in self.users_by_choice[c] :
					if msg[3] > self.users[user_id][1] :
						res[msg[0]].add(user_id)
		print(res)

def main() :
	ps = PubSub()
	ps.add_user(1, [1,2], 10)
	ps.add_user(2,[3],10)
	ps.add_user(3,[1],10)
	
	ps.add_news(1, [1,2], 500, 20)
	ps.add_news(2, [1,2], 200, 20)
	#ps.add_news(3, [3], 300, 5)
	ps.add_news(3, [3], 300, 50)

	ps.compute_broadcast(250)
	

if __name__ == "__main__" :
	main()
		
