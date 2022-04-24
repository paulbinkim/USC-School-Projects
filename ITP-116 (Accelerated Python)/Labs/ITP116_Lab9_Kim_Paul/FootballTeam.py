# ITP 116 Lab 9
# Football Team class

class FootballTeam:
    def __init__(self, city, name):
        self.city = city
        self.name = name
        self.score = 0

    def scoreFieldGoal(self):
        self.addToScore(3)

    def scoreTouchdown(self):
        self.addToScore(7)

    def addToScore(self, amount):
        if amount >= 0:
            self.score += amount

    def __str__(self):
        message = self.city + " " + self.name + ": " + str(self.score)
        return message