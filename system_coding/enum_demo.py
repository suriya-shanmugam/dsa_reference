from enum import Enum

class Status(Enum):
    INPROGRESS = "inprogress"
    COMPLETED = "completed"

status = Status.COMPLETED

if (status == Status.COMPLETED):
    print("Done")


class Point(Enum) :
    North = (0, 1)

    def move(self, x, y):
        dx, dy = self.value
        print(x + dx, y + dy)

Point.North.move(2,3)

