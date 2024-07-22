# Hammurabi: The Land Management Game

## Game Overview

You are Hammurabi, the city's mighty ruler. Your role is to manage land and resources for the city of Sumeria over a five-year term. Your objective is to ensure the city does not starve and manages its resources effectively. The game is played over 5 turns, with each turn representing one year.

### Game Mechanics

1. **Land Management**: Each year, you decide how many acres of land to buy or sell. Land prices vary randomly between 15 and 25 units of grain per acre.
2. **Grain Management**: Decide how many units of grain to feed your population. Each person needs 20 units of grain to survive. Grain is used to feed the population and to plant crops.
3. **Planting Crops**: You can plant crops on your land. The amount of land you plant crops on cannot exceed the amount of land you own. You cannot plant more acres than you have grain for.
4. **Population**: Each year, between 0 and 10 new people may come to the city. If you do not feed the population adequately, people will starve.
5. **Rat Infestation**: Each year, there is a 20% chance of a rat infestation. Rats can eat up to 10% of your stored grain.
6. **Yearly Report**: At the end of each year, you will receive a report on the following:
   - Number of people who starved
   - Number of new people who came to the city
   - Grain stocks
   - Acres of land owned
   - Land price

### Rules and Constraints

- You cannot buy more land than you have grain to support.
- You cannot sell more land than you own.
- You cannot feed more people than you have grain for.
- You cannot plant more acres than you have grain for.

### End of Game

At the end of the 5-year term, if you have over 100 people and over 1000 acres, you win and a congratulatory message will be displayed. Otherwise, a loss message will be shown.

### Example of a Yearly Report

**Year 1 Report:**
- People starved: 0
- People came to the city: 0
- Grain stocks: 2800 units
- Acres of land owned: 1000
- Land price: 22 units per acre
- Rats ate: 0 units of grain

**Year 2 Report:**
- People starved: 0
- People came to the city: 0
- Grain stocks: 1700 units
- Acres of land owned: 900
- Land price: 16 units per acre
- Rats ate: 0 units of grain

**Year 3 Report:**
- People starved: 10
- People came to the city: 9
- Grain stocks: 1300 units
- Acres of land owned: 800
- Land price: 24 units per acre
- Rats ate: 300 units of grain

**End of Game Report:**
- Population: 105
- Acres of land: 1100
- Grain stocks: 500 units
- Result: GAME OVER. You did not achieve the target.

### Non-Functional Requirements

- Implement a layered architecture solution.
- The program must handle all inputs gracefully and not crash.
- Ensure the game has working functionalities for managing land, grain, and population.
- Comprehensive testing is required to ensure reliability and accuracy.

---

Good luck, Hammurabi! Manage your resources wisely and ensure the prosperity of your city.
