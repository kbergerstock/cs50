# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


class Team:
    def __init__(self, team=None, rating=0):
        self.set(team, rating)
        self.count = 0

    def set(self, team, rating):
        self.team = team
        self.rating = rating

    def rating(self):
        return self.rating

    def team(self):
        return self.team

    def won(self):
        self.count += 1

    def count(self):
        return self.count


def add(teams, data):
    for Line in data:
        if ',' in Line:
            w = Line.split(',')
            v = w[1].rstrip()
            if v.isnumeric():
                t = Team(w[0], int(v))
                teams.append(t)


def main(fname):
    # Ensure correct usage
    if fname == None:
        sys.exit("Usage: python tournament.py FILENAME")

    try:
        teams = []
        # TODO: Read teams into memory from file
        fp = open(fname, 'rt')
        data = fp.readlines()
        fp.close()
    except:
        sys.exit("Unable to open team file: " + fname)

    try:
        add(teams, data)
    except:
        sys.exit('error in processing file data')

    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts
    for i in range(N):
        simulate_tournament(teams)
    # Print each team's chances of winning, according to simulation
    for team in sorted(teams, key=lambda Team: Team.count, reverse=True):
        print(f"{team.team}: {team.count * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1.rating
    rating2 = team2.rating
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams, winners):
    """Simulate a round. Return a list of winning teams."""
    w = []
    # Simulate games for all pairs of teams
    for i in range(0, len(winners), 2):
        if simulate_game(teams[winners[i]], teams[winners[i + 1]]):
            w.append(winners[i])
        else:
            w.append(winners[i + 1])

    return w


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO

    winners = range(0, len(teams))
    while(len(winners) > 1):
        winners = simulate_round(teams, winners)

    if(len(winners) == 1):
        teams[winners[0]].won()


if __name__ == "__main__":
    main(sys.argv[1])