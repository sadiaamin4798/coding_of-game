import tkinter as tk
import random

# Constants
GRID_SIZE = 20
GRID_WIDTH = 20
GRID_HEIGHT = 20
SPEED = 100  # Control snake movement speed

# Initialize window
window = tk.Tk()
window.title("Snake Game")

canvas = tk.Canvas(window, width=GRID_SIZE * GRID_WIDTH, height=GRID_SIZE * GRID_HEIGHT, bg="black")
canvas.pack()

# Snake and food setup
snake = [[5, 5]]
food = [random.randint(0, GRID_WIDTH - 1), random.randint(0, GRID_HEIGHT - 1)]
direction = "Right"
game_running = True  # Track game state

def restart_game():
    """Resets the game to initial state."""
    global snake, food, direction, game_running
    snake = [[5, 5]]
    food = [random.randint(0, GRID_WIDTH - 1), random.randint(0, GRID_HEIGHT - 1)]
    direction = "Right"
    game_running = True
    canvas.delete("all")  # Clear the screen
    move()  # Restart game loop

def move():
    """Handles snake movement and collision."""
    global direction, food, game_running
    
    if not game_running:
        return  # Stop moving if game is over
    
    head = snake[0][:]
    
    # Move the snake
    if direction == "Up":
        head[1] -= 1
    elif direction == "Down":
        head[1] += 1
    elif direction == "Left":
        head[0] -= 1
    elif direction == "Right":
        head[0] += 1

    # Check collision (Game Over)
    if head in snake or head[0] < 0 or head[0] >= GRID_WIDTH or head[1] < 0 or head[1] >= GRID_HEIGHT:
        canvas.create_text(GRID_SIZE * GRID_WIDTH // 2, GRID_SIZE * GRID_HEIGHT // 2, text="Game Over - Press 'R' to Restart", fill="red", font=("Arial", 18))
        window.bind("<r>", lambda event: restart_game())  # Restart with 'R'
        game_running = False
        return

    snake.insert(0, head)

    # Check if food is eaten
    if head == food:
        food = [random.randint(0, GRID_WIDTH - 1), random.randint(0, GRID_HEIGHT - 1)]  # New food position
    else:
        snake.pop()  # Remove last tail segment

    draw()  # Redraw screen
    window.after(200, move)  # Adjust speed dynamically

def draw():
    """Draws the game elements on the canvas."""
    canvas.delete("all")  # Clear previous frame
    canvas.create_rectangle(food[0] * GRID_SIZE, food[1] * GRID_SIZE, (food[0] + 1) * GRID_SIZE, (food[1] + 1) * GRID_SIZE, fill="red")
    for segment in snake:
        canvas.create_rectangle(segment[0] * GRID_SIZE, segment[1] * GRID_SIZE, (segment[0] + 1) * GRID_SIZE, (segment[1] + 1) * GRID_SIZE, fill="green")

def change_direction(event):
    """Prevents the snake from reversing its direction."""
    global direction
    if event.keysym == "Up" and direction != "Down":
        direction = "Up"
    elif event.keysym == "Down" and direction != "Up":
        direction = "Down"
    elif event.keysym == "Left" and direction != "Right":
        direction = "Left"
    elif event.keysym == "Right" and direction != "Left":
        direction = "Right"

# Bind keys for movement and restarting
window.bind("<Key>", change_direction)

# Start the game loop
move()
window.mainloop()
