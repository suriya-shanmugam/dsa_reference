command = "start"

match command:
    case "start" | "run":
        print("Starting...")
    case "stop":
        print("Stopping...")
    case _:
        print("Unknown command")