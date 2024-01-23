# Space Agency Simulation
* I've completed the assignment and created a fictional space agency simulation. The space agency conducts various space missions, covering their operational costs through ticket sales. However, there's a probability of failure during the launch of each mission. These failures result in mission rescheduling without fatal consequences, but the agency still has to pay the operational costs.
## Person Class
* **Private Attributes:** name and surname.
### Methods

* **_ _init_ _(self, name=None, surname=None):** Constructor to initialize the person with optional attributes.
* **get_name(self):** Returns the person's name.
* **get_surname(self):** Returns the person's surname.
* **full_name(self):** Returns the full name of the person.
## Passenger Class (Subclass of Person
* Additional Private Attributes: cash and has_ticket.
### Methods
* **_ _init_ _(self, name=None, surname=None, cash=0, has_ticket=False):** Constructor to initialize the passenger with optional attributes.
* **buy_ticket(self, ticket_price):** Buys a ticket if the passenger has enough cash.
* **get_cash(self):** Returns the passenger's cash.
* **has_ticket(self):** Returns whether the passenger has a ticket.
## Astronaut Class (Subclass of Person)
* **Additional Private Attributes:** num_missions.
### Methods
* _ _init_ _(self, name=None, surname=None, num_missions=0): Constructor to initialize the astronaut with optional attributes.
* **complete_mission(self):** Increments the num_missions attribute.
* **get_num_missions(self):** Returns the number of missions completed by the astronaut.
## Mission Class
* **Private Attributes:** name, missionNumber, cost, faultProbability, completed, passengers, crew.
* **Static Variable:** numMissions.
### Methods
* **_ _init_ _(self, name="AA-00", missionNumber=0, cost=0, faultProbability=0, completed=False):** Constructor to initialize the mission with optional attributes.
* **add_space_ship_staff(self, person):** Adds Passenger or Astronaut to the mission crew or passenger list.
* **execute_mission(self):** Executes the mission, determining success based on a random number generator.
* **calculate_profit(self, ticket_price):** Calculates the net profit of the mission.
* **get_name(self):** Returns the mission name.
* **get_mission_number(self):** Returns the mission number.
* **is_completed(self):** Returns whether the mission is completed.
## Agency Class
* **Private Attributes:** name, cash, ticket_price, completed_missions, next_missions.
### Methods
* **_ _init_ _(self, name="NASA", cash=25000, ticket_price=1200):** Constructor to initialize the agency with optional attributes.
* **add_mission(self, mission):** Adds a mission to the agency's next_missions list.
* **execute_next_mission(self):** Executes the next mission, updating cash and mission lists accordingly.
* **agency_info(self):** Prints information about the agency, including name, cash, ticket price, and details of next and completed missions
