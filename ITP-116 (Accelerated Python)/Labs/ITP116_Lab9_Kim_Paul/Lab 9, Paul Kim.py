# Paul Kim
# ITP 116, 10:00-10:50 AM
# Lab 9 - Football Game Program that gives experience with object-orientated programming,

from FootballGame import FootballGame
from FootballTeam import FootballTeam


def getTeamName(homeOrAway):
    teamname = input("What is the name of the " + homeOrAway + " team? ")
    return teamname


def getCity(homeOrAway):
    city = input("What is the name of the city for the " + homeOrAway + " team? ")
    return city


def getPoints(team):
    print("1. No points\n2. Field Goal\n3. Touchdown")
    teamStatus = input("What did " + team.name + " do? ")
    while teamStatus != "1" and teamStatus != "2" and teamStatus != "3":
        print("Please enter 1, 2, or 3.")
        teamStatus = input("What did " + team.name + " do? ")
    if teamStatus == "2":
        team.scoreFieldGoal()
    elif teamStatus == "3":
        team.scoreTouchdown()
    print()


def playGame(footballGame):
    quarter = 1
    while quarter <= 4:
        print("\nQuarter " + str(quarter))
        getPoints(footballGame.homeTeam)
        getPoints(footballGame.visitingTeam)
        print(footballGame)
        quarter += 1
    print()
    footballGame.printWinner()


def main():
    city = getCity("home")
    name = getTeamName("home")
    homeTeam = FootballTeam(city, name)
    city = getCity("away")
    name = getTeamName("away")
    awayTeam = FootballTeam(city, name)
    game = FootballGame(homeTeam, awayTeam)
    playGame(game)


main()