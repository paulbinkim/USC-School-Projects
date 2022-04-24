# ITP 116 Lab 9
# Football Game class

class FootballGame:
    # team1 and team2 are FootballTeam objects
    def __init__(self, team1, team2):
        self.homeTeam = team1
        self.visitingTeam = team2

    def printWinner(self):
        if self.homeTeam.score > self.visitingTeam.score:
            print(self.homeTeam.name + " beat " + self.visitingTeam.name)
        elif self.homeTeam.score < self.visitingTeam.score:
            print(self.visitingTeam.name + " beat " + self.homeTeam.name)
        else:
            print("It's a tie!")

    def __str__(self):
        message = "SCORE\n-----\n"
        message += str(self.homeTeam) + "\n" + str(self.visitingTeam)
        return message
