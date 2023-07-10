import numpy as np
from icecream import ic

arr = lambda lista: np.array(lista)

dimension = arr([90, 90])
velocity = arr([0, 0])
acceleration = arr([0.01, 0])
position = arr([50, 30])
ship_position = arr([600, 900])

direction = ship_position - position
direction_normalized = direction / np.linalg.norm(direction)
norma_acceleration = np.linalg.norm(acceleration)
norma_velocity = np.linalg.norm(velocity)
direction_scaled = norma_acceleration * direction_normalized

new_velocity = direction_normalized*norma_velocity

ic(direction)
ic(direction_normalized)
ic(norma_acceleration)
ic(norma_velocity)
ic(direction_scaled)

ic(new_velocity)


