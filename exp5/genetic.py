import random

# Function to calculate fitness of a solution
def calculate_fitness(board):
    clashes = 0
    n = len(board)

    for i in range(n):
        for j in range(i + 1, n):
            if board[i] == board[j] or abs(i - j) == abs(board[i] - board[j]):
                clashes += 1

    return clashes

# Function to perform crossover
def crossover(parent1, parent2):
    n = len(parent1)
    crossover_point = random.randint(0, n - 1)
    child = parent1[:crossover_point] + parent2[crossover_point:]
    return child

# Function to perform mutation
def mutate(individual):
    mutation_point = random.randint(0, len(individual) - 1)
    new_value = random.randint(0, len(individual) - 1)
    individual[mutation_point] = new_value

if __name__ == "__main__":
    n = 8  # Number of queens
    population_size = 10
    max_generations = 1000
    population = [[random.randint(0, n - 1) for _ in range(n)] for _ in range(population_size)]

    generation = 0
    while generation < max_generations:
        # Fitness Calculation
        fitness = [calculate_fitness(individual) for individual in population]

        # Selection
        new_population = []
        for _ in range(population_size):
            parent1 = random.choice(population)
            parent2 = random.choice(population)
            if fitness[population.index(parent1)] < fitness[population.index(parent2)]:
                new_population.append(parent1)
            else:
                new_population.append(parent2)

        # Crossover
        for i in range(0, population_size, 2):
            parent1 = new_population[i]
            parent2 = new_population[i + 1]
            child1 = crossover(parent1, parent2)
            child2 = crossover(parent2, parent1)
            new_population.extend([child1, child2])

        # Mutation
        for individual in new_population:
            if random.random() < 0.1:
                mutate(individual)

        population = new_population
        generation += 1

    # Output best solution
    best_fitness = float('inf')
    best_solution = []
    for individual in population:
        current_fitness = calculate_fitness(individual)
        if current_fitness < best_fitness:
            best_fitness = current_fitness
            best_solution = individual

    print("Best solution:", best_solution)

    # Print chessboard with queens
    print("\nChessboard with Queens:")
    for row in range(n):
        line = ""
        for col in range(n):
            if col == best_solution[row]:
                line += "Q "
            else:
                line += "- "
        print(line)
