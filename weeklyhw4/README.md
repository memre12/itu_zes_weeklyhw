
# Restaurant Bot

## Class Relations Explanation:
### 1. Inheritance:
* Base Class: MenuItem Pure virtual functions for getting and setting attributes (name, price, taste balance). Derived classes (e.g., Starter, Salad, MainCourse, Drink, Appetizer, Dessert) inherit from MenuItem. Each derived class overrides virtual functions and introduces additional attributes and functionality specific to its type.
### 2. Association:
* User Class Associated with Menu Class: User class contains a Menu object as an attribute. The User and Menu classes are associated, but not tightly coupled, as a User can exist independently of a Menu.
### 3. Composition:
* Menu Class Composed of MenuItem Objects: Menu class contains a vector of MenuItem pointers. This represents a composition relationship, as a Menu "owns" the MenuItem objects. When a Menu is destroyed, the associated MenuItem objects are also cleaned up.
### 4. Aggregation:
* Menu Class Aggregating Overall Taste Balance and Total Cost: Menu class aggregates attributes for overall taste balance and total cost. This represents an aggregation relationship, as these attributes can exist independently of the Menu. They are part of the Menu, but they can also be considered standalone.
## Concepts of Relationships in OOP:
### Inheritance:
* Definition: A mechanism in OOP that allows a new class (derived or child class) to inherit attributes and behaviors from an existing class (base or parent class).
* Application: Used in this project to create a hierarchy of food types (Starter, Salad, etc.) that inherit common properties and behaviors from the MenuItem base class.
### Association:
* Definition: A relationship where two or more classes are connected, but they may exist independently of each other.
* Application: The User class is associated with the Menu class, indicating that a user can have a menu, but the user and menu are separate entities.
### Composition:
* Definition: A relationship where a class (whole) contains another class (part), and the part cannot exist independently of the whole.
* Application: The Menu class composes a collection of MenuItem objects, indicating that the menu owns and manages the menu items.
### Aggregation:
* Definition: A special case of association where one class contains another class, but the contained class can exist independently of the container class.
* Application: The Menu class aggregates attributes like overall taste balance and total cost, indicating that these attributes can exist independently but are part of the menu.

## JSON file application:
In the provided code snippet, I have utilized the RapidJSON library to work with a JSON file named "menu.json." I included the relevant headers from the RapidJSON library to provide JSON parsing and generation. 

These headers enable the usage of RapidJSON's functionalities for handling JSON data. Specifically, 'document.h' is used for parsing JSON documents, 'writer.h' for generating JSON data, and 'stringbuffer.h' for managing string buffers.


## Taste Balance Functionality
* Users have the option to create a random menu or specify a taste balance for their menu. When creating a random menu, the bot randomly selects items from each food category.
* If the user provides a taste balance, the bot intelligently suggests food items that fit the given taste values for sweetness, saltiness, sourness, bitterness, and umami. It aims to create a menu that aligns with the user's taste preferences.

