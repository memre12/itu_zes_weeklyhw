import random
class Person:
    def __init__(self, name=None, surname=None):
        self.__name = name
        self.__surname = surname

    def get_name(self):
        return self.__name


    def get_surname(self):
        return self.__surname

    def full_name(self):
        return f"{self.__name} {self.__surname}"
class Passenger(Person):
    def __init__(self, name=None, surname=None, cash=0, has_ticket=False):
        super().__init__(name, surname)
        if cash < 0:
            cash = 0
            print("Passenger cash can't be negative. It is set to 0.")
        self.__cash = cash
        self.__has_ticket = has_ticket
    def buy_ticket(self, ticket_price):
        if self.__cash >= ticket_price:
            self.__has_ticket = True
            self.__cash -= ticket_price
            print("Ticket purchased successfully!")
            return True
        else:
            print("Not enough cash to buy a ticket.")
            return False

    def get_cash(self):
        return self.__cash
    def has_ticket(self):
        return self.__has_ticket
class Astronaut(Person):
    def __init__(self,name=0,surname=0, num_missions=0):
        super().__init__(name, surname)
        self.__num_missions = num_missions

    def complete_mission(self):
        self.__num_missions += 1

    def get_num_missions(self):
        return self.__num_missions
class Mission:
    numMissions = 0

    def __init__(self, name="AA-00", missionNumber=0 ,cost=0, faultProbability=0, completed=False):
        if not name or not self.validate_mission_name(name):
            print("Invalid mission name format. Setting default name 'AA-00'.")
            name = "AA-00"

        self.__name = name
        if missionNumber==0:
            missionNumber += 1
            self.__missionNumber = Mission.numMissions
        else:
            self.__missionNumber = missionNumber


        self.__cost = cost
        self.__faultProbability = max(0, min(faultProbability, 100))
        self.__completed = completed
        self.__passengers = []
        self.__crew = []

    @staticmethod
    def validate_mission_name(name):
        return len(name) == 5 and name[0].isalpha() and name[1].isalpha() and name[2] == '-' and name[3].isdigit() and name[4].isdigit()

    def add_space_ship_staff(self, person):
        if isinstance(person, Passenger) and not person.has_ticket():
            print("Passenger does not have a ticket. Cannot add to crew.")
            return
        elif isinstance(person, Passenger):
            self.__passengers.append(person)
        elif isinstance(person, Astronaut):
            self.__crew.append(person)

    def execute_mission(self):
        result = random.randint(0, 100)
        if result > self.__faultProbability:
            print(f"Mission {self.__name} was successful.")
            self.complete_mission()
            for astronaut in self.__crew:
                astronaut.complete_mission()
                print(f"{astronaut.full_name()} has completed {astronaut.get_num_missions()} missions.")
            self.__completed = True
        else:
            print(f"Mission {self.__name} failed.")
            self.__completed = False
        return self.__completed

    def calculate_profit(self, ticket_price):
        profit = 0
        if self.__completed:
            profit = ticket_price * len(self.__passengers)
        profit -= self.__cost
        return profit

    def get_name(self):
        return self.__name

    def get_mission_number(self):
        return self.__missionNumber

    def is_completed(self):
        return self.__completed

    def complete_mission(self):
        self.__completed = True
class Agency:
    def __init__(self, name="NASA", cash=25000, ticket_price=1200):
        self.__name = name
        self.__cash = cash
        self.__ticket_price = ticket_price
        self.__completed_missions = []
        self.__next_missions = []

    def add_mission(self, mission):
        self.__next_missions.append(mission)

    def execute_next_mission(self):
        if not self.__next_missions:
            print(f"No missions available to execute for {self.__name}.")
            return

        mission = self.__next_missions.pop(0)
        success = mission.execute_mission()

        if success:
            self.__completed_missions.append(mission)
            mission_profit = mission.calculate_profit(self.__ticket_price)
            self.__cash += mission_profit
        else:
            self.__next_missions.append(mission)
            mission_profit = mission.calculate_profit(self.__ticket_price)
            self.__cash += mission_profit

    def agency_info(self):
        print(f"Agency Name: {self.__name}")
        print(f"Current Cash: ${self.__cash}")
        print(f"Ticket Price: ${self.__ticket_price}")
        print("Next Missions:")
        for mission in self.__next_missions:
            print(f"- Mission {mission.get_mission_number()}: {mission.get_name()} (Cost: ${mission._Mission__cost})")
        print("Completed Missions:")
        for mission in self.__completed_missions:
            print(f"- Mission {mission.get_mission_number()}: {mission.get_name()} (Cost: ${mission._Mission__cost})")
